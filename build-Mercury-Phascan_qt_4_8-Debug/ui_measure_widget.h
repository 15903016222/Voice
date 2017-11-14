/********************************************************************************
** Form generated from reading UI file 'measure_widget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MEASURE_WIDGET_H
#define UI_MEASURE_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeasureWidget
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QLabel *valueLabel;

    void setupUi(QWidget *MeasureWidget)
    {
        if (MeasureWidget->objectName().isEmpty())
            MeasureWidget->setObjectName(QString::fromUtf8("MeasureWidget"));
        MeasureWidget->resize(65, 70);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MeasureWidget->sizePolicy().hasHeightForWidth());
        MeasureWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(MeasureWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nameLabel = new QLabel(MeasureWidget);
        nameLabel->setObjectName(QString::fromUtf8("nameLabel"));
        sizePolicy.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(16);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        nameLabel->setFont(font);
        nameLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	font: 16pt \"Arial\";\n"
"	color:yellow;\n"
"	background-color:rgba(0, 130, 195);\n"
"	color: rgb(255, 255, 255);\n"
"	border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565,\n"
"y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));\n"
"	border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));\n"
"}"));
        nameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(nameLabel);

        valueLabel = new QLabel(MeasureWidget);
        valueLabel->setObjectName(QString::fromUtf8("valueLabel"));
        sizePolicy.setHeightForWidth(valueLabel->sizePolicy().hasHeightForWidth());
        valueLabel->setSizePolicy(sizePolicy);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QLinearGradient gradient(0.5, 0, 0.5, 1);
        gradient.setSpread(QGradient::PadSpread);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush1(gradient);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QLinearGradient gradient1(0.5, 0, 0.5, 1);
        gradient1.setSpread(QGradient::PadSpread);
        gradient1.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient1.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient1.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush2(gradient1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        QLinearGradient gradient2(0.5, 0, 0.5, 1);
        gradient2.setSpread(QGradient::PadSpread);
        gradient2.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient2.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient2.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush3(gradient2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QLinearGradient gradient3(0.5, 0, 0.5, 1);
        gradient3.setSpread(QGradient::PadSpread);
        gradient3.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient3.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient3.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush4(gradient3);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QLinearGradient gradient4(0.5, 0, 0.5, 1);
        gradient4.setSpread(QGradient::PadSpread);
        gradient4.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient4.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient4.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush5(gradient4);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        QLinearGradient gradient5(0.5, 0, 0.5, 1);
        gradient5.setSpread(QGradient::PadSpread);
        gradient5.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient5.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient5.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush6(gradient5);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        QLinearGradient gradient6(0.5, 0, 0.5, 1);
        gradient6.setSpread(QGradient::PadSpread);
        gradient6.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient6.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient6.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush7(gradient6);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        QLinearGradient gradient7(0.5, 0, 0.5, 1);
        gradient7.setSpread(QGradient::PadSpread);
        gradient7.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient7.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient7.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush8(gradient7);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        QLinearGradient gradient8(0.5, 0, 0.5, 1);
        gradient8.setSpread(QGradient::PadSpread);
        gradient8.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient8.setColorAt(0.158192, QColor(0, 0, 0, 255));
        gradient8.setColorAt(0.559322, QColor(0, 130, 195, 255));
        QBrush brush9(gradient8);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        valueLabel->setPalette(palette);
        valueLabel->setStyleSheet(QString::fromUtf8("QLabel{\n"
"font: 14pt \"Arial\";\n"
"color: white;\n"
"background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255),\n"
"stop:0.559322 rgba(0, 130, 195, 255));\n"
"color: rgb(255, 255, 255);\n"
"border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,\n"
"stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));\n"
"}"));
        valueLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(valueLabel);

        verticalLayout->setStretch(0, 2);
        verticalLayout->setStretch(1, 1);

        retranslateUi(MeasureWidget);

        QMetaObject::connectSlotsByName(MeasureWidget);
    } // setupUi

    void retranslateUi(QWidget *MeasureWidget)
    {
        MeasureWidget->setWindowTitle(QApplication::translate("MeasureWidget", "Form", 0, QApplication::UnicodeUTF8));
        nameLabel->setText(QString());
        valueLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MeasureWidget: public Ui_MeasureWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MEASURE_WIDGET_H
