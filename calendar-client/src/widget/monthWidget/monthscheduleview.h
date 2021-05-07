/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
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
#ifndef MONTHSCHEDULEVIEW_H
#define MONTHSCHEDULEVIEW_H

#include "src/scheduledatainfo.h"
#include "scheduledaterangeinfo.h"
#include "graphicsItem/draginfoitem.h"
#include "graphicsItem/cmonthscheduleitem.h"

#include <QMouseEvent>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

DWIDGET_USE_NAMESPACE

class CWeekScheduleView;
class CMonthScheduleView : public QObject
{
    Q_OBJECT
public:
    explicit CMonthScheduleView(QWidget *parent, QGraphicsScene *scene);
    ~CMonthScheduleView() override;
    void setallsize(int w, int h, int left, int top, int buttom, int itemHeight = 22);
    void setData(QMap<QDate, QVector<ScheduleDataInfo> > &data, int currentMonth);
    void updateData();
    void updateHigh();
    QVector<QGraphicsRectItem *> getScheduleShowItem() const;
    int getScheduleHeight() const
    {
        return m_ItemHeight;
    }
    void updateDate(const ScheduleDataInfo &info);
    void changeDate(const ScheduleDataInfo &info);
    void updateDate(const int row, const ScheduleDataInfo &info);
signals:
    void signalsUpdateShcedule(int id = 0);
    void signalsCurrentScheduleDate(QDate date);
    void signalViewtransparentFrame(int type);
    void signalUpdateUI(int type);
    void signalPressScheduleShow(const bool isShow, const ScheduleDataInfo &out = ScheduleDataInfo());
public slots:
    void slotFontChange();
private:
    void updateDateShow(QVector<QVector<MScheduleDateRangeInfo>> &vCMDaySchedule, QVector<QGraphicsRectItem *> &schudeleShowItem);
    void createScheduleItemWidget(MScheduleDateRangeInfo info, int cnum, QVector<QGraphicsRectItem *> &schudeleShowItem);
    void createScheduleNumWidget(MScheduleDateRangeInfo info, int cnum, QVector<QGraphicsRectItem *> &schudeleShowItem);
    void computePos(int cnum, QDate bgeindate, QDate enddate, QPoint &pos, int &fw, int &fh);

private:
    QMap<QDate, QVector<ScheduleDataInfo> > m_data;
    int m_cNum = 2; //日程层数
    QWidget *m_parernt = nullptr;
    int m_currentMonth = 0;
    QDate m_beginDate;
    QDate m_endDate;
    int m_width = 0;
    int m_height = 0;
    int m_leftMagin = 0;
    int m_topMagin = 0;
    int m_buttommagin = 0;
    QVector<CWeekScheduleView *> m_weekSchedule;
    int m_ItemHeight = 42;
    QGraphicsScene *m_Scene = nullptr;
};

class CWeekScheduleView : public QObject
{
    Q_OBJECT
    typedef QVector<MScheduleDateRangeInfo> RowScheduleInfo;

public:
    explicit CWeekScheduleView(QObject *parent = nullptr);
    ~CWeekScheduleView() override;

public:
    void setData(QMap<QDate, QVector<ScheduleDataInfo> > &data, const QDate  &startDate, const QDate &stopDate);
    bool addData(const ScheduleDataInfo &info);
    void changeDate(const ScheduleDataInfo &info);
    void setHeight(const int ScheduleHeight, const int DayHeigth);
    QVector<RowScheduleInfo> getMScheduleInfo() const
    {
        return m_MScheduleInfo;
    }
    QVector<QGraphicsRectItem *> &getScheduleShowItem()
    {
        return m_scheduleShowItem;
    }
    void updateSchedule(const bool isNormalDisplay, const ScheduleDataInfo &info = ScheduleDataInfo());
    void clearItem();
private:
    void setMaxNum();
    void mScheduleClear();
    void sortAndFilter(QVector<MScheduleDateRangeInfo> &vMDaySchedule);
    /**
     * @brief addShowSchedule       添加显示的日程
     * @param startPos              其实位置
     * @param endPos                结束位置
     * @param addRow                需要添加的行
     * @param addInfo               添加的日程
     */
    void addShowSchedule(const int &startPos, const int &endPos, const int &addRow, const ScheduleDataInfo &addInfo);
private:
    QVector<QGraphicsRectItem *> m_scheduleShowItem;
    QVector<RowScheduleInfo> m_MScheduleInfo;
    QVector<ScheduleDataInfo> m_ScheduleInfo;
    QVector<int> m_ColumnScheduleCount;
    int m_ScheduleHeight = 0;
    int m_DayHeight = 0;
    int m_MaxNum = 0;
    QDate beginDate;
    QDate endDate;
    int m_colum = 0;
};
#endif // MONTHSCHEDULEVIEW_H
