/********************************************************************************
** Form generated from reading UI file 'base_menu.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BASE_MENU_H
#define UI_BASE_MENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BaseMenu
{
public:
    QHBoxLayout *horizontalLayout;
    QWidget *item0;
    QVBoxLayout *layout0;
    QWidget *item1;
    QVBoxLayout *layout1;
    QWidget *item2;
    QVBoxLayout *layout2;
    QWidget *item3;
    QVBoxLayout *layout3;
    QWidget *item4;
    QVBoxLayout *layout4;
    QWidget *item5;
    QVBoxLayout *layout5;

    void setupUi(QWidget *BaseMenu)
    {
        if (BaseMenu->objectName().isEmpty())
            BaseMenu->setObjectName(QString::fromUtf8("BaseMenu"));
        BaseMenu->resize(621, 70);
        BaseMenu->setMinimumSize(QSize(0, 70));
        BaseMenu->setStyleSheet(QString::fromUtf8("QWidget#item0,#item1,#item2,#item3,#item4,#item5\n"
"{\n"
"	border-left:  1px solid qlineargradient(spread:repeat, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(0, 130, 195, 255), stop:0.1 rgba(0, 130, 195, 255), stop:0.333 rgba(255, 255, 255, 255), stop:0.667 rgba(255, 255, 255, 255), stop:0.9 rgba(0, 130, 195, 255), stop:1 rgba(0, 130, 195, 255));\n"
"	border-right: 1px solid qlineargradient(spread:repeat, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(0, 130, 195, 255), stop:0.1 rgba(0, 130, 195, 255), stop:0.333 rgba(0, 0, 0, 255), stop:0.667 rgba(0, 0, 0, 255), stop:0.9 rgba(0, 130, 195, 255), stop:1 rgba(0, 130, 195, 255));\n"
"	background-color:  qlineargradient(spread:repeat, x1:0.5, y1:0, x2:0.5, y2:1,\n"
"stop:0 rgba(0, 130, 195, 255), \n"
"stop:0.666 rgba(0, 130, 195, 255), \n"
"stop:0.667 rgba(0, 0, 0, 255), \n"
"stop:0.718730666 rgba(0, 0, 0, 255),\n"
"stop:0.852440666 rgba(0, 130, 195, 255));\n"
"}\n"
""));
        horizontalLayout = new QHBoxLayout(BaseMenu);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        item0 = new QWidget(BaseMenu);
        item0->setObjectName(QString::fromUtf8("item0"));
        layout0 = new QVBoxLayout(item0);
        layout0->setSpacing(0);
        layout0->setObjectName(QString::fromUtf8("layout0"));
        layout0->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(item0);

        item1 = new QWidget(BaseMenu);
        item1->setObjectName(QString::fromUtf8("item1"));
        layout1 = new QVBoxLayout(item1);
        layout1->setSpacing(0);
        layout1->setObjectName(QString::fromUtf8("layout1"));
        layout1->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(item1);

        item2 = new QWidget(BaseMenu);
        item2->setObjectName(QString::fromUtf8("item2"));
        layout2 = new QVBoxLayout(item2);
        layout2->setSpacing(0);
        layout2->setObjectName(QString::fromUtf8("layout2"));
        layout2->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(item2);

        item3 = new QWidget(BaseMenu);
        item3->setObjectName(QString::fromUtf8("item3"));
        layout3 = new QVBoxLayout(item3);
        layout3->setSpacing(0);
        layout3->setObjectName(QString::fromUtf8("layout3"));
        layout3->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(item3);

        item4 = new QWidget(BaseMenu);
        item4->setObjectName(QString::fromUtf8("item4"));
        layout4 = new QVBoxLayout(item4);
        layout4->setSpacing(0);
        layout4->setObjectName(QString::fromUtf8("layout4"));
        layout4->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(item4);

        item5 = new QWidget(BaseMenu);
        item5->setObjectName(QString::fromUtf8("item5"));
        layout5 = new QVBoxLayout(item5);
        layout5->setSpacing(0);
        layout5->setObjectName(QString::fromUtf8("layout5"));
        layout5->setContentsMargins(0, 0, 0, 0);

        horizontalLayout->addWidget(item5);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 1);

        retranslateUi(BaseMenu);

        QMetaObject::connectSlotsByName(BaseMenu);
    } // setupUi

    void retranslateUi(QWidget *BaseMenu)
    {
        BaseMenu->setWindowTitle(QApplication::translate("BaseMenu", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class BaseMenu: public Ui_BaseMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BASE_MENU_H
