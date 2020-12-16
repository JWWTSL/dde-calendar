/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     chenhaifeng  <chenhaifeng@uniontech.com>
*
* Maintainer: chenhaifeng  <chenhaifeng@uniontech.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef SCHEDULETASK_H
#define SCHEDULETASK_H

#include "cscheduledbus.h"
#include "src/scheduledatainfo.h"
#include "src/calendardatastruct.h"

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>

struct QueryRange {
    QDate _startDate;   //开始日期
    QDate _stopDate;    //结束日期
};

class DataGetWork;
class CScheduleTask : public QObject
{
    Q_OBJECT
public:
    explicit CScheduleTask(QObject *parent = nullptr);
    ~CScheduleTask();
public:
    //更新缓存信息
    void updateInfo(const QDate &startDate, const QDate &stopDate, const bool isGetLunar = false);
    //判断是否含有这个时间段的日程信息
    bool hasScheduleInfo(const QDate &startDate, const QDate &stopDate);
    //获取缓存中日程信息
    QMap<QDate, QVector<ScheduleDataInfo> > getScheduleInfo(const QDate &startDate, const QDate &stopDate);
    //获取日期是否含有日程标志
    QMap<QDate, bool> getDateHasSchedule() const;
    //获取缓存中农历信息
    QMap<QDate, CaHuangLiDayInfo> getHuangliInfo(const QDate &startDate, const QDate &stopDate);
    //获取缓存中班休信息
    QMap<QDate, int> getFestivalInfo(const QDate &startDate, const QDate &stopDate);
    //获取搜索信息
    QMap<QDate, QVector<ScheduleDataInfo> > getSearchScheduleInfo(const QString &key, const QDateTime &startTime, const QDateTime &endTime);
    //获取缓存中搜索结果
    QMap<QDate, QVector<ScheduleDataInfo> > getSearchScheduleInfo() const;
    //获取缓存搜到的日程
    QVector<ScheduleDataInfo> getSearchScheduleInfoVector() const;
    //清空搜索日程
    void clearSearchScheduleInfo();
private:
    //添加查询时间范围
    void addQueryRange(const QDate &startDate, const QDate &stopDate, const bool isGetLunar);
signals:
    //日程获取成功信号
    void signalUpdateScheduleShow();
    //搜索日程更新
    void signalUpdateSearchSchedule();
    //农历信息获取成功信号
    void signalLunarGetSuccess();
    //日程更新信号
    void jobsUpdate();
public slots:
    //接收查询的日程信息
    void slotGetSchedule(const QMap<QDate, QVector<ScheduleDataInfo> > &scheduleInfo, const QMap<QDate, bool> &hasSchedule);
    //接收农历信息
    void slotGetLunar(const QMap<QDate, CaHuangLiDayInfo> &lunarInfo, const QMap<QDate, int> &festivalInfo);
private:
    QThread                         m_workerThread;
    CScheduleDBus                   *m_DBusManager = nullptr;
    DataGetWork                     *m_work = nullptr;
    //一年的日程信息
    QMap<QDate, QVector<ScheduleDataInfo> >     m_queryScheduleInfo{};
    //一年是否含有日程
    QMap<QDate, bool>               m_fullInfo{};
    //一年的黄历信息
    QMap<QDate, CaHuangLiDayInfo>   m_huangliInfo{};
    //一年的班休信息
    QMap<QDate, int>                m_festivalInfo{};
    //搜索的日程信息
    QMap<QDate, QVector<ScheduleDataInfo> >      m_searchScheduleInfo{};
    QVector<ScheduleDataInfo>           m_searchScheduleInfoVector{};
};


class DataGetWork : public QObject
{
    Q_OBJECT
public:
    explicit DataGetWork(CScheduleDBus *_DataManage);
    ~DataGetWork();
public:
    //设置日程停止
    void setStop(bool isStop);
    //添加查询时间范围
    void addQueryRange(const QDate &startDate, const QDate &stopDate, const bool isGetLunar);
private:
    //查询日程信息
    void queryScheduleInfo(const QueryRange &queryRange);
    //查询农历信息
    void queryLunarInfo(const QueryRange &queryRange);
    //根据时间获取班休信息
    char getFestivalInfoByDate(const QDate &date, const QVector<FestivalInfo> &festivalInfo);
signals:
    void signalGetSchedule(const QMap<QDate, QVector<ScheduleDataInfo> > &scheduleInfo, const QMap<QDate, bool> &hasSchedule);
    void signalGetLunar(const QMap<QDate, CaHuangLiDayInfo> &lunarInfo, const QMap<QDate, int> &festivalInfo);
public slots:
    // 开始查询
    void startQuery();
private:
    CScheduleDBus           *m_DataManage = nullptr;
    QMutex                  m_mutex;
    bool                    m_stop{false};
    QVector<QueryRange>     m_queryScheduleRange{};
    QWaitCondition          m_waitCondition;
    bool                    m_isGetLunar{false};
};

#endif // SCHEDULETASK_H
