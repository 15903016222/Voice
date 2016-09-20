#include "thirdmenuwidget.h"
#include "ui_thirdmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"
#include "pushbuttondelegate.h"
#include "probedialog.h"
#include "wedgedialog.h"
#include "myinputpanel.h"

#include "serializer.h"

#include <QDebug>
#include <QTextStream>
#include <QFileInfo>
#include <QResizeEvent>
#include <QItemEditorFactory>

//static const char* THIRD_MENU_STRING[FIRST_MENU_NUMBER][SECOND_MENU_NUMBER][THIRD_MENU_NUMBER] = {
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Gain\n(dB)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Range\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Velocity\n(m/s)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Wedge Delay\n(μs)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "UT Unit")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Tx/Rx mode"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Pulser\n(1 to 128)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Voltage\n(V)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "PW\n(ns)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "PRF")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Receiver\n(1 to 128)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Filter"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Rectifier"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Video Filter"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Averaging")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Set 80%"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "dB Ref."),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Points Qty."),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scale\nFactor"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Sum Gain")
//        }
//    }, //1
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Gate"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Width\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Threshold\n(%)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Synchro"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Measure Mode")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Alarm"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Switch"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group\nA"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Condition1"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Operator"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Condition2")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Output"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Sound"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Delay\n(ms)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Hold Time\n(ms)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Data")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Mode")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Mode")
//        }
//    }, //2
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Display"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "C-Scan\nSource"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Min Thickness\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max Thickness\n(mm)")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Amplitude"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Depth"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "TOFD")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan"),
//            "A", "B", "C"
//        }
//    }, //3
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Group Mode"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Probe"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Wedge"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Define"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Auto\nDetect")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan Offset\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index Offset\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Skew\n(°)")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Gain\n(dB)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Width\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Switch")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Geometry"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Thickness\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Diameter"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Material"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Overlay")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Load\nPart"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Clear\nPart")
//        }
//    }, //4
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Law Type"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Pulse\nConnection"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Receiver\nConnection"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Wave Type")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Min. Angle\n(°)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max. Angle\n(°)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Angle Step\n(°)")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Aperture"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "First\nElement"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Last\nElement"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Element Step")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Type.")
//        }
//    }, //5
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Type"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max Scan\nSpeed"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Max Scan\nSpeed(rpm)")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Encoder"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Encoder\nType"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Resolution"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Polarity"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Origin"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Preset")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan Start\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan End\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan Resolution\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index Start\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index End\n(mm)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Index Resolution\n(mm)")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Start"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Pause")
//        }
//    }, //6
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Reading\nGroup"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field1"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field2"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field3"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Field4")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Selection")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Select"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "TOFD\nSettings"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "TOFD\nAnalysis")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Add/Delete"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Flaw Image"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Comment"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Display\nTable"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Export\nTable")
//        }
//    }, //7
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Save Setup As"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Open"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "File Manager")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Storage"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Save Mode"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Save Data"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "File Name")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Template"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Report Name"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Customer"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Part Name"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Part Number"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Create")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Probe/Wedge\nInfo"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Inspection\nInfo"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Scan\nInfo"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Encoder\nInfo"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "DAC/TCG\nInfo"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Flaw Record\nTable")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Select"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Enable"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Label"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Content"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Edit Note"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Print")
//        }
//    }, //8
//    {
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Units"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Bright\n(%)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Opacity")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Clock Set\n(HH:MM:SS)"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Date Set"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Language")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "IP\nAddress"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Subnet\nMask")
//        },
//        {
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "System\nInfomation"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Cert\nImport"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "SW\nUpdate"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "HW\nUpdate"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "Reset\nConfiguration"),
//            QT_TRANSLATE_NOOP("ThirdMenuWidget", "About")
//        }
//    } //9
//};

