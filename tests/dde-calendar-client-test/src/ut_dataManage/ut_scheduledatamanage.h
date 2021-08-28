/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     hejinghai <hejinghai@uniontech.com>
*
* Maintainer: hejinghai <hejinghai@uniontech.com>
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
#ifndef TEST_SCHEDULEDATAMANAGE_H
#define TEST_SCHEDULEDATAMANAGE_H

#include "scheduledatamanage.h"
#include "gtest/gtest.h"
#include <QObject>

class ut_scheduledatamanage : public QObject
    , public ::testing::Test
{
public:
    ut_scheduledatamanage();
    ~ut_scheduledatamanage();

protected:
    CScheduleDataManage *datamanage = nullptr;
};

#endif // TEST_SCHEDULEDATAMANAGE_H
