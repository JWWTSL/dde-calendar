/*
 * Copyright (C) 2015 ~ 2018 Deepin Technology Co., Ltd.
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
#include "weekwindow.h"
#include "scheduleview.h"
#include "constants.h"
#include "weekheadview.h"
#include "weekview.h"
#include "schedulesearchview.h"
#include "todaybutton.h"
#include <scheduledatamanage.h>

#include <DPalette>
#include <DHiDPIHelper>

#include <QMessageBox>
#include <QDate>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QShortcut>

DGUI_USE_NAMESPACE
CWeekWindow::CWeekWindow(QWidget *parent)
    : CScheduleBaseWidget(parent)
    , m_today(new CTodayButton)
{
    setContentsMargins(0, 0, 0, 0);
    initUI();
    initConnection();
    setLunarVisible(m_calendarManager->getShowLunar());
}

CWeekWindow::~CWeekWindow()
{

}

/**
 * @brief setLunarVisible   设置是否显示阴历信息
 * @param state             是否显示阴历信息
 */
void CWeekWindow::setLunarVisible(bool state)
{
    m_weekHeadView->setLunarVisible(state);
    m_YearLunarLabel->setVisible(state);
    m_scheduleView->setLunarVisible(state);
}

/**
 * @brief initUI 初始化界面设置
 */