ThirdMenuWidget::ThirdMenuWidget(QWidget *parent) :
QWidget(parent),
	ui(new Ui::ThirdMenuWidget)
{
	ui->setupUi(this);

	widget = new FirstSecondMenuWidget;

	QFile *fileOne = new QFile(":/json/resources/menutwo.json");
    fileOne->open(QIODevice::ReadOnly | QIODevice::Text);
    QString stringOne = fileOne->readAll();
//#if QT_VERSION >= 0x050000
//    thirdMenuHash = read_json_file(stringOne);
//    jsonObjectOne = get_json_object(stringOne);
//#endif  
    thirdMenuMap = read_json_file(stringOne);
	fileOne->close();

    QFile *fileTwo = new QFile(":/json/resources/menuthree.json");
    fileTwo->open(QIODevice::ReadOnly | QIODevice::Text);
    QString stringTwo = fileTwo->readAll();
//#if QT_VERSION >= 0x050000
//    fourthMenuHash = read_json_file(stringTwo);
//    jsonObjectTwo = get_json_object(stringTwo);
//#endif
    fourthMenuMap = read_json_file(stringTwo);
	fileTwo->close();

//    QFile *fileThree = new QFile(":/json/resources/menucache.json");
//    fileThree->open(QIODevice::ReadOnly | QIODevice::Text);
//    QString stringThree = fileThree->readAll();
//    menuCacheMap = read_json_file(stringThree);
//    fileThree->close();

    height = this->geometry().height();
	initStandardModel();
	setThirdMenuName(0, 0);

    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));

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

	for(int k = 0; k < THIRD_MENU_NUMBER; k++)
	{
		QModelIndex index = model->index(k, 0, QModelIndex());
		model->setData(index, k);
	}

    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
        "{font: 13pt 'Times New Roman';"
        "background-color: rgba(0, 130, 195, 255);"
        "color: rgba(255, 255, 255, 255);"
        "border: 0px solid black;"
        "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
        "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

    ui->tableView->setStyleSheet("QTableView::item{"
        "border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 120, 195, 255));"
        "border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 120, 195, 255));}");


//    ui->tableView->show();
}

void ThirdMenuWidget::setThirdMenuName(int i, int j)
{
	currFirstNum = i;
	currSecondNum = j;
	model->clear();
	initStandardModel();
    firstMenuString = widget->firstMenuData.at(i);
    secondMenuString = widget->get_second_menu_list(i).at(j);
    QStringList thirdStringList = get_third_menu_list();
    set_model_item(0, thirdStringList.count());
	ui->tableView->show();
}

