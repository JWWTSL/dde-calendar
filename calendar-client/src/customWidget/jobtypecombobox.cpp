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
#include "jobtypecombobox.h"

#include <DPushButton>

#include <QLayout>
#include <QPainter>
#include <QKeyEvent>
#include <QAbstractItemView>
#include <QStandardItemModel>

JobTypeComboBox::JobTypeComboBox(QWidget *parent) : DComboBox(parent)
{
    initUI();
    //不启用自动匹配
    setAutoCompletion(false);
    //设置不接受回车键插入
    setInsertPolicy(QComboBox::NoInsert);
    connect(this, QOverload<int>::of(&QComboBox::highlighted), [this](int index) {
        view()->setFocus();
        m_hoverSelectedIndex = index;
    });
}

JobTypeComboBox::~JobTypeComboBox()
{
    return;
}

int JobTypeComboBox::getCurrentJobTypeNo()
{
    return m_lstJobType[this->currentIndex()].getJobTypeNo();
}

void JobTypeComboBox::setCurrentJobTypeNo(int strJobTypeNo)
{
    for (int i = 0; i < m_lstJobType.size(); i++) {
        if (strJobTypeNo == m_lstJobType[i].getJobTypeNo()) {
            this->setCurrentIndex(i);
            break;
        }
    }
    return;
}

bool JobTypeComboBox::updateJobType()
{
    QString strColorHex;
    QString strJobType;

    m_lstJobType = JobTypeInfoManager::instance()->getJobTypeList();

    clear(); //更新前先清空原有列表
    for (m_itemNumIndex = 0; m_itemNumIndex < m_lstJobType.size(); m_itemNumIndex++) {
        strColorHex = m_lstJobType[m_itemNumIndex].getColorHex();
        strJobType = m_lstJobType[m_itemNumIndex].getJobTypeName();

        if (strColorHex.isEmpty() || strJobType.isEmpty()) {
            continue;
        }
        addJobTypeItem(m_itemNumIndex, m_lstJobType[m_itemNumIndex].getColorHex(), m_lstJobType[m_itemNumIndex].getJobTypeName());
    }
    return true;
}

void JobTypeComboBox::addJobTypeItem(int idx, QString strColorHex, QString strJobType)
{
    //绘制的pixmap为基准大小的4倍，防止缩放时出现齿距
    QSize size(64, 64);
    QPixmap pixmap(size);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setRenderHints(QPainter::Antialiasing);
    painter.setBrush(QColor(strColorHex));
    painter.setPen(QColor(strColorHex));
    painter.drawRoundedRect(0, 0, 64, 64, 16, 16);

    //描边
    QPainterPath path;
    path.addRoundedRect(0, 0, 64, 64, 16, 16);
    path.addRoundedRect(4, 4, 56, 56, 16, 16);
    painter.setBrush(QColor(0, 0, 0, 255 / 10));
    painter.drawPath(path);

    insertItem(idx, QIcon(pixmap), tr(strJobType.toLocal8Bit()));
}