void CWeekWindow::initUI()
{
    m_today->setText(QCoreApplication::translate("today", "Today", "Today"));
    m_today->setFixedSize(DDEWeekCalendar::WTodayWindth, DDEWeekCalendar::WTodayHeight);
    DPalette todaypa = m_today->palette();
    QColor todayColor = CScheduleDataManage::getScheduleDataManage()->getSystemActiveColor();
    todaypa.setColor(DPalette::ButtonText, todayColor);
    todaypa.setColor(DPalette::Dark, Qt::white);
    todaypa.setColor(DPalette::Light, Qt::white);
    QColor sbcolor("#002A57");
    sbcolor.setAlphaF(0.05);
    todaypa.setColor(DPalette::Shadow, sbcolor);
    QFont todayfont;
    todayfont.setWeight(QFont::Medium);
    todayfont.setPixelSize(DDECalendar::FontSizeFourteen);
    m_today->setFont(todayfont);
    m_today->setPalette(todaypa);
    //新建年份label
    m_YearLabel = new QLabel();
    m_YearLabel->setFixedHeight(DDEWeekCalendar::W_YLableHeight);

    QFont t_labelF;
    t_labelF.setWeight(QFont::Medium);
    t_labelF.setPixelSize(DDECalendar::FontSizeTwentyfour);
    m_YearLabel->setFont(t_labelF);
    DPalette Lunadpa = m_YearLabel->palette();
    Lunadpa.setColor(DPalette::WindowText, QColor("#3B3B3B"));
    m_YearLabel->setPalette(Lunadpa);

    m_YearLunarLabel = new QLabel(this);
    m_YearLunarLabel->setFixedSize(DDEWeekCalendar::W_YLunatLabelWindth, DDEWeekCalendar::W_YLunatLabelHeight);

    m_weekview  = new CWeekView(&CalendarDateDataManager::getWeekNumOfYear, this);

    m_weekLabel = new QLabel();
    m_weekLabel->setFixedHeight(DDEWeekCalendar::W_YLableHeight);
    QFont weeklabelF;
    weeklabelF.setWeight(QFont::Medium);
    weeklabelF.setPixelSize(DDECalendar::FontSizeFourteen);
    m_weekLabel->setFont(weeklabelF);
    DPalette wpa = m_weekLabel->palette();
    wpa.setColor(DPalette::WindowText, QColor("#717171"));
    m_weekLabel->setPalette(wpa);
    m_weekLabel->setText(tr("Week"));

    QFont ylabelF;
    ylabelF.setWeight(QFont::Medium);
    ylabelF.setPixelSize(DDECalendar::FontSizeFourteen);
    m_YearLunarLabel->setFont(ylabelF);
    DPalette YearLpa = m_YearLunarLabel->palette();
    YearLpa.setColor(DPalette::WindowText, QColor("#8A8A8A"));

    m_YearLunarLabel->setPalette(YearLpa);

    QHBoxLayout *yeartitleLayout = new QHBoxLayout;
    yeartitleLayout->setMargin(0);
    yeartitleLayout->setSpacing(0);
    yeartitleLayout->setContentsMargins(21, 20, 8, 0);
    yeartitleLayout->addWidget(m_YearLabel);

    QHBoxLayout *yeartitleLayout1 = new QHBoxLayout;
    yeartitleLayout1->setMargin(0);
    yeartitleLayout1->setSpacing(0);
    yeartitleLayout1->setContentsMargins(14, 9, 0, 7);
    yeartitleLayout1->addWidget(m_YearLunarLabel);
    yeartitleLayout->addLayout(yeartitleLayout1);

    yeartitleLayout->addStretch();
    m_todayframe = new CustomFrame;
    m_todayframe->setContentsMargins(0, 0, 0, 0);
    m_todayframe->setRoundState(true, true, true, true);
    m_todayframe->setBColor(Qt::white);
    m_todayframe->setFixedHeight(DDEYearCalendar::Y_MLableHeight);
    m_todayframe->setboreder(1);
    QHBoxLayout *todaylayout = new QHBoxLayout;
    todaylayout->setMargin(0);
    todaylayout->setSpacing(0);
    //将显示周数的view加入布局
    todaylayout->addWidget(m_weekview);
    //设置布局
    m_todayframe->setLayout(todaylayout);

    yeartitleLayout->addWidget(m_todayframe, 0, Qt::AlignCenter);
    yeartitleLayout->addSpacing(10);
    yeartitleLayout->addWidget(m_weekLabel, 0, Qt::AlignCenter);
    yeartitleLayout->addStretch();
    yeartitleLayout->addWidget(m_today, 0, Qt::AlignRight);

    m_weekHeadView = new CWeekHeadView(this);
    m_scheduleView = new CScheduleView(this);
    m_scheduleView->setviewMagin(73, 109 + 30, 0, 0);
    m_scheduleView->setRange(763, 1032, QDate(2019, 8, 12), QDate(2019, 8, 18));

    m_mainhLayout = new QVBoxLayout;
    m_mainhLayout->setMargin(0);
    m_mainhLayout->setSpacing(0);
    m_mainhLayout->setContentsMargins(8, 20, 0, 9);
    m_mainhLayout->addWidget(m_weekHeadView);
    m_mainhLayout->addWidget(m_scheduleView);
    QVBoxLayout *hhLayout = new QVBoxLayout;
    hhLayout->setMargin(0);
    hhLayout->setSpacing(0);
    hhLayout->setContentsMargins(0, 0, 0, 0);
    hhLayout->addLayout(yeartitleLayout);
    hhLayout->addLayout(m_mainhLayout);

    m_tmainLayout = new QHBoxLayout;
    m_tmainLayout->setMargin(0);
    m_tmainLayout->setSpacing(0);
    m_tmainLayout->setContentsMargins(0, 0, 10, 0);
    m_tmainLayout->addLayout(hhLayout);

    QVBoxLayout *ssLayout = new QVBoxLayout;
    ssLayout->setMargin(0);
    ssLayout->setSpacing(0);
    ssLayout->setContentsMargins(0, 0, 0, 10);
    m_tmainLayout->addLayout(ssLayout);
    this->setLayout(m_tmainLayout);

    setTabOrder(m_weekview, m_today);
    setTabOrder(m_today, m_scheduleView);
}

/**
 * @brief initConnection 初始化信号和槽的连接
 */
