/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     hejinghai <hejinghai@uniontech.com>
*
* Maintainer: hejinghai <hejinghai@uniontech.com>
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
#include "test_graphicsview.h"
#include "graphicsItem/scheduleitem.h"
#include <QGraphicsView>

test_graphicsview::test_graphicsview()
{
    cGraphicsView = new CGraphicsView(nullptr, CGraphicsView::WeekPos);
}

test_graphicsview::~test_graphicsview()
{
    delete cGraphicsView;
}

//void CGraphicsView::setMargins(int left, int top, int right, int bottom)
TEST_F(test_graphicsview, setMargins)
{
    int left = 50;
    int top = 50;
    int right = 50;
    int bottom = 50;
    cGraphicsView->setMargins(left, top, right, bottom);
    assert(cGraphicsView->m_margins.left() == 50);
}

//void CGraphicsView::setTheMe(int type)
TEST_F(test_graphicsview, setTheMe)
{
    int type = 0;
    cGraphicsView->setTheMe(type);

    type = 2;
    cGraphicsView->setTheMe(type);
}

//bool CGraphicsView::MeetCreationConditions(const QDateTime &date)
TEST_F(test_graphicsview, MeetCreationConditions)
{
    QString strDate = "2020-12-28 12:24:36";
    QDateTime date = QDateTime::fromString(strDate, "yyyy-MM-dd hh:mm:ss");

    cGraphicsView->MeetCreationConditions(date);
}

//void CGraphicsView::setRange(int w, int h, QDate begindate, QDate enddate, int rightmagin)
TEST_F(test_graphicsview, setRange)
{
    int w = 20;
    int h = 20;
    QDate begindate(2020, 11, 11);
    QDate enddate(2020, 11, 31);
    int rightmagin = 10;

    cGraphicsView->setRange(w, h, begindate, enddate, rightmagin);
    cGraphicsView->setRange(begindate, enddate);
}

//void CGraphicsView::setCurrentDate(const QDateTime &currentDate)
TEST_F(test_graphicsview, setCurrentDate)
{
    QDateTime date = QDateTime::currentDateTime();
    cGraphicsView->setCurrentDate(date);
}

//void CGraphicsView::setInfo(const QVector<ScheduleDataInfo> &info)
TEST_F(test_graphicsview, setInfo)
{
    QVector<ScheduleDataInfo> infos = QVector<ScheduleDataInfo> {};
    cGraphicsView->setInfo(infos);
}

bool MScheduleTimeThan(const ScheduleDataInfo &s1, const ScheduleDataInfo &s2);
TEST_F(test_graphicsview, MScheduleTimeThan)
{
    ScheduleDataInfo info1 = ScheduleDataInfo{};
    ScheduleDataInfo info2 = ScheduleDataInfo{};
    MScheduleTimeThan(info1, info2);
}

//void CGraphicsView::upDateInfoShow(const CGraphicsView::DragStatus &status, const ScheduleDataInfo &info)
TEST_F(test_graphicsview, upDateInfoShow)
{
    ScheduleDataInfo info = ScheduleDataInfo{};
    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::IsCreate, info);
    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::ChangeEnd, info);
    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::ChangeBegin, info);
    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::ChangeWhole, info);
    cGraphicsView->upDateInfoShow(CGraphicsView::DragStatus::NONE, info);
}

//QDateTime CGraphicsView::getPosDate(const QPoint &p)
TEST_F(test_graphicsview, getPosDate)
{
    QDateTime dateTime;
    QPoint point(50, 40);
    dateTime = cGraphicsView->getPosDate(point);
}

//void CGraphicsView::ShowSchedule(DragInfoItem *infoitem)
//TEST_F(test_graphicsview, ShowSchedule)
//{
//    QPoint point(50, 40);
//    QGraphicsItem *listItem = itemAt(point);
//    DragInfoItem *infoitem = dynamic_cast<DragInfoItem *>(listItem);
//    CScheduleItem *scheduleitem = dynamic_cast<CScheduleItem *>(infoitem);
//    qInfo() << scheduleitem->getType();
//    cGraphicsView->ShowSchedule(infoitem);
//}

//void CGraphicsView::addSchduleItem(const ScheduleDataInfo &info, QDate date, int index, int totalNum, int type, int viewtype, int maxnum)
TEST_F(test_graphicsview, addSchduleItem)
{
    ScheduleDataInfo info = ScheduleDataInfo{};
    QDate date(2020, 12, 28);
    int index = 1;
    int totalNum = 2;
    int type = 2;
    int viewtype = 1;
    int maxnum = 3;
    cGraphicsView->addSchduleItem(info, date, index, totalNum, type, viewtype, maxnum);
}

