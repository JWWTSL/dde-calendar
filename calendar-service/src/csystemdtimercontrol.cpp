// SPDX-FileCopyrightText: 2022 UnionTech Software Technology Co., Ltd.
//
// SPDX-License-Identifier: LGPL-3.0-or-later

#include "csystemdtimercontrol.h"

#include <QDir>
#include <QStandardPaths>
#include <QProcess>
#include <QFile>

CSystemdTimerControl::CSystemdTimerControl(QObject *parent)
    : QObject(parent)
{
    createPath();
}

CSystemdTimerControl::~CSystemdTimerControl()
{
}

void CSystemdTimerControl::buildingConfiggure(const QVector<SystemDInfo> &infoVector)
{
    if (infoVector.size() == 0)
        return;
    QStringList fileNameList{};
    foreach (auto info, infoVector) {
        fileNameList.append(QString("calendar-remind-%1-%2").arg(info.alarmID.mid(1, 8)).arg(info.laterCount));
        createService(fileNameList.last(), info);
        createTimer(fileNameList.last(), info.triggerTimer);
    }
    startSystemdTimer(fileNameList);
}

void CSystemdTimerControl::stopSystemdTimerByJobInfos(const QVector<SystemDInfo> &infoVector)
{
    QStringList fileNameList;
    foreach (auto info, infoVector) {
        fileNameList.append(QString("calendar-remind-%1-%2").arg(info.alarmID.mid(1, 8)).arg(info.laterCount));
    }
    stopSystemdTimer(fileNameList);
}

void CSystemdTimerControl::stopSystemdTimerByJobInfo(const SystemDInfo &info)
{
    QStringList fileName;
    //停止刚刚提醒的稍后提醒，所以需要对提醒次数减一
    fileName << QString("calendar-remind-%1-%2").arg(info.alarmID).arg(info.laterCount - 1);
    stopSystemdTimer(fileName);
}

void CSystemdTimerControl::startSystemdTimer(const QStringList &timerName)
{
    QString command("systemctl --user start ");
    foreach (auto str, timerName) {
        command += QString(" %1.timer").arg(str);
    }
    execLinuxCommand(command);
}

void CSystemdTimerControl::stopSystemdTimer(const QStringList &timerName)
{
    QString command("systemctl --user stop ");
    foreach (auto str, timerName) {
        command += QString(" %1.timer").arg(str);
    }
    execLinuxCommand(command);
}

void CSystemdTimerControl::removeFile(const QStringList &fileName)
{
    foreach (auto f, fileName) {
        QFile::remove(f);
    }
}

void CSystemdTimerControl::stopAllRemindSystemdTimer()
{
    execLinuxCommand("systemctl --user stop calendar-remind-*.timer");
}

void CSystemdTimerControl::removeRemindFile()
{
    //
    QString cmd("rm ");
    cmd += m_systemdPath;
    cmd += "calendar-remind*";
    execLinuxCommand(cmd);
}

void CSystemdTimerControl::startCalendarServiceSystemdTimer()
{
    QFileInfo fileInfo(m_systemdPath + "timers.target.wants/com.dde.calendarserver.calendar.timer");
    //如果没有设置定时任务则开启定时任务
    if (!fileInfo.exists()) {
        execLinuxCommand("systemctl --user enable com.dde.calendarserver.calendar.timer");
        execLinuxCommand("systemctl --user start com.dde.calendarserver.calendar.timer");
    }
}

void CSystemdTimerControl::createPath()
{
    m_systemdPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation).append("/.config/systemd/user/");
    QDir dir;
    //如果该路径不存在，则创建该文件夹
    if (!dir.exists(m_systemdPath)) {
        dir.mkpath(m_systemdPath);
    }
}

QString CSystemdTimerControl::execLinuxCommand(const QString &command)
{
    QProcess process;
    process.start("/bin/bash", QStringList() << "-c" << command);
    process.waitForFinished();
    QString strResult = process.readAllStandardOutput();
    return strResult;
}

void CSystemdTimerControl::createService(const QString &name, const SystemDInfo &info)
{
    QString fileName;
    QString remindCMD = QString("dbus-send --session --print-reply --dest=com.deepin.dataserver.Calendar "
                                "/com/deepin/dataserver/Calendar/AccountManager "
                                "com.deepin.dataserver.Calendar.AccountManager.remindJob string:%1 string:%2")
                            .arg(info.accountID)
                            .arg(info.alarmID);
    fileName = m_systemdPath + name + ".service";
    QString content;
    content += "[Unit]\n";
    content += "Description = schedule reminder task.\n";
    content += "[Service]\n";
    content += QString("ExecStart = /bin/bash -c \"%1\"\n").arg(remindCMD);
    createFile(fileName, content);
}

void CSystemdTimerControl::createTimer(const QString &name, const QDateTime &triggerTimer)
{
    QString fileName;
    fileName = m_systemdPath + name + ".timer";
    QString content;
    content += "[Unit]\n";
    content += "Description = schedule reminder task.\n";
    content += "[Timer]\n";
    content += "AccuracySec = 1ms\n";
    content += "RandomizedDelaySec = 0\n";
    content += QString("OnCalendar = %1 \n").arg(triggerTimer.toString("yyyy-MM-dd hh:mm:ss"));
    createFile(fileName, content);
}

void CSystemdTimerControl::createFile(const QString &fileName, const QString &content)
{
    QFile file;
    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    file.write(content.toLatin1());
    file.close();
}
