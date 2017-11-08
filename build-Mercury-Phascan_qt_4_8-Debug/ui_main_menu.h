/********************************************************************************
** Form generated from reading UI file 'main_menu.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_MENU_H
#define UI_MAIN_MENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainMenu
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_up;
    QTreeWidget *treeWidget;
    QPushButton *pushButton_down;

    void setupUi(QWidget *MainMenu)
    {
        if (MainMenu->objectName().isEmpty())
            MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        MainMenu->resize(150, 466);
        MainMenu->setMaximumSize(QSize(155, 16777215));
        MainMenu->setStyleSheet(QString::fromUtf8("QWidget{\n"
"/*	background-color:rgb(0, 100, 150); */\n"
"	background-color: rgb(0, 130, 195);\n"
"	border-top-left-radius: 5px;\n"
"	border-bottom-left-radius: 5px;\n"
"}\n"
"\n"
"QPushButton{	\n"
"	/*background-color: rgba(37, 76, 124, 0);*/\n"
"	background-color: rgb(0, 130, 195);\n"
"}"));
        verticalLayout = new QVBoxLayout(MainMenu);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_up = new QPushButton(MainMenu);
        pushButton_up->setObjectName(QString::fromUtf8("pushButton_up"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_up->sizePolicy().hasHeightForWidth());
        pushButton_up->setSizePolicy(sizePolicy);
        pushButton_up->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8("://resource/up.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_up->setIcon(icon);

        verticalLayout->addWidget(pushButton_up);

        treeWidget = new QTreeWidget(MainMenu);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::NoBrush);
        QFont font;
        font.setPointSize(16);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("://resource/triangle_up.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8("://resource/triangle_down.png"), QSize(), QIcon::Normal, QIcon::On);
        QBrush brush1(QColor(255, 255, 255, 255));
        brush1.setStyle(Qt::NoBrush);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(16);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::NoBrush);
        QBrush brush3(QColor(255, 255, 255, 255));
        brush3.setStyle(Qt::NoBrush);
        QBrush brush4(QColor(255, 255, 255, 255));
        brush4.setStyle(Qt::NoBrush);
        QBrush brush5(QColor(255, 255, 255, 255));
        brush5.setStyle(Qt::NoBrush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::NoBrush);
        QBrush brush7(QColor(255, 255, 255, 255));
        brush7.setStyle(Qt::NoBrush);
        QBrush brush8(QColor(255, 255, 255, 255));
        brush8.setStyle(Qt::NoBrush);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem1->setIcon(1, icon1);
        __qtreewidgetitem1->setFont(0, font);
        __qtreewidgetitem1->setForeground(0, brush);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        QTreeWidgetItem *__qtreewidgetitem2 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem2->setIcon(1, icon1);
        __qtreewidgetitem2->setFont(0, font1);
        __qtreewidgetitem2->setForeground(0, brush1);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        new QTreeWidgetItem(__qtreewidgetitem2);
        QTreeWidgetItem *__qtreewidgetitem3 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem3->setIcon(1, icon1);
        __qtreewidgetitem3->setFont(0, font1);
        __qtreewidgetitem3->setForeground(0, brush2);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        new QTreeWidgetItem(__qtreewidgetitem3);
        QTreeWidgetItem *__qtreewidgetitem4 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem4->setIcon(1, icon1);
        __qtreewidgetitem4->setFont(0, font1);
        __qtreewidgetitem4->setForeground(0, brush3);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        new QTreeWidgetItem(__qtreewidgetitem4);
        QTreeWidgetItem *__qtreewidgetitem5 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem5->setIcon(1, icon1);
        __qtreewidgetitem5->setFont(0, font1);
        __qtreewidgetitem5->setForeground(0, brush4);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        new QTreeWidgetItem(__qtreewidgetitem5);
        QTreeWidgetItem *__qtreewidgetitem6 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem6->setIcon(1, icon1);
        __qtreewidgetitem6->setFont(0, font1);
        __qtreewidgetitem6->setForeground(0, brush5);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        new QTreeWidgetItem(__qtreewidgetitem6);
        QTreeWidgetItem *__qtreewidgetitem7 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem7->setIcon(1, icon1);
        __qtreewidgetitem7->setFont(0, font1);
        __qtreewidgetitem7->setForeground(0, brush6);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        new QTreeWidgetItem(__qtreewidgetitem7);
        QTreeWidgetItem *__qtreewidgetitem8 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem8->setIcon(1, icon1);
        __qtreewidgetitem8->setFont(0, font1);
        __qtreewidgetitem8->setForeground(0, brush7);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        new QTreeWidgetItem(__qtreewidgetitem8);
        QTreeWidgetItem *__qtreewidgetitem9 = new QTreeWidgetItem(treeWidget);
        __qtreewidgetitem9->setIcon(1, icon1);
        __qtreewidgetitem9->setFont(0, font1);
        __qtreewidgetitem9->setForeground(0, brush8);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        new QTreeWidgetItem(__qtreewidgetitem9);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        treeWidget->setFont(font2);
        treeWidget->setFocusPolicy(Qt::WheelFocus);
        treeWidget->setStyleSheet(QString::fromUtf8("QTreeWidget{\n"
"	font: 14pt \"Arial\";\n"
"	background-color:rgb(0, 130, 195);\n"
"	outline: 0px;\n"
"}\n"
"\n"
"QTreeWidget::item:has-children{\n"
"	color: white;\n"
"	margin: 8px;\n"
"	background-color: rgba(37, 76, 124, 0); \n"
"	background-clip: margin;\n"
"}\n"
"\n"
"QTreeWidget::item:!has-children {\n"
"	color:yellow;\n"
"	margin: 8px;\n"
"	margin-left: 25px;\n"
"	background-color: rgba(37, 76, 124, 0); \n"
"	background-clip: margin;\n"
"}\n"
"\n"
"QTreeWidget::item:selected{\n"
"	color: yellow;\n"
"	background-color: qlineargradient(spread:repeat, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(230, 230, 230, 200), stop:0.1 rgba(200, 200, 200, 127), stop:0.9 rgba(200, 200, 200, 127), stop:1 rgba(230, 230, 230, 200));\n"
"}\n"
"\n"
"QTreeWidget::branch{\n"
"	image:none;\n"
"	background-color:  rgba(37, 76, 124, 0); \n"
"}"));
        treeWidget->setFrameShape(QFrame::NoFrame);
        treeWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        treeWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        treeWidget->setAutoScroll(false);
        treeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        treeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        treeWidget->setIndentation(0);
        treeWidget->setRootIsDecorated(false);
        treeWidget->setExpandsOnDoubleClick(false);
        treeWidget->setColumnCount(2);
        treeWidget->header()->setVisible(false);

        verticalLayout->addWidget(treeWidget);

        pushButton_down = new QPushButton(MainMenu);
        pushButton_down->setObjectName(QString::fromUtf8("pushButton_down"));
        sizePolicy.setHeightForWidth(pushButton_down->sizePolicy().hasHeightForWidth());
        pushButton_down->setSizePolicy(sizePolicy);
        pushButton_down->setFocusPolicy(Qt::NoFocus);
        pushButton_down->setStyleSheet(QString::fromUtf8(""));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("://resource/down.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_down->setIcon(icon2);

        verticalLayout->addWidget(pushButton_down);

        verticalLayout->setStretch(1, 1);

        retranslateUi(MainMenu);

        QMetaObject::connectSlotsByName(MainMenu);
    } // setupUi

    void retranslateUi(QWidget *MainMenu)
    {
        MainMenu->setWindowTitle(QApplication::translate("MainMenu", "Form", 0, QApplication::UnicodeUTF8));
        pushButton_up->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(1, QApplication::translate("MainMenu", "2", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("MainMenu", "UT Settings", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("MainMenu", "General", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("MainMenu", "Pulser", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("MainMenu", "Receiver", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem1->child(3);
        ___qtreewidgetitem5->setText(0, QApplication::translate("MainMenu", "Advanced", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem6 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem6->setText(0, QApplication::translate("MainMenu", "Gate/Curves", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem7 = ___qtreewidgetitem6->child(0);
        ___qtreewidgetitem7->setText(0, QApplication::translate("MainMenu", "Gate", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem8 = ___qtreewidgetitem6->child(1);
        ___qtreewidgetitem8->setText(0, QApplication::translate("MainMenu", "Alarm", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem9 = ___qtreewidgetitem6->child(2);
        ___qtreewidgetitem9->setText(0, QApplication::translate("MainMenu", "Output", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem10 = ___qtreewidgetitem6->child(3);
        ___qtreewidgetitem10->setText(0, QApplication::translate("MainMenu", "DAC", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem11 = ___qtreewidgetitem6->child(4);
        ___qtreewidgetitem11->setText(0, QApplication::translate("MainMenu", "TCG", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem12 = treeWidget->topLevelItem(2);
        ___qtreewidgetitem12->setText(0, QApplication::translate("MainMenu", "Display", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem13 = ___qtreewidgetitem12->child(0);
        ___qtreewidgetitem13->setText(0, QApplication::translate("MainMenu", "Selection", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem14 = ___qtreewidgetitem12->child(1);
        ___qtreewidgetitem14->setText(0, QApplication::translate("MainMenu", "Color", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem15 = ___qtreewidgetitem12->child(2);
        ___qtreewidgetitem15->setText(0, QApplication::translate("MainMenu", "Properties", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem16 = treeWidget->topLevelItem(3);
        ___qtreewidgetitem16->setText(0, QApplication::translate("MainMenu", "Probe/Part", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem17 = ___qtreewidgetitem16->child(0);
        ___qtreewidgetitem17->setText(0, QApplication::translate("MainMenu", "Select", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem18 = ___qtreewidgetitem16->child(1);
        ___qtreewidgetitem18->setText(0, QApplication::translate("MainMenu", "Position", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem19 = ___qtreewidgetitem16->child(2);
        ___qtreewidgetitem19->setText(0, QApplication::translate("MainMenu", "FFT", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem20 = ___qtreewidgetitem16->child(3);
        ___qtreewidgetitem20->setText(0, QApplication::translate("MainMenu", "Part", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem21 = ___qtreewidgetitem16->child(4);
        ___qtreewidgetitem21->setText(0, QApplication::translate("MainMenu", "Advanced", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem22 = treeWidget->topLevelItem(4);
        ___qtreewidgetitem22->setText(0, QApplication::translate("MainMenu", "Focal Law", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem23 = ___qtreewidgetitem22->child(0);
        ___qtreewidgetitem23->setText(0, QApplication::translate("MainMenu", "Law Config", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem24 = ___qtreewidgetitem22->child(1);
        ___qtreewidgetitem24->setText(0, QApplication::translate("MainMenu", "Angle", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem25 = ___qtreewidgetitem22->child(2);
        ___qtreewidgetitem25->setText(0, QApplication::translate("MainMenu", "Apeture", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem26 = ___qtreewidgetitem22->child(3);
        ___qtreewidgetitem26->setText(0, QApplication::translate("MainMenu", "Focal Point", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem27 = treeWidget->topLevelItem(5);
        ___qtreewidgetitem27->setText(0, QApplication::translate("MainMenu", "Scan", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem28 = ___qtreewidgetitem27->child(0);
        ___qtreewidgetitem28->setText(0, QApplication::translate("MainMenu", "Inspection", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem29 = ___qtreewidgetitem27->child(1);
        ___qtreewidgetitem29->setText(0, QApplication::translate("MainMenu", "Encoder", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem30 = ___qtreewidgetitem27->child(2);
        ___qtreewidgetitem30->setText(0, QApplication::translate("MainMenu", "Area", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem31 = ___qtreewidgetitem27->child(3);
        ___qtreewidgetitem31->setText(0, QApplication::translate("MainMenu", "Start", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem32 = treeWidget->topLevelItem(6);
        ___qtreewidgetitem32->setText(0, QApplication::translate("MainMenu", "Measurement", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem33 = ___qtreewidgetitem32->child(0);
        ___qtreewidgetitem33->setText(0, QApplication::translate("MainMenu", "Cursors", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem34 = ___qtreewidgetitem32->child(1);
        ___qtreewidgetitem34->setText(0, QApplication::translate("MainMenu", "TOFD", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem35 = ___qtreewidgetitem32->child(2);
        ___qtreewidgetitem35->setText(0, QApplication::translate("MainMenu", "Flaw Record", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem36 = treeWidget->topLevelItem(7);
        ___qtreewidgetitem36->setText(0, QApplication::translate("MainMenu", "File/Report", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem37 = ___qtreewidgetitem36->child(0);
        ___qtreewidgetitem37->setText(0, QApplication::translate("MainMenu", "File", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem38 = ___qtreewidgetitem36->child(1);
        ___qtreewidgetitem38->setText(0, QApplication::translate("MainMenu", "Save Mode", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem39 = ___qtreewidgetitem36->child(2);
        ___qtreewidgetitem39->setText(0, QApplication::translate("MainMenu", "Report", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem40 = ___qtreewidgetitem36->child(3);
        ___qtreewidgetitem40->setText(0, QApplication::translate("MainMenu", "Format", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem41 = ___qtreewidgetitem36->child(4);
        ___qtreewidgetitem41->setText(0, QApplication::translate("MainMenu", "User Field", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem42 = treeWidget->topLevelItem(8);
        ___qtreewidgetitem42->setText(0, QApplication::translate("MainMenu", "Preference", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem43 = ___qtreewidgetitem42->child(0);
        ___qtreewidgetitem43->setText(0, QApplication::translate("MainMenu", "Preference", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem44 = ___qtreewidgetitem42->child(1);
        ___qtreewidgetitem44->setText(0, QApplication::translate("MainMenu", "System", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem45 = ___qtreewidgetitem42->child(2);
        ___qtreewidgetitem45->setText(0, QApplication::translate("MainMenu", "Network", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        pushButton_down->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_MENU_H
