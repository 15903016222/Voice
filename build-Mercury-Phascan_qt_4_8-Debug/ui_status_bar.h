/********************************************************************************
** Form generated from reading UI file 'status_bar.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STATUS_BAR_H
#define UI_STATUS_BAR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StatusBar
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *versionLabel;
    QLabel *scanEncLabel;
    QLabel *indexEncLabel;
    QLabel *label_4;
    QLabel *prfLabel;
    QLabel *label_2;
    QLabel *timeLabel;

    void setupUi(QWidget *StatusBar)
    {
        if (StatusBar->objectName().isEmpty())
            StatusBar->setObjectName(QString::fromUtf8("StatusBar"));
        StatusBar->setWindowModality(Qt::NonModal);
        StatusBar->resize(800, 20);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(StatusBar->sizePolicy().hasHeightForWidth());
        StatusBar->setSizePolicy(sizePolicy);
        StatusBar->setMaximumSize(QSize(16777215, 16777215));
        QFont font;
        font.setPointSize(6);
        StatusBar->setFont(font);
        StatusBar->setWindowOpacity(1);
        StatusBar->setLayoutDirection(Qt::LeftToRight);
        StatusBar->setAutoFillBackground(false);
        StatusBar->setStyleSheet(QString::fromUtf8("/*\n"
"#StatusBar{\n"
"	background-color: rgb(210, 150, 0); \n"
"}\n"
"*/\n"
"\n"
"QLabel {    \n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(210, 150, 0);    \n"
"	font:  bold 10pt \"Ubuntu\";\n"
"}\n"
"\n"
"#versionLabel\n"
"{\n"
"	border-right: 1px solid qlineargradient(spread:repeat, x1:0, y1:0, x2:0, y2:1, stop:0.05 rgba(210, 150, 0, 255), stop:0.3 rgba(0, 0, 0, 255), stop:0.7 rgba(0, 0, 0, 255), stop:0.95 rgba(210, 150, 0, 255));\n"
"}\n"
"\n"
"#scanEncLabel,#indexEncLabel,#label_2,#label_4,#label_1\n"
"{\n"
"	border-right: 1px solid qlineargradient(spread:repeat, x1:0, y1:0, x2:0, y2:1, stop:0.05 rgba(210, 150, 0, 255), stop:0.3 rgba(0, 0, 0, 255), stop:0.7 rgba(0, 0, 0, 255), stop:0.95 rgba(210, 150, 0, 255));\n"
"	border-left: 1px solid qlineargradient(spread:repeat, x1:0, y1:0, x2:0, y2:1, stop:0.05 rgba(210, 150, 0, 255), stop:0.3 rgba(255, 255, 255, 255), stop:0.7 rgba(255, 255, 255, 255), stop:0.95 rgba(210, 150, 0, 255));\n"
"}\n"
"\n"
"#timeLabel\n"
"{\n"
"	border-left: 1px solid ql"
                        "ineargradient(spread:repeat, x1:0, y1:0, x2:0, y2:1, stop:0.05 rgba(210, 150, 0, 255), stop:0.3 rgba(255, 255, 255, 255), stop:0.7 rgba(255, 255, 255, 255), stop:0.95 rgba(210, 150, 0, 255));\n"
"}"));
        horizontalLayout = new QHBoxLayout(StatusBar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        versionLabel = new QLabel(StatusBar);
        versionLabel->setObjectName(QString::fromUtf8("versionLabel"));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(210, 150, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        versionLabel->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Ubuntu"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setItalic(false);
        font1.setWeight(75);
        versionLabel->setFont(font1);
        versionLabel->setFrameShape(QFrame::NoFrame);
        versionLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(versionLabel);

        scanEncLabel = new QLabel(StatusBar);
        scanEncLabel->setObjectName(QString::fromUtf8("scanEncLabel"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        scanEncLabel->setPalette(palette1);
        scanEncLabel->setFont(font1);
        scanEncLabel->setFrameShape(QFrame::NoFrame);
        scanEncLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(scanEncLabel);

        indexEncLabel = new QLabel(StatusBar);
        indexEncLabel->setObjectName(QString::fromUtf8("indexEncLabel"));
        indexEncLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(indexEncLabel);

        label_4 = new QLabel(StatusBar);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_4->setPalette(palette2);
        label_4->setFont(font1);
        label_4->setFrameShape(QFrame::NoFrame);
        label_4->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_4);

        prfLabel = new QLabel(StatusBar);
        prfLabel->setObjectName(QString::fromUtf8("prfLabel"));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        prfLabel->setPalette(palette3);
        prfLabel->setFont(font1);
        prfLabel->setFrameShape(QFrame::NoFrame);
        prfLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(prfLabel);

        label_2 = new QLabel(StatusBar);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        label_2->setPalette(palette4);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8(""));
        label_2->setFrameShape(QFrame::NoFrame);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_2);

        timeLabel = new QLabel(StatusBar);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        timeLabel->setPalette(palette5);
        timeLabel->setFont(font1);
        timeLabel->setFrameShape(QFrame::NoFrame);
        timeLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(timeLabel);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 1);
        horizontalLayout->setStretch(2, 1);
        horizontalLayout->setStretch(3, 1);
        horizontalLayout->setStretch(4, 1);
        horizontalLayout->setStretch(5, 1);
        horizontalLayout->setStretch(6, 1);

        retranslateUi(StatusBar);

        QMetaObject::connectSlotsByName(StatusBar);
    } // setupUi

    void retranslateUi(QWidget *StatusBar)
    {
        StatusBar->setWindowTitle(QApplication::translate("StatusBar", "Form", 0, QApplication::UnicodeUTF8));
        versionLabel->setText(QApplication::translate("StatusBar", "32:64PR 3.5.1", 0, QApplication::UnicodeUTF8));
        scanEncLabel->setText(QApplication::translate("StatusBar", "Scan:0.00 s", 0, QApplication::UnicodeUTF8));
        indexEncLabel->setText(QApplication::translate("StatusBar", "Index:0.00 mm", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("StatusBar", "Rouxing.cfg", 0, QApplication::UnicodeUTF8));
        prfLabel->setText(QApplication::translate("StatusBar", "PRF: 143(7579)", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("StatusBar", "V:71.5mm/s", 0, QApplication::UnicodeUTF8));
        timeLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StatusBar: public Ui_StatusBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STATUS_BAR_H
