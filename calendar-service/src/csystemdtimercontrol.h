#ifndef CSYSTEMDTIMERCONTROL_H
#define CSYSTEMDTIMERCONTROL_H

#include <QObject>
#include <QDateTime>
#include <QVector>


struct SystemDInfo{
    qint64      jobID;              //日程id
    qint32      laterCount;         //稍后提醒次数
    QDateTime   triggerTimer;       //触发时间
};

/**
 * @brief The CSystemdTimerControl class
 * systemd timer 控制类
 */
class CSystemdTimerControl : public QObject
{
    Q_OBJECT
public:
    explicit CSystemdTimerControl(QObject *parent = nullptr);
    ~CSystemdTimerControl();

    /**
     * @brief buildingConfiggure       根据日程信息集，创建相关的systemd配置文件,并开启定时任务
     * @param infoVector
     */
    void buildingConfiggure(const QVector<SystemDInfo> &infoVector);

    /**
     * @brief systemdDaemonReload
     * 重新加载配置文件
     */
    void systemdDaemonReload();

    /**
     * @brief stopSystemdTimerByJobInfos        根据日程信息集，停止相应的任务
     * @param infoVector
     */
    void stopSystemdTimerByJobInfos(const QVector<SystemDInfo> &infoVector);

    /**
     * @brief stopSystemdTimerByJobInfo     根据日程信息，停止相关任务
     * @param info
     */
    void stopSystemdTimerByJobInfo(const SystemDInfo &info);
    /**
     * @brief startSystemdTimer        开启定时任务
     * @param timerName         定时任务.timer名称集合
     */
    void startSystemdTimer(const QStringList &timerName);
    /**
     * @brief stopSystemdTimer         停止定时任务
     * @param timerName         定时任务.timer名称集合
     */
    void stopSystemdTimer(const QStringList &timerName);

    /**
     * @brief stopAllRemindSystemdTimer 停止所有的日程定时任务
     */
    void stopAllRemindSystemdTimer();

    /**
     * @brief removeRemindFile      移除日程定时任务相关文件
     */
    void removeRemindFile();
private:
    /**
     * @brief removeFile        移除.service和.timer文件
     * @param fileName
     */
    void removeFile(const QStringList &fileName);
    /**
     * @brief createPath
     * 创建systemd文件路径
     */
    void createPath();

    /**
     * @brief execLinuxCommand      执行linux命令
     * @param command
     * @return
     */
    QString execLinuxCommand(const QString &command);

    /**
     * @brief createService
     * 创建 .service文件
     */
    void createService(const QString &name ,qint64 jobID);
    /**
     * @brief createTimer
     * 创建 .timer文件
     */
    void createTimer(const QString &name ,const QDateTime &triggerTimer);

    /**
     * @brief createFile        创建文件
     * @param fileName          文件名称
     * @param content           内容
     */
    void createFile(const QString &fileName ,const QString &content);
signals:

public slots:
private:
    QString m_systemdPath;
};

#endif // CSYSTEMDTIMERCONTROL_H
