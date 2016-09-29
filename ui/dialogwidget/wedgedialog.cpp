#include "wedgedialog.h"
#include "ui_wedgedialog.h"

#define WEDGE_NUMBER 8
static QString WEDGETYPE_STRING[WEDGETYPE_NUMBER] ={
    "Other", "SB10", "SB12", "SB23", "SB26", "SB40", "SB46", "SB54", "SB55", "SB56", "SB57", "SB58",
    "SB7", "SD1", "SD10", "SD2", "SD3", "SD57", "SD6", "SD62", "SD7", "user"
};

static QString WEDGE_STRING[WEDGETYPE_NUMBER][WEDGE_NUMBER] = {
    {
        "Contact.opw",
        "Water.opw"
    },
    {
        "SB10-N0L.opw",
        "SB10-N45L.opw",
        "SB10-N45S.opw",
        "SB10-N55S.opw",
        "SB10-N60S.opw"
    },
    {
        "SB12-N0L.opw",
        "SB12-N45L.opw",
        "SB12-N45S.opw",
        "SB12-N55S.opw",
        "SB12.opw"
    },
    {
        "SB23-N0L.opw",
        "SB23-N50S-IHC.opw",
        "SB23-N55S-IHC.opw"
    },
    {
        "SB26-N0L.opw",
        "SB26-N55S.opw"
    },
    {
        "SB40-N0L.opw",
        "SB40-N55S.opw"
    },
    {
        "SB46-N45S.opw",
        "SB46-N5S.opw"
    },
    {
        "SB54-N0L-1.opw",
        "SB54-N0L.opw",
        "SB54-N55S.opw"
    },
    {
        "SB55-N55S.opw"
    },
    {
        "SB56-N0L.opw",
        "SB56-N45S.opw",
        "SB56-N55S-IHC.opw",
        "SB56-N55S.opw",
        "SB56-N60L.opw",
        "SB56-N60S.opw"
    },
    {
        "SB57-N0L.opw",
        "SB57-N45L-IHC.opw",
        "SB57-N45L.opw",
        "SB57-N55S-IHC.opw",
        "SB57-N55S.opw",
        "SB57-N60L-IHC.opw",
        "SB57-N60L.opw",
        "SB57-N60S.opw"
    },
    {
        "SB58-N0L.opw",
        "SB58-N60L.opw",
        "SB58-N60S.opw"
    },
    {
        "SB7-N0L.opw",
        "SB7-N55S.opw",
        "SB7-N60L.opw",
    },
    {
        "SD1-N0L.opw",
        "SD1-N45L.opw",
        "SD1-N45S.opw",
        "SD1-N55S.opw",
        "SD1-N60L.opw",
        "SD1-N60S.opw"
    },
    {
        "SD10-N60S-IHC.opw"
    },
    {
        "SD2-N0L-IHC.opw",
        "SD2-N0L.opw",
        "SD2-N45L.opw",
        "SD2-N45S.opw",
        "SD2-N55S-IHC.opw",
        "SD2-N55S.opw",
        "SD2-N60L.opw",
        "SD2-N60S.opw"
    },
    {
        "SD3-N0L.opw",
        "SD3-N45L.opw",
        "SD3-N45S.opw",
        "SD3-N55S.opw",
        "SD3-N60L-IHC.opw",
        "SD3-N60S.opw"
    },
    {
        "SD57-N0L.opw",
        "SD57-N55S.opw",
    },
    {
        "SD6-N0L.opw",
        "SD6-N45L.opw",
        "SD6-N45S.opw",
        "SD6-N55S.opw",
        "SD6-N60L-IHC.opw",
        "SD6-N60S.opw"
    },
    {
        "SD62-N55-Dual-P0.75.opw",
        "SD62-N55S-Dual-P0.6.opw"
    },
    {
        "SD7-N0L.opw",
        "SD7-N55S.opw",
        "SD7-N60S.opw"
    }
};