void JobTypeComboBox::initUI()
{
    setEditable(false);
    setIconSize(QSize(16, 16));
    view()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void JobTypeComboBox::setItemSelectable(bool status)
{
    if (-1 == m_hoverSelectedIndex) {
        return;
    }
    //更改当前列表框里的高亮项的可选择状态设置，将其设置为不可选中状态可实现失去选中效果，待聚焦后再恢复过来
    QStandardItemModel *pItemModel = qobject_cast<QStandardItemModel *>(model());
    pItemModel->item(m_hoverSelectedIndex)->setSelectable(status);

    //设置“添加按键”按钮的高亮状态
    if (nullptr != m_addBtn) {
        m_addBtn->setHighlight(!status);
    }
}

void JobTypeComboBox::addCustomWidget(QFrame *viewContainer)
{
    if (viewContainer) {
        if (nullptr == m_customWidget) {
            //获取原控件布局
            QBoxLayout *layout = qobject_cast<QBoxLayout *>(viewContainer->layout());
            //自定义控件
            QVBoxLayout *hLayout = new QVBoxLayout;
            DPushButton *splitter = new DPushButton(this);
            m_addBtn = new CPushButton();
            splitter->setFixedHeight(2);
            splitter->setFocusPolicy(Qt::NoFocus);
            hLayout->addWidget(splitter);
            hLayout->addWidget(m_addBtn);
            hLayout->setContentsMargins(0, 0, 0, 0);
            hLayout->setSpacing(0);
            m_customWidget = new QWidget(this);
            m_customWidget->setFixedHeight(35);
            m_customWidget->setLayout(hLayout);
            //添加自定义控件到最后
            layout->insertWidget(-1, m_customWidget);
            viewContainer->setFixedHeight(viewContainer->height() + m_customWidget->height());
            //设置最大高度为400
            if (viewContainer->height() > 400) {
                viewContainer->setFixedHeight(400);
            }
            //设置可接受tab焦点
            m_addBtn->setFocusPolicy(Qt::TabFocus);
            setTabOrder(view(), m_addBtn);
            //注册事件监听
            m_addBtn->installEventFilter(this);
            view()->installEventFilter(this);
            connect(m_addBtn, &CPushButton::clicked, this, &JobTypeComboBox::slotBtnAddItemClicked);
        }
    }
}

void JobTypeComboBox::showPopup()
{
    //重置icon大小
    setItemSelectable(true);
    setIconSize(QSize(16, 16));
    //设置为不可编辑模式
    setEditable(false);
    emit activated(0);
    DComboBox::showPopup();

    //获取下拉视图容器
    QFrame *viewContainer = findChild<QFrame *>();
    if (m_lstJobType.size() < 20) {
        //添加自定义布局
        addCustomWidget(viewContainer);
    }
}

bool JobTypeComboBox::eventFilter(QObject *obj, QEvent *event)
{
    if (view() == obj && (event->type() == QEvent::Enter)) {
        view()->setFocus();
    } else if (m_addBtn == obj && (event->type() == QEvent::Enter)) {
        m_addBtn->setFocus();
    } else if (view() == obj && event->type() == QEvent::FocusIn) {
        //列表框控件焦点进入事件
        setItemSelectable(true);
    } else if (m_addBtn == obj && event->type() == QEvent::FocusIn) {
        //“添加按键”控件焦点进入事件
        setItemSelectable(false);
    } else if (event->type() == QEvent::KeyPress) {
        QKeyEvent *kEvent = dynamic_cast<QKeyEvent *>(event);
        if (view() == obj && kEvent->key() == Qt::Key_Down) {
            //焦点在列表框时的下方向按键按下事件
            if (m_addBtn->isHighlight()) {
                return true;
            }

            if (m_hoverSelectedIndex == m_itemNumIndex - 1) {
                //列表框到达最后一项时的下方向按键按下事件
                //将焦点转移到“添加按键”控件上
                m_addBtn->setFocus();
            }
        } else if (m_addBtn == obj && kEvent->key() == Qt::Key_Up) {
            //焦点在m_addBtn时的上方向按键按下事件
            if (m_addBtn->isHighlight()) {
                //将焦点转移到列表控件上
                view()->setFocus();
            }
        } else if (m_addBtn->isHighlight() && kEvent->key() == Qt::Key_Return) {
            //回车事件
            slotBtnAddItemClicked();
        }

        //过滤掉m_addBtn的所有按键事件
        if (m_addBtn == obj) {
            return true;
        }
    }
    return DComboBox::eventFilter(obj, event);
}

void JobTypeComboBox::slotBtnAddItemClicked()
{
    JobTypeComboBox::hidePopup();
    setIconSize(QSize(0, 0));
    setEditable(true);
    setCurrentText("");
    emit signalAddTypeBtnClicked();
    return;
}
