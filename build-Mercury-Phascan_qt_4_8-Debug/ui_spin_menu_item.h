/********************************************************************************
** Form generated from reading UI file 'spin_menu_item.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPIN_MENU_ITEM_H
#define UI_SPIN_MENU_ITEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SpinMenuItem
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QLineEdit *lineEdit;

    void setupUi(QWidget *SpinMenuItem)
    {
        if (SpinMenuItem->objectName().isEmpty())
            SpinMenuItem->setObjectName(QString::fromUtf8("SpinMenuItem"));
        SpinMenuItem->resize(65, 70);
        verticalLayout = new QVBoxLayout(SpinMenuItem);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nameLabel = new QLabel(SpinMenuItem);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        nameLabel->setFont(font);
        nameLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 14pt \"Arial\";\n"
"	background-color:rgba(0, 130, 195);\n"
"	border: 0px solid black;\n"
"	color: rgb(255, 255, 0);\n"
"	border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), 	stop:0.559322 rgba(255, 255, 255, 255));\n"
"	border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));\n"
"}"));
        nameLabel->setTextFormat(Qt::RichText);

        verticalLayout->addWidget(nameLabel);

        lineEdit = new QLineEdit(SpinMenuItem);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setFocusPolicy(Qt::NoFocus);
        lineEdit->setStyleSheet(QString::fromUtf8("QLineEdit{\n"
"	color: rgb(255, 255, 255);\n"
"	border-top:0px;\n"
"	border-bottom:0px;	\n"
"	font: 14pt \"Arial\";\n"
"	color:white;\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255),\n"
"stop:0.559322 rgba(0, 130, 195, 255));\n"
"	border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"	border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"}"));
        lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(lineEdit);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);

        retranslateUi(SpinMenuItem);

        QMetaObject::connectSlotsByName(SpinMenuItem);
    } // setupUi

    void retranslateUi(QWidget *SpinMenuItem)
    {
        SpinMenuItem->setWindowTitle(QApplication::translate("SpinMenuItem", "Form", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SpinMenuItem: public Ui_SpinMenuItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPIN_MENU_ITEM_H
