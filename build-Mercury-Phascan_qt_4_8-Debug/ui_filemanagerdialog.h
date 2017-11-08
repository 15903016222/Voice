/********************************************************************************
** Form generated from reading UI file 'filemanagerdialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEMANAGERDIALOG_H
#define UI_FILEMANAGERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FileManagerDialog
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_2;
    QGridLayout *gridLayout_3;
    QWidget *widget_5;
    QGridLayout *gridLayout_6;
    QWidget *widget_9;
    QGridLayout *gridLayout_10;
    QWidget *widget_11;
    QLabel *label_6;
    QComboBox *comboBox_2;
    QSpacerItem *horizontalSpacer_3;
    QTableView *tableView_2;
    QWidget *widget_3;
    QGridLayout *gridLayout_5;
    QPushButton *pushButton_copy;
    QPushButton *pushButton_move;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_rename;
    QPushButton *pushButton_selectAll;
    QPushButton *pushButton_select;
    QPushButton *pushButton_close;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QWidget *widget_1;
    QGridLayout *gridLayout_2;
    QWidget *widget_4;
    QGridLayout *gridLayout_4;
    QWidget *widget_8;
    QGridLayout *gridLayout_9;
    QWidget *widget_10;
    QLabel *label_5;
    QComboBox *comboBox_1;
    QSpacerItem *horizontalSpacer_2;
    QTableView *tableView_1;
    QWidget *widget;
    QGridLayout *gridLayout_7;
    QLabel *label_1;
    QWidget *widget_6;
    QGridLayout *gridLayout_8;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_2;
    QFrame *line;
    QListWidget *listWidget;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *FileManagerDialog)
    {
        if (FileManagerDialog->objectName().isEmpty())
            FileManagerDialog->setObjectName(QString::fromUtf8("FileManagerDialog"));
        FileManagerDialog->resize(800, 600);
        FileManagerDialog->setStyleSheet(QString::fromUtf8("QWidget QListWidget{\n"
"	font: 14pt 'Arial';\n"
"	outline: 0px;\n"
"}\n"
"\n"
"QWidget QListWidget::item{\n"
"	background-color: rgb(0, 0, 0, 0);\n"
"	color: yellow;\n"
"}\n"
"\n"
"QWidget QListWidget:item:Selected{\n"
"	background-color: rgba(0, 0, 0, 0);\n"
"	color: red;\n"
"}\n"
"\n"
"QWidget QTableView{\n"
"	font: 14pt 'Arial';\n"
"	color: gray;\n"
"	outline: none;\n"
"}\n"
"\n"
"QWidget QTableView::item{\n"
"	font: 14pt 'Arial';\n"
"	color: gray;\n"
"	selection-background-color: rgba(170, 255, 255);\n"
"\n"
"}\n"
""));
        gridLayout = new QGridLayout(FileManagerDialog);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget_2 = new QWidget(FileManagerDialog);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	\n"
"}\n"
"\n"
"QWidget QLabel{\n"
"	\n"
"	font: 13pt \"Times New Roman\";\n"
"}\n"
"\n"
"QWidget#widget_5{\n"
"	background-color: rgb(235, 235, 235);\n"
"}"));
        gridLayout_3 = new QGridLayout(widget_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(6);
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        widget_5 = new QWidget(widget_2);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        gridLayout_6 = new QGridLayout(widget_5);
        gridLayout_6->setSpacing(0);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(0, 0, 0, 0);
        widget_9 = new QWidget(widget_5);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        gridLayout_10 = new QGridLayout(widget_9);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setVerticalSpacing(0);
        gridLayout_10->setContentsMargins(0, 5, 0, 5);
        widget_11 = new QWidget(widget_9);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));

        gridLayout_10->addWidget(widget_11, 0, 0, 1, 1);

        label_6 = new QLabel(widget_9);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_10->addWidget(label_6, 0, 1, 1, 1);

        comboBox_2 = new QComboBox(widget_9);
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy);

        gridLayout_10->addWidget(comboBox_2, 0, 2, 1, 1);

        gridLayout_10->setColumnStretch(0, 1);
        gridLayout_10->setColumnStretch(1, 1);
        gridLayout_10->setColumnStretch(2, 2);

        gridLayout_6->addWidget(widget_9, 0, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_3, 0, 1, 1, 1);

        gridLayout_6->setColumnStretch(0, 1);
        gridLayout_6->setColumnStretch(1, 1);

        gridLayout_3->addWidget(widget_5, 0, 0, 1, 1);

        tableView_2 = new QTableView(widget_2);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));
        tableView_2->setFocusPolicy(Qt::NoFocus);
        tableView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView_2->setShowGrid(true);
        tableView_2->verticalHeader()->setVisible(false);

        gridLayout_3->addWidget(tableView_2, 1, 0, 1, 1);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setRowStretch(1, 6);

        gridLayout->addWidget(widget_2, 1, 1, 1, 1);

        widget_3 = new QWidget(FileManagerDialog);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8("QWidget QPushButton {\n"
"	font: 75 12pt \"Times New Roman\";\n"
"}"));
        gridLayout_5 = new QGridLayout(widget_3);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(5, 15, 5, 15);
        pushButton_copy = new QPushButton(widget_3);
        pushButton_copy->setObjectName(QString::fromUtf8("pushButton_copy"));
        sizePolicy.setHeightForWidth(pushButton_copy->sizePolicy().hasHeightForWidth());
        pushButton_copy->setSizePolicy(sizePolicy);
        pushButton_copy->setFocusPolicy(Qt::NoFocus);

        gridLayout_5->addWidget(pushButton_copy, 1, 3, 1, 1);

        pushButton_move = new QPushButton(widget_3);
        pushButton_move->setObjectName(QString::fromUtf8("pushButton_move"));
        sizePolicy.setHeightForWidth(pushButton_move->sizePolicy().hasHeightForWidth());
        pushButton_move->setSizePolicy(sizePolicy);
        pushButton_move->setFocusPolicy(Qt::NoFocus);

        gridLayout_5->addWidget(pushButton_move, 1, 4, 1, 1);

        pushButton_delete = new QPushButton(widget_3);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));
        sizePolicy.setHeightForWidth(pushButton_delete->sizePolicy().hasHeightForWidth());
        pushButton_delete->setSizePolicy(sizePolicy);
        pushButton_delete->setFocusPolicy(Qt::NoFocus);

        gridLayout_5->addWidget(pushButton_delete, 1, 5, 1, 1);

        pushButton_rename = new QPushButton(widget_3);
        pushButton_rename->setObjectName(QString::fromUtf8("pushButton_rename"));
        sizePolicy.setHeightForWidth(pushButton_rename->sizePolicy().hasHeightForWidth());
        pushButton_rename->setSizePolicy(sizePolicy);
        pushButton_rename->setFocusPolicy(Qt::NoFocus);

        gridLayout_5->addWidget(pushButton_rename, 1, 2, 1, 1);

        pushButton_selectAll = new QPushButton(widget_3);
        pushButton_selectAll->setObjectName(QString::fromUtf8("pushButton_selectAll"));
        sizePolicy.setHeightForWidth(pushButton_selectAll->sizePolicy().hasHeightForWidth());
        pushButton_selectAll->setSizePolicy(sizePolicy);
        pushButton_selectAll->setFocusPolicy(Qt::NoFocus);

        gridLayout_5->addWidget(pushButton_selectAll, 1, 1, 1, 1);

        pushButton_select = new QPushButton(widget_3);
        pushButton_select->setObjectName(QString::fromUtf8("pushButton_select"));
        sizePolicy.setHeightForWidth(pushButton_select->sizePolicy().hasHeightForWidth());
        pushButton_select->setSizePolicy(sizePolicy);
        pushButton_select->setFocusPolicy(Qt::NoFocus);

        gridLayout_5->addWidget(pushButton_select, 1, 0, 1, 1);

        pushButton_close = new QPushButton(widget_3);
        pushButton_close->setObjectName(QString::fromUtf8("pushButton_close"));
        sizePolicy.setHeightForWidth(pushButton_close->sizePolicy().hasHeightForWidth());
        pushButton_close->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        pushButton_close->setFont(font);
        pushButton_close->setFocusPolicy(Qt::NoFocus);
        pushButton_close->setStyleSheet(QString::fromUtf8(""));

        gridLayout_5->addWidget(pushButton_close, 1, 8, 1, 1);

        horizontalSpacer = new QSpacerItem(547, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer, 1, 6, 1, 1);

        pushButton = new QPushButton(widget_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(pushButton, 1, 7, 1, 1);

        gridLayout_5->setColumnStretch(0, 1);
        gridLayout_5->setColumnStretch(1, 1);
        gridLayout_5->setColumnStretch(2, 1);
        gridLayout_5->setColumnStretch(3, 1);
        gridLayout_5->setColumnStretch(4, 1);
        gridLayout_5->setColumnStretch(5, 1);
        gridLayout_5->setColumnStretch(6, 1);
        gridLayout_5->setColumnStretch(7, 1);
        gridLayout_5->setColumnStretch(8, 1);

        gridLayout->addWidget(widget_3, 2, 1, 1, 1);

        widget_1 = new QWidget(FileManagerDialog);
        widget_1->setObjectName(QString::fromUtf8("widget_1"));
        widget_1->setStyleSheet(QString::fromUtf8("QWidget{\n"
"\n"
"}\n"
"\n"
"QWidget QLabel{\n"
"	font: 13pt \"Times New Roman\";\n"
"	\n"
"}\n"
"\n"
"QWidget#widget_4{\n"
"	\n"
"	background-color: rgb(235, 235, 235);\n"
"}"));
        gridLayout_2 = new QGridLayout(widget_1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(6);
        gridLayout_2->setVerticalSpacing(0);
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget_4 = new QWidget(widget_1);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        gridLayout_4 = new QGridLayout(widget_4);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        widget_8 = new QWidget(widget_4);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        gridLayout_9 = new QGridLayout(widget_8);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setVerticalSpacing(0);
        gridLayout_9->setContentsMargins(0, 5, 0, 5);
        widget_10 = new QWidget(widget_8);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));

        gridLayout_9->addWidget(widget_10, 0, 0, 1, 1);

        label_5 = new QLabel(widget_8);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_9->addWidget(label_5, 0, 1, 1, 1);

        comboBox_1 = new QComboBox(widget_8);
        comboBox_1->setObjectName(QString::fromUtf8("comboBox_1"));
        sizePolicy.setHeightForWidth(comboBox_1->sizePolicy().hasHeightForWidth());
        comboBox_1->setSizePolicy(sizePolicy);

        gridLayout_9->addWidget(comboBox_1, 0, 2, 1, 1);

        gridLayout_9->setColumnStretch(0, 1);
        gridLayout_9->setColumnStretch(1, 1);
        gridLayout_9->setColumnStretch(2, 2);

        gridLayout_4->addWidget(widget_8, 0, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        gridLayout_4->setColumnStretch(0, 1);
        gridLayout_4->setColumnStretch(1, 1);

        gridLayout_2->addWidget(widget_4, 0, 0, 1, 1);

        tableView_1 = new QTableView(widget_1);
        tableView_1->setObjectName(QString::fromUtf8("tableView_1"));
        tableView_1->setFocusPolicy(Qt::NoFocus);
        tableView_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        tableView_1->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableView_1->setShowGrid(false);
        tableView_1->verticalHeader()->setVisible(false);

        gridLayout_2->addWidget(tableView_1, 1, 0, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        gridLayout_2->setRowStretch(1, 6);

        gridLayout->addWidget(widget_1, 0, 1, 1, 1);

        widget = new QWidget(FileManagerDialog);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color: rgb(37, 76, 124);\n"
"}\n"
"QWidget#label_1{\n"
"	color: rgb(255, 255, 255);\n"
"	font: italic 16pt \"Times New Roman\";\n"
"	background-color: rgb(0, 130, 195);\n"
"\n"
"}\n"
"QWidget#label_2{\n"
"	background-color: rgba(255, 255, 255, 0);\n"
"	color: rgb(255, 255, 255);\n"
"	font: 15pt \"Times New Roman\";\n"
"}\n"
""));
        gridLayout_7 = new QGridLayout(widget);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(0, 0, 0, 0);
        label_1 = new QLabel(widget);
        label_1->setObjectName(QString::fromUtf8("label_1"));
        label_1->setAlignment(Qt::AlignCenter);

        gridLayout_7->addWidget(label_1, 0, 0, 1, 1);

        widget_6 = new QWidget(widget);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        gridLayout_8 = new QGridLayout(widget_6);
        gridLayout_8->setSpacing(0);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(0, 10, 0, 0);
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_8->addItem(horizontalSpacer_4, 2, 0, 1, 1);

        label_2 = new QLabel(widget_6);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_2, 0, 1, 1, 1);

        line = new QFrame(widget_6);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_8->addWidget(line, 1, 0, 1, 2);

        listWidget = new QListWidget(widget_6);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        new QListWidgetItem(listWidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setFrameShape(QFrame::NoFrame);
        listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listWidget->setSpacing(8);

        gridLayout_8->addWidget(listWidget, 2, 1, 1, 1);

        gridLayout_8->setRowStretch(0, 1);
        gridLayout_8->setRowStretch(1, 1);
        gridLayout_8->setRowStretch(2, 6);
        gridLayout_8->setColumnStretch(0, 1);
        gridLayout_8->setColumnStretch(1, 4);

        gridLayout_7->addWidget(widget_6, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_7->addItem(verticalSpacer, 2, 0, 1, 1);

        gridLayout_7->setRowStretch(0, 1);
        gridLayout_7->setRowStretch(1, 3);
        gridLayout_7->setRowStretch(2, 2);

        gridLayout->addWidget(widget, 0, 0, 3, 1);

        gridLayout->setRowStretch(0, 7);
        gridLayout->setRowStretch(1, 7);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 5);

        retranslateUi(FileManagerDialog);

        QMetaObject::connectSlotsByName(FileManagerDialog);
    } // setupUi

    void retranslateUi(QDialog *FileManagerDialog)
    {
        FileManagerDialog->setWindowTitle(QApplication::translate("FileManagerDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("FileManagerDialog", "Target Path:", 0, QApplication::UnicodeUTF8));
        pushButton_copy->setText(QApplication::translate("FileManagerDialog", "Copy", 0, QApplication::UnicodeUTF8));
        pushButton_move->setText(QApplication::translate("FileManagerDialog", "Move", 0, QApplication::UnicodeUTF8));
        pushButton_delete->setText(QApplication::translate("FileManagerDialog", "Delete", 0, QApplication::UnicodeUTF8));
        pushButton_rename->setText(QApplication::translate("FileManagerDialog", "Rename", 0, QApplication::UnicodeUTF8));
        pushButton_selectAll->setText(QApplication::translate("FileManagerDialog", "Select All", 0, QApplication::UnicodeUTF8));
        pushButton_select->setText(QApplication::translate("FileManagerDialog", "Select", 0, QApplication::UnicodeUTF8));
        pushButton_close->setText(QApplication::translate("FileManagerDialog", "Close", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("FileManagerDialog", "Open", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("FileManagerDialog", "Source Path:", 0, QApplication::UnicodeUTF8));
        label_1->setText(QApplication::translate("FileManagerDialog", "File Manager", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("FileManagerDialog", "File Type", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("FileManagerDialog", "Setup", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("FileManagerDialog", "Data", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("FileManagerDialog", "Report", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("FileManagerDialog", "Image", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("FileManagerDialog", "CAD", 0, QApplication::UnicodeUTF8));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("FileManagerDialog", "All", 0, QApplication::UnicodeUTF8));
        listWidget->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class FileManagerDialog: public Ui_FileManagerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEMANAGERDIALOG_H
