#include "thirdmenuwidget.h"
#include "ui_thirdmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"

static const char* THIRD_MENU_STRING[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER][THIRD_MENU_NUMBER] = {
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Gain\n(dB)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Range\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Velocity\n(m/s)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Wedge Delay\n(μs)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "UT Unit")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Tx/Rx mode"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Pulser\n(1 to 128)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Voltage\n(V)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "PW\n(ns)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "PRF")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Receiver\n(1 to 128)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Filter"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Rectifier"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Video Filter"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Averaging")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Set 80%"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "dB Ref."),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Points Qty."),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scale\nFactor"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Sum Gain")
        }
    }, //1
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Gate"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Width\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Threshold\n(%)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Synchro"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Measure Mode")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Alarm"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Switch"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group\nA"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Condition1"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Operator"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Condition2")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Output"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Sound"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Delay\n(ms)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Hold Time\n(ms)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Data")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Mode")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Mode")
        }
    }, //2
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Display"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "C-Scan\nSource"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Min Thickness\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max Thickness\n(mm)")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Amplitude"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Depth"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "TOFD")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan"),
            "A", "B", "C"
        }
    }, //3
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group Mode"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Probe"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Wedge"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Define"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Auto\nDetect")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan Offset\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index Offset\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Skew\n(°)")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Gain\n(dB)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Width\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Switch")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Geometry"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Thickness\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Diameter"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Material"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Overlay")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Load\nPart"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Clear\nPart")
        }
    }, //4
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Law Type"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Pulse\nConnection"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Receiver\nConnection"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Wave Type")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Min. Angle\n(°)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max. Angle\n(°)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Angle Step\n(°)")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Aperture"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "First\nElement"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Last\nElement"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Element Step")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Type.")
        }
    }, //5
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Type"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max Scan\nSpeed"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max Scan\nSpeed(rpm)")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Encoder"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Encoder\nType"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Resolution"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Polarity"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Origin"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Preset")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan Start\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan End\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan Resolution\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index Start\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index End\n(mm)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index Resolution\n(mm)")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Pause")
        }
    }, //6
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Reading\nGroup"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field1"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field2"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field3"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field4")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Selection")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Select"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "TOFD\nSettings"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "TOFD\nAnalysis")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Add/Delete"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Flaw Image"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Comment"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Display\nTable"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Export\nTable")
        }
    }, //7
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Save Setup As"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Open"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "File Manager")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Storage"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Save Mode"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Save Data"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "File Name")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Template"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Report Name"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Customer"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Part Name"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Part Number"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Create")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Probe/Wedge\nInfo"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Inspection\nInfo"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan\nInfo"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Encoder\nInfo"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "DAC/TCG\nInfo"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Flaw Record\nTable")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Select"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Enable"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Label"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Content"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Edit Note"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Print")
        }
    }, //8
    {
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Units"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Bright\n(%)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Opacity")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Clock Set\n(HH:MM:SS)"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Date Set"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Language")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "IP\nAddress"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Subnet\nMask")
        },
        {
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "System\nInfomation"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Cert\nImport"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "SW\nUpdate"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "HW\nUpdate"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Reset\nConfiguration"),
            QT_TRANSLATE_NOOP("ThirdMenuWidget", "About")
        }
    } //9
};

ThirdMenuWidget::ThirdMenuWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ThirdMenuWidget)
{
    ui->setupUi(this);

    initStandardModel();
    setThirdMenuName(0, 0);
}

ThirdMenuWidget::~ThirdMenuWidget()
{
    delete ui;
}

void ThirdMenuWidget::reTranslatorThirdMenuUi()
{
    ui->retranslateUi(this);
}

void ThirdMenuWidget::initStandardModel()
{
    model = new QStandardItemModel(1, THIRD_MENU_NUMBER, this);
    ui->tableView->setModel(model);
#if QT_VERSION >= 0x050000
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

#if QT_VERSION < 0x050000
    ui->tableView->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
#endif
    ui->tableView->horizontalHeader()->setFixedHeight(height * 45 / 70);
    ui->tableView->verticalHeader()->setDefaultSectionSize(height * 25 / 70);
    ui->tableView->verticalHeader()->hide();

    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
                                                     "{font: 13pt 'Times New Roman';"
                                                     "background-color: rgba(0, 130, 195, 255);"
                                                     "color: rgba(255, 255, 255, 255);"
                                                     "border: 0px solid black;"
                                                     "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75,"
                                                     "stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
                                                     "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1,"
                                                     "stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

    //  ui->tableView->setStyleSheet("QTableView::item{"
    //                               "border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));"
    //                               "border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));}");


    for(int k = 0; k < THIRD_MENU_NUMBER; k++)
    {
        QModelIndex index = model->index(k, 0, QModelIndex());
        model->setData(index, k);
    }
    ui->tableView->show();
}

void ThirdMenuWidget::setThirdMenuName(int i, int j)
{
    currFirstNum = i;
    currSecondNum = j;
    model->clear();
    initStandardModel();
    for(int k = 0; k < THIRD_MENU_NUMBER; k ++)
    {
        if(THIRD_MENU_STRING[i][j][k] != NULL)
        {
            widgetStyleChoice(i, j, k);
            model->item(0, k)->setTextAlignment(Qt::AlignCenter);
            model->item(0, k)->setForeground(Qt::yellow);
            model->item(0, k)->setFont(QFont("Times New Roman", 13));
            model->item(0, k)->setBackground(QBrush(QColor(0, 0, 63, 255)));
        }else
        {
            model->setHeaderData(k, Qt::Horizontal, "");
            QStandardItem *item = new QStandardItem(QString(tr("")));
            model->setItem(0, k, item);
            model->item(0, k)->setFlags(Qt::NoItemFlags);
            model->item(0, k)->setBackground(QBrush(QColor(0, 130, 195, 0.5)));
        }
    }
}

void ThirdMenuWidget::widgetStyleChoice(int i, int j, int k)
{
    model->setHeaderData(k, Qt::Horizontal, tr(THIRD_MENU_STRING[i][j][k]));

    switch(WIDGET_CHOICE_CHAR[i][j][k].toInt())
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
        QStandardItem *item = new QStandardItem(QString("Chinese"));
        model->setItem(0, k, item);
        break;
    }
    default:
        break;
    }
}

void ThirdMenuWidget::resizeEvent(QResizeEvent *event)
{
    width = event->size().width();
    height = event->size().height();
    model->clear();
    initStandardModel();
    setThirdMenuName(currFirstNum, currSecondNum);
}
