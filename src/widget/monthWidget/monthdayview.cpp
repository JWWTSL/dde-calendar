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

#include "monthdayview.h"
#include "scheduledatamanage.h"
#include "constants.h"

#include <DPalette>
#include <DHiDPIHelper>

#include <QHBoxLayout>
#include <QPainter>
#include <QBrush>
#include <QEvent>
#include <QMouseEvent>
#include <QDebug>

DGUI_USE_NAMESPACE
CMonthDayView::CMonthDayView(QWidget *parent)
    : DFrame(parent)
{
    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->setMargin(0);
    hboxLayout->setSpacing(0);
    hboxLayout->setContentsMargins(10, 0, 10, 0);
    m_monthWidget = new CMonthWidget(this);
    hboxLayout->addWidget(m_monthWidget);
    setLayout(hboxLayout);
    setFrameRounded(true);
    setLineWidth(0);
    setWindowFlags(Qt::FramelessWindowHint);

    connect(m_monthWidget,
            &CMonthWidget::signalsSelectDate,
            this,
            &CMonthDayView::signalsSelectDate);
}

CMonthDayView::~CMonthDayView()
{
}

void CMonthDayView::setCurrentDate(const QDate date)
{
    m_selectDate = date;
    m_days[5] = m_selectDate;

    for (int i(4); i >= 0; i--) {
        m_days[4 - i] = m_selectDate.addMonths(-i - 1);
    }
    for (int i(6); i != DDEMonthCalendar::MonthNumofYear; ++i) {
        m_days[i] = m_selectDate.addMonths(i - 5);
    }
    update();
    m_monthWidget->setDate(m_days);
}

void CMonthDayView::setRCurrentDate(const QDate date)
{
    if (m_selectDate == date) return;

    m_selectDate = date;
    m_days[5] = m_selectDate;

    for (int i(4); i >= 0; i--) {
        m_days[4 - i] = m_selectDate.addMonths(-i - 1);
    }

    for (int i(6); i != DDEMonthCalendar::MonthNumofYear; ++i) {
        m_days[i] = m_selectDate.addMonths(i - 5);
    }

    m_monthWidget->setDate(m_days);
    update();
}

void CMonthDayView::setTheMe(int type)
{
    QColor frameclor;

    if (type == 0 || type == 1) {
        frameclor = "#FFFFFF";
    } else if (type == 2) {
        frameclor = "#FFFFFF";
        frameclor.setAlphaF(0.05);
    }

    DPalette anipa = palette();
    anipa.setColor(DPalette::Background, frameclor);
    setPalette(anipa);
    setBackgroundRole(DPalette::Background);
    CMonthRect::setTheMe(type);
}

void CMonthDayView::setwindowFixw(int w, int rw)
{
    m_fixwidth = w;
    m_realwidth = rw;
}

void CMonthDayView::setsearchfalg(bool flag)
{
    m_searchfalg = flag;
}

CMonthWidget::CMonthWidget(QWidget *parent)
    :QWidget(parent)
{
    for (int i = 0; i < DDEMonthCalendar::MonthNumofYear; ++i) {
        CMonthRect *monthrect = new CMonthRect();
        m_MonthItem.append(monthrect);
    }
}

CMonthWidget::~CMonthWidget()
{
    for (int i = 0; i < DDEMonthCalendar::MonthNumofYear; ++i) {
        CMonthRect *monthrect = m_MonthItem.at(i);
        delete  monthrect;
    }

    m_MonthItem.clear();
}

void CMonthWidget::setDate(const QDate date[12])
{
    for (int i = 0; i < DDEMonthCalendar::MonthNumofYear; ++i) {
        m_MonthItem.at(i)->setDate(date[i]);
    }

    CMonthRect::setSelectRect(m_MonthItem.at(5));
    update();
}

void CMonthWidget::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    updateSize();
}

void CMonthWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() ==Qt::RightButton)
        return;

    int itemindex = getMousePosItem(event->pos());

    if (!(itemindex<0)) {
        if (m_MonthItem.at(itemindex)->getDate().year() < DDECalendar::QueryEarliestYear) {
            return;
        }
        CMonthRect::setSelectRect(m_MonthItem.at(itemindex));
        emit signalsSelectDate(m_MonthItem.at(itemindex)->getDate());
    }
    update();
}

void CMonthWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;

    for (int i = 0; i < m_MonthItem.size(); ++i) {
        m_MonthItem.at(i)->paintItem(&painter,
                                     m_MonthItem.at(i)->rect());
    }
    painter.end();
}

