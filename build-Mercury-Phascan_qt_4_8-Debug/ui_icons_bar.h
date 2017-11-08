/********************************************************************************
** Form generated from reading UI file 'icons_bar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ICONS_BAR_H
#define UI_ICONS_BAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "battery_label.h"

QT_BEGIN_NAMESPACE

class Ui_IconsBar
{
public:
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_1;
    QHBoxLayout *horizontalLayout;
    QPushButton *keyboardPushButton;
    QVBoxLayout *verticalLayout;
    BatteryLabel *fstBatteryLabel;
    BatteryLabel *sndBatteryLabel;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *encoderLabel;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *dacLabel;
    QLabel *tcgLabel;
    QLabel *tempLabel;
    QHBoxLayout *horizontalLayout_4;
    QLabel *sLabel;
    QLabel *vLabel;
    QLabel *wLabel;
    QLabel *beamLabel;

    void setupUi(QWidget *IconsBar)
    {
        if (IconsBar->objectName().isEmpty())
            IconsBar->setObjectName(QString::fromUtf8("IconsBar"));
        IconsBar->setWindowModality(Qt::NonModal);
        IconsBar->resize(189, 88);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(IconsBar->sizePolicy().hasHeightForWidth());
        IconsBar->setSizePolicy(sizePolicy);
        IconsBar->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(6);
        IconsBar->setFont(font);
        IconsBar->setWindowOpacity(1);
        IconsBar->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(IconsBar);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_1 = new QWidget(IconsBar);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));
        widget_1->setStyleSheet(QString::fromUtf8("QWidget#widget_1\n"
"{\n"
"	background-color: rgba(0, 130, 195);\n"
"    border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));\n"
"}"));
        horizontalLayout = new QHBoxLayout(widget_1);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 3);
        keyboardPushButton = new QPushButton(widget_1);
        keyboardPushButton->setObjectName(QString::fromUtf8("keyboardPushButton"));
        sizePolicy.setHeightForWidth(keyboardPushButton->sizePolicy().hasHeightForWidth());
        keyboardPushButton->setSizePolicy(sizePolicy);
        keyboardPushButton->setMinimumSize(QSize(0, 0));
        keyboardPushButton->setFocusPolicy(Qt::NoFocus);
        keyboardPushButton->setStyleSheet(QString::fromUtf8("border-image: url(://resource/keyboard.png);"));

        horizontalLayout->addWidget(keyboardPushButton);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(-1, 6, -1, -1);
        fstBatteryLabel = new BatteryLabel(widget_1);
        fstBatteryLabel->setObjectName(QString::fromUtf8("fstBatteryLabel"));
        fstBatteryLabel->setStyleSheet(QString::fromUtf8(""));
        fstBatteryLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(fstBatteryLabel);

        sndBatteryLabel = new BatteryLabel(widget_1);
        sndBatteryLabel->setObjectName(QString::fromUtf8("sndBatteryLabel"));
        sndBatteryLabel->setLayoutDirection(Qt::LeftToRight);
        sndBatteryLabel->setStyleSheet(QString::fromUtf8(""));
        sndBatteryLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(sndBatteryLabel);


        horizontalLayout->addLayout(verticalLayout);

        horizontalLayout->setStretch(0, 2);
        horizontalLayout->setStretch(1, 1);

        verticalLayout_3->addWidget(widget_1);

        widget_2 = new QWidget(IconsBar);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy1);
        widget_2->setStyleSheet(QString::fromUtf8("QWidget#widget_2\n"
"{\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.559322 rgba(0, 130, 195, 255));\n"
"	border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"}"));
        horizontalLayout_6 = new QHBoxLayout(widget_2);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        encoderLabel = new QLabel(widget_2);
        encoderLabel->setObjectName(QString::fromUtf8("encoderLabel"));
        encoderLabel->setEnabled(true);
        encoderLabel->setMinimumSize(QSize(28, 28));
        encoderLabel->setMaximumSize(QSize(28, 28));
        encoderLabel->setScaledContents(false);

        horizontalLayout_6->addWidget(encoderLabel);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        dacLabel = new QLabel(widget_2);
        dacLabel->setObjectName(QString::fromUtf8("dacLabel"));
        QPalette palette;
        QBrush brush(QColor(0, 255, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        dacLabel->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Times New Roman"));
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        dacLabel->setFont(font1);
        dacLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(dacLabel);

        tcgLabel = new QLabel(widget_2);
        tcgLabel->setObjectName(QString::fromUtf8("tcgLabel"));
        QPalette palette1;
        QBrush brush2(QColor(28, 244, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        tcgLabel->setPalette(palette1);
        tcgLabel->setFont(font1);
        tcgLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(tcgLabel);

        tempLabel = new QLabel(widget_2);
        tempLabel->setObjectName(QString::fromUtf8("tempLabel"));
        QPalette palette2;
        QBrush brush3(QColor(255, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        tempLabel->setPalette(palette2);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Times New Roman"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setWeight(75);
        tempLabel->setFont(font2);
        tempLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(tempLabel);


        verticalLayout_2->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        sLabel = new QLabel(widget_2);
        sLabel->setObjectName(QString::fromUtf8("sLabel"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        QBrush brush4(QColor(190, 190, 190, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        sLabel->setPalette(palette3);
        QFont font3;
        font3.setBold(true);
        font3.setWeight(75);
        sLabel->setFont(font3);
        sLabel->setText(QString::fromUtf8("S"));
        sLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(sLabel);

        vLabel = new QLabel(widget_2);
        vLabel->setObjectName(QString::fromUtf8("vLabel"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        vLabel->setPalette(palette4);
        vLabel->setFont(font3);
        vLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(vLabel);

        wLabel = new QLabel(widget_2);
        wLabel->setObjectName(QString::fromUtf8("wLabel"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        wLabel->setPalette(palette5);
        wLabel->setFont(font3);
        wLabel->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_4->addWidget(wLabel);

        beamLabel = new QLabel(widget_2);
        beamLabel->setObjectName(QString::fromUtf8("beamLabel"));
        QPalette palette6;
        QBrush brush5(QColor(255, 220, 20, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette6.setBrush(QPalette::Active, QPalette::WindowText, brush5);
        palette6.setBrush(QPalette::Inactive, QPalette::WindowText, brush5);
        palette6.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        beamLabel->setPalette(palette6);
        beamLabel->setFont(font2);
        beamLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(beamLabel);

        horizontalLayout_4->setStretch(0, 1);
        horizontalLayout_4->setStretch(1, 1);
        horizontalLayout_4->setStretch(2, 1);
        horizontalLayout_4->setStretch(3, 2);

        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_2);

        horizontalLayout_6->setStretch(0, 1);
        horizontalLayout_6->setStretch(1, 5);

        verticalLayout_3->addWidget(widget_2);

        verticalLayout_3->setStretch(0, 2);
        verticalLayout_3->setStretch(1, 1);

        retranslateUi(IconsBar);

        QMetaObject::connectSlotsByName(IconsBar);
    } // setupUi

    void retranslateUi(QWidget *IconsBar)
    {
        IconsBar->setWindowTitle(QApplication::translate("IconsBar", "Form", 0, QApplication::UnicodeUTF8));
        keyboardPushButton->setText(QString());
        fstBatteryLabel->setText(QString());
        sndBatteryLabel->setText(QString());
        encoderLabel->setText(QString());
        dacLabel->setText(QApplication::translate("IconsBar", "DAC", 0, QApplication::UnicodeUTF8));
        tcgLabel->setText(QApplication::translate("IconsBar", "TCG", 0, QApplication::UnicodeUTF8));
        tempLabel->setText(QApplication::translate("IconsBar", "50\302\260C", 0, QApplication::UnicodeUTF8));
        vLabel->setText(QApplication::translate("IconsBar", "V", 0, QApplication::UnicodeUTF8));
        wLabel->setText(QApplication::translate("IconsBar", "W", 0, QApplication::UnicodeUTF8));
        beamLabel->setText(QApplication::translate("IconsBar", "0 /", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class IconsBar: public Ui_IconsBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ICONS_BAR_H