//void CGraphicsView::scheduleClassificationType(QVector<ScheduleDataInfo> &scheduleInfolist, QList<ScheduleclassificationInfo> &info)
TEST_F(test_graphicsview, scheduleClassificationType)
{
    QVector<ScheduleDataInfo> scheduleInfolist = QVector<ScheduleDataInfo> {};
    QList<ScheduleclassificationInfo> info = QList<ScheduleclassificationInfo> {};
    cGraphicsView->scheduleClassificationType(scheduleInfolist, info);
}

//void CGraphicsView::slotDoubleEvent(int type)
TEST_F(test_graphicsview, slotDoubleEvent)
{
    int type = 1;
    cGraphicsView->slotDoubleEvent(type);
}

//void CGraphicsView::slotScrollBar()
TEST_F(test_graphicsview, slotScrollBar)
{
    cGraphicsView->slotScrollBar();
}

//void CGraphicsView::slotUpdateScene()
TEST_F(test_graphicsview, slotUpdateScene)
{
    cGraphicsView->slotUpdateScene();
}

//void CGraphicsView::scrollBarValueChangedSlot()
TEST_F(test_graphicsview, scrollBarValueChangedSlot)
{
    cGraphicsView->scrollBarValueChangedSlot();
}

//ScheduleDataInfo CGraphicsView::getScheduleInfo(const QDateTime &beginDate, const QDateTime &endDate)
TEST_F(test_graphicsview, getScheduleInfo)
{
    QString begin = "2020-12-01 12:24:36";
    QDateTime begindate = QDateTime::fromString(begin, "yyyy-MM-dd hh:mm:ss");
    QString end = "2020-12-21 12:24:36";
    QDateTime enddate = QDateTime::fromString(end, "yyyy-MM-dd hh:mm:ss");

    cGraphicsView->getScheduleInfo(begindate, enddate);
}

//bool CGraphicsView::IsEqualtime(const QDateTime &timeFirst, const QDateTime &timeSecond)
TEST_F(test_graphicsview, IsEqualtime)
{
    QString begin = "2020-12-01 12:24:36";
    QDateTime begindate = QDateTime::fromString(begin, "yyyy-MM-dd hh:mm:ss");
    QString end = "2020-12-21 12:24:36";
    QDateTime enddate = QDateTime::fromString(end, "yyyy-MM-dd hh:mm:ss");

    cGraphicsView->IsEqualtime(begindate, enddate);
}

//bool CGraphicsView::JudgeIsCreate(const QPointF &pos)
TEST_F(test_graphicsview, JudgeIsCreate)
{
    QPointF pos(20, 20);
    bool getBool = cGraphicsView->JudgeIsCreate(pos);
    qInfo() << getBool;
}

//void CGraphicsView::RightClickToCreate(QGraphicsItem *listItem, const QPoint &pos)
TEST_F(test_graphicsview, RightClickToCreate)
{
//    QGraphicsItem *listItem = nullptr;
//    QPoint pos(20, 20);
    //cGraphicsView->RightClickToCreate(listItem, pos);
}

//QDateTime CGraphicsView::getDragScheduleInfoBeginTime(const QDateTime &moveDateTime)
TEST_F(test_graphicsview, getDragScheduleInfoBeginTime)
{
    QString begin = "2020-12-01 12:24:36";
    QDateTime begindate = QDateTime::fromString(begin, "yyyy-MM-dd hh:mm:ss");

    cGraphicsView->getDragScheduleInfoBeginTime(begindate);
}

//QDateTime CGraphicsView::getDragScheduleInfoEndTime(const QDateTime &moveDateTime)
TEST_F(test_graphicsview, getDragScheduleInfoEndTime)
{
    QString end = "2020-12-21 12:24:36";
    QDateTime enddate = QDateTime::fromString(end, "yyyy-MM-dd hh:mm:ss");

    cGraphicsView->getDragScheduleInfoEndTime(enddate);
}

//void CGraphicsView::keepCenterOnScene()
TEST_F(test_graphicsview, keepCenterOnScene)
{
    cGraphicsView->keepCenterOnScene();
}

//void CGraphicsView::setTime(QTime time)
TEST_F(test_graphicsview, setTime)
{
    QTime time(7, 30, 5, 100);

    cGraphicsView->setTime(time);
}

//void CGraphicsView::updateInfo()
TEST_F(test_graphicsview, updateInfo)
{
    cGraphicsView->updateInfo();
}

////void CGraphicsView::mousePressEvent(QMouseEvent *event)
//TEST_F(test_graphicsview, mousePressEvent)
//{
//    QMouseEvent *event;
//    cGraphicsView->mousePressEvent(event);
//    assert(1 == 1);
//}