void CWeekWindow::initConnection()
{
    connect(m_today, &CTodayButton::clicked, this, &CWeekWindow::slottoday);
    //周数信息区域前按钮点击事件关联触发前一周
    connect(m_weekview, &CWeekView::signalBtnPrev, this, &CWeekWindow::slotprev);
    //周数信息区域后按钮点击事件关联触发后一周
    connect(m_weekview, &CWeekView::signalBtnNext, this, &CWeekWindow::slotnext);
    connect(m_weekview, &CWeekView::signalsSelectDate, this, &CWeekWindow::slotSelectDate);
    connect(m_scheduleView, &CScheduleView::signalViewtransparentFrame, this, &CWeekWindow::signalViewtransparentFrame);
    connect(m_weekHeadView, &CWeekHeadView::signalsViewSelectDate, this, &CWeekWindow::slotViewSelectDate);
    connect(m_weekview, &CWeekView::signalIsDragging, this, &CWeekWindow::slotIsDragging);
    //日程信息区域滚动信号关联
    connect(m_scheduleView, &CScheduleView::signalAngleDelta, this, &CWeekWindow::slotAngleDelta);
    //每周信息区域滚动信号关联
    connect(m_weekHeadView, &CWeekHeadView::signalAngleDelta, this, &CWeekWindow::slotAngleDelta);
    //双击"..."标签切换日视图
    connect(m_scheduleView, &CScheduleView::signalsCurrentScheduleDate, this, &CWeekWindow::slotViewSelectDate);

    connect(m_scheduleView, &CScheduleView::signalSwitchPrePage, this, &CWeekWindow::slotSwitchPrePage);
    connect(m_scheduleView, &CScheduleView::signalSwitchNextPage, this, &CWeekWindow::slotSwitchNextPage);
}

/**
 * @brief setTheMe  根据系统主题类型设置颜色
 * @param type      系统主题类型
 */
void CWeekWindow::setTheMe(int type)
{
    if (type == 0 || type == 1) {
        DPalette todaypa = m_today->palette();
        QColor todayColor = CScheduleDataManage::getScheduleDataManage()->getSystemActiveColor();
        todaypa.setColor(DPalette::ButtonText, todayColor);
        todaypa.setColor(DPalette::Dark, Qt::white);
        todaypa.setColor(DPalette::Light, Qt::white);
        QColor sbcolor("#002A57");
        sbcolor.setAlphaF(0.05);
        todaypa.setColor(DPalette::Shadow, sbcolor);
        m_today->setPalette(todaypa);
        QColor todayhover = "#000000";
        todayhover.setAlphaF(0.1);
        QColor todaypress = "#000000";
        todaypress.setAlphaF(0.2);
        m_today->setBColor("#FFFFFF", todayhover, todaypress, "#FFFFFF", todayhover, todaypress);
        m_today->setTColor(todayColor, "#001A2E", "#0081FF");
        m_today->setshadowColor(sbcolor);
        //返回今天按钮的背景色
        m_todayframe->setBColor(Qt::white);
        DPalette pa = m_YearLabel->palette();
        pa.setColor(DPalette::WindowText, QColor("#3B3B3B"));
        m_YearLabel->setPalette(pa);
        m_YearLabel->setForegroundRole(DPalette::WindowText);
        DPalette Lunapa = m_YearLunarLabel->palette();
        Lunapa.setColor(DPalette::WindowText, QColor("#8A8A8A"));
        m_YearLunarLabel->setPalette(Lunapa);
        m_YearLunarLabel->setForegroundRole(DPalette::WindowText);

        DPalette wpa = m_weekLabel->palette();
        wpa.setColor(DPalette::WindowText, QColor("#717171"));
        m_weekLabel->setPalette(wpa);
        m_weekLabel->setForegroundRole(DPalette::WindowText);
    } else if (type == 2) {
        DPalette todaypa = m_today->palette();
        QColor todayColor = CScheduleDataManage::getScheduleDataManage()->getSystemActiveColor();
        todaypa.setColor(DPalette::ButtonText, todayColor);
        todaypa.setColor(DPalette::Dark, "#414141");
        todaypa.setColor(DPalette::Light, "#484848");
        QColor sbcolor("#000000");
        sbcolor.setAlphaF(0.05);
        todaypa.setColor(DPalette::Shadow, sbcolor);
        m_today->setPalette(todaypa);
        m_today->setBColor("#484848", "#727272", "#242424", "#414141", "#535353", "#282828");
        m_today->setTColor(todayColor, "#FFFFFF", "#0081FF");
        m_today->setshadowColor(sbcolor);
        //设置返回今天按钮的背景色
        QColor bcolor = "#FFFFFF";
        bcolor.setAlphaF(0.05);
        m_todayframe->setBColor(bcolor);

        DPalette pa = m_YearLabel->palette();
        pa.setColor(DPalette::WindowText, QColor("#C0C6D4"));
        m_YearLabel->setPalette(pa);
        m_YearLabel->setForegroundRole(DPalette::WindowText);
        DPalette Lunapa = m_YearLunarLabel->palette();
        Lunapa.setColor(DPalette::WindowText, QColor("#798BA8"));
        m_YearLunarLabel->setPalette(Lunapa);
        m_YearLunarLabel->setForegroundRole(DPalette::WindowText);
        DPalette wpa = m_weekLabel->palette();
        wpa.setColor(DPalette::WindowText, QColor("#717171"));
        m_weekLabel->setPalette(wpa);
        m_weekLabel->setForegroundRole(DPalette::WindowText);
    }
    m_weekview->setTheMe(type);
    m_weekHeadView->setTheMe(type);
    m_scheduleView->setTheMe(type);
}

