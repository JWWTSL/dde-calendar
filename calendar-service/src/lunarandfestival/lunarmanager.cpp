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
#include "lunarmanager.h"
#include "lunarcalendar.h"

stLunarDayInfo SolarToLunar(qint32 year, qint32 month, qint32 day)
{
    stLunarDayInfo info;
    LunarCalendar *pcalendar = LunarCalendar::GetLunarCalendar(year);
    lunarInfo lday = pcalendar->SolarDayToLunarDay(month, day);
    info.GanZhiYear = GetGanZhiYear(lday.LunarYear);
    info.GanZhiMonth = GetGanZhiMonth(year, lday.MonthZhi);
    info.GanZhiDay = GetGanZhiDay(year, month, day);
    info.LunarMonthName = GetLunarMonthName(lday.LunarMonthName, lday.IsLeap);
    info.LunarDayName = GetLunarDayName(lday.LunarDay);
    info.Term = GetSolarTermName(lday.SolarTerm);
    info.SolarFestival = GetSolarDayFestival(year, month, day);
    info.LunarFestival = GetLunarDayFestival(lday.LunarMonthName, lday.LunarDay, lday.LunarMonthDays, lday.SolarTerm);
    info.Zodiac = GetYearZodiac(lday.LunarYear);
    return info;
}

/**
 * 获取指定公历月份的农历数据
 * year,month 公历年，月
 * fill 是否用上下月数据补齐首尾空缺，首例数据从周日开始
 */
LunarMonthInfo GetLunarMonthCalendar(qint32 year, qint32 month, bool fill)
{
    SolarMonthInfo solarMonth = GetSolarMonthCalendar(year, month, fill);
    return GetLunarMonthCalendar(solarMonth);
}

LunarMonthInfo GetLunarMonthCalendar(const SolarMonthInfo &solarMonth)
{
    LunarMonthInfo lunarmonth;
    lunarmonth.FirstDayWeek = solarMonth.FirstDayWeek;
    lunarmonth.Days = solarMonth.Days;
    foreach (stDay d, solarMonth.Datas) {
        stLunarDayInfo info = SolarToLunar(d.Year, d.Month, d.Day);
        lunarmonth.Datas.append(info);
    }
    return lunarmonth;
}

/**
 * 公历某月日历
 * year,month 公历年，月
 * fill 是否用上下月数据补齐首尾空缺，首例数据从周日开始(7*6阵列)
 */
SolarMonthInfo GetSolarMonthCalendar(qint32 year, qint32 month, bool fill)
{
    SolarMonthInfo solarMonth;
    int weekday = GetWeekday(year, month);
    int daycount = GetSolarMonthDays(year, month);
    // 本月的数据
    QList<stDay> daysData = GetMonthDays(year, month, 1, daycount);
    QList<int> YearMonth;
    if (fill) {
        if (weekday > 0) {
            //获取前一个月所在年份及月份（如果当前月份为1月则为前一年的十二月）
            YearMonth = GetPreMonth(year, month);
            int premonthyear = YearMonth.at(0);
            int premonth = YearMonth.at(1);
            GetSolarMonthDays(premonthyear, premonth);
            // 前一个月的天数
            int preMonthDays = GetSolarMonthDays(premonthyear, premonth);
            // 要补充上去的前一个月的数据
            QList<stDay> preMonthCompleteDaysData = GetMonthDays(premonthyear, premonth, preMonthDays - weekday + 1, preMonthDays);
            preMonthCompleteDaysData.append(daysData);
            daysData = preMonthCompleteDaysData;
        }
        YearMonth = GetNextMonth(year, month);
        int nextmonthyear = YearMonth.at(0);
        int nextmonth = YearMonth.at(1);
        int count = 6 * 7 - (weekday + daycount);
        // 要补充上去的下一个月的数据
        QList<stDay> nextMonthCompleteDaysData = GetMonthDays(nextmonthyear, nextmonth, 1, count);
        daysData.append(nextMonthCompleteDaysData);
    }
    solarMonth.FirstDayWeek = weekday;
    solarMonth.Days = daycount;
    solarMonth.Datas = daysData;
    return solarMonth;
}

QList<stDay> GetMonthDays(qint32 year, qint32 month, qint32 start, qint32 days)
{
    QList<stDay> DayInfo;
    for (int day = start; day <= days; day++) {
        stDay stday = {year, month, day};
        DayInfo.append(stday);
    }
    return DayInfo;
}

QList<int> GetPreMonth(qint32 year, qint32 month)
{
    QList<int> datas;
    int preYear, preMonth;
    if (month == 1) {
        preYear = year - 1;
        preMonth = 12;
    } else {
        preYear = year;
        preMonth = month - 1;
    }
    datas.append(preYear);
    datas.append(preMonth);
    return datas;
}

QList<int> GetNextMonth(qint32 year, qint32 month)
{
    QList<int> datas;
    int nextYear, nextMonth;
    if (month == 12) {
        nextYear = year + 1;
        nextMonth = 1;
    } else {
        nextYear = year;
        nextMonth = month + 1;
    }
    datas.append(nextYear);
    datas.append(nextMonth);
    return datas;
}
