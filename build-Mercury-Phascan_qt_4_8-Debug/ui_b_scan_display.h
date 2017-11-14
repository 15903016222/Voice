/********************************************************************************
** Form generated from reading UI file 'b_scan_display.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_B_SCAN_DISPLAY_H
#define UI_B_SCAN_DISPLAY_H

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
#include "ui/display/scroll_ruler_widget.h"

QT_BEGIN_NAMESPACE

class Ui_BscanDisplay
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout;
    ScrollRulerWidget *leftRuler;
    QVBoxLayout *bScanWidgetVerticalLayout;
    ColorBar *colorBar;
    RulerWidget *rightRuler;
    QHBoxLayout *bottomHorizontalLayout;
    QWidget *leftEmptyWidget;
    ScrollRulerWidget *bottomRuler;
    QWidget *rightEmptyWidget;

    void setupUi(QWidget *BscanDisplay)
    {
        if (BscanDisplay->objectName().isEmpty())
            BscanDisplay->setObjectName(QString::fromUtf8("BscanDisplay"));
        BscanDisplay->resize(400, 300);
        verticalLayout = new QVBoxLayout(BscanDisplay);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(BscanDisplay);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 127);\n"
"color: rgb(255, 255, 255);"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        leftRuler = new ScrollRulerWidget(BscanDisplay);
        leftRuler->setObjectName(QString::fromUtf8("leftRuler"));
        leftRuler->setMinimumSize(QSize(20, 0));

        horizontalLayout->addWidget(leftRuler);

        bScanWidgetVerticalLayout = new QVBoxLayout();
        bScanWidgetVerticalLayout->setSpacing(0);
        bScanWidgetVerticalLayout->setObjectName(QString::fromUtf8("bScanWidgetVerticalLayout"));

        horizontalLayout->addLayout(bScanWidgetVerticalLayout);

        colorBar = new ColorBar(BscanDisplay);
        colorBar->setObjectName(QString::fromUtf8("colorBar"));
        colorBar->setMinimumSize(QSize(5, 0));

        horizontalLayout->addWidget(colorBar);

        rightRuler = new RulerWidget(BscanDisplay);
        rightRuler->setObjectName(QString::fromUtf8("rightRuler"));
        rightRuler->setMinimumSize(QSize(20, 0));

        horizontalLayout->addWidget(rightRuler);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        bottomHorizontalLayout = new QHBoxLayout();
        bottomHorizontalLayout->setSpacing(0);
        bottomHorizontalLayout->setObjectName(QString::fromUtf8("bottomHorizontalLayout"));
        leftEmptyWidget = new QWidget(BscanDisplay);
        leftEmptyWidget->setObjectName(QString::fromUtf8("leftEmptyWidget"));
        leftEmptyWidget->setMinimumSize(QSize(20, 20));

        bottomHorizontalLayout->addWidget(leftEmptyWidget);

        bottomRuler = new ScrollRulerWidget(BscanDisplay);
        bottomRuler->setObjectName(QString::fromUtf8("bottomRuler"));
        bottomRuler->setMinimumSize(QSize(0, 20));

        bottomHorizontalLayout->addWidget(bottomRuler);

        rightEmptyWidget = new QWidget(BscanDisplay);
        rightEmptyWidget->setObjectName(QString::fromUtf8("rightEmptyWidget"));
        rightEmptyWidget->setMinimumSize(QSize(25, 0));

        bottomHorizontalLayout->addWidget(rightEmptyWidget);

        bottomHorizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(bottomHorizontalLayout);

        verticalLayout->setStretch(1, 1);

        retranslateUi(BscanDisplay);

        QMetaObject::connectSlotsByName(BscanDisplay);
    } // setupUi

    void retranslateUi(QWidget *BscanDisplay)
    {
        BscanDisplay->setWindowTitle(QApplication::translate("BscanDisplay", "Form", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("BscanDisplay", "B-Scan", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BscanDisplay: public Ui_BscanDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_B_SCAN_DISPLAY_H
