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
#ifndef TEST_MONTHSCHEDULEVIEW_H
#define TEST_MONTHSCHEDULEVIEW_H

#include <QObject>
#include "monthWidget/monthscheduleview.h"
#include "graphicsItem/cmonthscheduleitem.h"
#include "graphicsItem/cmonthschedulenumitem.h"
#include "gtest/gtest.h"

class ut_monthscheduleview : public QObject
    , public ::testing::Test
{
public:
    ut_monthscheduleview();
    ~ut_monthscheduleview();

protected:
    CMonthScheduleView *mMonthScheduleView = nullptr;
    CMonthScheduleItem *mMonthScheduleWidgetItem = nullptr;
    CWeekScheduleView *mWeekScheduleView = nullptr;
    CMonthScheduleNumItem *mMonthScheduleNumButton = nullptr;
    QGraphicsScene *m_scene = nullptr;
};

#endif // TEST_MONTHSCHEDULEVIEW_H
