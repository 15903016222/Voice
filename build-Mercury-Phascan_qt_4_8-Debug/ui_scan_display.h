/********************************************************************************
** Form generated from reading UI file 'scan_display.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCAN_DISPLAY_H
#define UI_SCAN_DISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "ui/display/color_bar.h"
#include "ui/display/ruler_widget.h"

QT_BEGIN_NAMESPACE

class Ui_ScanDisplay
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout_2;
    RulerWidget *leftRulerWidget;
    QVBoxLayout *scanLayout;
    ColorBar *colorBarWidget;
    RulerWidget *rightRulerWidget;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_5;
    RulerWidget *bottomRulerWidget;
    QWidget *widget;

    void setupUi(QWidget *ScanDisplay)
    {
        if (ScanDisplay->objectName().isEmpty())
            ScanDisplay->setObjectName(QString::fromUtf8("ScanDisplay"));
        ScanDisplay->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(ScanDisplay);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(ScanDisplay);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 127);\n"
"color: rgb(255, 255, 255);"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(titleLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        leftRulerWidget = new RulerWidget(ScanDisplay);
        leftRulerWidget->setObjectName(QString::fromUtf8("leftRulerWidget"));
        leftRulerWidget->setMinimumSize(QSize(20, 0));

        horizontalLayout_2->addWidget(leftRulerWidget);

        scanLayout = new QVBoxLayout();
        scanLayout->setObjectName(QString::fromUtf8("scanLayout"));

        horizontalLayout_2->addLayout(scanLayout);

        colorBarWidget = new ColorBar(ScanDisplay);
        colorBarWidget->setObjectName(QString::fromUtf8("colorBarWidget"));
        colorBarWidget->setMinimumSize(QSize(5, 0));
        colorBarWidget->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(colorBarWidget);

        rightRulerWidget = new RulerWidget(ScanDisplay);
        rightRulerWidget->setObjectName(QString::fromUtf8("rightRulerWidget"));
        rightRulerWidget->setMinimumSize(QSize(20, 0));

        horizontalLayout_2->addWidget(rightRulerWidget);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_5 = new QWidget(ScanDisplay);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setMinimumSize(QSize(20, 0));

        horizontalLayout->addWidget(widget_5);

        bottomRulerWidget = new RulerWidget(ScanDisplay);
        bottomRulerWidget->setObjectName(QString::fromUtf8("bottomRulerWidget"));
        bottomRulerWidget->setMinimumSize(QSize(0, 20));

        horizontalLayout->addWidget(bottomRulerWidget);

        widget = new QWidget(ScanDisplay);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(25, 0));

        horizontalLayout->addWidget(widget);

        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(1, 1);

        retranslateUi(ScanDisplay);

        QMetaObject::connectSlotsByName(ScanDisplay);
    } // setupUi

    void retranslateUi(QWidget *ScanDisplay)
    {
        ScanDisplay->setWindowTitle(QApplication::translate("ScanDisplay", "Form", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("ScanDisplay", "S-Scan", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ScanDisplay: public Ui_ScanDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCAN_DISPLAY_H
