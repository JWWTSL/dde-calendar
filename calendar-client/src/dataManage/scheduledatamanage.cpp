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
#include "scheduledatamanage.h"

CScheduleDataManage *CScheduleDataManage::m_vscheduleDataManage = new CScheduleDataManage;

CSchedulesColor CScheduleDataManage::getScheduleColorByType(int type)
{
    CSchedulesColor color;
    color.type = -1;

    for (int i = 0; i < m_vScheduleColor.count(); i++) {
        if (m_vScheduleColor.at(i).type == type) {
            color = m_vScheduleColor.at(i);
            break;
        }
    }

    return color;
}

QColor CScheduleDataManage::getSystemActiveColor()
{
    return DGuiApplicationHelper::instance()->applicationPalette().highlight().color();
}

void CScheduleDataManage::setTheMe(int type)
{
    m_theme = type;
    m_vScheduleColor.clear();

    if (type == 0 || type == 1) {
        CSchedulesColor workC;
        workC.type = 1;
        workC.dotColor = "#FB2525";
        workC.dotColor.setAlphaF(0.5);
        workC.gradientFromC = "#FBCEB7";
        workC.gradientFromC.setAlphaF(0.7);
        workC.gradientToC = "#FA9D9A";
        workC.gradientToC.setAlphaF(0.7);
        workC.Purecolor = "#F85566";
        workC.Purecolor.setAlphaF(0.2);
        workC.shadowcolor = "#FB2525";
        workC.shadowcolor.setAlphaF(0.5);
        workC.textColor = "#000000";
        workC.timeColor = "#B54A4B";
        workC.hightlightgradientFromC = "#FFD0B8";
        workC.hightlightgradientToC = "#FF908D";

        QColor workP("#F9AEB8");
        workC.hightlightPurecolor = workP;
        workC.splitColor = "#FB2525";
        workC.splitColor.setAlphaF(0.5);
        workC.hovergradientFromC = "#FFD0B8";
        workC.hovergradientFromC.setAlphaF(0.95);
        workC.hovergradientToC = "#FF9D9A";
        workC.hovergradientToC.setAlphaF(0.95);

        QColor workhP("#FFB6BD");
        workhP.setAlphaF(0.8);
        workC.hoverPurecolor = workhP;
        workC.pressgradientToC = workC.gradientToC;
        workC.pressgradientFromC = workC.gradientFromC;
        workC.pressPurecolor = workC.Purecolor;
        workC.pressgradientToC.setAlphaF(0.8);
        workC.pressgradientFromC.setAlphaF(0.8);
        workC.pressPurecolor.setAlphaF(0.2);
        m_vScheduleColor.append(workC);

        CSchedulesColor lifeC;
        lifeC.type = 2;
        lifeC.dotColor = "#82D245";
        lifeC.dotColor.setAlphaF(1);
        lifeC.gradientFromC = "#B7E6FB";
        lifeC.gradientFromC.setAlphaF(0.7);
        lifeC.gradientToC = "#D4FFB3";
        lifeC.gradientToC.setAlphaF(0.7);
        lifeC.Purecolor = "#6FFF00";
        lifeC.Purecolor.setAlphaF(0.2);
        lifeC.shadowcolor = "#82D245";
        lifeC.textColor = "#000000";
        lifeC.timeColor = "#53A316";
        lifeC.hightlightgradientFromC = "#9AE5FF";
        lifeC.hightlightgradientToC = "#C7FF94";

        QColor lifeP("#C7FF94");
        lifeC.hightlightPurecolor = lifeP;
        lifeC.hovergradientFromC = "#A8E9FF";
        lifeC.hovergradientToC = "#D5FFAF";
        lifeC.hovergradientFromC.setAlphaF(0.95);
        lifeC.hovergradientToC.setAlphaF(0.95);

        QColor lifehP("#C4FF98");
        lifehP.setAlphaF(0.8);
        lifeC.hoverPurecolor = lifehP;
        lifeC.splitColor = "#82D245";
        lifeC.pressgradientToC = lifeC.gradientToC;
        lifeC.pressgradientFromC = lifeC.gradientFromC;
        lifeC.pressPurecolor = lifeC.Purecolor;
        lifeC.pressgradientToC.setAlphaF(0.8);
        lifeC.pressgradientFromC.setAlphaF(0.8);
        lifeC.pressPurecolor.setAlphaF(0.2);
        m_vScheduleColor.append(lifeC);

        CSchedulesColor otherC;
        otherC.type = 3;
        otherC.dotColor = "#BA60FA";
        otherC.dotColor.setAlphaF(1);
        otherC.gradientFromC = "#FBE9B7";
        otherC.gradientFromC.setAlphaF(0.7);
        otherC.gradientToC = "#DFB3FF";
        otherC.gradientToC.setAlphaF(0.7);
        otherC.Purecolor = "#D191FF";
        otherC.Purecolor.setAlphaF(0.2);
        otherC.shadowcolor = "#BA60FA";
        otherC.textColor = "#000000";
        otherC.timeColor = "#8548B1";
        otherC.hightlightgradientFromC = "#FFE8AC";
        otherC.hightlightgradientToC = "#FBA5FF";

        QColor otherP("#EAC4FF");
        otherC.hightlightPurecolor = otherP;
        otherC.hovergradientFromC = "#FFE8AC";
        otherC.hovergradientToC = "#E2A5FF";
        otherC.hovergradientFromC.setAlphaF(0.95);
        otherC.hovergradientToC.setAlphaF(0.95);

        QColor otherhP("#E6C5FF");
        otherhP.setAlphaF(0.8);
        otherC.hoverPurecolor = otherhP;
        otherC.splitColor = "#BA60FA";
        otherC.pressgradientToC = otherC.gradientToC;
        otherC.pressgradientFromC = otherC.gradientFromC;
        otherC.pressPurecolor = otherC.Purecolor;
        otherC.pressgradientToC.setAlphaF(0.8);
        otherC.pressgradientFromC.setAlphaF(0.8);
        otherC.pressPurecolor.setAlphaF(0.2);
        m_vScheduleColor.append(otherC);

        CSchedulesColor solar;
        solar.type = 4;
        solar.dotColor = "#FF7272";
        solar.dotColor.setAlphaF(1);
        solar.gradientFromC = "#FF7272";
        solar.gradientFromC.setAlphaF(0.3);
        solar.gradientToC = "#FF7272";
        solar.gradientToC.setAlphaF(0.3);
        solar.Purecolor = "#FF7272";
        solar.Purecolor.setAlphaF(0.3);
        solar.shadowcolor = "#BA60FA";
        solar.textColor = "#000000";
        solar.timeColor = "#8548B1";
        solar.hightlightgradientFromC = "#F9AAAA";
        solar.hightlightgradientFromC.setAlphaF(1);
        solar.hightlightgradientToC = "#F9AAAA";
        solar.hightlightgradientToC.setAlphaF(1);
        solar.hightlightPurecolor = "#F9AAAA";
        solar.hightlightPurecolor.setAlphaF(1);
        solar.hovergradientFromC = "#FFB0B1";
        solar.hovergradientToC = "#FFB0B1";
        solar.hovergradientFromC.setAlphaF(0.95);
        solar.hovergradientToC.setAlphaF(0.95);
        solar.hoverPurecolor = "#FF7272";
        solar.splitColor = "#FF7272";
        solar.pressgradientFromC = "#FF7272";
        solar.pressgradientFromC.setAlphaF(0.3);
        solar.pressgradientToC = "#FF7272";
        solar.pressgradientToC.setAlphaF(0.3);
        solar.pressPurecolor = solar.Purecolor;
        solar.pressgradientToC.setAlphaF(0.4);
        solar.pressgradientFromC.setAlphaF(0.4);
        solar.pressPurecolor.setAlphaF(0.1);
        m_vScheduleColor.append(solar);
    } else if (type == 2) {
        CSchedulesColor workC;
        workC.type = 1;
        workC.dotColor = "#F85566";
        workC.dotColor.setAlphaF(0.5);
        workC.gradientFromC = "#965A26";
        workC.gradientToC = "#8B2521";
        workC.gradientToC.setAlphaF(0.5);
        workC.gradientFromC.setAlphaF(0.5);
        workC.Purecolor = "#F85566";
        workC.Purecolor.setAlphaF(0.1);
        workC.shadowcolor = "#FB2525";
        workC.shadowcolor.setAlphaF(0.5);
        workC.textColor = "#C0C6D4";
        workC.timeColor = "#B54A4B";
        workC.hightlightgradientToC = "#992D2A";
        workC.hightlightgradientToC.setAlphaF(0.8);
        workC.hightlightgradientFromC = "#8B521F";
        workC.hightlightgradientFromC.setAlphaF(0.8);

        QColor workP("#77373E");
        workP.setAlphaF(0.8);
        workC.hightlightPurecolor = workP;
        workC.hovergradientFromC = "#965A26";
        workC.hovergradientToC = "#8B2521";
        workC.hovergradientFromC.setAlphaF(0.65);
        workC.hovergradientToC.setAlphaF(0.65);

        QColor workhP("#F85566");
        workhP.setAlphaF(0.2);
        workC.hoverPurecolor = workhP;
        workC.splitColor = "#F85566";
        workC.splitColor.setAlphaF(0.5);
        workC.pressgradientToC = workC.gradientToC;
        workC.pressgradientFromC = workC.gradientFromC;
        workC.pressPurecolor = workC.Purecolor;
        workC.pressgradientToC.setAlphaF(0.4);
        workC.pressgradientFromC.setAlphaF(0.4);
        workC.pressPurecolor.setAlphaF(0.15);
        m_vScheduleColor.append(workC);

        CSchedulesColor lifeC;
        lifeC.type = 2;
        lifeC.dotColor = "#59F88D";
        lifeC.dotColor.setAlphaF(0.5);
        lifeC.gradientFromC = "#2D6883";
        lifeC.gradientToC = "#5D7D44";
        lifeC.gradientToC.setAlphaF(0.5);
        lifeC.gradientFromC.setAlphaF(0.5);
        lifeC.Purecolor = "#59F88D";
        lifeC.Purecolor.setAlphaF(0.1);
        lifeC.shadowcolor = "#25FA6B";
        lifeC.shadowcolor.setAlphaF(0.5);
        lifeC.textColor = "#C0C6D4";
        lifeC.timeColor = "#38A35B";
        lifeC.hightlightgradientFromC = "#2D6883";
        lifeC.hightlightgradientFromC.setAlphaF(0.8);
        lifeC.hightlightgradientToC = "#5D7D44";
        lifeC.hightlightgradientToC.setAlphaF(0.8);

        QColor lifeP("#337044");
        lifeP.setAlphaF(0.8);
        lifeC.hightlightPurecolor = lifeP;
        lifeC.splitColor = "#25FA6B";
        lifeC.splitColor.setAlphaF(0.3);
        lifeC.hovergradientFromC = "#2D6883";
        lifeC.hovergradientToC = "#5D7D44";
        lifeC.hovergradientFromC.setAlphaF(0.65);
        lifeC.hovergradientToC.setAlphaF(0.65);

        QColor lifehP("#59F88D");
        lifehP.setAlphaF(0.2);
        lifeC.hoverPurecolor = lifehP;
        lifeC.pressgradientToC = lifeC.gradientToC;
        lifeC.pressgradientFromC = lifeC.gradientFromC;
        lifeC.pressPurecolor = lifeC.Purecolor;
        lifeC.pressgradientToC.setAlphaF(0.4);
        lifeC.pressgradientFromC.setAlphaF(0.4);
        lifeC.pressPurecolor.setAlphaF(0.15);
        m_vScheduleColor.append(lifeC);

        CSchedulesColor otherC;
        otherC.type = 3;
        otherC.dotColor = "#C155F8";
        otherC.dotColor.setAlphaF(0.7);
        otherC.gradientFromC = "#8C4E2C";
        otherC.gradientToC = "#7D37AF";
        otherC.gradientToC.setAlphaF(0.5);
        otherC.gradientFromC.setAlphaF(0.5);
        otherC.Purecolor = "#C155F8";
        otherC.Purecolor.setAlphaF(0.1);
        otherC.shadowcolor = "#BE3DFF";
        otherC.shadowcolor.setAlphaF(0.5);
        otherC.textColor = "#C0C6D4";
        otherC.timeColor = "#9857C8";
        otherC.hightlightgradientFromC = "#8C4E2C";
        otherC.hightlightgradientFromC.setAlphaF(0.8);
        otherC.hightlightgradientToC = "#803BAE";
        otherC.hightlightgradientToC.setAlphaF(0.8);

        QColor otherP("#613776");
        otherP.setAlphaF(0.8);
        otherC.hightlightPurecolor = otherP;
        otherC.hovergradientFromC = "#8C4E2C";
        otherC.hovergradientToC = "#7D37AF";
        otherC.hovergradientFromC.setAlphaF(0.65);
        otherC.hovergradientToC.setAlphaF(0.65);

        QColor otherhP("#C155F8");
        otherhP.setAlphaF(0.2);
        otherC.hoverPurecolor = otherhP;
        otherC.splitColor = "#BA32FF";
        otherC.splitColor.setAlphaF(0.5);
        otherC.pressgradientToC = otherC.gradientToC;
        otherC.pressgradientFromC = otherC.gradientFromC;
        otherC.pressPurecolor = otherC.Purecolor;
        otherC.pressgradientToC.setAlphaF(0.4);
        otherC.pressgradientFromC.setAlphaF(0.4);
        otherC.pressPurecolor.setAlphaF(0.15);
        m_vScheduleColor.append(otherC);

        CSchedulesColor solar;
        solar.type = 4;
        solar.dotColor = "#FF7272";
        solar.dotColor.setAlphaF(0.8);
        solar.gradientFromC = "#FF7272";
        solar.gradientFromC.setAlphaF(0.3);
        solar.gradientToC = "#FF7272";
        solar.gradientToC.setAlphaF(0.3);
        solar.Purecolor = "#FF7272";
        solar.Purecolor.setAlphaF(0.3);
        solar.shadowcolor = "#BA60FA";
        solar.textColor = "#C0C6D4";
        solar.timeColor = "#8548B1";
        solar.hightlightgradientFromC = "#A24545";
        solar.hightlightgradientFromC.setAlphaF(0.8);
        solar.hightlightgradientToC = "#A24545";
        solar.hightlightgradientToC.setAlphaF(0.8);
        solar.hightlightPurecolor = "#A24545";
        solar.hightlightPurecolor.setAlphaF(0.8);
        solar.hovergradientFromC = "#E56464";
        solar.hovergradientToC = "#E56464";
        solar.hovergradientFromC.setAlphaF(0.35);
        solar.hovergradientToC.setAlphaF(0.35);
        solar.hoverPurecolor = "#E56464";
        solar.splitColor = "#FF7272";
        solar.pressgradientFromC = "#FF7272";
        solar.pressgradientFromC.setAlphaF(0.3);
        solar.pressgradientToC = solar.pressgradientFromC;
        solar.pressPurecolor = solar.Purecolor;
        solar.pressgradientToC.setAlphaF(0.4);
        solar.pressgradientFromC.setAlphaF(0.4);
        solar.pressPurecolor.setAlphaF(0.1);
        m_vScheduleColor.append(solar);
    }
}