static const char* WEDGEINFO_STRING[WEDGETYPE_NUMBER][WEDGE_NUMBER] = {
    {
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: Contact    Angle: 0.0°\nOrientation: Normal    Height: 0.00 mm\n"
        "Velocity: 25 m/s    Pri Offset: 0.00 mm\nSec Offset: 0.000 mm    Length: 0.00mm"),
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: Water    Angle: 0.0°\nOrientation: Normal    Height: 0.00 mm\n"
        "Velocity: 1480 m/s    Pri Offset: 0.00 mm\nSec Offset: 0.000 mm    Length: 0.00mm")
    },
    {
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: SB10-N0L    Angle: 0.0°\nOrientation: Normal    Height: 20.00 mm\n"
        "Velocity: 2337 m/s    Pri Offset: 18.25 mm\nSec Offset: 16.800 mm    Length: 0.00mm"),
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: SB10-N45L    Angle: 16.5°\nOrientation: Normal    Height: 26.60 mm\n"
        "Velocity: 2337 m/s    Pri Offset: 29.00 mm\nSec Offset: 16.750 mm    Length: 0.00mm"),
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: SB10-N45S    Angle: 30.0°\nOrientation: Normal    Height: 9.38 mm\n"
        "Velocity: 2337 m/s    Pri Offset: 30.22 mm\nSec Offset: 16.750 mm    Length: 0.00mm"),
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: SB10-N55S    Angle: 36.0°\nOrientation: Normal    Height: 8.24 mm\n"
        "Velocity: 2337 m/s    Pri Offset: 30.38 mm\nSec Offset: 16.750 mm    Length: 0.00mm"),
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: SB10-N60S    Angle: 38.0°\nOrientation: Normal    Height: 7.85 mm\n"
        "Velocity: 2337 m/s    Pri Offset: 30.24 mm\nSec Offset: 16.750 mm    Length: 0.00mm")
    },
    {
        QT_TRANSLATE_NOOP("WedgeDialog", "Model: SB12-N0L    Angle: 0.0°\nOrientation: Normal    Height: 20.00 mm\n"
        "Velocity: 2337 m/s    Pri Offset: 11.25 mm\nSec Offset: 14.000 mm    Length: 0.00mm"),

        QT_TRANSLATE_NOOP("WedgeDialog", "Model: SB12-N45L    Angle: 0.0°\nOrientation: Normal    Height: 20.00 mm\n"
        "Velocity: 2337 m/s    Pri Offset: 11.25 mm\nSec Offset: 14.000 mm    Length: 0.00mm"),

        ".opw",
        ".opw",
        "SB12-N45S.opw",
        "SB12-N55S.opw",
        "SB12.opw"
    },
    {
        "SB23-N0L.opw",
        "SB23-N50S-IHC.opw",
        "SB23-N55S-IHC.opw"
    },
    {
        "SB26-N0L.opw",
        "SB26-N55S.opw"
    },
    {
        "SB40-N0L.opw",
        "SB40-N55S.opw"
    },
    {
        "SB46-N45S.opw",
        "SB46-N5S.opw"
    },
    {
        "SB54-N0L-1.opw",
        "SB54-N0L.opw",
        "SB54-N55S.opw"
    },
    {
        "SB55-N55S.opw"
    },
    {
        "SB56-N0L.opw",
        "SB56-N45S.opw",
        "SB56-N55S-IHC.opw",
        "SB56-N55S.opw",
        "SB56-N60L.opw",
        "SB56-N60S.opw"
    },
    {
        "SB57-N0L.opw",
        "SB57-N45L-IHC.opw",
        "SB57-N45L.opw",
        "SB57-N55S-IHC.opw",
        "SB57-N55S.opw",
        "SB57-N60L-IHC.opw",
        "SB57-N60L.opw",
        "SB57-N60S.opw"
    },
    {
        "SB58-N0L.opw",
        "SB58-N60L.opw",
        "SB58-N60S.opw"
    },
    {
        "SB7-N0L.opw",
        "SB7-N55S.opw",
        "SB7-N60L.opw",
    },
    {
        "SD1-N0L.opw",
        "SD1-N45L.opw",
        "SD1-N45S.opw",
        "SD1-N55S.opw",
        "SD1-N60L.opw",
        "SD1-N60S.opw"
    },
    {
        "SD10-N60S-IHC.opw"
    },
    {
        "SD2-N0L-IHC.opw",
        "SD2-N0L.opw",
        "SD2-N45L.opw",
        "SD2-N45S.opw",
        "SD2-N55S-IHC.opw",
        "SD2-N55S.opw",
        "SD2-N60L.opw",
        "SD2-N60S.opw"
    },
    {
        "SD3-N0L.opw",
        "SD3-N45L.opw",
        "SD3-N45S.opw",
        "SD3-N55S.opw",
        "SD3-N60L-IHC.opw",
        "SD3-N60S.opw"
    },
    {
        "SD57-N0L.opw",
        "SD57-N55S.opw",
    },
    {
        "SD6-N0L.opw",
        "SD6-N45L.opw",
        "SD6-N45S.opw",
        "SD6-N55S.opw",
        "SD6-N60L-IHC.opw",
        "SD6-N60S.opw"
    },
    {
        "SD62-N55-Dual-P0.75.opw",
        "SD62-N55S-Dual-P0.6.opw"
    },
    {
        "SD7-N0L.opw",
        "SD7-N55S.opw",
        "SD7-N60S.opw"
    }
};

