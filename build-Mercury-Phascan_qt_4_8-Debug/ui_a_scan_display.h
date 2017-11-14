/********************************************************************************
** Form generated from reading UI file 'a_scan_display.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_A_SCAN_DISPLAY_H
#define UI_A_SCAN_DISPLAY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "ui/display/ruler_widget.h"

QT_BEGIN_NAMESPACE

class Ui_AscanDisplay
{
public:
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QHBoxLayout *horizontalLayout_2;
    RulerWidget *leftRulerWidget;
    QVBoxLayout *ascanWidgetLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    RulerWidget *bottomRulerWidget;

    void setupUi(QWidget *AscanDisplay)
    {
        if (AscanDisplay->objectName().isEmpty())
            AscanDisplay->setObjectName(QString::fromUtf8("AscanDisplay"));
        AscanDisplay->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(AscanDisplay);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(AscanDisplay);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 85, 127);\n"
"color: rgb(255, 255, 255);"));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(titleLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        leftRulerWidget = new RulerWidget(AscanDisplay);
        leftRulerWidget->setObjectName(QString::fromUtf8("leftRulerWidget"));
        leftRulerWidget->setMinimumSize(QSize(20, 0));

        horizontalLayout_2->addWidget(leftRulerWidget);

        ascanWidgetLayout = new QVBoxLayout();
        ascanWidgetLayout->setSpacing(0);
        ascanWidgetLayout->setObjectName(QString::fromUtf8("ascanWidgetLayout"));

        horizontalLayout_2->addLayout(ascanWidgetLayout);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(AscanDisplay);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(20, 0));

        horizontalLayout->addWidget(widget);

        bottomRulerWidget = new RulerWidget(AscanDisplay);
        bottomRulerWidget->setObjectName(QString::fromUtf8("bottomRulerWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bottomRulerWidget->sizePolicy().hasHeightForWidth());
        bottomRulerWidget->setSizePolicy(sizePolicy);
        bottomRulerWidget->setMinimumSize(QSize(0, 20));

        horizontalLayout->addWidget(bottomRulerWidget);

        horizontalLayout->setStretch(1, 1);

        verticalLayout_2->addLayout(horizontalLayout);

        verticalLayout_2->setStretch(1, 1);

        retranslateUi(AscanDisplay);

        QMetaObject::connectSlotsByName(AscanDisplay);
    } // setupUi

    void retranslateUi(QWidget *AscanDisplay)
    {
        AscanDisplay->setWindowTitle(QApplication::translate("AscanDisplay", "Form", 0, QApplication::UnicodeUTF8));
        titleLabel->setText(QApplication::translate("AscanDisplay", "<html><head/><body><p><span style=\" color:#ffffff;\">A-Scan</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AscanDisplay: public Ui_AscanDisplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_A_SCAN_DISPLAY_H
