#include "firstsecondmenuwidget.h"
#include "ui_firstsecondmenuwidget.h"

static const char* SECOND_MENU_STRING[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER] = {
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "General"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Pulser"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Receiver"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Advanced")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Gate"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Alarm"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Output"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "DAC"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "TCG")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Selection"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Color Setting"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Properties")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Select"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Position"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "FFT"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Part"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Advanced")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Law Config"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Angle"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Aperture"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Focal Point")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Inspection"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Encoder"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Area"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Start")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Reading"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Cursors"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "TOFD"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Flaw Record")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "File"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Save Mode"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Report"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Format"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "User Field")
    },
    {
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Preference"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "System"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Network"),
        QT_TRANSLATE_NOOP("FirstSecondMenuWidget", "Service")
    }
};
#include <QDebug>

FirstSecondMenuWidget::FirstSecondMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FirstSecondMenuWidget)
{
    ui->setupUi(this);
    qDebug()<<__func__<<tr(SECOND_MENU_STRING[1][1]);
    initUI();

    /**/
    //  QList<QString> list;
    //  list.append(tr("Format"));
    //  list.append();

}

FirstSecondMenuWidget::~FirstSecondMenuWidget()
{
    delete ui;
}

void FirstSecondMenuWidget::reTranslatorFirstSecondMenuUi()
{
    ui->retranslateUi(this);
}

void FirstSecondMenuWidget::setSecondMenuName(int i)
{
    // QStringList list = firstMenuMap(name);
    // QStringList::Iterator iter = list.
    QStringList secondMenuList;
    for(int j = 0; j < SECOND_MENU_NUMBER; j++)
    {
        if(SECOND_MENU_STRING[i][j] != NULL)
        {
            //qDebug()<<__func__<<tr(SECOND_MENU_STRING[i][j]);
            secondMenuList.append(tr(SECOND_MENU_STRING[i][j]));

            QString string = static_cast<QString>(secondMenuList.at(j));

            QStandardItem *item = new QStandardItem(string);
            modelList.at(i)->appendRow(item);
            item->setForeground(QBrush(Qt::yellow));
        }
    }
}

void FirstSecondMenuWidget::initSecondMenuItem(int i)
{
    for(int j = 0; j < SECOND_MENU_NUMBER; j++)
    {
        if(SECOND_MENU_STRING[i][j] != NULL)
        {
            QModelIndex modelIndex = modelList.at(i)->index(j, 0);
            QStandardItem *item = modelList.at(i)->itemFromIndex(modelIndex);

            if(item->row() == 0)
            {
                //  item->setForeground(QBrush(Qt::red));
                menuList.at(i)->setCurrentIndex(modelIndex);
            }else{
                //  item->setForeground(QBrush(Qt::yellow));
            }
        }
    }
}

void FirstSecondMenuWidget::secondMenuItemClicked(int i, QModelIndex index)
{
    for(int j = 0; j < SECOND_MENU_NUMBER; j++)
    {
        if(SECOND_MENU_STRING[i][j] != NULL)
        {
            QModelIndex modelIndex = modelList.at(i)->index(j, 0);
            QStandardItem *item = modelList.at(i)->itemFromIndex(modelIndex);

            if(modelIndex == index)
            {
                item->setForeground(QBrush(QColor(255, 0, 0)));
            }else{
                item->setForeground(QBrush(Qt::yellow));
            }
        }
    }
}

void FirstSecondMenuWidget::initUI()
{
    toolBox.append(ui->toolBox);

    for(int i = 0; i < FIRST_MENU_NUMBER; i++)
    {
        QListView* listView = findChild<QListView*>("listView_" + QString::number(i+1));
        listView->setStyleSheet("QListView{font: 14px}");
        listView->adjustSize();
        menuList.append(listView);

        QStandardItemModel *standardItemModel = new QStandardItemModel(this);
        standardItemModel->setObjectName("standardItemModel_"+QString::number(i+1));
        modelList.append(standardItemModel);

        setSecondMenuName(i);

        //    QModelIndex initModelIndex = modelList.at(i)->index(0, 0);
        //    QStandardItem *initItem = modelList.at(i)->itemFromIndex(initModelIndex);
        //    initItem->setForeground(QBrush(Qt::red));
        //    menuList.at(i)->setCurrentIndex(initModelIndex);

        menuList.at(i)->setModel(modelList.at(i));
    }

    ui->toolBox->setCurrentIndex(0);
    QModelIndex initModelIndex = modelList.at(0)->index(0, 0);
    menuList.at(0)->setCurrentIndex(initModelIndex);
}
