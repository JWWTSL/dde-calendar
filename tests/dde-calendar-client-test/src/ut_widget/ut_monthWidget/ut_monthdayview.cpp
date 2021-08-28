/*
* Copyright (C) 2019 ~ 2021 Uniontech Software Technology Co.,Ltd.
*
* Author:     zhengxiaokang <zhengxiaokang@uniontech.com>
*
* Maintainer: zhengxiaokang <zhengxiaokang@uniontech.com>
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
#include "ut_monthdayview.h"

ut_monthdayview::ut_monthdayview()
{
    mMonthDayView = new CMonthDayView();
    mMonthWidget = new CMonthWidget();
    mMonthRect = new CMonthRect();
}

ut_monthdayview::~ut_monthdayview()
{
    delete mMonthDayView;
    mMonthDayView = nullptr;
    delete mMonthWidget;
    mMonthWidget = nullptr;
    delete mMonthRect;
    mMonthRect = nullptr;
}

//void CMonthDayView::setSelectDate(const QDate &date)
TEST_F(ut_monthdayview, setSelectdate)
{
    mMonthDayView->setSelectDate(QDate::currentDate());
}

//void CMonthDayView::setTheMe(int type)
TEST_F(ut_monthdayview, setTheMe)
{
    mMonthDayView->setTheMe(1);
    mMonthDayView->setTheMe(2);
}

//void CMonthDayView::setSearchflag(bool flag)
TEST_F(ut_monthdayview, setSearchflag)
{
    mMonthDayView->setSearchflag(false);
}

//void CMonthWidget::setDate(const QDate date[12])
TEST_F(ut_monthdayview, setDate)
{
    QDate m_days[12];
    QDate currentDate = QDate::currentDate();
    for (int i = 0; i < 12; i++) {
        m_days[i] = currentDate.addDays(i);
    }
    mMonthWidget->setDate(m_days);
}

//void CMonthWidget::updateSize()
TEST_F(ut_monthdayview, updateSize)
{
    mMonthWidget->updateSize();
}

//void CMonthRect::setDate(const QDate &date)
TEST_F(ut_monthdayview, setRectDate)
{
    mMonthRect->setDate(QDate::currentDate());
    mMonthRect->getDate();
}

//void CMonthRect::setRect(const QRectF &rect)
TEST_F(ut_monthdayview, setRect)
{
    mMonthRect->setRect(QRectF());
    mMonthRect->rect();
}

//void CMonthRect::setDevicePixelRatio(const qreal pixel)
TEST_F(ut_monthdayview, setDevicePixelRatio)
{
    mMonthRect->setDevicePixelRatio(1.2);
}

//void CMonthRect::setTheMe(int type)
TEST_F(ut_monthdayview, setRTheMe)
{
    mMonthRect->setTheMe(1);
    mMonthRect->setTheMe(2);
}
