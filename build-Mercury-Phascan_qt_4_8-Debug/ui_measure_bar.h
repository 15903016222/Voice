/********************************************************************************
** Form generated from reading UI file 'measure_bar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASURE_BAR_H
#define UI_MEASURE_BAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>
#include "measure_widget.h"

QT_BEGIN_NAMESPACE

class Ui_MeasureBar
{
public:
    QHBoxLayout *horizontalLayout;
    MeasureWidget *measureWidget1;
    MeasureWidget *measureWidget2;
    MeasureWidget *measureWidget3;
    MeasureWidget *measureWidget4;
    MeasureWidget *measureWidget5;
    MeasureWidget *measureWidget6;
    MeasureWidget *measureWidget7;
    MeasureWidget *measureWidget8;

    void setupUi(QWidget *MeasureBar)
    {
        if (MeasureBar->objectName().isEmpty())
            MeasureBar->setObjectName(QString::fromUtf8("MeasureBar"));
        MeasureBar->resize(686, 70);
        QFont font;
        font.setPointSize(10);
        MeasureBar->setFont(font);
        horizontalLayout = new QHBoxLayout(MeasureBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        measureWidget1 = new MeasureWidget(MeasureBar);
        measureWidget1->setObjectName(QString::fromUtf8("measureWidget1"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(measureWidget1->sizePolicy().hasHeightForWidth());
        measureWidget1->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget1);

        measureWidget2 = new MeasureWidget(MeasureBar);
        measureWidget2->setObjectName(QString::fromUtf8("measureWidget2"));
        sizePolicy.setHeightForWidth(measureWidget2->sizePolicy().hasHeightForWidth());
        measureWidget2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget2);

        measureWidget3 = new MeasureWidget(MeasureBar);
        measureWidget3->setObjectName(QString::fromUtf8("measureWidget3"));
        sizePolicy.setHeightForWidth(measureWidget3->sizePolicy().hasHeightForWidth());
        measureWidget3->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget3);

        measureWidget4 = new MeasureWidget(MeasureBar);
        measureWidget4->setObjectName(QString::fromUtf8("measureWidget4"));
        sizePolicy.setHeightForWidth(measureWidget4->sizePolicy().hasHeightForWidth());
        measureWidget4->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget4);

        measureWidget5 = new MeasureWidget(MeasureBar);
        measureWidget5->setObjectName(QString::fromUtf8("measureWidget5"));
        sizePolicy.setHeightForWidth(measureWidget5->sizePolicy().hasHeightForWidth());
        measureWidget5->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget5);

        measureWidget6 = new MeasureWidget(MeasureBar);
        measureWidget6->setObjectName(QString::fromUtf8("measureWidget6"));
        sizePolicy.setHeightForWidth(measureWidget6->sizePolicy().hasHeightForWidth());
        measureWidget6->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget6);

        measureWidget7 = new MeasureWidget(MeasureBar);
        measureWidget7->setObjectName(QString::fromUtf8("measureWidget7"));
        sizePolicy.setHeightForWidth(measureWidget7->sizePolicy().hasHeightForWidth());
        measureWidget7->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget7);

        measureWidget8 = new MeasureWidget(MeasureBar);
        measureWidget8->setObjectName(QString::fromUtf8("measureWidget8"));
        sizePolicy.setHeightForWidth(measureWidget8->sizePolicy().hasHeightForWidth());
        measureWidget8->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(measureWidget8);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 1);
        horizontalLayout->setStretch(6, 1);
        horizontalLayout->setStretch(7, 1);

        retranslateUi(MeasureBar);

        QMetaObject::connectSlotsByName(MeasureBar);
    } // setupUi

    void retranslateUi(QWidget *MeasureBar)
    {
        MeasureBar->setWindowTitle(QApplication::translate("MeasureBar", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MeasureBar: public Ui_MeasureBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASURE_BAR_H
