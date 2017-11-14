/********************************************************************************
** Form generated from reading UI file 'virtualkeyboard.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIRTUALKEYBOARD_H
#define UI_VIRTUALKEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VirtualKeyboard
{
public:
    QGridLayout *gridLayout;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_1;
    QPushButton *panelButton_0;
    QPushButton *panelButton_1;
    QPushButton *panelButton_2;
    QPushButton *panelButton_4;
    QPushButton *panelButton_7;
    QPushButton *panelButton_3;
    QPushButton *panelButton_5;
    QPushButton *panelButton_6;
    QPushButton *panelButton_8;
    QPushButton *panelButton_9;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_7;

    void setupUi(QWidget *VirtualKeyboard)
    {
        if (VirtualKeyboard->objectName().isEmpty())
            VirtualKeyboard->setObjectName(QString::fromUtf8("VirtualKeyboard"));
        VirtualKeyboard->resize(213, 266);
        VirtualKeyboard->setStyleSheet(QString::fromUtf8("QWidget QPushButton {\n"
"	font: bold 14 \"Arial\";\n"
"}"));
        gridLayout = new QGridLayout(VirtualKeyboard);
        gridLayout->setSpacing(3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        pushButton_5 = new QPushButton(VirtualKeyboard);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy);
        pushButton_5->setMaximumSize(QSize(50, 16777215));
        QFont font;
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(1);
        pushButton_5->setFont(font);
        pushButton_5->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_5, 3, 3, 2, 1);

        pushButton_6 = new QPushButton(VirtualKeyboard);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy);
        pushButton_6->setMinimumSize(QSize(50, 50));
        pushButton_6->setMaximumSize(QSize(50, 16777215));

        gridLayout->addWidget(pushButton_6, 0, 3, 1, 1);

        pushButton_1 = new QPushButton(VirtualKeyboard);
        pushButton_1->setObjectName(QString::fromUtf8("pushButton_1"));
        sizePolicy.setHeightForWidth(pushButton_1->sizePolicy().hasHeightForWidth());
        pushButton_1->setSizePolicy(sizePolicy);
        pushButton_1->setMinimumSize(QSize(50, 50));
        pushButton_1->setMaximumSize(QSize(50, 16777215));
        pushButton_1->setFont(font);
        pushButton_1->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_1, 4, 2, 1, 1);

        panelButton_0 = new QPushButton(VirtualKeyboard);
        panelButton_0->setObjectName(QString::fromUtf8("panelButton_0"));
        sizePolicy.setHeightForWidth(panelButton_0->sizePolicy().hasHeightForWidth());
        panelButton_0->setSizePolicy(sizePolicy);
        panelButton_0->setMinimumSize(QSize(50, 50));
        panelButton_0->setMaximumSize(QSize(16777215, 50));
        panelButton_0->setFont(font);
        panelButton_0->setFocusPolicy(Qt::NoFocus);
        panelButton_0->setProperty("buttonValue", QVariant(QChar(48)));

        gridLayout->addWidget(panelButton_0, 4, 0, 1, 2);

        panelButton_1 = new QPushButton(VirtualKeyboard);
        panelButton_1->setObjectName(QString::fromUtf8("panelButton_1"));
        sizePolicy.setHeightForWidth(panelButton_1->sizePolicy().hasHeightForWidth());
        panelButton_1->setSizePolicy(sizePolicy);
        panelButton_1->setMinimumSize(QSize(50, 50));
        panelButton_1->setMaximumSize(QSize(50, 50));
        panelButton_1->setFont(font);
        panelButton_1->setFocusPolicy(Qt::NoFocus);
        panelButton_1->setProperty("buttonValue", QVariant(QChar(49)));

        gridLayout->addWidget(panelButton_1, 3, 0, 1, 1);

        panelButton_2 = new QPushButton(VirtualKeyboard);
        panelButton_2->setObjectName(QString::fromUtf8("panelButton_2"));
        sizePolicy.setHeightForWidth(panelButton_2->sizePolicy().hasHeightForWidth());
        panelButton_2->setSizePolicy(sizePolicy);
        panelButton_2->setMinimumSize(QSize(50, 50));
        panelButton_2->setMaximumSize(QSize(50, 50));
        panelButton_2->setFont(font);
        panelButton_2->setFocusPolicy(Qt::NoFocus);
        panelButton_2->setProperty("buttonValue", QVariant(QChar(50)));

        gridLayout->addWidget(panelButton_2, 3, 1, 1, 1);

        panelButton_4 = new QPushButton(VirtualKeyboard);
        panelButton_4->setObjectName(QString::fromUtf8("panelButton_4"));
        sizePolicy.setHeightForWidth(panelButton_4->sizePolicy().hasHeightForWidth());
        panelButton_4->setSizePolicy(sizePolicy);
        panelButton_4->setMinimumSize(QSize(50, 50));
        panelButton_4->setMaximumSize(QSize(50, 50));
        panelButton_4->setFont(font);
        panelButton_4->setFocusPolicy(Qt::NoFocus);
        panelButton_4->setProperty("buttonValue", QVariant(QChar(52)));

        gridLayout->addWidget(panelButton_4, 2, 0, 1, 1);

        panelButton_7 = new QPushButton(VirtualKeyboard);
        panelButton_7->setObjectName(QString::fromUtf8("panelButton_7"));
        sizePolicy.setHeightForWidth(panelButton_7->sizePolicy().hasHeightForWidth());
        panelButton_7->setSizePolicy(sizePolicy);
        panelButton_7->setMinimumSize(QSize(50, 50));
        panelButton_7->setMaximumSize(QSize(50, 50));
        panelButton_7->setFont(font);
        panelButton_7->setFocusPolicy(Qt::NoFocus);
        panelButton_7->setProperty("buttonValue", QVariant(QChar(55)));

        gridLayout->addWidget(panelButton_7, 1, 0, 1, 1);

        panelButton_3 = new QPushButton(VirtualKeyboard);
        panelButton_3->setObjectName(QString::fromUtf8("panelButton_3"));
        sizePolicy.setHeightForWidth(panelButton_3->sizePolicy().hasHeightForWidth());
        panelButton_3->setSizePolicy(sizePolicy);
        panelButton_3->setMinimumSize(QSize(50, 50));
        panelButton_3->setMaximumSize(QSize(50, 50));
        panelButton_3->setFont(font);
        panelButton_3->setFocusPolicy(Qt::NoFocus);
        panelButton_3->setProperty("buttonValue", QVariant(QChar(51)));

        gridLayout->addWidget(panelButton_3, 3, 2, 1, 1);

        panelButton_5 = new QPushButton(VirtualKeyboard);
        panelButton_5->setObjectName(QString::fromUtf8("panelButton_5"));
        sizePolicy.setHeightForWidth(panelButton_5->sizePolicy().hasHeightForWidth());
        panelButton_5->setSizePolicy(sizePolicy);
        panelButton_5->setMinimumSize(QSize(50, 50));
        panelButton_5->setMaximumSize(QSize(50, 50));
        panelButton_5->setFont(font);
        panelButton_5->setFocusPolicy(Qt::NoFocus);
        panelButton_5->setProperty("buttonValue", QVariant(QChar(53)));

        gridLayout->addWidget(panelButton_5, 2, 1, 1, 1);

        panelButton_6 = new QPushButton(VirtualKeyboard);
        panelButton_6->setObjectName(QString::fromUtf8("panelButton_6"));
        sizePolicy.setHeightForWidth(panelButton_6->sizePolicy().hasHeightForWidth());
        panelButton_6->setSizePolicy(sizePolicy);
        panelButton_6->setMinimumSize(QSize(50, 50));
        panelButton_6->setMaximumSize(QSize(50, 50));
        panelButton_6->setFont(font);
        panelButton_6->setFocusPolicy(Qt::NoFocus);
        panelButton_6->setProperty("buttonValue", QVariant(QChar(54)));

        gridLayout->addWidget(panelButton_6, 2, 2, 1, 1);

        panelButton_8 = new QPushButton(VirtualKeyboard);
        panelButton_8->setObjectName(QString::fromUtf8("panelButton_8"));
        sizePolicy.setHeightForWidth(panelButton_8->sizePolicy().hasHeightForWidth());
        panelButton_8->setSizePolicy(sizePolicy);
        panelButton_8->setMinimumSize(QSize(50, 50));
        panelButton_8->setMaximumSize(QSize(50, 50));
        panelButton_8->setFont(font);
        panelButton_8->setFocusPolicy(Qt::NoFocus);
        panelButton_8->setProperty("buttonValue", QVariant(QChar(56)));

        gridLayout->addWidget(panelButton_8, 1, 1, 1, 1);

        panelButton_9 = new QPushButton(VirtualKeyboard);
        panelButton_9->setObjectName(QString::fromUtf8("panelButton_9"));
        sizePolicy.setHeightForWidth(panelButton_9->sizePolicy().hasHeightForWidth());
        panelButton_9->setSizePolicy(sizePolicy);
        panelButton_9->setMinimumSize(QSize(50, 50));
        panelButton_9->setMaximumSize(QSize(50, 50));
        panelButton_9->setFont(font);
        panelButton_9->setFocusPolicy(Qt::NoFocus);
        panelButton_9->setProperty("buttonValue", QVariant(QChar(57)));

        gridLayout->addWidget(panelButton_9, 1, 2, 1, 1);

        pushButton_4 = new QPushButton(VirtualKeyboard);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy);
        pushButton_4->setMinimumSize(QSize(50, 50));
        pushButton_4->setMaximumSize(QSize(50, 50));
        pushButton_4->setFont(font);
        pushButton_4->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_4, 0, 2, 1, 1);

        pushButton_2 = new QPushButton(VirtualKeyboard);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setMinimumSize(QSize(50, 50));
        pushButton_2->setMaximumSize(QSize(50, 16777215));
        pushButton_2->setFont(font);
        pushButton_2->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_2, 1, 3, 2, 1);

        pushButton_3 = new QPushButton(VirtualKeyboard);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy);
        pushButton_3->setMinimumSize(QSize(50, 50));
        pushButton_3->setMaximumSize(QSize(50, 50));
        pushButton_3->setFont(font);
        pushButton_3->setFocusPolicy(Qt::NoFocus);

        gridLayout->addWidget(pushButton_3, 0, 1, 1, 1);

        pushButton_7 = new QPushButton(VirtualKeyboard);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy);
        pushButton_7->setMaximumSize(QSize(50, 50));

        gridLayout->addWidget(pushButton_7, 0, 0, 1, 1);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 1);
        gridLayout->setRowStretch(2, 1);
        gridLayout->setRowStretch(3, 1);
        gridLayout->setRowStretch(4, 1);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);

        retranslateUi(VirtualKeyboard);

        QMetaObject::connectSlotsByName(VirtualKeyboard);
    } // setupUi

    void retranslateUi(QWidget *VirtualKeyboard)
    {
        VirtualKeyboard->setWindowTitle(QApplication::translate("VirtualKeyboard", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_5->setText(QApplication::translate("VirtualKeyboard", "Enter", 0, QApplication::UnicodeUTF8));
        pushButton_6->setText(QApplication::translate("VirtualKeyboard", " \342\200\224", 0, QApplication::UnicodeUTF8));
        pushButton_1->setText(QApplication::translate("VirtualKeyboard", ".", 0, QApplication::UnicodeUTF8));
        panelButton_0->setText(QApplication::translate("VirtualKeyboard", "0", 0, QApplication::UnicodeUTF8));
        panelButton_1->setText(QApplication::translate("VirtualKeyboard", "1", 0, QApplication::UnicodeUTF8));
        panelButton_2->setText(QApplication::translate("VirtualKeyboard", "2", 0, QApplication::UnicodeUTF8));
        panelButton_4->setText(QApplication::translate("VirtualKeyboard", "4", 0, QApplication::UnicodeUTF8));
        panelButton_7->setText(QApplication::translate("VirtualKeyboard", "7", 0, QApplication::UnicodeUTF8));
        panelButton_3->setText(QApplication::translate("VirtualKeyboard", "3", 0, QApplication::UnicodeUTF8));
        panelButton_5->setText(QApplication::translate("VirtualKeyboard", "5", 0, QApplication::UnicodeUTF8));
        panelButton_6->setText(QApplication::translate("VirtualKeyboard", "6", 0, QApplication::UnicodeUTF8));
        panelButton_8->setText(QApplication::translate("VirtualKeyboard", "8", 0, QApplication::UnicodeUTF8));
        panelButton_9->setText(QApplication::translate("VirtualKeyboard", "9", 0, QApplication::UnicodeUTF8));
        pushButton_4->setText(QApplication::translate("VirtualKeyboard", "\342\206\222", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("VirtualKeyboard", "Del", 0, QApplication::UnicodeUTF8));
        pushButton_3->setText(QApplication::translate("VirtualKeyboard", "\342\206\220", 0, QApplication::UnicodeUTF8));
        pushButton_7->setText(QApplication::translate("VirtualKeyboard", "Esc", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class VirtualKeyboard: public Ui_VirtualKeyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIRTUALKEYBOARD_H
