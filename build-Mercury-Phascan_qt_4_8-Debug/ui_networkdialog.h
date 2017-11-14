/********************************************************************************
** Form generated from reading UI file 'networkdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKDIALOG_H
#define UI_NETWORKDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkDialog
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QWidget *widget_5;
    QLabel *label;
    QWidget *widget_7;
    QWidget *widget_6;
    QWidget *widget_8;
    QWidget *widget_3;
    QGridLayout *gridLayout_5;
    QWidget *widget_9;
    QGridLayout *gridLayout_3;
    QSpinBox *spinBox_1;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QLabel *label_4;
    QSpinBox *spinBox_4;
    QWidget *widget_2;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_ok;

    void setupUi(QDialog *NetworkDialog)
    {
        if (NetworkDialog->objectName().isEmpty())
            NetworkDialog->setObjectName(QString::fromUtf8("NetworkDialog"));
        NetworkDialog->resize(320, 210);
        NetworkDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(236, 236, 236);"));
        gridLayout_2 = new QGridLayout(NetworkDialog);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(NetworkDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget{\n"
"	background-color: rgba(220, 220, 220, 204);\n"
"\n"
"}\n"
"\n"
"QWidget#label{\n"
"	font: bold 18pt \"Arial\";\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"}\n"
"\n"
"QWidget#widget_3{\n"
"	border-left: 1px solid gray;\n"
"	border-bottom: 1px solid gray;\n"
"	border-right: 1px solid gray;\n"
"	border-bottom-left-radius: 4px;\n"
"	border-bottom-right-radius: 4px;\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"}\n"
"\n"
"QWidget#widget_6{\n"
"	border-left: 1px solid gray;\n"
"	border-top: 1px solid gray;\n"
"	border-top-left-radius: 4px;\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"}\n"
"\n"
"QWidget#widget_8{\n"
"	border-top: 1px solid gray;\n"
"	border-right: 1px solid gray;\n"
"	border-top-right-radius: 4px;\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"}\n"
"\n"
"QWidget#widget_2{\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"	font: 16pt \"Arial\";\n"
"}\n"
"\n"
"QWidget#widget_5,#widget_7{\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"}\n"
"\n"
"QWidget QPushButton{\n"
"	font: 16pt \"Arial\""
                        ";\n"
"}\n"
"\n"
"QWidget#widget_9{\n"
"	border-radius: 5px;\n"
"	background-color: rgb(55, 55, 55);\n"
"	/*background-color:rgb(9, 157, 247);*/\n"
"	/*background-color: rgb(0, 130, 195);*/\n"
"}\n"
"\n"
"QWidget#label_2,#label_3,#label_4{\n"
"	color: rgb(125, 125, 125);\n"
"	font: bold 16pt \"Arial\";\n"
"	background-color: rgba(55, 55, 55, 0);\n"
"}\n"
"\n"
"QWidget QSpinBox{\n"
"   color: rgb(125, 125, 125);\n"
"	font: bold 16pt \"Arial\";\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:0.5, stop:0 rgba(220, 220, 220, 255), stop:0.957143 rgba(190, 190, 190, 255), stop:1 rgba(220, 220, 220, 255));\n"
"	selection-background-color: rgba(0, 0, 0, 0);\n"
"	selection-color: rgb(125, 125, 125);\n"
"	border: 0px solid;\n"
"	border-radius: 2px;\n"
"}\n"
""));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(5, 5, 5, 5);
        widget_5 = new QWidget(widget);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));

        gridLayout->addWidget(widget_5, 0, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(18);
        font.setBold(true);
        font.setItalic(false);
        font.setWeight(75);
        label->setFont(font);
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 1, 2, 1);

        widget_7 = new QWidget(widget);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));

        gridLayout->addWidget(widget_7, 0, 2, 1, 1);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));

        gridLayout->addWidget(widget_6, 1, 0, 1, 1);

        widget_8 = new QWidget(widget);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));

        gridLayout->addWidget(widget_8, 1, 2, 1, 1);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        gridLayout_5 = new QGridLayout(widget_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(6, 0, 6, 9);
        widget_9 = new QWidget(widget_3);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(widget_9);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(10, 10, 10, 10);
        spinBox_1 = new QSpinBox(widget_9);
        spinBox_1->setObjectName(QString::fromUtf8("spinBox_1"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(spinBox_1->sizePolicy().hasHeightForWidth());
        spinBox_1->setSizePolicy(sizePolicy);
        spinBox_1->setMaximumSize(QSize(65, 65));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        spinBox_1->setFont(font1);
        spinBox_1->setAlignment(Qt::AlignCenter);
        spinBox_1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_1->setMaximum(255);

        gridLayout_3->addWidget(spinBox_1, 0, 0, 1, 1);

        label_2 = new QLabel(widget_9);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        spinBox_2 = new QSpinBox(widget_9);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        sizePolicy.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy);
        spinBox_2->setMaximumSize(QSize(65, 65));
        spinBox_2->setFont(font1);
        spinBox_2->setAlignment(Qt::AlignCenter);
        spinBox_2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_2->setMaximum(255);

        gridLayout_3->addWidget(spinBox_2, 0, 2, 1, 1);

        label_3 = new QLabel(widget_9);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 0, 3, 1, 1);

        spinBox_3 = new QSpinBox(widget_9);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        sizePolicy.setHeightForWidth(spinBox_3->sizePolicy().hasHeightForWidth());
        spinBox_3->setSizePolicy(sizePolicy);
        spinBox_3->setMaximumSize(QSize(65, 65));
        spinBox_3->setFont(font1);
        spinBox_3->setAlignment(Qt::AlignCenter);
        spinBox_3->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_3->setMaximum(255);

        gridLayout_3->addWidget(spinBox_3, 0, 4, 1, 1);

        label_4 = new QLabel(widget_9);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_4, 0, 5, 1, 1);

        spinBox_4 = new QSpinBox(widget_9);
        spinBox_4->setObjectName(QString::fromUtf8("spinBox_4"));
        sizePolicy.setHeightForWidth(spinBox_4->sizePolicy().hasHeightForWidth());
        spinBox_4->setSizePolicy(sizePolicy);
        spinBox_4->setMaximumSize(QSize(65, 65));
        spinBox_4->setFont(font1);
        spinBox_4->setAlignment(Qt::AlignCenter);
        spinBox_4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        spinBox_4->setMaximum(255);

        gridLayout_3->addWidget(spinBox_4, 0, 6, 1, 1);

        gridLayout_3->setColumnStretch(0, 4);
        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 4);
        gridLayout_3->setColumnStretch(3, 1);
        gridLayout_3->setColumnStretch(4, 4);
        gridLayout_3->setColumnStretch(5, 1);
        gridLayout_3->setColumnStretch(6, 4);

        gridLayout_5->addWidget(widget_9, 1, 0, 1, 1);


        gridLayout->addWidget(widget_3, 2, 0, 1, 3);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        gridLayout_4 = new QGridLayout(widget_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(0, 5, 0, 5);
        horizontalSpacer = new QSpacerItem(108, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 0, 1, 1);

        pushButton_cancel = new QPushButton(widget_2);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        sizePolicy.setHeightForWidth(pushButton_cancel->sizePolicy().hasHeightForWidth());
        pushButton_cancel->setSizePolicy(sizePolicy);
        pushButton_cancel->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(pushButton_cancel, 0, 1, 1, 1);

        pushButton_ok = new QPushButton(widget_2);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        sizePolicy.setHeightForWidth(pushButton_ok->sizePolicy().hasHeightForWidth());
        pushButton_ok->setSizePolicy(sizePolicy);
        pushButton_ok->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(pushButton_ok, 0, 2, 1, 1);


        gridLayout->addWidget(widget_2, 3, 0, 1, 3);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 4);
        gridLayout->setRowStretch(3, 2);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 3);
        gridLayout->setColumnStretch(2, 4);

        gridLayout_2->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(NetworkDialog);

        QMetaObject::connectSlotsByName(NetworkDialog);
    } // setupUi

    void retranslateUi(QDialog *NetworkDialog)
    {
        NetworkDialog->setWindowTitle(QApplication::translate("NetworkDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_2->setText(QApplication::translate("NetworkDialog", ".", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("NetworkDialog", ".", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("NetworkDialog", ".", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("NetworkDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("NetworkDialog", "&Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NetworkDialog: public Ui_NetworkDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKDIALOG_H
