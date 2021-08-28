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
#ifndef TEST_DAYHUANGLIVIEW_H
#define TEST_DAYHUANGLIVIEW_H

#include <QObject>
#include <dayWidget/dayhuangliview.h>
#include <gtest/gtest.h>

class ut_dayhuangliview : public QObject
    , public ::testing::Test
{
public:
    ut_dayhuangliview();
    ~ut_dayhuangliview();

protected:
    CDayHuangLiLabel *mDayHuangLiLabel = nullptr;
};

#endif // TEST_DAYHUANGLIVIEW_H
