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
#ifndef MYSCHCEDULEVIEW_H
#define MYSCHCEDULEVIEW_H

#include "schedulestructs.h"

#include <DDialog>
#include <DPushButton>
#include <DSuggestButton>
#include <DTextEdit>

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QScrollArea>
#include <QScrollBar>

DWIDGET_USE_NAMESPACE

class CMySchceduleView : public DDialog
{
    Q_OBJECT
public:
    explicit CMySchceduleView(const ScheduleDtailInfo &schduleInfo,QWidget *parent = nullptr);
    ~CMySchceduleView() override;
    ScheduleDtailInfo getSchedules()
    {
        return  m_scheduleInfo;
    }
signals:
    void signalsEditorDelete(int type = 0);
    void signalViewtransparentFrame(int type);
public slots:
    void slotEditBt(int buttonIndex, QString buttonName);
    void slotDeleteBt(int buttonIndex, QString buttonName);
private:
    void initUI();
    void initConnection();
    void AutoFeed(QString text);
    /**
     * @brief setLabelTextColor     设置label文字颜色
     * @param type  主题type
     */
    void setLabelTextColor(const int type);
    /**
     * @brief setPaletteTextColor   设置调色板颜色
     * @param widget    需要设置的widget
     * @param textColor     显示颜色
     */
    void setPaletteTextColor(QWidget *widget,QColor textColor);
protected:
    void showEvent(QShowEvent *event) override;
    bool eventFilter(QObject *o, QEvent *e) override;
private:
    QLabel                           *m_schceduleLabel = nullptr;
    QLabel                           *m_timeLabel = nullptr;
    DSuggestButton *m_editBt = nullptr;
    DPushButton                      *m_deleteBt = nullptr;
    DPushButton                      *m_okBt = nullptr;
    QLabel *m_icon = nullptr;
    QLabel *m_Title = nullptr;
    ScheduleDtailInfo m_scheduleInfo; //日程
    QScrollArea *area = nullptr;
    QFont labelF;
};

#endif // MYSCHCEDULEVIEW_H
