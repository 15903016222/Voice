/********************************************************************************
** Form generated from reading UI file 'datetimesetdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATETIMESETDIALOG_H
#define UI_DATETIMESETDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DateTimeSetDialog
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QFrame *line;
    QLabel *label;
    QWidget *widget_3;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_1;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QWidget *widget_2;
    QGridLayout *gridLayout_4;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_ok;

    void setupUi(QDialog *DateTimeSetDialog)
    {
        if (DateTimeSetDialog->objectName().isEmpty())
            DateTimeSetDialog->setObjectName(QString::fromUtf8("DateTimeSetDialog"));
        DateTimeSetDialog->resize(320, 210);
        DateTimeSetDialog->setStyleSheet(QString::fromUtf8("background-color: rgb(236, 236, 236);"));
        gridLayout_2 = new QGridLayout(DateTimeSetDialog);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(1, 1, 1, 1);
        widget = new QWidget(DateTimeSetDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget#widget{\n"
"	background-color:rgba(220, 220, 220, 204);\n"
"}\n"
"\n"
"QWidget#label{\n"
"	background-color:rgba(0, 0, 0, 0);\n"
"}\n"
"\n"
"QWidget#widget_2{\n"
"	background-color: rgba(0, 0, 0, 0)\n"
"}\n"
"\n"
"QWidget QPushButton{\n"
"	font: 16pt \"Arial\";\n"
"}\n"
"\n"
"QWidget#widget_3{\n"
"	background-color: rgb(55, 55, 55);\n"
"}\n"
"\n"
"QWidget QLabel{\n"
"	color: rgb(125, 125, 125);\n"
"	font: bold 24pt \"Arial\";\n"
"	background-color: rgba(55, 55, 55, 0);\n"
"\n"
"}\n"
"QWidget QSpinBox{\n"
"  	color: rgb(125, 125, 125);\n"
"	font: bold 24pt \"Arial\";\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:0.5, stop:0 rgba(220, 220, 220, 255), stop:0.957143 rgba(190, 190, 190, 255), stop:1 rgba(220, 220, 220, 255));\n"
"	selection-color: rgb(125, 125, 125);\n"
"	border: 0px solid;\n"
"	border-radius: 2px;\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setHorizontalSpacing(9);
        gridLayout->setVerticalSpacing(6);
        gridLayout->setContentsMargins(9, 9, 9, 9);
        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShadow(QFrame::Sunken);
        line->setFrameShape(QFrame::HLine);

        gridLayout->addWidget(line, 1, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(16);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: bold 16pt \"Arial\";\n"
"color: rgb(50, 50, 50);"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setStyleSheet(QString::fromUtf8(""));
        gridLayout_3 = new QGridLayout(widget_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(0);
        gridLayout_3->setContentsMargins(-1, 9, -1, -1);
        label_2 = new QLabel(widget_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        spinBox_2 = new QSpinBox(widget_3);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinBox_2->sizePolicy().hasHeightForWidth());
        spinBox_2->setSizePolicy(sizePolicy1);
        spinBox_2->setAlignment(Qt::AlignCenter);
        spinBox_2->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout_3->addWidget(spinBox_2, 0, 2, 1, 1);

        spinBox_1 = new QSpinBox(widget_3);
        spinBox_1->setObjectName(QString::fromUtf8("spinBox_1"));
        sizePolicy1.setHeightForWidth(spinBox_1->sizePolicy().hasHeightForWidth());
        spinBox_1->setSizePolicy(sizePolicy1);
        spinBox_1->setAlignment(Qt::AlignCenter);
        spinBox_1->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout_3->addWidget(spinBox_1, 0, 0, 1, 1);

        label_3 = new QLabel(widget_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_3, 0, 3, 1, 1);

        spinBox_3 = new QSpinBox(widget_3);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        sizePolicy1.setHeightForWidth(spinBox_3->sizePolicy().hasHeightForWidth());
        spinBox_3->setSizePolicy(sizePolicy1);
        spinBox_3->setAlignment(Qt::AlignCenter);
        spinBox_3->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout_3->addWidget(spinBox_3, 0, 4, 1, 1);

        gridLayout_3->setColumnStretch(0, 5);
        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnStretch(2, 5);
        gridLayout_3->setColumnStretch(3, 1);
        gridLayout_3->setColumnStretch(4, 5);

        gridLayout->addWidget(widget_3, 2, 0, 1, 1);

        widget_2 = new QWidget(widget);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8(""));
        gridLayout_4 = new QGridLayout(widget_2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(5);
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(3, 3, 0, 0);
        horizontalSpacer = new QSpacerItem(111, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer, 0, 0, 1, 1);

        pushButton_cancel = new QPushButton(widget_2);
        pushButton_cancel->setObjectName(QString::fromUtf8("pushButton_cancel"));
        sizePolicy1.setHeightForWidth(pushButton_cancel->sizePolicy().hasHeightForWidth());
        pushButton_cancel->setSizePolicy(sizePolicy1);
        pushButton_cancel->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(pushButton_cancel, 0, 1, 1, 1);

        pushButton_ok = new QPushButton(widget_2);
        pushButton_ok->setObjectName(QString::fromUtf8("pushButton_ok"));
        sizePolicy1.setHeightForWidth(pushButton_ok->sizePolicy().hasHeightForWidth());
        pushButton_ok->setSizePolicy(sizePolicy1);
        pushButton_ok->setFocusPolicy(Qt::NoFocus);

        gridLayout_4->addWidget(pushButton_ok, 0, 2, 1, 1);

        gridLayout_4->setColumnStretch(0, 2);
        gridLayout_4->setColumnStretch(1, 1);
        gridLayout_4->setColumnStretch(2, 1);

        gridLayout->addWidget(widget_2, 3, 0, 1, 1);

        gridLayout->setRowStretch(0, 2);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 6);
        gridLayout->setRowStretch(3, 3);

        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(DateTimeSetDialog);

        QMetaObject::connectSlotsByName(DateTimeSetDialog);
    } // setupUi

    void retranslateUi(QDialog *DateTimeSetDialog)
    {
        DateTimeSetDialog->setWindowTitle(QApplication::translate("DateTimeSetDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        label_2->setText(QApplication::translate("DateTimeSetDialog", ":", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("DateTimeSetDialog", ":", 0, QApplication::UnicodeUTF8));
        pushButton_cancel->setText(QApplication::translate("DateTimeSetDialog", "&Cancel", 0, QApplication::UnicodeUTF8));
        pushButton_ok->setText(QApplication::translate("DateTimeSetDialog", "&Ok", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DateTimeSetDialog: public Ui_DateTimeSetDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATETIMESETDIALOG_H