/**
 * @brief setTime 设置CScheduleView的时间
 * @param time 时间
 */
void CWeekWindow::setTime(QTime time)
{
    m_scheduleView->setTime(time);
}

/**
 * @brief setSearchWFlag 设置搜索标志
 * @param flag 是否进行了搜索
 */
void CWeekWindow::setSearchWFlag(bool flag)
{
    m_searchfalg = flag;
    update();
}

/**
 * @brief CWeekWindow::updateHigh       更新全天区域高度
 */
void CWeekWindow::updateHigh()
{
    m_scheduleView->updateHigh();
}

/**
 * @brief CWeekWindow::setYearData      设置年显示和今天按钮显示
 */
void CWeekWindow::setYearData()
{
    if (getSelectDate() == getCurrendDateTime().date()) {
        m_today->setText(QCoreApplication::translate("today", "Today", "Today"));
    } else {
        m_today->setText(QCoreApplication::translate("Return Today", "Today", "Return Today"));
    }
    if (getShowLunar()) {
        m_YearLabel->setText(QString::number(getSelectDate().year()) + tr("Y"));
    } else {
        m_YearLabel->setText(QString::number(getSelectDate().year()));
    }
}

/**
 * @brief CWeekWindow::updateShowDate       更新显示时间
 * @param isUpdateBar
 */
void CWeekWindow::updateShowDate(const bool isUpdateBar)
{
    setYearData();
    QVector<QDate> _weekShowData = m_calendarManager->getCalendarDateDataManage()->getWeekDate(getSelectDate());
    m_weekHeadView->setWeekDay(_weekShowData, getSelectDate());
    //获取一周的开始结束时间
    m_startDate = _weekShowData.first();
    m_stopDate = _weekShowData.last();
    //如果时间无效则打印log
    if (m_startDate.isNull() || m_stopDate.isNull()) {
        qWarning() << "week start or stop date error";
    }
    //设置全天和非全天显示时间范围
    m_scheduleView->setRange(m_startDate, m_stopDate);
    m_scheduleView->setTimeFormat(m_calendarManager->getCalendarDateDataManage()->getTimeFormat());
    //是否更新显示周数窗口
    if (isUpdateBar) {
        m_weekview->setCurrent(getCurrendDateTime());
        m_weekview->setSelectDate(getSelectDate());
    }
    if (getShowLunar())
        updateShowLunar();
    updateShowSchedule();
    update();
}

/**
 * @brief CWeekWindow::updateShowSchedule       更新日程显示
 */
void CWeekWindow::updateShowSchedule()
{
    QMap<QDate, QVector<ScheduleDataInfo> > _weekScheduleInfo = m_calendarManager->getScheduleTask()->getScheduleInfo(m_startDate, m_stopDate);
    m_scheduleView->setShowScheduleInfo(_weekScheduleInfo);
}

/**
 * @brief CWeekWindow::updateShowLunar                  更新显示农历信息
 */
void CWeekWindow::updateShowLunar()
{
    getLunarInfo();
    m_YearLunarLabel->setText(m_lunarYear);
    QMap<QDate, CaHuangLiDayInfo> _weekHuangliInfo = m_calendarManager->getScheduleTask()->getHuangliInfo(m_startDate, m_stopDate);
    m_weekHeadView->setHunagliInfo(_weekHuangliInfo);
}

