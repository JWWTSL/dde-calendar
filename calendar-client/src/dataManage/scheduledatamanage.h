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
#ifndef SCHEDULEDATAMANAGE_H
#define SCHEDULEDATAMANAGE_H
#include "src/scheduledatainfo.h"

#include <DGuiApplicationHelper>

#include <QThread>
#include <QDate>
#include <QMutex>

DGUI_USE_NAMESPACE
struct CSchedulesColor {
    QColor normalColor; //正常状态颜色
    QColor hoverColor; //鼠标悬浮颜色
    QColor pressColor; //鼠标点击颜色
    QColor hightColor; //高亮色
    QColor orginalColor; //最初的颜色
};

class CScheduleDataManage
{
public:
    static CScheduleDataManage *getScheduleDataManage();
    CSchedulesColor getScheduleColorByType(int type);
    static QColor getSystemActiveColor();
    static QColor getTextColor();
    int getTheme() const
    {
        return m_theme;
    }
private:
    CScheduleDataManage();
    ~CScheduleDataManage();
private:
    int m_theme = 0;
    static CScheduleDataManage *m_vscheduleDataManage;
};

class JobTypeInfoManager
{
private:
    JobTypeInfoManager();
public:
    static JobTypeInfoManager *instance();
    /**
     * @brief updateInfo  更新信息
     */
    void updateInfo();
    //查询列表、返回列表
    QList<JobTypeInfo> getJobTypeList()
    {
        return m_lstJobType;
    }

    QList<JobTypeColorInfo> getJobTypeColorList()
    {
        return  m_lstJobTypeColor;
    }

    /**
     * @brief isSysJobTypeColor   是否是默认颜色
     * @param colorTypeNo         颜色类型编号
     * @return                    是否是默认颜色
     */
    bool isSysJobTypeColor(int colorTypeNo);
    /**
     * @brief getSysJobTypeColor  获取指定编号的默认颜色
     * @param colorTypeNo         颜色类型编号
     * @param jobTypeColorInfo    颜色信息
     * @return                    操作结果
     */
    bool getSysJobTypeColor(int colorTypeNo, JobTypeColorInfo &jobTypeColorInfo);
    //查询日程类型
    bool getJobTypeByNo(int iNo, JobTypeInfo &jobType);
    //查询日程类型颜色
    bool getJobTypeColorByNo(int iNo, JobTypeColorInfo &jobType);

    //查询日程类型名称是否重复
    bool isJobTypeNameUsed(QString strName);
    //根据日程类型信息判断修改的日程类型名称是否与其它日程类型名称重复
    bool isJobTypeNameUsed(const JobTypeInfo &info);

    //获取自定义日程类型下一个编号
    int getNextTypeNo();
    //获取自定义日程类型颜色下一个编号
    int getNextColorTypeNo();

    //通知单,添加回调函数
    void addToNoticeBill(QObject *obj, const QByteArray &method);
    //通知单,移除回调函数
    void removeFromNoticeBill(QObject *obj);
private:
    QList<JobTypeInfo> m_lstJobType;
    QList<JobTypeColorInfo> m_lstJobTypeColor;
    QMap<QObject *, QByteArray> noticeObjBill;//当日程类型改变时，会触发notice对应的回调函数
};
#endif // SCHEDULEVIEW_H
