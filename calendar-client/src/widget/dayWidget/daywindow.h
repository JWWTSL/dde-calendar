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
#ifndef DAYWINDOW_H
#define DAYWINDOW_H

#include "src/scheduledatainfo.h"
#include "src/dbusdatastruct.h"
#include "cschedulebasewidget.h"

#include <DMainWindow>
#include <DFrame>

#include <QWidget>
#include <QDate>
#include <QLabel>
DWIDGET_USE_NAMESPACE

class CDayMonthView;
class CScheduleView;
class CScheduleSearchView;
class ScheduleRemindWidget;
class QHBoxLayout;
class CustomFrame;
class CDayWindow: public CScheduleBaseWidget
{
    Q_OBJECT
public:
    explicit CDayWindow(QWidget *parent = nullptr);
    ~CDayWindow() override;
    void setSearchWFlag(bool flag);
    void setLunarVisible(bool state);
    void setTheMe(int type = 0);
    //设置显示的时间位置
    void setTime(const QTime time = QTime());
    //更新全天和非全天高度
    void updateHigh();
    //设置当前时间
    void setCurrentDateTime(const QDateTime &currentDate) override;
    //设置选择时间年信息显示
    void setYearData() override;
    //更新显示时间
    void updateShowDate(const bool isUpdateBar = true) override;
    //更新日程显示
    void updateShowSchedule() override;
    //更新显示农历信息
    void updateShowLunar() override;
    //设置选中搜索日程
    void setSelectSearchScheduleInfo(const ScheduleDataInfo &info) override;
    //删除选中日程
    void deleteselectSchedule() override;
private:
    void initUI();
    void initConnection();
    //获取界面显示定位时间位置
    void setMakeTime(QMap<QDate, QVector<ScheduleDataInfo> > &info);
public slots:
    void slotScheduleHide();
    //更新选择时间
    void slotChangeSelectDate(const QDate &date);
protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void slotIsDragging(bool &isDragging);
    //切换选择时间
    void slotSwitchPrePage();
    //切换选择时间
    void slotSwitchNextPage();
    //接收设置悬浮框是否显示
    void slotScheduleShow(const bool isShow, const ScheduleDataInfo &out = ScheduleDataInfo());

private:
    CDayMonthView *m_daymonthView = nullptr;
    CustomFrame *m_leftground = nullptr;
    DVerticalLine *m_verline = nullptr;
    QLabel *m_YearLabel = nullptr;
    QLabel *m_LunarLabel = nullptr;
    QLabel *m_SolarDay = nullptr;
    CScheduleView *m_scheduleView = nullptr;
    QString m_searchText;
    bool m_searchfalg = false;
    QHBoxLayout *m_mainLayout = nullptr;
    QTime           m_makeTime{};   //界面显示定位时间位置
    ScheduleRemindWidget *m_ScheduleRemindWidget = nullptr; //悬浮框
};

#endif // YEARWINDOW_H
