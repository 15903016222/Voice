#include "wedgedialog.h"
#include "ui_wedgedialog.h"

static QString WEDGETYPE_STRING[WEDGETYPE_NUMBER] ={
    "Other", "SB10", "SB12", "SB23", "SB26", "SB40", "SB46", "SB54", "SB55", "SB56", "SB57", "SB58"
    "SB7", "SD1", "SD10", "SD2", "SD3", "SD57", "SD6", "SD62", "SD7", "user"
};

WedgeDialog::WedgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WedgeDialog)
{
    ui->setupUi(this);
    initUI();
}

WedgeDialog::~WedgeDialog()
{
    delete ui;
}

void WedgeDialog::initUI()
{
//    buttonList.append(ui->pushButton_cancel);
//    buttonList.append(ui->pushButton_ok);

    wedgeTypeModel = new QStandardItemModel(this);

    for(int i = 0; i < WEDGETYPE_NUMBER; i++)
    {
        wedgeTypeList.append(WEDGETYPE_STRING[i]);

        QString string = static_cast<QString>(wedgeTypeList.at(i));
        QStandardItem *item = new QStandardItem(string);
        wedgeTypeModel->appendRow(item);
        item->setForeground(QBrush(Qt::black));
        item->setFont(QFont("Times New Roman", 14));
    }

    listView = new QListView(this);
    listView->resize(ui->scrollArea_1->geometry().width(), 300);
    listView->setSpacing(3);
    ui->scrollArea_1->setFrameShape(QFrame::NoFrame);
    ui->scrollArea_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_1->setWidget(listView);
    listView->setModel(wedgeTypeModel);

    connect(listView, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_listViewItemClicked(QModelIndex)));
}

void WedgeDialog::slot_listViewItemClicked(QModelIndex index)
{
    QStandardItem *item = wedgeTypeModel->itemFromIndex(index);
    changedString = labelMap.key(item->text());
}