void ThirdMenuWidget::widgetStyleChoice(int k)
{
    QString thirdMenuString = get_third_menu_list().at(k);
    QString subString = firstMenuString + "_" + secondMenuString;

    QVariantMap subVariantMap = get_sub_menu_map(fourthMenuMap, thirdMenuString, subString);
    QVariantMap subCacheMap = get_sub_menu_map(menuCacheMap, thirdMenuString, subString);

    QString newThirdMenuString = set_long_contents_header(k, thirdMenuString);
    if(subVariantMap.contains("unit")) {
        model->setHeaderData(k, Qt::Horizontal, QString(newThirdMenuString + "\n(" + subVariantMap["unit"].toString() + ")"));
    } else {
        model->setHeaderData(k, Qt::Horizontal, newThirdMenuString);
    }

    if(subVariantMap.contains("style")) {
        switch(subVariantMap["style"].toString().toInt()) {
            case 1: {
                //SpinBox
                QList<int> rangeList = get_spinBox_range_list(subVariantMap);
                QStringList stepList = get_spinBox_step_list(subVariantMap, thirdMenuString);
                int decimal = subVariantMap["decimal"].toInt();

                DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
                doubleSpinBox->set_number_range(rangeList);
                doubleSpinBox->set_number_step_list(stepList);
                doubleSpinBox->set_number_step(stepList.at(0));
                doubleSpinBox->set_decimal_amount(decimal);               

                QStandardItem *item;
                if(subCacheMap.contains(thirdMenuString)) {
                    item = new QStandardItem(QString::number(subCacheMap[thirdMenuString].toString().toFloat(), 'f', decimal));
                } else {
                    item = new QStandardItem(QString::number((rangeList.at(0) + rangeList.at(1)) / 2, 'f', decimal));
                }

                model->setItem(0, k, item);
                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

                ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
                ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(createEditorHeaderText(QStringList)), this, SLOT(set_header_text_create(QStringList)));
//                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(closeEditorHeaderText(int)), this, SLOT(set_header_text_close(int)));
                break;
            }
            case 2: {
                //ComboBox
                QList<QStringList> list = get_comboBox_option_list(subVariantMap, thirdMenuString);

                ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
                comboBox->set_comboBox_item_list(list.at(0));
                comboBox->set_model_item_list(list.at(1));
                comboBox->set_minimum_contents_length(width / 6);                

                QStandardItem *item;
                if(subCacheMap.contains(thirdMenuString)) {
                    item = new QStandardItem(subCacheMap[thirdMenuString].toString());
                } else {
                    item = new QStandardItem(list.at(1).at(0));
                }

                model->setItem(0, k, item);
                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->tableView->setItemDelegateForColumn(k, comboBox);
                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(comboBox_current_text(QString)), this, SLOT(change_related_third_menu_data(QString)));
                break;
            }
            case 3: {
                //切换字on/off
                QVariantList tmpList = subVariantMap["label"].toList();
                QStringList switchList;
                if(tmpList.size() != 0) {
                    for(int index = 0; index < tmpList.size(); index ++) {
                    QMap<QString, QVariant> map = tmpList.at(index).toMap();
                    QVariant result = map.value(thirdMenuString);
                    switchList.append(result.toString());
                    }
                } else {
                    switchList.append("");
                }

                PushButtonDelegate *pushButton = new PushButtonDelegate(this);

                QStandardItem *item;
                if(subCacheMap.contains(thirdMenuString)) {
                    item = new QStandardItem(subCacheMap[thirdMenuString].toString());
                } else {
                    item = new QStandardItem(QString("On"));
                }

                model->setItem(0, k, item);
                model->item(0, k)->setFlags(Qt::NoItemFlags);
                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                ui->tableView->setItemDelegateForColumn(k, pushButton);
                break;
            }
//            case 4: {
//                //探头选择对话框
//                QStandardItem *item;
//                if(subCacheMap.contains(thirdMenuString)) {
//                    item = new QStandardItem(subCacheMap[thirdMenuString].toString());
//                } else {
//                    item = new QStandardItem("");
//                }

//                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//                model->setItem(0, k, item);
//                model->item(0, k)->setFlags(Qt::NoItemFlags);
//                break;
//            }
//            case 5: {
//                //楔块选择对话框
//                QStandardItem *item;
//                if(subCacheMap.contains(thirdMenuString)) {
//                    item = new QStandardItem(subCacheMap[thirdMenuString].toString());
//                } else {
//                    item = new QStandardItem("");
//                }

//                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//                model->setItem(0, k, item);
//                model->item(0, k)->setFlags(Qt::NoItemFlags);
//                break;
//            }
//            case 6: {
//                //软键盘输入
//                QStandardItem *item;
//                if(subCacheMap.contains(thirdMenuString)) {
//                    item = new QStandardItem(subCacheMap[thirdMenuString].toString());
//                } else {
//                    item = new QStandardItem("");
//                }

//                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//                model->setItem(0, k, item);
//                model->item(0, k)->setFlags(Qt::NoItemFlags);
//                break;
//            }
            case 0: {                
                QStandardItem *item = new QStandardItem(QString(""));
                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                model->setItem(0, k, item);
                model->item(0, k)->setFlags(Qt::NoItemFlags);
                break;
            }
            default:
                ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
                QStandardItem *item = new QStandardItem(QString(""));
                ui->tableView->setItemDelegateForColumn(k, comboBox);
                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                model->setItem(0, k, item);
                model->item(0, k)->setFlags(Qt::NoItemFlags);
                break;
        }
    } else {        
        ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
        QStandardItem *item = new QStandardItem(QString(""));
        ui->tableView->setItemDelegateForColumn(k, comboBox);
        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        model->setItem(0, k, item);
        model->item(0, k)->setFlags(Qt::NoItemFlags);
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

QVariantMap ThirdMenuWidget::read_json_file(QString string)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse(string.toUtf8(), &ok);
    QVariantMap variantMap = variant.toMap();
    if(!ok) {
        qDebug() << "An error occured during parsing.";
    }
    return variantMap;
}

