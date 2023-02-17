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
#ifndef TIMEJUMPDIALOG_H
#define TIMEJUMPDIALOG_H

#include "ctimelineedit.h"
#include <DArrowRectangle>
#include <DSuggestButton>
#include <QDate>

DWIDGET_USE_NAMESPACE

//时间跳转弹窗
class TimeJumpDialog : public DArrowRectangle
{
    Q_OBJECT
public:

    //时间编辑控件类型
    enum EditType{
        EditYear = 1,
        EditMonth,
        EditDay,
    };

    explicit TimeJumpDialog(ArrowDirection direction, QWidget *parent = nullptr);

    //显示控件
    void showPopup(const QDate& date, const QPoint& pos);
    void showPopup(const QDate& date, int x, int y);

signals:

public slots:
    //时间编辑器数字改变事件
    void slotEditNumChange(int id, int num);
    //时间编辑器时间跳转时间
    void slotDateJump(int id, int num);
    //跳转控件点击事件
    void slotJumpButtonClicked();

private:
    void initView();
    void initConnect();
    void initData();
    //获取当月最大天数
    int getMaxDayNum();

private:
    QDate m_date;

    CTimeLineEdit *m_yearEdit = nullptr;    //年编辑器
    CTimeLineEdit *m_monthEdit = nullptr;   //月编辑器
    CTimeLineEdit *m_dayEdit = nullptr;     //天编辑器
    DSuggestButton *m_jumpButton = nullptr; //跳转控件
};

#endif // TIMEJUMPDIALOG_H