WedgeDialog::WedgeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WedgeDialog)
{
    ui->setupUi(this);
    init_ui();
}

WedgeDialog::~WedgeDialog()
{
    delete ui;
}

void WedgeDialog::init_ui()
{
    wedgeTypeModel = new QStandardItemModel(this);
    QStringList wedgeTypeList;

    for(int i = 0; i < WEDGETYPE_NUMBER; i++){
        wedgeTypeList.append(WEDGETYPE_STRING[i]);

        QString string = static_cast<QString>(wedgeTypeList.at(i));
        QStandardItem *item = new QStandardItem(string);
        wedgeTypeModel->appendRow(item);
        item->setForeground(QBrush(Qt::black));
        item->setFont(QFont("Times New Roman", 14));

        wedgeModel = new QStandardItemModel(this);
        wedgeModel->setObjectName("standardItemModel_" + QString::number(i));
        wedgeModelList.append(wedgeModel);
    }

    listView_1 = new QListView(this);
    listView_1->resize(ui->scrollArea_1->geometry().width(), 300);
    listView_1->setSpacing(3);
    ui->scrollArea_1->setFrameShape(QFrame::NoFrame);
    ui->scrollArea_1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea_1->setWidget(listView_1);
    listView_1->setModel(wedgeTypeModel);

    listView_1CurrentIndex = 0;
    insert_wedge(listView_1CurrentIndex);
    connect(listView_1, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_listView_1ItemClicked(QModelIndex)));
}

void WedgeDialog::insert_wedge(int i)
{
    QStringList wedgeList;
    for(int j = 0; j < WEDGE_NUMBER; j++){
        if(WEDGE_STRING[i][j] != NULL){
            wedgeList.append(WEDGE_STRING[i][j]);

            QString string = static_cast<QString>(wedgeList.at(j));
            QStandardItem *item = new QStandardItem(string);
            wedgeModelList.at(i)->appendRow(item);
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
    listView_2->setModel(wedgeModelList.at(i));

    connect(listView_2, SIGNAL(clicked(QModelIndex)), this, SLOT(slot_listView_2ItemClicked(QModelIndex)));
}

void WedgeDialog::slot_listView_1ItemClicked(QModelIndex index)
{
    QStandardItem *item = wedgeTypeModel->itemFromIndex(index);
    listView_1CurrentIndex = item->row();

    wedgeModelList.at(listView_1CurrentIndex)->clear();
    insert_wedge(listView_1CurrentIndex);
    ui->label->clear();

    if(listView_1CurrentIndex < WEDGETYPE_NUMBER-1){
        ui->label->setText(tr("Ultrasonic phased array wedge family."));
    }else if(listView_1CurrentIndex == WEDGETYPE_NUMBER-1){
        ui->label->setText(tr("This group contains all user-defined \nultrasonic phased array wedges."));
    }
    ui->label->setAlignment(Qt::AlignCenter);
}

void WedgeDialog::slot_listView_2ItemClicked(QModelIndex index)
{
    QStandardItem *item = wedgeModelList.at(listView_1CurrentIndex)->itemFromIndex(index);
    currentItem = item->text();
    listView_2CurrentIndex = item->row();

    ui->label->clear();
    ui->label->setText(tr(WEDGEINFO_STRING[listView_1CurrentIndex][listView_2CurrentIndex]));
    ui->label->setAlignment(Qt::AlignLeft);
}

void WedgeDialog::on_buttonBox_accepted()
{
    emit wedgeChanged(currentItem);
}
