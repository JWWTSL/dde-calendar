/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     uniontech  <uniontech@uniontech.com>
*
* Maintainer: uniontech  <chenhaifeng@uniontech.com>
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
#ifndef DRAGINFOGRAPHICSVIEW_H
#define DRAGINFOGRAPHICSVIEW_H
#include "draginfoitem.h"

#include <DGraphicsView>

#include <QDate>
#include <QDrag>

DWIDGET_USE_NAMESPACE

class CScheduleDataManage;
class DragInfoGraphicsView : public DGraphicsView
{
    Q_OBJECT
public:
    explicit DragInfoGraphicsView(DWidget *parent = nullptr);
    ~DragInfoGraphicsView() override;
public:
//鼠标位置
    enum PosInItem {LEFT,MIDDLE,RIGHT,TOP,BOTTOM};
    //鼠标移动状态
    enum DragStatus {IsCreate =0,ChangeBegin =1,ChangeEnd =2,ChangeWhole =3,NONE =4};
    /**
     * @brief The TouchState enum   触摸状态
     */
    enum TouchState{
        TS_NONE             //默认状态
        ,TS_PRESS           //点击
        ,TS_DRAG_MOVE       //拖拽移动
        ,TS_SLIDE           //滑动
        ,TS_LONG_PRESS       //长按
    };

    int getDragStatus() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragLeaveEvent(QDragLeaveEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    bool event(QEvent *e) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    void slotCreate();
    void setPressSelectInfo(const ScheduleDtailInfo &info);
    void updateScheduleInfo(const ScheduleDtailInfo &info);
    void DragPressEvent(const QPoint &pos,DragInfoItem *item);
    void mouseReleaseScheduleUpdate();
    /**
     * @brief mousePress        鼠标左击事件处理
     * @param point             左击坐标
     */
    void mousePress(const QPoint &point);
protected:
    void DeleteItem(const ScheduleDtailInfo &info);
protected:
    virtual void setDragPixmap(QDrag *drag,DragInfoItem *item);
    virtual void slotCreate(const QDateTime &date);
    //符合创建条件
    virtual bool MeetCreationConditions(const QDateTime &date) =0;
    virtual void upDateInfoShow(const DragStatus &status = NONE,const ScheduleDtailInfo &info =ScheduleDtailInfo()) =0;
    virtual QDateTime getPosDate(const QPoint &p) =0;
    virtual void MoveInfoProcess(ScheduleDtailInfo &info,const QPointF &pos) = 0;
    virtual PosInItem getPosInItem(const QPoint &p,const QRectF &itemRect) =0;
    virtual ScheduleDtailInfo getScheduleInfo(const QDateTime &beginDate,const QDateTime &endDate);
    virtual void ShowSchedule(DragInfoItem *infoitem);
    //设置主题
    virtual void setTheMe(int type = 0) =0;
    //判断时间是否相等
    virtual bool IsEqualtime(const QDateTime &timeFirst,const QDateTime &timeSecond) =0;
    //根据鼠标移动的距离判断是否创建日程
    virtual bool JudgeIsCreate(const QPointF &pos) =0;
    virtual void RightClickToCreate(QGraphicsItem *listItem,const QPoint &pos) =0;
    /**
     * @brief getDragScheduleInfoBeginTime      获取拖拽日程开始时间
     * @param moveDateTime                      当前鼠标移动坐标对应的时间
     * @return
     */
    virtual QDateTime getDragScheduleInfoBeginTime(const QDateTime &moveDateTime) =0;
    /**
     * @brief getDragScheduleInfoEndTime    获取拖拽日程结束时间
     * @param moveDateTime                  当前鼠标移动坐标对应的时间
     * @return
     */
    virtual QDateTime getDragScheduleInfoEndTime(const QDateTime &moveDateTime) =0;
    /**
     * @brief slideEvent            触摸滑动事件处理
     * @param startPoint            触摸开始坐标
     * @param stopPort              触摸结束坐标
     */
    virtual void slideEvent(QPointF &startPoint,QPointF &stopPort);
signals:
    /**
     * @brief signalAngleDelta      发送滚动信号滚动相对量
     * @param delta     滚动相对量
     */
    void signalAngleDelta(int delta);
    //更新获取日程信息
    void signalsUpdateShcedule();
    void signalViewtransparentFrame(const int id = 0);
    /**
     * @brief signalScheduleShow        发送日程提示框信号
     * @param isShow                    是否显示
     * @param out                       显示的日程信息
     */
    void signalScheduleShow(const bool isShow, const ScheduleDtailInfo &out = ScheduleDtailInfo());
protected:
    int                                 m_themetype = 0;
    QGraphicsScene *m_Scene = nullptr;
    bool                                m_press = false;

    QAction *m_createAction = nullptr; // 创建日程
    QAction *m_editAction = nullptr;
    QAction *m_deleteAction = nullptr;
    DMenu *m_rightMenu = nullptr;

    QDateTime                           m_createDate;
    DragStatus                          m_DragStatus =NONE;
    bool                                m_isCreate;
    QDateTime                           m_PressDate;
    QDateTime                           m_MoveDate;
    QPoint                              m_PressPos;
    ScheduleDtailInfo                   m_DragScheduleInfo;
    QDateTime                           m_InfoBeginTime;
    QDateTime                           m_InfoEndTime;
    QDrag *m_Drag = nullptr;
    //点击的原始info
    ScheduleDtailInfo                   m_PressScheduleInfo;
    QRectF                              m_PressRect;
    /**
     * @brief m_TouchBeginPoint     触摸开始坐标
     */
    QPointF         m_TouchBeginPoint;
    /**
     * @brief m_TouchBeginTime      触摸点击屏幕的事件
     */
    qint64          m_TouchBeginTime;
    /**
     * @brief m_touchState          触摸状态
     */
    TouchState      m_touchState;
    /**
     * @brief m_touchDragMoveState      触摸拖拽移动状态
     * 0 原始状态
     * 1 拖拽确认，移动的时候触发点击事件
     * 2 拖拽移动
     */
    int             m_touchDragMoveState;

};

#endif // DRAGINFOGRAPHICSVIEW_H
