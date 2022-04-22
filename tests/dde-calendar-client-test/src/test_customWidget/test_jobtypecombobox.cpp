/*
* Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd.
*
* Author:     leilong  <leilong@uniontech.com>
*
* Maintainer: leilong  <leilong@uniontech.com>
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
#include "test_jobtypecombobox.h"
#include "../third-party_stub/stub.h"

static QList<JobTypeInfo> jobtypecombobox_stub_JobTypeInfos1()
{
    QList<JobTypeInfo> infos;
    infos.push_back(JobTypeInfo(1, "1", 0, "#000000"));
    infos.push_back(JobTypeInfo(2));
    infos.push_back(JobTypeInfo(3, "3", 2, "#000000"));

    return infos;
}

static QList<JobTypeInfo> jobtypecombobox_stub_JobTypeInfos2()
{
    QList<JobTypeInfo> infos;
    infos.push_back(JobTypeInfo(1, "1", 0, "#000000"));
    infos.push_back(JobTypeInfo(2, "2", 1, "#000000"));
    infos.push_back(JobTypeInfo(3, "3", 2, "#000000"));

    return infos;
}

static int jobtypecombobox_stub_flase()
{
    return 0;
}

test_jobtypecombobox::test_jobtypecombobox()
{

}

TEST_F(test_jobtypecombobox, updateJobType_001)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos2);
    EXPECT_TRUE(mWidget->updateJobType());
}

TEST_F(test_jobtypecombobox, getCurrentJobTypeNo_001)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos1);
    stub.set(ADDR(QComboBox, currentIndex), jobtypecombobox_stub_flase);
    mWidget->updateJobType();
    mWidget->getCurrentJobTypeNo();
}

TEST_F(test_jobtypecombobox, setCurrentJobTypeNo_001)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos1);
    mWidget->updateJobType();
    mWidget->setCurrentJobTypeNo(3);
}

TEST_F(test_jobtypecombobox, slotBtnAddItemClicked_001)
{
    mWidget->slotBtnAddItemClicked();
    EXPECT_TRUE(mWidget->isEditable());
    EXPECT_TRUE(mWidget->currentText().isEmpty());
}

TEST_F(test_jobtypecombobox, showPopup_001)
{
    mWidget->showPopup();
    EXPECT_FALSE(mWidget->isEditable());
}

TEST_F(test_jobtypecombobox, eventFilter_001)
{
    QPointF point(1, 1);
    QEnterEvent e(point, point, point);
    mWidget->showPopup();
    mWidget->eventFilter(mWidget->m_addBtn, &e);
}

TEST_F(test_jobtypecombobox, eventFilter_002)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos2);
    mWidget->updateJobType();
    QPointF point(1, 1);
    QFocusEvent e(QEvent::FocusIn);
    mWidget->showPopup();
    mWidget->eventFilter(mWidget->m_addBtn, &e);
}

TEST_F(test_jobtypecombobox, eventFilter_003)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos2);
    mWidget->updateJobType();
    QPointF point(1, 1);
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
    mWidget->showPopup();
    mWidget->m_addBtn->setHighlight(true);
    mWidget->eventFilter(mWidget->m_addBtn, &e);
    EXPECT_TRUE(mWidget->m_addBtn->isHighlight());
}

TEST_F(test_jobtypecombobox, eventFilter_004)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos2);
    mWidget->updateJobType();
    QPointF point(1, 1);
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    mWidget->showPopup();
    mWidget->m_addBtn->setHighlight(true);
    mWidget->eventFilter(mWidget->m_addBtn, &e);
    EXPECT_TRUE(mWidget->m_addBtn->isHighlight());
}

TEST_F(test_jobtypecombobox, eventFilter_005)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos2);
    mWidget->updateJobType();
    QPointF point(1, 1);
    QKeyEvent e(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
    mWidget->showPopup();
    mWidget->m_addBtn->setHighlight(true);
    mWidget->eventFilter(mWidget->m_customWidget, &e);
    EXPECT_TRUE(mWidget->m_addBtn->isHighlight());
}

TEST_F(test_jobtypecombobox, initUI_001)
{
    mWidget->initUI();
    EXPECT_FALSE(mWidget->isEditable());
}

TEST_F(test_jobtypecombobox, addJobTypeItem_001)
{
    mWidget->addJobTypeItem(1, "#000000", "");
}

TEST_F(test_jobtypecombobox, addCustomWidget_001)
{
    QFrame *viewContainer = mWidget->findChild<QFrame *>();
    mWidget->addCustomWidget(viewContainer);
    EXPECT_TRUE(mWidget->m_addBtn != nullptr);
}

TEST_F(test_jobtypecombobox, setItemSelectable_001)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos2);
    mWidget->updateJobType();
    mWidget->showPopup();
    mWidget->setItemSelectable(true);
    EXPECT_FALSE(mWidget->m_addBtn->isHighlight());
}

TEST_F(test_jobtypecombobox, setItemSelectable_002)
{
    Stub stub;
    stub.set(ADDR(JobTypeInfoManager, getJobTypeList), jobtypecombobox_stub_JobTypeInfos2);
    mWidget->updateJobType();
    mWidget->showPopup();
    mWidget->setItemSelectable(false);
}
