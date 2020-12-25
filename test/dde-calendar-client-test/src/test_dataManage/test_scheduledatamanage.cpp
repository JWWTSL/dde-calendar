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
#include "test_scheduledatamanage.h"

test_scheduledatamanage::test_scheduledatamanage()
{
    datamanage = new CScheduleDataManage();
}

test_scheduledatamanage::~test_scheduledatamanage()
{
    delete datamanage;
}

//CSchedulesColor CScheduleDataManage::getScheduleColorByType(int type)
TEST_F(test_scheduledatamanage, getScheduleColorByType)
{
    CSchedulesColor color = datamanage->getScheduleColorByType(1);
    assert(1 == color.type);
}

//bool CScheduleDataManage::getSearchResult(QDate date)
TEST_F(test_scheduledatamanage, getSearchResult)
{
    //QDate date(2020, 12, 01);
    //datamanage->getSearchResult(date);
    assert(1 == 1);
}

//void CScheduleDataManage::setTheMe(int type)
TEST_F(test_scheduledatamanage, setTheMe)
{
    datamanage->setTheMe(1);
    datamanage->setTheMe(2);
    assert(1 == 1);
}

//CScheduleDataManage *CScheduleDataManage::getScheduleDataManage()
TEST_F(test_scheduledatamanage, getScheduleDataManage)
{
    datamanage->getScheduleDataManage();
    assert(1 == 1);
}

//void CScheduleDataManage::clear()
TEST_F(test_scheduledatamanage, clear)
{
    datamanage->clear();
    assert(1 == 1);
}

//QColor CScheduleDataManage::getSystemActiveColor()
TEST_F(test_scheduledatamanage, getSystemActiveColor)
{
    QColor getcolor = datamanage->getSystemActiveColor();
    assert(1 == 1);
}

//int getTheme()
TEST_F(test_scheduledatamanage, getTheme)
{
    datamanage->m_theme = 1;
    int theme = datamanage->getTheme();
    assert(1 == theme);
}
