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
#include "dbusdatastruct.h"

#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonArray>

void CaLunarDayInfo::registerMetaType()
{
    qRegisterMetaType<CaLunarDayInfo>();
    qDBusRegisterMetaType<CaLunarDayInfo>();
}

QDebug operator<<(QDebug argument, const CaLunarDayInfo &what)
{
    argument << what.mGanZhiYear << what.mGanZhiMonth << what.mGanZhiDay;
    argument << what.mLunarMonthName << what.mLunarDayName;
    argument << what.mLunarLeapMonth;
    argument << what.mZodiac << what.mTerm;
    argument << what.mSolarFestival << what.mLunarFestival;
    argument << what.mWorktime;

    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const CaLunarDayInfo &what)
{
    argument.beginStructure();
    argument << what.mGanZhiYear << what.mGanZhiMonth << what.mGanZhiDay;
    argument << what.mLunarMonthName << what.mLunarDayName;
    argument << what.mLunarLeapMonth;
    argument << what.mZodiac << what.mTerm;
    argument << what.mSolarFestival << what.mLunarFestival;
    argument << what.mWorktime;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, CaLunarDayInfo &what)
{
    argument.beginStructure();
    argument >> what.mGanZhiYear >> what.mGanZhiMonth >> what.mGanZhiDay;
    argument >> what.mLunarMonthName >> what.mLunarDayName;
    argument >> what.mLunarLeapMonth;
    argument >> what.mZodiac >> what.mTerm;
    argument >> what.mSolarFestival >> what.mLunarFestival;
    argument >> what.mWorktime;
    argument.endStructure();

    return argument;
}

void CaLunarMonthInfo::registerMetaType()
{
    qRegisterMetaType<CaLunarMonthInfo>();
    qDBusRegisterMetaType<CaLunarMonthInfo>();
}

QDebug operator<<(QDebug argument, const CaLunarMonthInfo &what)
{
    argument << what.mFirstDayWeek << what.mDays;
    argument << what.mCaLunarDayInfo;

    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const CaLunarMonthInfo &what)
{
    argument.beginStructure();
    argument << what.mFirstDayWeek << what.mDays;
    argument << what.mCaLunarDayInfo;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, CaLunarMonthInfo &what)
{
    argument.beginStructure();
    argument >> what.mFirstDayWeek >> what.mDays;
    argument >> what.mCaLunarDayInfo;
    argument.endStructure();

    return argument;
}

void CaHuangLiDayInfo::registerMetaType()
{
    qRegisterMetaType<CaHuangLiDayInfo>();
    qDBusRegisterMetaType<CaHuangLiDayInfo>();
}

QDebug operator<<(QDebug argument, const CaHuangLiDayInfo &what)
{
    argument << what.mSuit << what.mAvoid;
    argument << what.mWorktime;
    argument << what.mLunarFestival << what.mSolarFestival;
    argument << what.mTerm << what.mZodiac;
    argument << what.mLunarLeapMonth;
    argument << what.mLunarDayName << what.mLunarMonthName;
    argument << what.mGanZhiDay << what.mGanZhiMonth << what.mGanZhiYear;
    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const CaHuangLiDayInfo &what)
{
    argument.beginStructure();
    argument << what.mSuit << what.mAvoid;
    argument << what.mWorktime;
    argument << what.mLunarFestival << what.mSolarFestival;
    argument << what.mTerm << what.mZodiac;
    argument << what.mLunarLeapMonth;
    argument << what.mLunarDayName << what.mLunarMonthName;
    argument << what.mGanZhiDay << what.mGanZhiMonth << what.mGanZhiYear;
    argument.endStructure();
    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, CaHuangLiDayInfo &what)
{
    argument.beginStructure();
    argument >> what.mSuit >> what.mAvoid;
    argument >> what.mWorktime;
    argument >> what.mLunarFestival >> what.mSolarFestival;
    argument >> what.mTerm >> what.mZodiac;
    argument >> what.mLunarLeapMonth;
    argument >> what.mLunarDayName >> what.mLunarMonthName;
    argument >> what.mGanZhiDay >> what.mGanZhiMonth >> what.mGanZhiYear;
    argument.endStructure();
    return argument;
}

void CaHuangLiMonthInfo::registerMetaType()
{
    qRegisterMetaType<CaHuangLiMonthInfo>();
    qDBusRegisterMetaType<CaHuangLiMonthInfo>();
}

QString CaHuangLiMonthInfo::toJson()
{
    QJsonArray daysarr;
    QJsonDocument doc;
    QJsonObject obj;
    obj.insert("Days", mDays);
    obj.insert("FirstDayWeek", mFirstDayWeek);
    foreach (CaHuangLiDayInfo dayinfo, mCaLunarDayInfo) {
        QJsonObject dayobj;
        dayobj.insert("Suit", dayinfo.mSuit);
        dayobj.insert("Avoid", dayinfo.mAvoid);
        dayobj.insert("Worktime", dayinfo.mWorktime);
        dayobj.insert("LunarFestival", dayinfo.mLunarFestival);
        dayobj.insert("SolarFestival", dayinfo.mSolarFestival);
        dayobj.insert("Term", dayinfo.mTerm);
        dayobj.insert("Zodiac", dayinfo.mZodiac);
        dayobj.insert("LunarLeapMonth", dayinfo.mLunarLeapMonth);
        dayobj.insert("LunarDayName", dayinfo.mLunarDayName);
        dayobj.insert("LunarMonthName", dayinfo.mLunarMonthName);
        dayobj.insert("GanZhiDay", dayinfo.mGanZhiDay);
        dayobj.insert("GanZhiMonth", dayinfo.mGanZhiMonth);
        dayobj.insert("GanZhiYear", dayinfo.mGanZhiYear);
        daysarr.append(dayobj);
    }
    obj.insert("Datas", daysarr);
    doc.setObject(obj);
    QString strJson = QString::fromUtf8(doc.toJson(QJsonDocument::Compact));
    return strJson;
}

QDebug operator<<(QDebug argument, const CaHuangLiMonthInfo &what)
{
    argument << what.mDays << what.mFirstDayWeek;
    argument << what.mCaLunarDayInfo;

    return argument;
}

QDBusArgument &operator<<(QDBusArgument &argument, const CaHuangLiMonthInfo &what)
{
    argument.beginStructure();
    argument << what.mDays << what.mFirstDayWeek;
    argument << what.mCaLunarDayInfo;
    argument.endStructure();

    return argument;
}

const QDBusArgument &operator>>(const QDBusArgument &argument, CaHuangLiMonthInfo &what)
{
    argument.beginStructure();
    argument >> what.mDays >> what.mFirstDayWeek;
    argument >> what.mCaLunarDayInfo;
    argument.endStructure();

    return argument;
}
