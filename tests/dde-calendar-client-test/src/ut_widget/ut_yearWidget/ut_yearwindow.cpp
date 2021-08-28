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
#include "ut_yearwindow.h"

ut_yearwindow::ut_yearwindow()
{
    mYearWindow = new CYearWindow();
    dateaManger = new CalendarDateDataManager();
}

ut_yearwindow::~ut_yearwindow()
{
    delete mYearWindow;
    mYearWindow = nullptr;
    delete dateaManger;
    dateaManger = nullptr;
}

//void CYearWindow::setTheMe(int type)
TEST_F(ut_yearwindow, setTheMe)
{
    int type = 1;
    mYearWindow->setTheMe(type);
    type = 2;
    mYearWindow->setTheMe(type);
}

TEST_F(ut_yearwindow, slotMousePress)
{
    QDate currentDate = QDate::currentDate();
    mYearWindow->slotMousePress(currentDate, 0);
    mYearWindow->slotMousePress(currentDate, 1);
    mYearWindow->slotMousePress(currentDate, 2);
    mYearWindow->slotMousePress(currentDate, 3);
    mYearWindow->slotMousePress(currentDate, 4);
}

TEST_F(ut_yearwindow, calculateAzimuthAngle)
{
    QPointF startPoint(0, 0);
    QPointF stopPoint(30, 20);
    mYearWindow->calculateAzimuthAngle(startPoint, stopPoint);
    stopPoint.setX(20);
    stopPoint.setY(30);
    mYearWindow->calculateAzimuthAngle(startPoint, stopPoint);
    stopPoint.setX(-20);
    stopPoint.setY(30);
    mYearWindow->calculateAzimuthAngle(startPoint, stopPoint);
    stopPoint.setX(-30);
    stopPoint.setY(20);
    mYearWindow->calculateAzimuthAngle(startPoint, stopPoint);
}
