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

#ifndef CALENDARMAINWINDOW_H
#define CALENDARMAINWINDOW_H

#include "src/scheduledatainfo.h"

#include <DLabel>
#include <DButtonBox>
#include <DFrame>
#include <DMainWindow>
#include <DSearchEdit>
#include <DToolButton>

#include <QStackedLayout>
#include <QPropertyAnimation>
#include <QStackedWidget>
#include <QButtonGroup>
#include <QObject>

DWIDGET_USE_NAMESPACE
class CYearWindow;
class CMonthWindow;
class CWeekWindow;
class CDayWindow;
class CScheduleSearchView;
class AnimationStackedWidget;
class CScheduleDataManage;
class Calendarmainwindow : public DMainWindow
{
    Q_OBJECT
public:
    explicit Calendarmainwindow(int index, QWidget *w = nullptr);
    ~Calendarmainwindow() override;
    void viewWindow(int type, const bool showAnimation = false);
    void updateHeight();
    void setSearchWidth(int w);
public slots:
    void slotTheme(int type);
    void slotOpenSchedule(QString job);
    void slotViewShortcut();
    //更新当前时间
    void slotCurrentDateUpdate();
    void slotSetSearchFocus();
private:
    void initUI();
    void initConnection();
    //创建视图
    void createview();
protected:
    void resizeEvent(QResizeEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void changeEvent(QEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    bool event(QEvent *event) override;
private slots:
    //隐藏提示框
    void setScheduleHide();
    //点击按钮切换视图
    void slotstackWClicked(QAbstractButton *bt);
    void slotWUpdateSchedule();
    void slotSreturnPressed();
    void slotStextChanged();
    //搜索框有焦点时隐藏提示框
    void slotStextfocusChanged(bool onFocus);
    void slotSearchEdit();
    //单击搜索日程动画设置
    void slotSearchSelectSchedule(const ScheduleDataInfo &scheduleInfo);
    //添加视图阴影
    void slotViewtransparentFrame(const bool isShow);
    //启用buttonbox
    void slotSetButtonBox();
    //切换视图
    void slotSwitchView(const int viewIndex);
    //新建日程
    void slotNewSchedule();
    //快捷键删除选中日程
    void slotDeleteitem();
    //设置最大大小
    void slotSetMaxSize(int size = 0);
    void slotSearchFocusSwitch();

private:
    DLabel *m_icon = nullptr;
    AnimationStackedWidget *m_stackWidget = nullptr;
    DButtonBox *m_buttonBox = nullptr;
    DSearchEdit *m_searchEdit = nullptr;
    CYearWindow *m_yearwindow = nullptr;
    CMonthWindow *m_monthWindow = nullptr;
    CWeekWindow *m_weekWindow = nullptr;
    CDayWindow *m_DayWindow = nullptr;
    bool m_searchflag = false;
    CScheduleSearchView *m_scheduleSearchView = nullptr;
    DFrame *m_contentBackground = nullptr;
    int m_priindex = 3; //默认打开日视图双击
    DFrame *m_transparentFrame = nullptr;
    bool m_opensearchflag = false;
    int m_scheduleSearchViewMaxWidth;
    QPropertyAnimation *m_animation = nullptr;
    QTimer *m_currentDateUpdateTimer = nullptr;
    DIconButton *m_newScheduleBtn {nullptr}; //全局的新建日程按钮
    //日历打开默认显示视图
    int m_defaultIndex;
    bool m_setButtonFocus {false};
};

#endif // CALENDARMAINWINDOW_H