CScheduleDataManage *CScheduleDataManage::getScheduleDataManage()
{
    return m_vscheduleDataManage;
}

void CScheduleDataManage::clear()
{
}

CScheduleDataManage::CScheduleDataManage()
{
//    m_GetAllYearScheduleInfo = new YearScheduleInfo();
    CSchedulesColor workC;
    workC.type = 1;
    workC.gradientFromC = "#FBCEB7";
    workC.gradientToC = "#FA9D9A";
    workC.Purecolor = "#F85566";
    workC.Purecolor.setAlphaF(0.2);
    workC.shadowcolor = "#FB2525";
    workC.shadowcolor.setAlphaF(0.5);
    workC.textColor = "#000000";
    workC.timeColor = "#B54A4B";
    m_vScheduleColor.append(workC);

    CSchedulesColor lifeC;
    lifeC.type = 2;
    lifeC.gradientFromC = "#B7E6FB";
    lifeC.gradientToC = "#D4FFB3";
    lifeC.Purecolor = "#6FFF00";
    lifeC.Purecolor.setAlphaF(0.2);
    lifeC.shadowcolor = "#82D245";
    lifeC.textColor = "#000000";
    lifeC.timeColor = "#53A316";
    m_vScheduleColor.append(lifeC);

    CSchedulesColor otherC;
    otherC.type = 3;
    otherC.gradientFromC = "#FBE9B7";
    otherC.gradientToC = "#DFB3FF";
    otherC.Purecolor = "#D191FF";
    otherC.Purecolor.setAlphaF(0.2);
    otherC.shadowcolor = "#BA60FA";
    otherC.textColor = "#000000";
    otherC.timeColor = "#8548B1";
    m_vScheduleColor.append(otherC);

    CSchedulesColor solar;
    solar.type = 4;
    solar.dotColor = "#FF7272";
    solar.dotColor.setAlphaF(1);
    solar.gradientFromC = "#FF7272";
    solar.gradientFromC.setAlphaF(0.3);
    solar.gradientToC = "#FF7272";
    solar.gradientToC.setAlphaF(0.3);
    solar.Purecolor = "#FF7272";
    solar.Purecolor.setAlphaF(0.3);
    solar.shadowcolor = "#BA60FA";
    solar.textColor = "#000000";
    solar.timeColor = "#8548B1";
    m_vScheduleColor.append(solar);
}

CScheduleDataManage::~CScheduleDataManage()
{
}