QStringList ThirdMenuWidget::get_third_menu_list()
{
//#if QT_VERSION >= 0x050000
//    QStringList stringList;
//    if(get_json_document_type(secondMenuString, jsonObjectOne) == true) {
//        if(get_json_document_type(firstMenuString, jsonObjectOne[secondMenuString].toObject()) == false) {
//            QVariantList variantList = get_subsidiary_array(firstMenuString, jsonObjectOne[secondMenuString].toObject()).toVariantList();
//            for(int k = 0; k < variantList.size(); k ++) {
//                stringList.append(variantList.at(k).toString());
//            }
//        }
//    } else {
//        QVariantList variantList = thirdMenuHash.values(secondMenuString);
//        stringList = variantList.at(0).toStringList();
//    }
//    return stringList;
//#endif

//#if QT_VERSION < 0x050000
    QStringList stringList;
    QVariantList variantList;
    QVariantMap variantMap = thirdMenuMap[secondMenuString].toMap();
    if(!variantMap.isEmpty() && variantMap.contains(firstMenuString)) {
        variantList = variantMap.values(firstMenuString);
    } else if(!variantMap.isEmpty() && variantMap.contains("first third_menu")) {
        QString string = variantMap.value("first third_menu").toString();
        QVariantMap firstThirdMenuMap = get_sub_menu_map(fourthMenuMap, string, firstMenuString + "_" + secondMenuString);
        QStringList otherThirdMenuList = get_comboBox_option_list(firstThirdMenuMap, string).at(1);
        if(relatedMenuString == NULL || !otherThirdMenuList.contains(relatedMenuString)) {
            variantList = variantMap.values(otherThirdMenuList.at(0));
        } else {
            variantList = variantMap.values(relatedMenuString);
        }
    } else {
        variantList = thirdMenuMap.values(secondMenuString);
    }
    stringList = variantList.at(0).toStringList();
    return stringList;
//#endif
}

bool ThirdMenuWidget::eventFilter(QObject *object, QEvent *event)
{


    return QWidget::eventFilter(object, event);
}

void ThirdMenuWidget::onHeaderClicked(int index)
{
    QString thirdMenuString;
    if(get_third_menu_list().count() > index) {
       thirdMenuString  = get_third_menu_list().at(index);
    }
    QString subString = firstMenuString + "_" + secondMenuString;
    QVariantMap subVariantMap = get_sub_menu_map(fourthMenuMap, thirdMenuString, subString);

    if(subVariantMap["style"].toString().toInt() == 1) {
        //createEditor
        DoubleSpinBoxDelegate *doubleSpinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
//        const QStyleOptionViewItem option;
//        const QModelIndex modelIndex = model->item(0, index)->index();
//        QDoubleSpinBox *editor = static_cast<QDoubleSpinBox*>(doubleSpinBox->createEditor(ui->tableView, option, modelIndex));
//        qDebug() << editor->geometry();

//       const QItemEditorFactory *factory = doubleSpinBox->editorFactory;
//        qDebug() << "userType:" << modelIndex.data(Qt::EditRole).userType();
//        QWidget *w = factory->createEditor(modelIndex.data(Qt::EditRole).userType(), ui->tableView);
//        w->show();
        //点击表头更改spinbox的步进及表头文字
        QString currentHeaderText =  model->horizontalHeaderItem(index)->text();
        QString currentStep = doubleSpinBox->get_number_step();
        int stepIndex;
        QStringList stringList = doubleSpinBox->stepList;
        for(int i = 0; i < stringList.count(); i ++) {
            if(currentStep == stringList.at(i)) {
                stepIndex = i;
                break;
            }
        }
        QString headerText;
        if(currentHeaderText.contains("Δ")) {
            headerText = currentHeaderText.left(currentHeaderText.indexOf("Δ"));
        } else {
            headerText = currentHeaderText;
        }
        if(stepIndex == stringList.count() - 1) {
            doubleSpinBox->set_number_step(stringList.at(0));
            model->setHeaderData(index, Qt::Horizontal,QString(headerText + "Δ" + stringList.at(0)));
        } else {
            doubleSpinBox->set_number_step(stringList.at(stepIndex + 1));
            model->setHeaderData(index, Qt::Horizontal,QString(headerText + "Δ" + stringList.at(stepIndex + 1)));
        }
    } else if(subVariantMap["style"].toString().toInt() == 2) {
//        ComboBoxDelegate *comboBoxSpinBox = static_cast<ComboBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
//        comboBoxSpinBox->comboBoxList.at(comboBoxSpinBox->comboBoxList.count() - 1)->showPopup();
    } else if(subVariantMap["style"].toString().toInt() == 4) {
        //点击表头弹出探头选择对话框
        ProbeDialog *probeDialog = new ProbeDialog(this);
        probeDialog->show();
    } else if(subVariantMap["style"].toString().toInt() == 5) {
        //点击表头弹出楔块选择对话框
        WedgeDialog *wedgeDialog = new WedgeDialog(this);
        wedgeDialog->show();
    } else if(subVariantMap["style"].toString().toInt() == 6) {
        //点击表头弹出软键盘
        MyInputPanel inputPanel;
        inputPanel.showNormal();
        inputPanel.exec();
    }
}