void CMonthWidget::updateSize()
{
    qreal w= this->width()/m_MonthItem.size();

    for (int i = 0; i < m_MonthItem.size(); ++i) {
        m_MonthItem.at(i)->setRect(i*w,0,w,this->height());
    }
    update();
}

int CMonthWidget::getMousePosItem(const QPointF &pos)
{
    int res =-1;

    for (int i = 0 ; i < m_MonthItem.size(); ++i) {
        if (m_MonthItem.at(i)->rect().contains(pos)) {
            res = i;
            break;
        }
    }

    return res;
}


int         CMonthRect::m_themetype ;
qreal       CMonthRect::m_DevicePixelRatio;

QColor      CMonthRect::m_defaultTextColor;
QColor      CMonthRect::m_backgrounddefaultColor ;
QColor      CMonthRect::m_currentDayTextColor;
QColor      CMonthRect::m_backgroundcurrentDayColor;
QColor      CMonthRect::m_fillColor;
QFont       CMonthRect::m_dayNumFont;
CMonthRect         *CMonthRect::m_SelectRect = nullptr;

CMonthRect::CMonthRect()
{
    m_dayNumFont.setPixelSize(DDECalendar::FontSizeSixteen);
    m_dayNumFont.setWeight(QFont::Light);
}

void CMonthRect::setDate(const QDate &date)
{
    m_Date = date;
}

QDate CMonthRect::getDate() const
{
    return  m_Date;
}

QRectF CMonthRect::rect() const
{
    return  m_rect;
}

void CMonthRect::setRect(const QRectF &rect)
{
    m_rect = rect;
}

void CMonthRect::setRect(qreal x, qreal y, qreal w, qreal h)
{
    m_rect.setRect(x,y,w,h);
}

void CMonthRect::paintItem(QPainter *painter, const QRectF &rect)
{
    m_selectColor = CScheduleDataManage::getScheduleDataManage()->getSystemActiveColor();

    if (m_Date.year() < DDECalendar::QueryEarliestYear)
        return;
    const bool isCurrentDay = (m_Date.month() == QDate::currentDate().month()
                               && m_Date.year() == QDate::currentDate().year());

    painter->setPen(Qt::SolidLine);

    const QString dayNum = QString::number(m_Date.month());

    if (m_SelectRect ==this) {
        QRectF fillRect((rect.width() - 36) / 2 +rect.x() + 6,
                        (rect.height() - 36) / 2 + 7 +rect.y(),
                        24,
                        24);
        painter->setBrush(QBrush(m_selectColor));
        painter->setPen(Qt::NoPen);
        painter->drawEllipse(fillRect);
        painter->setRenderHint(QPainter::HighQualityAntialiasing);
        painter->setPen(m_currentDayTextColor);
        painter->setFont(m_dayNumFont);
        painter->drawText(rect, Qt::AlignCenter, dayNum);
    } else {
        if (isCurrentDay) {
            painter->setPen(m_backgroundcurrentDayColor);
        } else {
            painter->setPen(m_defaultTextColor);
        }
        painter->setFont(m_dayNumFont);
        painter->drawText(rect, Qt::AlignCenter, dayNum);
    }

}

void CMonthRect::setDevicePixelRatio(const qreal pixel)
{
    m_DevicePixelRatio = pixel;
}

void CMonthRect::setTheMe(int type)
{
    m_themetype = type;
    QColor frameclor;

    if (type == 0 || type == 1) {
        m_defaultTextColor = Qt::black;
        m_backgrounddefaultColor = Qt::white;
        m_currentDayTextColor = Qt::white;
        m_backgroundcurrentDayColor = CScheduleDataManage::getScheduleDataManage()->getSystemActiveColor();
        m_fillColor = "#FFFFFF";
        frameclor = m_fillColor;
        m_fillColor.setAlphaF(0);
    } else if (type == 2) {
        m_defaultTextColor = "#C0C6D4";
        QColor framecolor = Qt::black;
        framecolor.setAlphaF(0.5);
        m_backgrounddefaultColor = framecolor;
        m_currentDayTextColor = "#C0C6D4";
        m_backgroundcurrentDayColor = CScheduleDataManage::getScheduleDataManage()->getSystemActiveColor();
        m_fillColor = "#FFFFFF";
        m_fillColor.setAlphaF(0.05);
        frameclor = m_fillColor;
        m_fillColor.setAlphaF(0);
    }
}

void CMonthRect::setSelectRect(CMonthRect *selectRect)
{
    m_SelectRect =selectRect;
}