/**
 * @brief CWeekWindow::setSelectSearchScheduleInfo      设置选中搜索日程
 * @param info
 */
void CWeekWindow::setSelectSearchScheduleInfo(const ScheduleDataInfo &info)
{
    m_scheduleView->setSelectSchedule(info);
}

/**
 * @brief CWeekWindow::deleteselectSchedule 快捷键删除日程
 */
void CWeekWindow::deleteselectSchedule()
{
    m_scheduleView->slotDeleteitem();
}

/**
 * @brief CWeekWindow::slotIsDragging                   判断是否可以拖拽
 * @param isDragging
 */
void CWeekWindow::slotIsDragging(bool &isDragging)
{
    isDragging = m_scheduleView->IsDragging();
}

/**
 * @brief CWeekWindow::slotViewSelectDate       切换日视图并设置选择时间
 * @param date
 */
void CWeekWindow::slotViewSelectDate(const QDate &date)
{
    if (setSelectDate(date)) {
        //更加界面
        updateData();
        emit signalSwitchView(3);
    }
}

void CWeekWindow::slotSwitchPrePage()
{
    slotprev();
}

void CWeekWindow::slotSwitchNextPage()
{
    slotnext();
}

/**
 * @brief slotprev 切换到上一周，隐藏日程浮框
 */
void CWeekWindow::slotprev()
{
    switchDate(getSelectDate().addDays(-7));
}

/**
 * @brief slotnext 切换到下一周，隐藏日程浮框
 */
void CWeekWindow::slotnext()
{
    switchDate(getSelectDate().addDays(7));
}

/**
 * @brief slottoday     返回到当前时间，隐藏日程浮框
 */
void CWeekWindow::slottoday()
{
    switchDate(getCurrendDateTime().date());
}

/**
 * @brief CWeekWindow::slotSelectDate       修改选择时间
 * @param date
 */
void CWeekWindow::slotSelectDate(const QDate &date)
{
    //更新选择时间
    setSelectDate(date);
    updateShowDate(false);
}

/**
 * @brief slotAngleDelta    接受处理滚动相对量
 * @param delta             滚动相对量
 */
void CWeekWindow::slotAngleDelta(int delta)
{
    //如果为拖拽状态则退出
    if (!m_scheduleView->IsDragging()) {
        if (delta > 0) {
            slotprev();
        } else if (delta < 0) {
            slotnext();
        }
    }
}

/**
 * @brief CWeekWindow::switchDate       切换选择时间
 * @param date
 */
void CWeekWindow::switchDate(const QDate &date)
{
    //隐藏提示框
    slotScheduleHide();
    //设置选择时间
    if (setSelectDate(date, true)) {
        updateData();
    }
}

/**
 * @brief slotScheduleHide 隐藏日程浮框
 */
void CWeekWindow::slotScheduleHide()
{
    m_scheduleView->slotScheduleShow(false);
}

/**
 * @brief resizeEvent 调整周视图窗口
 * @param event 窗口大小调整事件
 */
void CWeekWindow::resizeEvent(QResizeEvent *event)
{
    qreal headh = height() * 0.0924 + 0.5;
    qreal dw = width() * 0.4186 + 0.5;
    int dh = 36;
    int winframe = 10;
    m_mainhLayout->setContentsMargins(10, 20, 0, 10);

    if (m_searchfalg) {
        m_tmainLayout->setContentsMargins(0, 0, 0, 0);
    } else {
        winframe += 10;
        m_tmainLayout->setContentsMargins(0, 0, 10, 0);
    }

    //添加2个按钮的宽度 36+36。原来m_weekview 不包含前后按钮
    if (!m_searchfalg) {
        m_weekview->setFixedSize(qRound(dw + 72), dh);
    } else {
        m_weekview->setFixedSize(qRound(dw - 100 + 72), dh);
    }
    m_weekHeadView->setFixedSize(width() - winframe, qRound(headh));
    QWidget::resizeEvent(event);
}

/**
 * @brief mousePressEvent 鼠标单击隐藏日程浮框
 * @param event 鼠标事件
 */
void CWeekWindow::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    slotScheduleHide();
}


