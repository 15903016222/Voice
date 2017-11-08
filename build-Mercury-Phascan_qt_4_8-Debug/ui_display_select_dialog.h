/********************************************************************************
** Form generated from reading UI file 'display_select_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DISPLAY_SELECT_DIALOG_H
#define UI_DISPLAY_SELECT_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DisplaySelectDialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_all;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QDialogButtonBox *buttonBox;
    QButtonGroup *buttonGroup;

    void setupUi(QDialog *DisplaySelectDialog)
    {
        if (DisplaySelectDialog->objectName().isEmpty())
            DisplaySelectDialog->setObjectName(QString::fromUtf8("DisplaySelectDialog"));
        DisplaySelectDialog->resize(622, 456);
        DisplaySelectDialog->setLayoutDirection(Qt::LeftToRight);
        verticalLayout = new QVBoxLayout(DisplaySelectDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(3, 2, 3, 3);
        groupBox = new QGroupBox(DisplaySelectDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox_all = new QCheckBox(groupBox);
        checkBox_all->setObjectName(QString::fromUtf8("checkBox_all"));
        checkBox_all->setLayoutDirection(Qt::RightToLeft);
        checkBox_all->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));
        checkBox_all->setIconSize(QSize(16, 16));

        horizontalLayout->addWidget(checkBox_all);

        checkBox_1 = new QCheckBox(groupBox);
        buttonGroup = new QButtonGroup(DisplaySelectDialog);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->setExclusive(false);
        buttonGroup->addButton(checkBox_1);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setLayoutDirection(Qt::RightToLeft);
        checkBox_1->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));

        horizontalLayout->addWidget(checkBox_1);

        checkBox_2 = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_2);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setLayoutDirection(Qt::RightToLeft);
        checkBox_2->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));

        horizontalLayout->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_3);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setLayoutDirection(Qt::RightToLeft);
        checkBox_3->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));

        horizontalLayout->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_4);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setLayoutDirection(Qt::RightToLeft);
        checkBox_4->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));

        horizontalLayout->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_5);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setLayoutDirection(Qt::RightToLeft);
        checkBox_5->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));

        horizontalLayout->addWidget(checkBox_5);

        checkBox_6 = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_6);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setLayoutDirection(Qt::RightToLeft);
        checkBox_6->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));

        horizontalLayout->addWidget(checkBox_6);

        checkBox_7 = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_7);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setLayoutDirection(Qt::RightToLeft);
        checkBox_7->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));

        horizontalLayout->addWidget(checkBox_7);

        checkBox_8 = new QCheckBox(groupBox);
        buttonGroup->addButton(checkBox_8);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setLayoutDirection(Qt::RightToLeft);
        checkBox_8->setStyleSheet(QString::fromUtf8("QCheckBox::Indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}"));
        checkBox_8->setAutoExclusive(false);

        horizontalLayout->addWidget(checkBox_8);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(DisplaySelectDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setAlignment(Qt::AlignCenter);
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addWidget(groupBox_2);

        buttonBox = new QDialogButtonBox(DisplaySelectDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buttonBox->sizePolicy().hasHeightForWidth());
        buttonBox->setSizePolicy(sizePolicy);
        buttonBox->setStyleSheet(QString::fromUtf8(" QPushButton\n"
"{\n"
"	height:30px;\n"
"}"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);

        verticalLayout->setStretch(1, 1);

        retranslateUi(DisplaySelectDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), DisplaySelectDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(DisplaySelectDialog);
    } // setupUi

    void retranslateUi(QDialog *DisplaySelectDialog)
    {
        DisplaySelectDialog->setWindowTitle(QApplication::translate("DisplaySelectDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("DisplaySelectDialog", "Group Select", 0, QApplication::UnicodeUTF8));
        checkBox_all->setText(QApplication::translate("DisplaySelectDialog", "All", 0, QApplication::UnicodeUTF8));
        checkBox_1->setText(QApplication::translate("DisplaySelectDialog", "G1", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("DisplaySelectDialog", "G2", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("DisplaySelectDialog", "G3", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("DisplaySelectDialog", "G4", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("DisplaySelectDialog", "G5", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("DisplaySelectDialog", "G6", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("DisplaySelectDialog", "G7", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("DisplaySelectDialog", "G8", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("DisplaySelectDialog", "Layout Select", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DisplaySelectDialog: public Ui_DisplaySelectDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DISPLAY_SELECT_DIALOG_H