void ThirdMenuWidget::set_header_text_create(QStringList stringList) const
{
    QString string = stringList.at(0);
    int index = string.toInt();
    QString headerText;
    QString currentHeaderText = model->horizontalHeaderItem(index)->text();
    if(currentHeaderText.contains("Δ")) {
        headerText = currentHeaderText.left(currentHeaderText.indexOf("Δ"));
    } else {
        headerText = currentHeaderText;
    }
    model->setHeaderData(index, Qt::Horizontal,QString(headerText + "Δ" + stringList.at(1)));
}

void ThirdMenuWidget::set_header_text_close(int index) const
{
//    QString currentHeaderText = model->horizontalHeaderItem(index)->text();
//    if(currentHeaderText.contains("Δ")) {
//        model->setHeaderData(index, Qt::Horizontal,QString(currentHeaderText.left(currentHeaderText.indexOf("Δ"))));
//    } else {
//        model->setHeaderData(index, Qt::Horizontal,QString(currentHeaderText));
//    }
}

QVariantMap ThirdMenuWidget::get_sub_menu_map(QVariantMap variantMap, QString thirdMenuString, QString subString)
{
    QVariantMap subVariantMap;
    if(!variantMap[thirdMenuString].toMap().isEmpty()) {
        QVariantMap map = variantMap[thirdMenuString].toMap();
        if(!map[subString].toMap().isEmpty()) {
            subVariantMap = map[subString].toMap();
        } else {
            subVariantMap = map;
        }
    }
    return subVariantMap;
}

QList<int> ThirdMenuWidget::get_spinBox_range_list(QVariantMap variantMap)
{
    int minimum = variantMap["minimum"].toInt();
    int maximum = variantMap["maximum"].toInt();
    QList<int> rangeList;
    rangeList.append(minimum);
    rangeList.append(maximum);
    return rangeList;
}

QStringList ThirdMenuWidget::get_spinBox_step_list(QVariantMap variantMap, QString thirdMenuString)
{
    QVariantList tmpList = variantMap["steps"].toList();
    QStringList stepList;
    if(tmpList.size() != 0) {
        for(int index = 0; index < tmpList.size(); index ++) {
            QMap<QString, QVariant> map = tmpList.at(index).toMap();
            QVariant result = map.value(thirdMenuString);
            stepList.append(result.toString());
        }
    } else {
        stepList.append("");
    }
    return stepList;
}

QList<QStringList> ThirdMenuWidget::get_comboBox_option_list(QVariantMap variantMap, QString thirdMenuString)
{
    QVariantList tmpList = variantMap["options"].toList();
    QStringList optionList;
    QStringList abbreviationList;
    QList<QStringList> list;
    if(tmpList.size() != 0) {
        for(int index = 0; index < tmpList.size(); index ++) {
            QMap<QString, QVariant> map = tmpList.at(index).toMap();
            QVariant result = map.value(thirdMenuString);
            optionList.append(result.toString());
            if(map.contains("ShortText")) {
                QVariant shortText = map.value("ShortText");
                abbreviationList.append(shortText.toString());
            } else {
                abbreviationList.append(optionList.at(index));
            }
        }
    } else {
        optionList.append("");
        abbreviationList.append("");
    }
    list.append(optionList);
    list.append(abbreviationList);
    return list;
}

