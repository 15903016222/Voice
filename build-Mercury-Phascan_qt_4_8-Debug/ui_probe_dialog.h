/********************************************************************************
** Form generated from reading UI file 'probe_dialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROBE_DIALOG_H
#define UI_PROBE_DIALOG_H

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

class Ui_ProbeDialog
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
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_2;
    QListWidget *defineListWidget;
    QPushButton *delPushButton;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *modelLabel;
    QLabel *serialLabel;
    QLabel *typeLabel;
    QLabel *freqLabel;
    QLabel *priElemQtyLabel;
    QLabel *secElemQtyLabel;
    QLabel *refPointLabel;
    QLabel *priPitchLabel;
    QLabel *secPitchLabel;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *modelLineEdit;
    QLineEdit *serialLineEdit;
    QComboBox *typeComboBox;
    QDoubleSpinBox *freqDoubleSpinBox;
    QSpinBox *priElemQtySpinBox;
    QSpinBox *secElemQtySpinBox;
    QDoubleSpinBox *refPointDoubleSpinBox;
    QDoubleSpinBox *priPitchDoubleSpinBox;
    QDoubleSpinBox *secPitchDoubleSpinBox;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *saveApplyPushButton;
    QPushButton *savePushButton;
    QPushButton *cancelDefinePushButton;

    void setupUi(QDialog *ProbeDialog)
    {
        if (ProbeDialog->objectName().isEmpty())
            ProbeDialog->setObjectName(QString::fromUtf8("ProbeDialog"));
        ProbeDialog->resize(564, 384);
        ProbeDialog->setStyleSheet(QString::fromUtf8("QDialog {\n"
"background-color: rgba(255, 255, 255, 0);\n"
"}"));
        verticalLayout = new QVBoxLayout(ProbeDialog);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tabWidget = new QTabWidget(ProbeDialog);
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
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Preferred);
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
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

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
        horizontalLayout_5 = new QHBoxLayout(defineTab);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_2 = new QLabel(defineTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_2);

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

        verticalLayout_5->setStretch(1, 1);

        horizontalLayout_5->addLayout(verticalLayout_5);

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

        typeLabel = new QLabel(defineTab);
        typeLabel->setObjectName(QString::fromUtf8("typeLabel"));

        verticalLayout_3->addWidget(typeLabel);

        freqLabel = new QLabel(defineTab);
        freqLabel->setObjectName(QString::fromUtf8("freqLabel"));

        verticalLayout_3->addWidget(freqLabel);

        priElemQtyLabel = new QLabel(defineTab);
        priElemQtyLabel->setObjectName(QString::fromUtf8("priElemQtyLabel"));

        verticalLayout_3->addWidget(priElemQtyLabel);

        secElemQtyLabel = new QLabel(defineTab);
        secElemQtyLabel->setObjectName(QString::fromUtf8("secElemQtyLabel"));

        verticalLayout_3->addWidget(secElemQtyLabel);

        refPointLabel = new QLabel(defineTab);
        refPointLabel->setObjectName(QString::fromUtf8("refPointLabel"));

        verticalLayout_3->addWidget(refPointLabel);

        priPitchLabel = new QLabel(defineTab);
        priPitchLabel->setObjectName(QString::fromUtf8("priPitchLabel"));

        verticalLayout_3->addWidget(priPitchLabel);

        secPitchLabel = new QLabel(defineTab);
        secPitchLabel->setObjectName(QString::fromUtf8("secPitchLabel"));

        verticalLayout_3->addWidget(secPitchLabel);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        modelLineEdit = new QLineEdit(defineTab);
        modelLineEdit->setObjectName(QString::fromUtf8("modelLineEdit"));

        verticalLayout_2->addWidget(modelLineEdit);

        serialLineEdit = new QLineEdit(defineTab);
        serialLineEdit->setObjectName(QString::fromUtf8("serialLineEdit"));

        verticalLayout_2->addWidget(serialLineEdit);

        typeComboBox = new QComboBox(defineTab);
        typeComboBox->setObjectName(QString::fromUtf8("typeComboBox"));

        verticalLayout_2->addWidget(typeComboBox);

        freqDoubleSpinBox = new QDoubleSpinBox(defineTab);
        freqDoubleSpinBox->setObjectName(QString::fromUtf8("freqDoubleSpinBox"));
        freqDoubleSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        freqDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        freqDoubleSpinBox->setMinimum(0.5);
        freqDoubleSpinBox->setMaximum(20);
        freqDoubleSpinBox->setValue(1);

        verticalLayout_2->addWidget(freqDoubleSpinBox);

        priElemQtySpinBox = new QSpinBox(defineTab);
        priElemQtySpinBox->setObjectName(QString::fromUtf8("priElemQtySpinBox"));
        priElemQtySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        priElemQtySpinBox->setMinimum(1);

        verticalLayout_2->addWidget(priElemQtySpinBox);

        secElemQtySpinBox = new QSpinBox(defineTab);
        secElemQtySpinBox->setObjectName(QString::fromUtf8("secElemQtySpinBox"));
        secElemQtySpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        secElemQtySpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        secElemQtySpinBox->setMinimum(1);
        secElemQtySpinBox->setMaximum(1024);

        verticalLayout_2->addWidget(secElemQtySpinBox);

        refPointDoubleSpinBox = new QDoubleSpinBox(defineTab);
        refPointDoubleSpinBox->setObjectName(QString::fromUtf8("refPointDoubleSpinBox"));
        refPointDoubleSpinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        refPointDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        refPointDoubleSpinBox->setValue(0);

        verticalLayout_2->addWidget(refPointDoubleSpinBox);

        priPitchDoubleSpinBox = new QDoubleSpinBox(defineTab);
        priPitchDoubleSpinBox->setObjectName(QString::fromUtf8("priPitchDoubleSpinBox"));
        priPitchDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        priPitchDoubleSpinBox->setValue(1);

        verticalLayout_2->addWidget(priPitchDoubleSpinBox);

        secPitchDoubleSpinBox = new QDoubleSpinBox(defineTab);
        secPitchDoubleSpinBox->setObjectName(QString::fromUtf8("secPitchDoubleSpinBox"));
        secPitchDoubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);

        verticalLayout_2->addWidget(secPitchDoubleSpinBox);


        horizontalLayout_3->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout_3);

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

        verticalLayout_6->setStretch(0, 1);

        horizontalLayout_5->addLayout(verticalLayout_6);

        horizontalLayout_5->setStretch(0, 4);
        horizontalLayout_5->setStretch(1, 5);
        tabWidget->addTab(defineTab, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(ProbeDialog);

        tabWidget->setCurrentIndex(1);
        typeComboBox->setCurrentIndex(3);


        QMetaObject::connectSlotsByName(ProbeDialog);
    } // setupUi

    void retranslateUi(QDialog *ProbeDialog)
    {
        ProbeDialog->setWindowTitle(QApplication::translate("ProbeDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("ProbeDialog", "Serial", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("ProbeDialog", "Probe", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("ProbeDialog", "Information", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ProbeDialog", "Ultrasonic phased array probe family.", 0, QApplication::UnicodeUTF8));
        okPushButton->setText(QApplication::translate("ProbeDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("ProbeDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(selectTab), QApplication::translate("ProbeDialog", "Select", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("ProbeDialog", "Probe Name", 0, QApplication::UnicodeUTF8));
        delPushButton->setText(QApplication::translate("ProbeDialog", "Delete", 0, QApplication::UnicodeUTF8));
        modelLabel->setText(QApplication::translate("ProbeDialog", "Model", 0, QApplication::UnicodeUTF8));
        serialLabel->setText(QApplication::translate("ProbeDialog", "Serial", 0, QApplication::UnicodeUTF8));
        typeLabel->setText(QApplication::translate("ProbeDialog", "Type", 0, QApplication::UnicodeUTF8));
        freqLabel->setText(QApplication::translate("ProbeDialog", "Frequency", 0, QApplication::UnicodeUTF8));
        priElemQtyLabel->setText(QApplication::translate("ProbeDialog", "Pri Element Qty", 0, QApplication::UnicodeUTF8));
        secElemQtyLabel->setText(QApplication::translate("ProbeDialog", "Sec Element Qty", 0, QApplication::UnicodeUTF8));
        refPointLabel->setText(QApplication::translate("ProbeDialog", "Ref Point", 0, QApplication::UnicodeUTF8));
        priPitchLabel->setText(QApplication::translate("ProbeDialog", "Pri Pitch", 0, QApplication::UnicodeUTF8));
        secPitchLabel->setText(QApplication::translate("ProbeDialog", "Sec Pitch", 0, QApplication::UnicodeUTF8));
        modelLineEdit->setText(QString());
        serialLineEdit->setText(QString());
        typeComboBox->clear();
        typeComboBox->insertItems(0, QStringList()
         << QApplication::translate("ProbeDialog", "Contact", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ProbeDialog", "Delay", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ProbeDialog", "Immersion", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("ProbeDialog", "Angle Beam", 0, QApplication::UnicodeUTF8)
        );
        freqDoubleSpinBox->setSuffix(QApplication::translate("ProbeDialog", " MHz", 0, QApplication::UnicodeUTF8));
        refPointDoubleSpinBox->setSuffix(QApplication::translate("ProbeDialog", " mm", 0, QApplication::UnicodeUTF8));
        priPitchDoubleSpinBox->setSuffix(QApplication::translate("ProbeDialog", " mm", 0, QApplication::UnicodeUTF8));
        secPitchDoubleSpinBox->setSuffix(QApplication::translate("ProbeDialog", " mm", 0, QApplication::UnicodeUTF8));
        saveApplyPushButton->setText(QApplication::translate("ProbeDialog", "Save && Apply", 0, QApplication::UnicodeUTF8));
        savePushButton->setText(QApplication::translate("ProbeDialog", "Save", 0, QApplication::UnicodeUTF8));
        cancelDefinePushButton->setText(QApplication::translate("ProbeDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(defineTab), QApplication::translate("ProbeDialog", "Define", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ProbeDialog: public Ui_ProbeDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROBE_DIALOG_H
