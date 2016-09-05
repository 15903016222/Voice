#include "commonmenuwidget.h"
#include "ui_commonmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"

#include <QResizeEvent>

static const char* COMMON_MENU_STRING[COMMON_MENU_NUMBER] = {
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Straightening"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Straightening"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Straightening"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Remove Lateral"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Ref. Position\n(mm)"),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Depth Cal."),
    QT_TRANSLATE_NOOP("CommonMenuWidget", "Wedge Sep.\n(mm)")
};

CommonMenuWidget::CommonMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonMenuWidget)
{
    ui->setupUi(this);
    this->resize(800, 72);

    initStandardModel();
}

CommonMenuWidget::~CommonMenuWidget()
{
    delete ui;
}

void CommonMenuWidget::reTranslatorCommonMenuUi()
{
    ui->retranslateUi(this);
}

void CommonMenuWidget::initStandardModel()
{
    model = new QStandardItemModel(1, COMMON_MENU_NUMBER, this);
    ui->tableView->setModel(model);
//  ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setFixedHeight(height * 45 / 70);
    ui->tableView->verticalHeader()->setDefaultSectionSize(height * 25 / 70);
    ui->tableView->verticalHeader()->hide();

#if QT_VERSION >= 0x050000
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

#if QT_VERSION < 0x050000
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                     "{font: 13pt 'Times New Roman';background-color: rgba(0, 130, 195, 255);"
                                                     "color:rgba(255, 255, 255, 255);"
                                                     "border: 0px solid black;"
                                                     "border-left:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.068, x2:0.5, y2:0.75,"
                                                     "stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
                                                     "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1,"
                                                     "stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

    for(int k = 0; k < COMMON_MENU_NUMBER; k++)
    {
        QModelIndex index = model->index(k, 0, QModelIndex());
        model->setData(index, k);

        widgetStyleChoice(k);
    }

    ui->tableView->show();
}

void CommonMenuWidget::setCommonMenuName()
{
    initStandardModel();
    for(int k = 0; k < COMMON_MENU_NUMBER; k ++)
    {
        if(COMMON_MENU_STRING[k] != NULL)
        {
            widgetStyleChoice(k);
            model->item(0, k)->setTextAlignment(Qt::AlignCenter);
            model->item(0, k)->setForeground(Qt::yellow);
            model->item(0, k)->setFont(QFont("Times New Roman", 13));
            model->item(0, k)->setBackground(QBrush(QColor(0, 0, 63, 255)));
        }
    }
}

void CommonMenuWidget::widgetStyleChoice(int k)
{
    model->setHeaderData(k, Qt::Horizontal, tr(COMMON_MENU_STRING[k]));
    switch(CHOICE_WIDGET_CHAR[k].toInt())
    {
    case 1:
    {
        DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString::number(0, 'f', 2));
        model->setItem(0, k, item);
        ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
        ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
        break;
    }
    case 2:
    {
        ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString("off"));
        model->setItem(0, k, item);
        ui->tableView->setItemDelegateForColumn(k, comboBox);
        break;
    }
    case 3:
    {
        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString("on"));
        model->setItem(0, k, item);
        model->item(0, k)->setFlags(Qt::NoItemFlags);
        break;
    }
    default:
        break;
    }
}

void CommonMenuWidget::resizeEvent(QResizeEvent *event)
{
    width = event->size().width();
    height = event->size().height();
    model->clear();
    initStandardModel();
    setCommonMenuName();
}