QString ThirdMenuWidget::set_long_contents_header(int index, QString string)
{
//    qDebug() << ":" << ui->tableView->horizontalHeader()->fontMetrics().width(string);
//    qDebug() << string;
//    qDebug() << width/6;
    QString newString;
    if(ui->tableView->horizontalHeader()->fontMetrics().width(string) >= width / 6) {
        QString leftText, rightText;
        if(string.contains(" ")) {
            int index = string.indexOf(" ");
            leftText = string.left(index);
            rightText = string.right(string.length() - index - 1);
//            model->setHeaderData(index, Qt::Horizontal, leftText + "\n" + rightText);
            newString = leftText + "\n" + rightText;
        }
    } else {
        newString = string;
    }
    return newString;
}

void ThirdMenuWidget::change_related_third_menu_data(QString string)
{
    QVariantMap variantMap = thirdMenuMap[secondMenuString].toMap();
    if(!variantMap.isEmpty() && variantMap.contains("first third_menu")) {
        relatedMenuString = string;
        QVariantList variantList = variantMap.values(string);
        QStringList thirdStringList = variantList.at(0).toStringList();

        set_model_item(1, thirdStringList.count());
    }
}

void ThirdMenuWidget::set_model_item(int startIndex, int count)
{
    for(int k = startIndex; k < THIRD_MENU_NUMBER; k ++) {
        if(count >= k + 1) {
            widgetStyleChoice(k);
            model->item(0, k)->setTextAlignment(Qt::AlignCenter);
            model->item(0, k)->setForeground(Qt::yellow);
            model->item(0, k)->setFont(QFont("Times New Roman", 12));
        } else {
            model->setHeaderData(k, Qt::Horizontal, "");
            ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
            QStandardItem *item = new QStandardItem(QString(tr("")));
            ui->tableView->setItemDelegateForColumn(k, comboBox);
            model->setItem(0, k, item);
            model->item(0, k)->setFlags(Qt::NoItemFlags);
        }
        QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, height * 25 / 70));
        linearGradient.setColorAt(0.4, QColor(0, 0, 0));
        linearGradient.setColorAt(1, QColor(0, 120, 195));
        linearGradient.setSpread(QGradient::PadSpread);
        model->item(0, k)->setBackground(QBrush(linearGradient));
    }
}

void ThirdMenuWidget::cache_menu_data()
{
//    QJson::Serializer serializer;
//    bool ok;

//    QVariantList menuCacheList;
//    for(int k = 0; k < get_third_menu_list().count(); k ++) {
//        QString thirdMenuString = get_third_menu_list().at(k);
//        QVariantMap subCacheMap = get_sub_menu_map(menuCacheMap, thirdMenuString, firstMenuString + "_" + secondMenuString);
//        if(subCacheMap.contains(thirdMenuString)) {
//            subCacheMap.remove(thirdMenuString);
//        } else {
//            subCacheMap.insert(thirdMenuString, model->item(0, k)->text());
//        }
//        menuCacheList.append(subCacheMap);
//    }

//    QByteArray json = serializer.serialize(menuCacheList, &ok);
//    if(ok) {
//        qDebug() << json;
//        QFile file("./ui/resources/menuchace.json");
//        QFileInfo fileInfo(file);
//        QString filePath;
//        file.close();
//        filePath = fileInfo.absoluteFilePath();
//        qDebug() << filePath;
//        QFile *fileAbsolute = new QFile(filePath);
//        if(!fileAbsolute->open(QIODevice::ReadWrite | QIODevice::Text)) {
//            qDebug() << "Open failed.";
//            qDebug() << fileAbsolute->permissions();
//        }
//        qDebug() << fileAbsolute->readAll();
//        QTextStream out(fileAbsolute);
//        out << json << "\n";
//        out.flush();
//        file->close();
//        fileAbsolute->close();
//    } else {
//        qCritical() << "Something went wrong:" << serializer.errorMessage();
//    }
}


//#if QT_VERSION >= 0x050000
//void ThirdMenuWidget::widgetStyleChoice(int i, int j, int k)
//{
//    QStringList thirdStringList = get_third_menu_list(i, j);

//    QString firstMenuString = widget->firstMenuData.at(i);
//    QString secondMenuString = widget->get_second_menu_list(i).at(j);

