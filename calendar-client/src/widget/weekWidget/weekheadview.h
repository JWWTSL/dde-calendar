/*
 * Copyright (C) 2015 ~ 2018 Deepin Technology Co., Ltd.
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

#ifndef WEEKHEADVIEW_H
#define WEEKHEADVIEW_H

#include "constants.h"
#include "../touchgestureoperation.h"
#include "src/dbusdatastruct.h"

#include <DLabel>
#include <DFrame>

#include <QWidget>
#include <QList>
#include <QDate>
#include <QStyleOption>

DWIDGET_USE_NAMESPACE

class CustomFrame;
class CWeekHeadView: public DFrame
{
    Q_OBJECT
public:
    enum ShowState {
        ShowLunar = 0x01,
        ShowLunarFestivalHighlight = 0x02,
        Normal = ShowLunar | ShowLunarFestivalHighlight,
    };

public:
    explicit CWeekHeadView(QWidget *parent = nullptr);
    ~CWeekHeadView() override;
    //根据系统主题类型设置颜色
    void setTheMe(int type = 0);
    //设置一周的时间
    void setWeekDay(QVector<QDate> vDays, const QDate &selectDate);
    //设置黄历信息
    void setHunagliInfo(const QMap<QDate, CaHuangLiDayInfo> &huangliInfo);
signals:
    /**
     * @brief signalsViewSelectDate 选择日期的信号
     * @param date 日期
     */
    void signalsViewSelectDate(QDate date);
    /**
     * @brief signalAngleDelta      发送滚动信号滚动相对量
     * @param delta     滚动相对量
     */
    void signalAngleDelta(int delta);
public slots:
    //设置是否显示阴历信息
    void setLunarVisible(bool visible);
private:
    //根据索引值获取当天是在一个月中的第几天
    const QString getCellDayNum(int pos);
    //根据索引获取当天的日期
    const QDate getCellDate(int pos);
    //根据索引值获取当天的阴历信息
    const QString getLunar(int pos);
    //绘制周信息
    void paintCell(QWidget *cell);
    bool eventFilter(QObject *o, QEvent *e) override;
protected:
    void wheelEvent(QWheelEvent *e) override;
    bool event(QEvent *e) override;
private slots:
private:
    QList<QWidget *> m_cellList;
    CustomFrame *m_monthLabel = nullptr;
    QVector<QDate>         m_days;
    ShowState m_showState = Normal;
    int m_selectedCell = 0;
    QMap<QDate, CaHuangLiDayInfo>    m_huangliInfo;

    QFont m_dayNumFont;
    QFont m_monthFont;

    QColor m_backgroundCircleColor = "#2ca7f8";
    QColor m_backgroundShowColor = "#2CA7F8";
    QColor m_defaultTextColor = "#6F6F6F";
    QColor m_currentDayTextColor = "#FFFFFF";
    QColor m_defaultLunarColor = "#898989";
    QColor m_weekendsTextColor = "#0887FF";
    QColor m_currentMonthColor = "#000000";
    QColor m_backgroudColor = "#E6EEF2";
    /**
     * @brief m_Background_Weekend_Color 周六周日背景色
     */
    QColor m_Background_Weekend_Color = "#00429A";
    QColor m_solofestivalLunarColor = "#4DFF7272";
    int m_themetype = 1;
    const int m_radius = 8;
    /**
     * @brief m_touchGesture        触摸手势处理
     */
    touchGestureOperation m_touchGesture;
};

#endif // MYCALENDARWIDGET_H
