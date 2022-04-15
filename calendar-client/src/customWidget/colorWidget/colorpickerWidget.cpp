/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     liulibang <liulibang@uniontech.com>
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
#include "colorpickerWidget.h"
#include "tabletconfig.h"

#include <DFontSizeManager>
#include <DFrame>
#include <DListView>
#include <DTitlebar>
#include <DSuggestButton>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>

DGUI_USE_NAMESPACE

CColorPickerWidget::CColorPickerWidget(QWidget *parent)
    : DAbstractDialog(parent)
    , m_colorLabel(new ColorLabel(this))
    , m_colorSlider(new ColorSlider(this))
    , m_colHexLineEdit(new DLineEdit(this))
    , m_wordLabel(new DLabel(this))
    , m_cancelBtn(new DPushButton(this))
    , m_enterBtn(new DSuggestButton(this))
{
    initUI();
    setColorHexLineEdit();
    moveToCenter();

    connect(m_cancelBtn, &DPushButton::clicked, this, &CColorPickerWidget::slotCancelBtnClicked);
    connect(m_enterBtn, &DPushButton::clicked, this, &CColorPickerWidget::slotEnterBtnClicked);
    connect(m_colorLabel, &ColorLabel::signalpickedColor, this, &CColorPickerWidget::slotUpdateColor);
    connect(m_colHexLineEdit, &DLineEdit::textChanged, this, &CColorPickerWidget::slotHexLineEditChange);
    connect(m_colorSlider, &ColorSlider::valueChanged, this, [this](int val) {
        m_colorLabel->setHue(val);
    });
}

CColorPickerWidget::~CColorPickerWidget()
{
}

void CColorPickerWidget::setColorHexLineEdit()
{
    m_colHexLineEdit->setText("");
    //确认按钮初始置灰
    m_enterBtn->setDisabled(true);
    //输入框输入限制
    QRegExp reg("^[0-9A-Fa-f]{6}$");
    QValidator *validator = new QRegExpValidator(reg,m_colHexLineEdit->lineEdit());
    m_colHexLineEdit->lineEdit()->setValidator(validator);
    setFocusProxy(m_colHexLineEdit);
}
/**
 * @brief CColorPickerDlg::initUI      初始化
 */
void CColorPickerWidget::initUI()
{
    QFont mlabelTitle;
    QFont mlabelContext;
    mlabelTitle.setWeight(QFont::Bold);
    mlabelContext.setWeight(QFont::Medium);
    setFixedSize(314, 276);
    m_colorLabel->setFixedSize(294, 136);
    m_colorSlider->setFixedSize(294,14);

    QVBoxLayout *mLayout = new QVBoxLayout(this);
    mLayout->setSpacing(12);
    mLayout->setContentsMargins(10, 10, 10, 8);
    mLayout->addWidget(m_colorLabel);
    mLayout->addWidget(m_colorSlider);

    m_wordLabel->setText(tr("Color"));
    m_wordLabel->setFixedWidth(40);
    m_wordLabel->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_colHexLineEdit->setClearButtonEnabled(false); //不显示清空按钮
    QHBoxLayout *inputLayout = new QHBoxLayout;
    inputLayout->setMargin(0);
    inputLayout->setSpacing(6);
    inputLayout->addWidget(m_wordLabel);
    inputLayout->addWidget(m_colHexLineEdit, 1);
    mLayout->addLayout(inputLayout);
    mLayout->addSpacing(4);

    m_cancelBtn->setText(tr("Cancel"));
    m_cancelBtn->setFixedSize(140, 36);
    m_enterBtn->setText(tr("Save"));
    m_enterBtn->setFixedSize(140, 36);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->setMargin(0);
    btnLayout->setSpacing(5);
    btnLayout->addWidget(m_cancelBtn);
    DVerticalLine *line = new DVerticalLine(this);
    line->setObjectName("VLine");
    line->setFixedSize(3,28);
    btnLayout->addWidget(line);
    line->show();
    btnLayout->addWidget(m_enterBtn);
    mLayout->addLayout(btnLayout);
    this->setLayout(mLayout);

    this->setFocusPolicy(Qt::TabFocus);
    setTabOrder(m_colHexLineEdit,m_cancelBtn);
    setTabOrder(m_cancelBtn,m_enterBtn);
    setTabOrder(m_enterBtn,m_colorSlider);
}

void CColorPickerWidget::slotHexLineEditChange(const QString &text)
{
    QString lowerText = text.toLower();
    if (lowerText == text) {
        QRegExp rx("^[0-9a-f]{6}$");
        if (rx.indexIn(lowerText) == -1) {
            m_enterBtn->setDisabled(true);
        } else {
            m_enterBtn->setDisabled(false);
        }
    } else {
        m_colHexLineEdit->setText(lowerText);
    }
}

QColor CColorPickerWidget::getSelectedColor()
{
    return QColor("#" + m_colHexLineEdit->text());
}

void CColorPickerWidget::slotUpdateColor(const QColor &color)
{
    if (color.isValid()) {
        this->m_colHexLineEdit->setText(color.name().remove("#"));
    }
}

void CColorPickerWidget::slotCancelBtnClicked()
{
    reject();
}

void CColorPickerWidget::slotEnterBtnClicked()
{
    accept();
}
