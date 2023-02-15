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
#include "cscheduleoperation.h"

#include <QJsonArray>
#include <QJsonDocument>

CScheduleDataManage *CScheduleDataManage::m_vscheduleDataManage = new CScheduleDataManage;

CSchedulesColor CScheduleDataManage::getScheduleColorByType(int type)
{
    CSchedulesColor color;
    JobTypeColorInfo colorinfo;
    bool isOk = false;
    if (type != 4) {
        //如果不是节假日
        JobTypeInfo typeInfo;
        //根据类型获取日程类型信息getJobTypeByNo
        JobTypeInfoManager::instance()->getJobTypeByNo(type, typeInfo);
        //根据类型关联的颜色编号获取对应的颜色
        isOk = JobTypeInfoManager::instance()->getJobTypeColorByNo(typeInfo.getColorTypeNo(), colorinfo);
    } else {
        //节假日 颜色变化为8
        isOk = JobTypeInfoManager::instance()->getJobTypeColorByNo(8, colorinfo);
    }

    if (isOk) {
        color.orginalColor = QColor(colorinfo.getColorHex());
        color.normalColor = color.orginalColor;
        color.normalColor.setAlphaF(0.2);
        color.pressColor = color.orginalColor;
        color.pressColor.setAlphaF(0.35);

        color.hoverColor = color.orginalColor;
        color.hoverColor.setAlphaF(0.3);

        color.hightColor = color.orginalColor;
        color.hightColor.setAlphaF(0.35);

    } else {
        //获取颜色失败
        qWarning() << "get type color fail ,type:" << type;
    }

    return color;
}

QColor CScheduleDataManage::getSystemActiveColor()
{
    return DGuiApplicationHelper::instance()->applicationPalette().highlight().color();
}

QColor CScheduleDataManage::getTextColor()
{
    return DGuiApplicationHelper::instance()->applicationPalette().text().color();
}

CScheduleDataManage *CScheduleDataManage::getScheduleDataManage()
{
    return m_vscheduleDataManage;
}

CScheduleDataManage::CScheduleDataManage()
{
}

CScheduleDataManage::~CScheduleDataManage()
{
}

void JobTypeInfoManager::updateInfo()
{
    CScheduleOperation so;
    so.getJobTypeList(this->m_lstJobType);
    so.getColorTypeList(this->m_lstJobTypeColor);
    return;
}
JobTypeInfoManager::JobTypeInfoManager()               //私有静态构造函数
{
}
JobTypeInfoManager *JobTypeInfoManager::instance()
{
    static JobTypeInfoManager instance;             //局部静态变量
    return &instance;
}
/**
 * @brief isSysJobTypeColor   是否是默认颜色
 * @param colorTypeNo         颜色类型编号
 * @return                    是否是默认颜色
 */
bool JobTypeInfoManager::isSysJobTypeColor(int colorTypeNo)
{
    for (JobTypeColorInfo jobTypeColorInfo : m_lstJobTypeColor) {
        if ((jobTypeColorInfo.getTypeNo() == colorTypeNo) && (jobTypeColorInfo.getAuthority() == 1)) { //设定1为展示权限
            return true;
        }
    }
    return  false;
}
/**
 * @brief getSysJobTypeColor  获取指定编号的默认颜色
 * @param colorTypeNo         颜色类型编号
 * @param jobTypeColorInfo    颜色信息
 * @return                    操作结果
 */
bool JobTypeInfoManager::getSysJobTypeColor(int colorTypeNo, JobTypeColorInfo &jobTypeColorInfo)
{
    for (JobTypeColorInfo _jobTypeColorInfo : m_lstJobTypeColor) {
        if ((_jobTypeColorInfo.getTypeNo() == colorTypeNo) && (_jobTypeColorInfo.getAuthority() == 1)) { //设定1为展示权限
            jobTypeColorInfo = _jobTypeColorInfo;
            return true;
        }
    }
    return  false;
}

//查询日程类型
bool JobTypeInfoManager::getJobTypeByNo(int iNo, JobTypeInfo &jobType)
{
    for (JobTypeInfo &jb : m_lstJobType) {
        if (jb.getJobTypeNo() == iNo) {
            jobType = jb;
            return true;
        }
    }
    return false;
}
//查询日程类型颜色
bool JobTypeInfoManager::getJobTypeColorByNo(int iNo, JobTypeColorInfo &jobType)
{
    for (JobTypeColorInfo &color : m_lstJobTypeColor) {
        if (color.getTypeNo() == iNo) {
            jobType = color;
            return true;
        }
    }
    return false;
}

//查询日程类型名称是否重复
bool JobTypeInfoManager::isJobTypeNameUsed(QString strName)
{
    for (JobTypeInfo &jb : m_lstJobType) {
        if (jb.getJobTypeName() == strName) {
            return true;
        }
    }
    return false;
}
//获取自定义日程类型下一个编号
int JobTypeInfoManager::getNextTypeNo()
{
    int typeNo = 1;

    for (JobTypeInfo &job : m_lstJobType) {
        if (job.getJobTypeNo() >= typeNo) {
            typeNo = job.getJobTypeNo() + 1;
        }
    }
    if (4 == typeNo) { //节日类型占用
        typeNo += 1;
    }
    return typeNo;
}
//获取自定义日程类型颜色下一个编号
int JobTypeInfoManager::getNextColorTypeNo()
{
    int colorTypeNo = 1;
    for (JobTypeColorInfo &jobColor : m_lstJobTypeColor) {
        if (jobColor.getTypeNo() >= colorTypeNo) {
            colorTypeNo = jobColor.getTypeNo() + 1;
        }
    }
    return colorTypeNo;
}
