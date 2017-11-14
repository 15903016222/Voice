/********************************************************************************
** Form generated from reading UI file 'resetconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RESETCONFIGDIALOG_H
#define UI_RESETCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ResetConfigDialog
{
public:
    QGridLayout *gridLayout_2;
    QFrame *frame;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ResetConfigDialog)
    {
        if (ResetConfigDialog->objectName().isEmpty())
            ResetConfigDialog->setObjectName(QString::fromUtf8("ResetConfigDialog"));
        ResetConfigDialog->resize(303, 105);
        ResetConfigDialog->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(ResetConfigDialog);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        frame = new QFrame(ResetConfigDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        gridLayout = new QGridLayout(frame);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(9);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(://resource/tip.jpg);"));
        pushButton->setIconSize(QSize(64, 64));

        horizontalLayout->addWidget(pushButton);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);

        horizontalLayout->addWidget(label);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 10);

        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(frame);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(ResetConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ResetConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ResetConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ResetConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *ResetConfigDialog)
    {
        ResetConfigDialog->setWindowTitle(QApplication::translate("ResetConfigDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QString());
        label->setText(QApplication::translate("ResetConfigDialog", "Reset Config ?", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ResetConfigDialog: public Ui_ResetConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RESETCONFIGDIALOG_H
