/*
   * Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
   *
   * Author:     chenhaifeng <chenhaifeng@uniontech.com>
   *
   * Maintainer: chenhaifeng <chenhaifeng@uniontech.com>
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
#include "ut_timeedit.h"

#include <QPixmap>
#include <QFocusEvent>
#include <QApplication>

ut_timeedit::ut_timeedit()
{
    mTimeEdit = new CTimeEdit();
}

ut_timeedit::~ut_timeedit()
{
    delete mTimeEdit;
    mTimeEdit = nullptr;
}

//void CTimeEdit::setTime(QTime time)
TEST_F(ut_timeedit, setTime)
{
    mTimeEdit->setTime(QTime(23, 59, 59));
}

//QTime CTimeEdit::getTime()
TEST_F(ut_timeedit, getTime)
{
    mTimeEdit->getTime();
}

//setTimeFormat
TEST_F(ut_timeedit, setTimeFormat)
{
    mTimeEdit->setTimeFormat(1);
    mTimeEdit->setTimeFormat(0);
}

//slotFocusDraw
TEST_F(ut_timeedit, slotFocusDraw)
{
    mTimeEdit->slotFocusDraw(false);
}

//getPixmap
TEST_F(ut_timeedit, getPixmap)
{
    mTimeEdit->slotFocusDraw(true);
    mTimeEdit->setFixedSize(200, 50);
    QPixmap pixmap(mTimeEdit->size());
    mTimeEdit->render(&pixmap);
}

TEST_F(ut_timeedit, focusInEvent)
{
    QFocusEvent focusEvent_in( QEvent::FocusIn,Qt::FocusReason::TabFocusReason);
    QApplication::sendEvent(mTimeEdit,&focusEvent_in);
}
