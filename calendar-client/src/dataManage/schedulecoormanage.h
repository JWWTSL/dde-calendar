/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
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
#ifndef SCHEDULECOORMANAGE_H
#define SCHEDULECOORMANAGE_H

#include <QDate>
#include <QDateTime>
#include <QRect>

class CScheduleCoorManage
{
public:
    CScheduleCoorManage();
    ~CScheduleCoorManage();
    void setRange(int w, int h, QDate begindate, QDate enddate, int rightmagin);
    void setDateRange(QDate begindate, QDate enddate);
    int getRightMagin() const
    {
        return m_rightmagin;
    }
    QRectF getDrawRegion(QDate date, QDateTime begintime, QDateTime endtime, int index, int coount, int maxNum, int type = 0);
    QRectF getAllDayDrawRegion(QDate begin, QDate end);
    QDateTime getDate(QPointF pos);
    QDate getsDate(QPointF pos);
    float getHeight(const QTime &time) const;
    QDate getBegindate() const
    {
        return m_begindate;
    }

private:
    int m_width {0};
    int m_height {0};
    QDate m_begindate;
    QDate m_enddate;
    qint64 m_totalDay {0};
    int m_rightmagin = 0;
};

#endif // SCHEDULECOORMANAGE_H
