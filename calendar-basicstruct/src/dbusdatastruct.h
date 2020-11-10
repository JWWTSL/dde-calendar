/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     kongyunzhen <kongyunzhen@uniontech.com>
*
* Maintainer: kongyunzhen <kongyunzhen@uniontech.com>
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
#ifndef DBUSDATASTRUCT_H
#define DBUSDATASTRUCT_H

#include <QtCore/QDebug>
#include <QtDBus/QtDBus>

class CaLunarDayInfo
{
public:
    CaLunarDayInfo() {}

    static void registerMetaType();

    friend QDebug operator<<(QDebug argument, const CaLunarDayInfo &what);
    friend QDBusArgument &operator<<(QDBusArgument &argument, const CaLunarDayInfo &what);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, CaLunarDayInfo &what);

public:
    QString mGanZhiYear; // 农历年的干支
    QString mGanZhiMonth; // 农历月的干支
    QString mGanZhiDay; // 农历日的干支
    QString mLunarMonthName; // 农历月名
    QString mLunarDayName; // 农历日名
    qint32 mLunarLeapMonth; // 未使用
    QString mZodiac; // 农历年的生肖
    QString mTerm; // 农历节气
    QString mSolarFestival; // 公历节日
    QString mLunarFestival; // 农历节日
    qint32 mWorktime; // 未使用
};

class CaLunarMonthInfo
{
public:
    CaLunarMonthInfo() {}

    static void registerMetaType();

    friend QDebug operator<<(QDebug argument, const CaLunarMonthInfo &what);
    friend QDBusArgument &operator<<(QDBusArgument &argument, const CaLunarMonthInfo &what);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, CaLunarMonthInfo &what);

public:
    qint32 mFirstDayWeek;
    qint32 mDays;
    QList<CaLunarDayInfo> mCaLunarDayInfo;
};

class CaHuangLiDayInfo
{
public:
    CaHuangLiDayInfo()
    {
        mWorktime = mLunarLeapMonth = 0;
    }
    static void registerMetaType();
    friend QDebug operator<<(QDebug argument, const CaHuangLiDayInfo &what);
    friend QDBusArgument &operator<<(QDBusArgument &argument, const CaHuangLiDayInfo &what);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, CaHuangLiDayInfo &what);
    QString toJson();

public:
    QString mGanZhiYear; //年干支
    QString mGanZhiMonth; //月干支
    QString mGanZhiDay; //日干支
    QString mLunarMonthName; //农历月名称
    QString mLunarDayName; //农历日名称
    qint32 mLunarLeapMonth; //闰月
    QString mZodiac; //生肖
    QString mTerm; //农历节气
    QString mSolarFestival; //阳历节日
    QString mLunarFestival; //农历节日
    qint32 mWorktime; //未使用
    QString mSuit; //黄历宜
    QString mAvoid; //黄历忌
};

class CaHuangLiMonthInfo
{
public:
    CaHuangLiMonthInfo() {}
    static void registerMetaType();

    friend QDebug operator<<(QDebug argument, const CaHuangLiMonthInfo &what);
    friend QDBusArgument &operator<<(QDBusArgument &argument, const CaHuangLiMonthInfo &what);
    friend const QDBusArgument &operator>>(const QDBusArgument &argument, CaHuangLiMonthInfo &what);
    QString toJson();

public:
    qint32 mFirstDayWeek; //第一天所在周
    qint32 mDays; //每月天数
    QVector<CaHuangLiDayInfo> mCaLunarDayInfo;
};

Q_DECLARE_METATYPE(CaLunarDayInfo)
Q_DECLARE_METATYPE(CaLunarMonthInfo)
Q_DECLARE_METATYPE(CaHuangLiDayInfo)
Q_DECLARE_METATYPE(CaHuangLiMonthInfo)

#endif // DBUSDATASTRUCT_H
