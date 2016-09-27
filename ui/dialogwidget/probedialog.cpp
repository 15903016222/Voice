#include "probedialog.h"
#include "ui_probedialog.h"

#define PROBE_NUMBER 9
static QString PROBETYPE_STRING[PROBETYPE_NUMBER] = {
    "B10", "B12", "B23", "B26", "B40", "B44", "B46", "B54", "B55", "B56", "B57", "B58",
    "B60", "B7", "D1", "D10", "D2", "D3", "D4", "D57", "D6", "D62", "D7", "user"
};

static QString PROBE_STRING[PROBETYPE_NUMBER][PROBE_NUMBER] = {
    {
        "10L16-1.0-10-B10.opp",
        "1L16-1.0-10-B10.opp",
        "2.25L16-1.0-10-B10.opp",
        "2.25L32-0.5-10-B10.opp",
        "2.25L16-1.0-12-B10.opp",
        "4L16-1.0-10-B10.opp",
        "4L32-0.5-10-B10.opp",
        "5L32-0.5-10-B10.opp",
        "7.5L32-0.5-10-B10.opp"
    },
    {
        "2L8-1.0-10-B12.opp",
        "2L8-1.0-9-B12.opp",
        "4L16-0.5-10-B12.opp",
        "4L16-0.5-9-B12.opp",
        "4L8-1.0-9-B12.opp",
        "7.5L16-0.5-10-B12.opp"
    },
    {
        "7.5L60-1.0-10-B23.opp"
    },
    {
        "1L64-1.0-10-B26.opp",
        "5L64-1.0-10-B26.opp"
    },
    {
        "2.25L32-0.8-12-B40.opp",
        "5L32-0.8-12-B40.opp"
    },
    {
        "10L64-0.8-12-B44.opp",
        "2.5L64-0.8-10-B44.opp",
        "5L64-0.8-10-B44.opp",
        "7.5L64-0.8-10-B44.opp"
    },
    {
        "5L16-0.6-10-B46.opp",
        "5L32-0.31-10-B46.opp",
        "7.5L32-0.31-10-B46.opp"
    },
    {
        "10L10-0.6-5-B54.opp",
        "5L10-0.6-5-B54.opp"
    },
    {
        "10L10-0.31-5-B55.opp",
        "5L10-0.31-5-B55.opp"
    },
    {
        "10L16-0.6-10-B56.opp",
        "10L32-0.31-10-B56.opp",
        "5L16-0.6-10-B56.opp",
        "7.5L16-0.6-10-B56.opp"
    },
    {
        "10L64-0.6-10-B57.opp",
        "2.25L48-0.8-10-B57.opp",
        "2.2L48-0.8-10-B57.opp",
        "3.5L64-0.6-10-B57.opp",
        "5L64-0.6-10-B57.opp"
    },
    {
        "2.25L16-1.0-16-B58.opp",
        "5L16-1.0-16-B58.opp"
    },
    {
        "10L128-0.8-10-B60.opp",
        "2L128-0.8-10-B60.opp",
        "5L128-0.8-10-B60.opp",
        "7.5L128-0.8-10-B60.opp"
    },
    {
        "5L64-0.6-10-B7.opp",
        "5L64-0.6-12-B7.opp"
    },
    {
        "2.25L16-0.6-10-D1.opp",
        "2.5L16-1.0-9-D1.opp",
        "5L16-0.6-10-D1.opp"
    },
    {
        "10S16-0.5-10-D10.opp",
        "10S32-0.25-10-D10.opp",
        "5S16-0.5-10-D10.opp",
        "7.5S16-0.5-10-D10.opp",
        "7.5S32-0.25-10-D10.opp"
    },
    {
        "4L32-0.5-10-D2.opp",
        "5L32-0.5-10-D2.opp",
        "7.5L32-0.5-10-D2.opp"
    },
    {
        "10L64-0.6-12-D3.opp",
        "2.25L64-0.6-10-D3.opp",
        "5L64-0.6-10-D3.opp"
    },
    {
        "5L10-0.6-6-D4.opp",
    },
    {
        "1.5L16-2.0-10-D57.opp",
        "5L32-1.0-10-D57.opp",
        "5L64-0.5-10-D57.opp",
        "7.5L32-1.0-10-D57.opp"
    },
    {
        "2.25L32-1.0-20-D6.opp"
    },
    {
        "2.25L64-0.75-12-D62.opp",
        "5L64-0.6-10-D62.opp"
    },
    {
        "5L128-0.75-10-D7.opp"
    }
};

ProbeDialog::ProbeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ProbeDialog)
{
    ui->setupUi(this);
    init_ui();
}

ProbeDialog::~ProbeDialog()
{
    delete ui;
}

void ProbeDialog::init_ui()
{
    probeTypeModel = new QStandardItemModel(this);
    QStringList probeTypeList;

    for(int i = 0; i < PROBETYPE_NUMBER; i++){
        probeTypeList.append(PROBETYPE_STRING[i]);

        QString string = static_cast<QString>(probeTypeList.at(i));
        QStandardItem *item = new QStandardItem(string);
        probeTypeModel->appendRow(item);
        item->setForeground(QBrush(Qt::black));
        item->setFont(QFont("Times New Roman", 14));

        probeModel = new QStandardItemModel(this);
        probeModel->setObjectName("standardItemModel_" + QString::number(i));
        probeModelList.append(probeModel);
    }

    listView_1 = new QListView(this);
    listView_1->resize(ui->scrollArea_1->geometry().width(), 300);
    listView_1->setSpacing(3);
    ui->scrollArea_1->setFrameShape(QFrame::NoFrame);
    ui->scrollArea_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_1->setWidget(listView_1);
    listView_1->setModel(probeTypeModel);

    currentIndex = 0;
    insert_probe(currentIndex);
    connect(listView_1, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_listViewItemClicked(QModelIndex)));
}

void ProbeDialog::insert_probe(int i)
{
    QStringList probeList;
    for(int j = 0; j < PROBE_NUMBER; j++){
        if(PROBE_STRING[i][j] != NULL){
            probeList.append(PROBE_STRING[i][j]);

            QString string = static_cast<QString>(probeList.at(j));
            QStandardItem *item = new QStandardItem(string);
            probeModelList.at(i)->appendRow(item);
            item->setForeground(QBrush(Qt::black));
            item->setFont(QFont("Times New Roman", 14));
        }
    }
    listView_2 = new QListView(this);
    listView_2->resize(ui->scrollArea_2->geometry().width(), 300);
    listView_2->setSpacing(3);
    ui->scrollArea_2->setFrameShape(QFrame::NoFrame);
    ui->scrollArea_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_2->setWidget(listView_2);
    listView_2->setModel(probeModelList.at(i));
}

void ProbeDialog::slot_listViewItemClicked(QModelIndex index)
{
    QStandardItem *item = probeTypeModel->itemFromIndex(index);
    currentIndex = item->row();

    probeModelList.at(currentIndex)->clear();
    insert_probe(currentIndex);
    ui->label->clear();

    if(currentIndex < PROBETYPE_NUMBER-1){
        ui->label->setText(tr("Ultrasonic phased array probe family."));
    }else if(currentIndex == PROBETYPE_NUMBER-1){
        ui->label->setText(tr("This group contains all user-defined \nultrasonic phased array probes."));
    }
}
