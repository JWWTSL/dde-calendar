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
#ifndef LUNARDATASTRUCT_H
#define LUNARDATASTRUCT_H
#include <QString>
#include <QVector>
#include <QDate>

typedef struct HuangLi {
    qint64 ID; //  `json:"id"` // format: ("%s%02s%02s", year, month, day)
    QString Avoid; // `json:"avoid"`
    QString Suit; //`json:"suit"`
} stHuangLi;

typedef struct _tagHolidayInfo {
    QDate date;
    char status;
} HolidayInfo;

typedef struct _tagFestivalInfo {
    QString ID;
    QString FestivalName;
    QString description;
    QString Rest;
    int month;
    int year;
    QVector<HolidayInfo> listHoliday;
} FestivalInfo;

#endif // LUNARDATASTRUCT_H
