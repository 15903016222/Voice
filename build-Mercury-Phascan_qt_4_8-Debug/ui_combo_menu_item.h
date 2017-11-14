/********************************************************************************
** Form generated from reading UI file 'combo_menu_item.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COMBO_MENU_ITEM_H
#define UI_COMBO_MENU_ITEM_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ComboMenuItem
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QWidget *ComboMenuItem)
    {
        if (ComboMenuItem->objectName().isEmpty())
            ComboMenuItem->setObjectName(QString::fromUtf8("ComboMenuItem"));
        ComboMenuItem->resize(65, 70);
        verticalLayout = new QVBoxLayout(ComboMenuItem);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nameLabel = new QLabel(ComboMenuItem);
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

        comboBox = new QComboBox(ComboMenuItem);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setFocusPolicy(Qt::NoFocus);
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox{\n"
"	border-top:0px;\n"
"	border-bottom:0px;\n"
"	font: 14pt \"Arial\";\n"
"	color: white;\n"
"	selection-background-color: rgba(0, 130, 195, 0);\n"
"	selection-color: white;\n"
"	background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255),\n"
"stop:0.559322 rgba(0, 130, 195, 255));\n"
"	border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"	border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"}\n"
"\n"
"QComboBox:drop-down {\n"
"	border-style:none;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView{\n"
"	font: 14pt \"Arial\";\n"
"	background-color: rgb(255, 255, 255);\n"
"	margin-bottom: 0px;\n"
"	outline: 0px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView::item{\n"
"	height: 35px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView::item:hover{\n"
""
                        "	color: black;\n"
"	background-color: rgba(255 255, 255, 225);\n"
"}\n"
"\n"
"QComboBox QAbstractItemView::item:selected{\n"
"	color: yellow;\n"
"	background-color: rgba(0, 150, 255, 225);\n"
"}"));
        comboBox->setEditable(false);
        comboBox->setMaxVisibleItems(12);
        comboBox->setIconSize(QSize(16, 16));

        verticalLayout->addWidget(comboBox);

        label = new QLabel(ComboMenuItem);
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
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);
        label->setWordWrap(false);

        verticalLayout->addWidget(label);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);
        verticalLayout->setStretch(2, 1);

        retranslateUi(ComboMenuItem);

        QMetaObject::connectSlotsByName(ComboMenuItem);
    } // setupUi

    void retranslateUi(QWidget *ComboMenuItem)
    {
        ComboMenuItem->setWindowTitle(QApplication::translate("ComboMenuItem", "Form", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ComboMenuItem: public Ui_ComboMenuItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COMBO_MENU_ITEM_H
