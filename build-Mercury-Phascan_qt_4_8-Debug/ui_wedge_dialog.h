/********************************************************************************
** Form generated from reading UI file 'wedge_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WEDGE_DIALOG_H
#define UI_WEDGE_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WedgeDialog
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *selectTab;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QListWidget *dirListWidget;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_4;
    QListWidget *fileListWidget;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_5;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *okPushButton;
    QPushButton *cancelPushButton;
    QWidget *defineTab;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QListWidget *defineListWidget;
    QPushButton *delPushButton;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *modelLabel;
    QLabel *serialLabel;
    QLabel *waveTypeLabel;
    QLabel *angleLabel;
    QLabel *delayLabel;
    QLabel *OrientationLabel;
    QLabel *velocityLabel;
    QLabel *primaryOffsetLabel;
    QLabel *sndOffsetLabel;
    QLabel *HeightLabel;
    QLabel *LengthLabel;
    QLabel *refPointLlabel;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *modelLineEdit;
    QLineEdit *serialLineEdit;
    QComboBox *waveTypeComboBox;
    QDoubleSpinBox *angleDoubleSpinBox;
    QSpinBox *delaySpinBox;
    QComboBox *orientationComboBox;
    QDoubleSpinBox *velocityDoubleSpinBox;
    QDoubleSpinBox *primaryOffsetDoubleSpinBox;
    QDoubleSpinBox *sndOffsetDoubleSpinBox;
    QDoubleSpinBox *heightDoubleSpinBox;
    QDoubleSpinBox *lengthDoubleSpinBox;
    QDoubleSpinBox *refPointDoubleSpinBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *saveApplyPushButton;
    QPushButton *savePushButton;
    QPushButton *cancelDefinePushButton;

    void setupUi(QDialog *WedgeDialog)
    {
        if (WedgeDialog->objectName().isEmpty())
            WedgeDialog->setObjectName(QString::fromUtf8("WedgeDialog"));
        WedgeDialog->resize(564, 496);
        WedgeDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}"));
        verticalLayout = new QVBoxLayout(WedgeDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(WedgeDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        selectTab = new QWidget();
        selectTab->setObjectName(QString::fromUtf8("selectTab"));
        verticalLayout_9 = new QVBoxLayout(selectTab);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_3 = new QLabel(selectTab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_3);

        dirListWidget = new QListWidget(selectTab);
        dirListWidget->setObjectName(QString::fromUtf8("dirListWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dirListWidget->sizePolicy().hasHeightForWidth());
        dirListWidget->setSizePolicy(sizePolicy);

        verticalLayout_4->addWidget(dirListWidget);

        verticalLayout_4->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_4 = new QLabel(selectTab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label_4);

        fileListWidget = new QListWidget(selectTab);
        fileListWidget->setObjectName(QString::fromUtf8("fileListWidget"));
        sizePolicy.setHeightForWidth(fileListWidget->sizePolicy().hasHeightForWidth());
        fileListWidget->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(fileListWidget);

        verticalLayout_7->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_5 = new QLabel(selectTab);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_5);

        label = new QLabel(selectTab);
        label->setObjectName(QString::fromUtf8("label"));
        label->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setFrameShape(QFrame::NoFrame);
        label->setLineWidth(0);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        verticalLayout_8->addWidget(label);

        verticalLayout_8->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_8);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 2);
        horizontalLayout->setStretch(2, 3);

        verticalLayout_9->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okPushButton = new QPushButton(selectTab);
        okPushButton->setObjectName(QString::fromUtf8("okPushButton"));
        okPushButton->setMinimumSize(QSize(0, 35));

        horizontalLayout_2->addWidget(okPushButton);

        cancelPushButton = new QPushButton(selectTab);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));
        cancelPushButton->setMinimumSize(QSize(0, 35));

        horizontalLayout_2->addWidget(cancelPushButton);


        verticalLayout_9->addLayout(horizontalLayout_2);

        tabWidget->addTab(selectTab, QString());
        defineTab = new QWidget();
        defineTab->setObjectName(QString::fromUtf8("defineTab"));
        verticalLayout_10 = new QVBoxLayout(defineTab);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(defineTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_5->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        horizontalLayout_5->setStretch(0, 1);
        horizontalLayout_5->setStretch(1, 1);

        verticalLayout_10->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        defineListWidget = new QListWidget(defineTab);
        defineListWidget->setObjectName(QString::fromUtf8("defineListWidget"));

        verticalLayout_5->addWidget(defineListWidget);

        delPushButton = new QPushButton(defineTab);
        delPushButton->setObjectName(QString::fromUtf8("delPushButton"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(delPushButton->sizePolicy().hasHeightForWidth());
        delPushButton->setSizePolicy(sizePolicy2);
        delPushButton->setMinimumSize(QSize(0, 35));

        verticalLayout_5->addWidget(delPushButton);


        horizontalLayout_6->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        modelLabel = new QLabel(defineTab);
        modelLabel->setObjectName(QString::fromUtf8("modelLabel"));

        verticalLayout_3->addWidget(modelLabel);

        serialLabel = new QLabel(defineTab);
        serialLabel->setObjectName(QString::fromUtf8("serialLabel"));

        verticalLayout_3->addWidget(serialLabel);

        waveTypeLabel = new QLabel(defineTab);
        waveTypeLabel->setObjectName(QString::fromUtf8("waveTypeLabel"));

        verticalLayout_3->addWidget(waveTypeLabel);

        angleLabel = new QLabel(defineTab);
        angleLabel->setObjectName(QString::fromUtf8("angleLabel"));

        verticalLayout_3->addWidget(angleLabel);

        delayLabel = new QLabel(defineTab);
        delayLabel->setObjectName(QString::fromUtf8("delayLabel"));

        verticalLayout_3->addWidget(delayLabel);

        OrientationLabel = new QLabel(defineTab);
        OrientationLabel->setObjectName(QString::fromUtf8("OrientationLabel"));

        verticalLayout_3->addWidget(OrientationLabel);

        velocityLabel = new QLabel(defineTab);
        velocityLabel->setObjectName(QString::fromUtf8("velocityLabel"));

        verticalLayout_3->addWidget(velocityLabel);

        primaryOffsetLabel = new QLabel(defineTab);
        primaryOffsetLabel->setObjectName(QString::fromUtf8("primaryOffsetLabel"));

        verticalLayout_3->addWidget(primaryOffsetLabel);

        sndOffsetLabel = new QLabel(defineTab);
        sndOffsetLabel->setObjectName(QString::fromUtf8("sndOffsetLabel"));

        verticalLayout_3->addWidget(sndOffsetLabel);

        HeightLabel = new QLabel(defineTab);
        HeightLabel->setObjectName(QString::fromUtf8("HeightLabel"));

        verticalLayout_3->addWidget(HeightLabel);

        LengthLabel = new QLabel(defineTab);
        LengthLabel->setObjectName(QString::fromUtf8("LengthLabel"));

        verticalLayout_3->addWidget(LengthLabel);

        refPointLlabel = new QLabel(defineTab);
        refPointLlabel->setObjectName(QString::fromUtf8("refPointLlabel"));

        verticalLayout_3->addWidget(refPointLlabel);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        modelLineEdit = new QLineEdit(defineTab);
        modelLineEdit->setObjectName(QString::fromUtf8("modelLineEdit"));

        verticalLayout_2->addWidget(modelLineEdit);

        serialLineEdit = new QLineEdit(defineTab);
        serialLineEdit->setObjectName(QString::fromUtf8("serialLineEdit"));

        verticalLayout_2->addWidget(serialLineEdit);

        waveTypeComboBox = new QComboBox(defineTab);
        waveTypeComboBox->setObjectName(QString::fromUtf8("waveTypeComboBox"));

        verticalLayout_2->addWidget(waveTypeComboBox);

        angleDoubleSpinBox = new QDoubleSpinBox(defineTab);
        angleDoubleSpinBox->setObjectName(QString::fromUtf8("angleDoubleSpinBox"));
        angleDoubleSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        angleDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        angleDoubleSpinBox->setMinimum(0.5);
        angleDoubleSpinBox->setMaximum(20);
        angleDoubleSpinBox->setValue(1);

        verticalLayout_2->addWidget(angleDoubleSpinBox);

        delaySpinBox = new QSpinBox(defineTab);
        delaySpinBox->setObjectName(QString::fromUtf8("delaySpinBox"));
        delaySpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        delaySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        delaySpinBox->setMinimum(1);
        delaySpinBox->setMaximum(1024);

        verticalLayout_2->addWidget(delaySpinBox);

        orientationComboBox = new QComboBox(defineTab);
        orientationComboBox->setObjectName(QString::fromUtf8("orientationComboBox"));

        verticalLayout_2->addWidget(orientationComboBox);

        velocityDoubleSpinBox = new QDoubleSpinBox(defineTab);
        velocityDoubleSpinBox->setObjectName(QString::fromUtf8("velocityDoubleSpinBox"));
        velocityDoubleSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        velocityDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        velocityDoubleSpinBox->setValue(0);

        verticalLayout_2->addWidget(velocityDoubleSpinBox);

        primaryOffsetDoubleSpinBox = new QDoubleSpinBox(defineTab);
        primaryOffsetDoubleSpinBox->setObjectName(QString::fromUtf8("primaryOffsetDoubleSpinBox"));
        primaryOffsetDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        primaryOffsetDoubleSpinBox->setValue(1);

        verticalLayout_2->addWidget(primaryOffsetDoubleSpinBox);

        sndOffsetDoubleSpinBox = new QDoubleSpinBox(defineTab);
        sndOffsetDoubleSpinBox->setObjectName(QString::fromUtf8("sndOffsetDoubleSpinBox"));
        sndOffsetDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        verticalLayout_2->addWidget(sndOffsetDoubleSpinBox);

        heightDoubleSpinBox = new QDoubleSpinBox(defineTab);
        heightDoubleSpinBox->setObjectName(QString::fromUtf8("heightDoubleSpinBox"));
        heightDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        verticalLayout_2->addWidget(heightDoubleSpinBox);

        lengthDoubleSpinBox = new QDoubleSpinBox(defineTab);
        lengthDoubleSpinBox->setObjectName(QString::fromUtf8("lengthDoubleSpinBox"));
        lengthDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        verticalLayout_2->addWidget(lengthDoubleSpinBox);

        refPointDoubleSpinBox = new QDoubleSpinBox(defineTab);
        refPointDoubleSpinBox->setObjectName(QString::fromUtf8("refPointDoubleSpinBox"));
        refPointDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        verticalLayout_2->addWidget(refPointDoubleSpinBox);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        saveApplyPushButton = new QPushButton(defineTab);
        saveApplyPushButton->setObjectName(QString::fromUtf8("saveApplyPushButton"));
        sizePolicy2.setHeightForWidth(saveApplyPushButton->sizePolicy().hasHeightForWidth());
        saveApplyPushButton->setSizePolicy(sizePolicy2);
        saveApplyPushButton->setMinimumSize(QSize(0, 35));

        horizontalLayout_4->addWidget(saveApplyPushButton);

        savePushButton = new QPushButton(defineTab);
        savePushButton->setObjectName(QString::fromUtf8("savePushButton"));
        sizePolicy2.setHeightForWidth(savePushButton->sizePolicy().hasHeightForWidth());
        savePushButton->setSizePolicy(sizePolicy2);
        savePushButton->setMinimumSize(QSize(0, 35));

        horizontalLayout_4->addWidget(savePushButton);

        cancelDefinePushButton = new QPushButton(defineTab);
        cancelDefinePushButton->setObjectName(QString::fromUtf8("cancelDefinePushButton"));
        sizePolicy2.setHeightForWidth(cancelDefinePushButton->sizePolicy().hasHeightForWidth());
        cancelDefinePushButton->setSizePolicy(sizePolicy2);
        cancelDefinePushButton->setMinimumSize(QSize(0, 35));

        horizontalLayout_4->addWidget(cancelDefinePushButton);


        verticalLayout_6->addLayout(horizontalLayout_4);


        horizontalLayout_6->addLayout(verticalLayout_6);


        verticalLayout_10->addLayout(horizontalLayout_6);

        tabWidget->addTab(defineTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(WedgeDialog);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(WedgeDialog);
    } // setupUi

    void retranslateUi(QDialog *WedgeDialog)
    {
        WedgeDialog->setWindowTitle(QApplication::translate("WedgeDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("WedgeDialog", "Serial", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("WedgeDialog", "Wedge", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("WedgeDialog", "Information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("WedgeDialog", "Ultrasonic phased array wedge family.", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("WedgeDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("WedgeDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(selectTab), QApplication::translate("WedgeDialog", "Select", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("WedgeDialog", "Wedge", 0, QApplication::UnicodeUTF8));
        delPushButton->setText(QApplication::translate("WedgeDialog", "Delete", 0, QApplication::UnicodeUTF8));
        modelLabel->setText(QApplication::translate("WedgeDialog", "Model", 0, QApplication::UnicodeUTF8));
        serialLabel->setText(QApplication::translate("WedgeDialog", "Serial", 0, QApplication::UnicodeUTF8));
        waveTypeLabel->setText(QApplication::translate("WedgeDialog", "Wave Type", 0, QApplication::UnicodeUTF8));
        angleLabel->setText(QApplication::translate("WedgeDialog", "Angle", 0, QApplication::UnicodeUTF8));
        delayLabel->setText(QApplication::translate("WedgeDialog", "Delay", 0, QApplication::UnicodeUTF8));
        OrientationLabel->setText(QApplication::translate("WedgeDialog", "Orientation", 0, QApplication::UnicodeUTF8));
        velocityLabel->setText(QApplication::translate("WedgeDialog", "Velocity", 0, QApplication::UnicodeUTF8));
        primaryOffsetLabel->setText(QApplication::translate("WedgeDialog", "Primary Offset", 0, QApplication::UnicodeUTF8));
        sndOffsetLabel->setText(QApplication::translate("WedgeDialog", "Secondary Offset", 0, QApplication::UnicodeUTF8));
        HeightLabel->setText(QApplication::translate("WedgeDialog", "Height", 0, QApplication::UnicodeUTF8));
        LengthLabel->setText(QApplication::translate("WedgeDialog", "Length", 0, QApplication::UnicodeUTF8));
        refPointLlabel->setText(QApplication::translate("WedgeDialog", "Ref Point", 0, QApplication::UnicodeUTF8));
        modelLineEdit->setText(QString());
        serialLineEdit->setText(QString());
        waveTypeComboBox->clear();
        waveTypeComboBox->insertItems(0, QStringList()
         << QApplication::translate("WedgeDialog", "L", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WedgeDialog", "S", 0, QApplication::UnicodeUTF8)
        );
        angleDoubleSpinBox->setSuffix(QApplication::translate("WedgeDialog", " \302\260", 0, QApplication::UnicodeUTF8));
        delaySpinBox->setSuffix(QApplication::translate("WedgeDialog", " us", 0, QApplication::UnicodeUTF8));
        orientationComboBox->clear();
        orientationComboBox->insertItems(0, QStringList()
         << QApplication::translate("WedgeDialog", "Normal", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("WedgeDialog", "Revesal", 0, QApplication::UnicodeUTF8)
        );
        velocityDoubleSpinBox->setSuffix(QApplication::translate("WedgeDialog", " mm", 0, QApplication::UnicodeUTF8));
        primaryOffsetDoubleSpinBox->setSuffix(QApplication::translate("WedgeDialog", " mm", 0, QApplication::UnicodeUTF8));
        sndOffsetDoubleSpinBox->setSuffix(QApplication::translate("WedgeDialog", " mm", 0, QApplication::UnicodeUTF8));
        heightDoubleSpinBox->setSuffix(QApplication::translate("WedgeDialog", " mm", 0, QApplication::UnicodeUTF8));
        lengthDoubleSpinBox->setPrefix(QString());
        lengthDoubleSpinBox->setSuffix(QApplication::translate("WedgeDialog", " mm", 0, QApplication::UnicodeUTF8));
        refPointDoubleSpinBox->setPrefix(QString());
        refPointDoubleSpinBox->setSuffix(QApplication::translate("WedgeDialog", " mm", 0, QApplication::UnicodeUTF8));
        saveApplyPushButton->setText(QApplication::translate("WedgeDialog", "Save && Apply", 0, QApplication::UnicodeUTF8));
        savePushButton->setText(QApplication::translate("WedgeDialog", "Save", 0, QApplication::UnicodeUTF8));
        cancelDefinePushButton->setText(QApplication::translate("WedgeDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(defineTab), QApplication::translate("WedgeDialog", "Define", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class WedgeDialog: public Ui_WedgeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WEDGE_DIALOG_H
