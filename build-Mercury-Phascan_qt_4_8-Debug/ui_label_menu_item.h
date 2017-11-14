/********************************************************************************
** Form generated from reading UI file 'label_menu_item.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABEL_MENU_ITEM_H
#define UI_LABEL_MENU_ITEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LabelMenuItem
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *LabelMenuItem)
    {
        if (LabelMenuItem->objectName().isEmpty())
            LabelMenuItem->setObjectName(QString::fromUtf8("LabelMenuItem"));
        LabelMenuItem->resize(101, 70);
        verticalLayout = new QVBoxLayout(LabelMenuItem);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(LabelMenuItem);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setFocusPolicy(Qt::NoFocus);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton{\n"
"	background-position: center;\n"
"	font: 16pt \"Arial\";\n"
"	background-color:rgba(0, 130, 195);\n"
"	border: 0px solid black;\n"
"	color: rgb(255, 255, 0);\n"
"	border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), 	stop:0.559322 rgba(255, 255, 255, 255));\n"
"	border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));\n"
"}\n"
""));

        verticalLayout->addWidget(pushButton);

        label = new QLabel(LabelMenuItem);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	border-top:0px;\n"
"	border-bottom:0px;\n"
"	font: 14pt \"Arial\";\n"
"	color: white;\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255),\n"
"stop:0.559322 rgba(0, 130, 195, 255));\n"
"	border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"	border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"}"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);

        retranslateUi(LabelMenuItem);

        QMetaObject::connectSlotsByName(LabelMenuItem);
    } // setupUi

    void retranslateUi(QWidget *LabelMenuItem)
    {
        LabelMenuItem->setWindowTitle(QApplication::translate("LabelMenuItem", "Form", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("LabelMenuItem", "PushButton", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LabelMenuItem: public Ui_LabelMenuItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABEL_MENU_ITEM_H