//    QJsonObject subObject = get_subsidiary_object(thirdStringList.at(k), jsonObjectTwo);
//    if(subObject.contains(firstMenuString + "_" + secondMenuString)) {
//        subObject = get_subsidiary_object(firstMenuString + "_" + secondMenuString, subObject);
//    } else {

//    }
//    if(subObject.contains("unit")) {
//        model->setHeaderData(k, Qt::Horizontal, QString(thirdStringList.at(k) + "\n(" + subObject["unit"].toString() + ")"));
//    } else {
//        model->setHeaderData(k, Qt::Horizontal, thirdStringList.at(k));
//    }

//    if(subObject.contains("style")) {
//        switch(subObject["style"].toString().toInt()) {
//            case 1: {
//                int minimum = subObject["minimum"].toInt();
//                int maximum = subObject["maximum"].toInt();
//                int decimal = subObject["decimal"].toInt();
//                QList<int> rangeList;
//                rangeList.append(minimum);
//                rangeList.append(maximum);

//                QVariantList tmpList = subObject["steps"].toArray().toVariantList();
//                QStringList stepList;
//                if(tmpList.size() != 0) {
//                    for(int index = 0; index < tmpList.size(); index ++) {
//                        QMap<QString, QVariant> map = tmpList.at(index).toMap();
//                        QVariant result = map.value(thirdStringList.at(k));
//                        stepList.append(result.toString());
//                    }
//                } else {
//                    stepList.append("");
//                }

//                DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
//                doubleSpinBox->setObjectName("doubleSpinBoxDelegate_" + QString::number(k + 1));
//                doubleSpinBox->set_number_range(rangeList);
//                doubleSpinBox->set_number_step(stepList);
//                doubleSpinBox->set_decimal_amount(decimal);

//                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//                QStandardItem *item = new QStandardItem(QString::number((minimum + maximum) / 2, 'f', decimal));
//                model->setItem(0, k, item);
//                ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
//                ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);

//                break;
//            }
//            case 2: {
//                QVariantList tmpList = subObject["options"].toArray().toVariantList();
//                QStringList optionList;
//                QStringList abbreviationList;
//                if(tmpList.size() != 0) {
//                    for(int index = 0; index < tmpList.size(); index ++) {
//                        QMap<QString, QVariant> map = tmpList.at(index).toMap();
//                        QVariant result = map.value(thirdStringList.at(k));
//                        optionList.append(result.toString());
//                        if(map.contains("ShortText")) {
//                            QVariant shortText = map.value("ShortText");
//                            abbreviationList.append(shortText.toString());
//                        } else {
//                            abbreviationList.append(optionList.at(index));
//                        }
//                    }
//                } else {
//                    optionList.append("");
//                    abbreviationList.append("");
//                }

//                ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
//                comboBox->set_comboBox_item_list(optionList);
//                comboBox->set_model_item_list(abbreviationList);

//                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//                QStandardItem *item = new QStandardItem(abbreviationList.at(0));
//                model->setItem(0, k, item);
//                ui->tableView->setItemDelegateForColumn(k, comboBox);
//                break;
//            }
//            case 3: {
//                //切换字on/off
//                QVariantList tmpList = subObject["label"].toArray().toVariantList();
//                QStringList switchList;
//                if(tmpList.size() != 0) {
//                    for(int index = 0; index < tmpList.size(); index ++) {
//                    QMap<QString, QVariant> map = tmpList.at(index).toMap();
//                    QVariant result = map.value(thirdStringList.at(k));
//                    switchList.append(result.toString());
//                    }
//                } else {
//                    switchList.append("");
//                }

//                PushButtonDelegate *pushButton = new PushButtonDelegate(this);


//                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//                QStandardItem *item = new QStandardItem(QString("on"));
//                model->setItem(0, k, item);
//                //          model->item(0, k)->setFlags(Qt::ItemIsEnabled);
//                ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
//                ui->tableView->setItemDelegateForColumn(k, pushButton);
//                break;
//            }
//            case 0: {
//                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//                QStandardItem *item = new QStandardItem(QString(""));
//                model->setItem(0, k, item);
//                model->item(0, k)->setFlags(Qt::NoItemFlags);
//                break;
//            }
//            default:
//                break;
//        }
//    } else {
//        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
//        QStandardItem *item = new QStandardItem(QString(""));
//        model->setItem(0, k, item);
//        model->item(0, k)->setFlags(Qt::NoItemFlags);
//    }
//}

