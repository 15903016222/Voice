/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "../menu/menu_item/spin_menu_item.h"
#include "icons_bar.h"
#include "measure_bar.h"
#include "status_bar.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    SpinMenuItem *gainMenuItem;
    MeasureBar *measureBar;
    SpinMenuItem *angleMenuItem;
    IconsBar *iconsBarWidget;
    StatusBar *statusBar;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *mainMenuLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *displayLayout;
    QHBoxLayout *subMenuLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setWindowTitle(QString::fromUtf8("Mercury"));
        MainWindow->setAutoFillBackground(false);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow  {\n"
"	background-color: rgb(0, 0, 0);\n"
"}"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gainMenuItem = new SpinMenuItem(centralWidget);
        gainMenuItem->setObjectName(QString::fromUtf8("gainMenuItem"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gainMenuItem->sizePolicy().hasHeightForWidth());
        gainMenuItem->setSizePolicy(sizePolicy1);
        gainMenuItem->setMinimumSize(QSize(0, 70));

        horizontalLayout->addWidget(gainMenuItem);

        measureBar = new MeasureBar(centralWidget);
        measureBar->setObjectName(QString::fromUtf8("measureBar"));
        sizePolicy1.setHeightForWidth(measureBar->sizePolicy().hasHeightForWidth());
        measureBar->setSizePolicy(sizePolicy1);
        measureBar->setMinimumSize(QSize(0, 70));

        horizontalLayout->addWidget(measureBar);

        angleMenuItem = new SpinMenuItem(centralWidget);
        angleMenuItem->setObjectName(QString::fromUtf8("angleMenuItem"));
        sizePolicy1.setHeightForWidth(angleMenuItem->sizePolicy().hasHeightForWidth());
        angleMenuItem->setSizePolicy(sizePolicy1);
        angleMenuItem->setMinimumSize(QSize(0, 70));

        horizontalLayout->addWidget(angleMenuItem);

        iconsBarWidget = new IconsBar(centralWidget);
        iconsBarWidget->setObjectName(QString::fromUtf8("iconsBarWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(iconsBarWidget->sizePolicy().hasHeightForWidth());
        iconsBarWidget->setSizePolicy(sizePolicy2);
        iconsBarWidget->setMinimumSize(QSize(0, 70));

        horizontalLayout->addWidget(iconsBarWidget);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 16);
        horizontalLayout->setStretch(2, 2);
        horizontalLayout->setStretch(3, 4);

        verticalLayout->addLayout(horizontalLayout);

        statusBar = new StatusBar(centralWidget);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        sizePolicy1.setHeightForWidth(statusBar->sizePolicy().hasHeightForWidth());
        statusBar->setSizePolicy(sizePolicy1);
        statusBar->setMinimumSize(QSize(0, 20));

        verticalLayout->addWidget(statusBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mainMenuLayout = new QVBoxLayout();
        mainMenuLayout->setSpacing(0);
        mainMenuLayout->setObjectName(QString::fromUtf8("mainMenuLayout"));

        horizontalLayout_2->addLayout(mainMenuLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        displayLayout = new QVBoxLayout();
        displayLayout->setSpacing(0);
        displayLayout->setObjectName(QString::fromUtf8("displayLayout"));

        verticalLayout_2->addLayout(displayLayout);

        subMenuLayout = new QHBoxLayout();
        subMenuLayout->setSpacing(0);
        subMenuLayout->setObjectName(QString::fromUtf8("subMenuLayout"));

        verticalLayout_2->addLayout(subMenuLayout);

        verticalLayout_2->setStretch(0, 1);

        horizontalLayout_2->addLayout(verticalLayout_2);

        horizontalLayout_2->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 7);
        verticalLayout->setStretch(1, 2);
        verticalLayout->setStretch(2, 51);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
