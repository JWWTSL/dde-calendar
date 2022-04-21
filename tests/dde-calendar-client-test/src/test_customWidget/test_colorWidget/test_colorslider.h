/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     leilong  <leilong@uniontech.com>
*
* Maintainer: leilong  <leilong@uniontech.com>
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
#ifndef TEXT_COLORSLIDER_H
#define TEXT_COLORSLIDER_H

#include <colorWidget/colorslider.h>
#include <QObject>
#include <QTest>
#include <gtest/gtest.h>

class test_colorslider : public QObject, public::testing::Test
{
    Q_OBJECT
public:
    explicit test_colorslider(QObject *parent = nullptr);

    virtual void SetUp()
    {
        mWidget = new ColorSlider();
    }

    virtual void TearDown()
    {
        delete mWidget;
        mWidget = nullptr;
    }
protected:
    ColorSlider *mWidget = nullptr;
};

#endif // TEXT_COLORSLIDER_H