//QVariantHash ThirdMenuWidget::read_json_file(QString string)
//{
//    QJsonParseError error;
//    QJsonDocument jsonDocument = QJsonDocument::fromJson(string.toUtf8(), &error);
//    QVariantHash variantHash;
//    if(error.error == QJsonParseError::NoError) {
//        if(!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
//            if(jsonDocument.isObject()) {
//                QJsonObject jsonObject = jsonDocument.object();
//                variantHash = jsonObject.toVariantHash();
//            } else if(jsonDocument.isArray()) {

//            }
//        }
//    } else {
//        qDebug() << "Error Type" << error.error;
//        qDebug() << "Error Message:" << error.errorString();
//    }
//    return variantHash;
//}

//QJsonObject ThirdMenuWidget::get_json_object(QString string)
//{
//    QJsonParseError error;
//    QJsonDocument jsonDocument = QJsonDocument::fromJson(string.toUtf8(), &error);
//    QJsonObject jsonObject;
//    if(error.error == QJsonParseError::NoError) {
//        if(!(jsonDocument.isNull() || jsonDocument.isEmpty())) {
//            if(jsonDocument.isObject()) {
//                jsonObject = jsonDocument.object();
//            } else if(jsonDocument.isArray()) {

//            }
//        }
//    } else {
//        qDebug() << "Error Type" << error.error;
//        qDebug() << "Error Message:" << error.errorString();
//    }
//    return jsonObject;
//}

//bool ThirdMenuWidget::get_json_document_type(QString string, QJsonObject jsonObject)
//{
//    bool isObjectFlag;
//    if(jsonObject.contains(string)) {
//        if(jsonObject[string].isObject()) {
//            isObjectFlag = true;
//        } else if(jsonObject[string].isArray()) {
//            isObjectFlag = false;
//        }
//    }
//    return isObjectFlag;
//}

//QJsonObject ThirdMenuWidget::get_subsidiary_object(QString string, QJsonObject jsonObject)
//{
//	QJsonObject subObject;
//	if(jsonObject.contains(string)) {
//		if(jsonObject[string].isObject()) {
//			subObject = jsonObject[string].toObject();
//		}
//	}
//	return subObject;
//}

//QJsonArray ThirdMenuWidget::get_subsidiary_array(QString string, QJsonObject jsonObject)
//{
//    QJsonArray subArray;
//    if(jsonObject.contains(string)) {
//        if(jsonObject[string].isArray()) {
//            subArray = jsonObject[string].toArray();
//        }
//    }
//    return subArray;
//}
//#endif

//void ThirdMenuWidget::paintBorder()
//{
//  QPainter painter(ui->tableView);
//  QLinearGradient linearGradientOne(QPointF(0, 0), QPointF(0, height * 25 / 70));
//  linearGradientOne.setColorAt(0.158192, QColor(255, 255, 255));
//  linearGradientOne.setColorAt(0.757062, QColor(0, 120, 195));
//  QLinearGradient linearGradientTwo(QPointF(0, 0), QPointF(0, height * 25 / 70));
//  linearGradientTwo.setColorAt(0.158192, QColor(0, 0, 0));
//  linearGradientTwo.setColorAt(0.757062, QColor(0, 120, 195));
//  painter.setBrush(linearGradientOne);

//  for(int i = 0; i < 6; i ++)
//  {
//    painter.drawRect(i * width / 6, 0, 1, height);
//  }
//  painter.setBrush(linearGradientTwo);
//  for(int i = 0; i < 6; i ++)
//  {
//    painter.drawRect((i + 1) * (width / 6), 0, 1, height);
//  }
//  update();
//}

//bool ThirdMenuWidget::eventFilter(QObject *object, QEvent *event)
//{
//  if(object == ui->tableView && event->type() == QEvent::Paint)
//  {
//    paintBorder();
//  }
//  return QWidget::eventFilter(object, event);
//}



