#include "topmenu.h"
#include "ui_topmenu.h"

#include "doublespinboxdelegate.h"

TopMenu :: TopMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TopMenu)
{
    ui->setupUi(this);
    initUI();

    initGain_angle();

}

TopMenu :: ~TopMenu()
{
    delete(ui);
}

void TopMenu::reTranslatorTopMenuUi()
{
    ui->retranslateUi(this);
}

void TopMenu::initUI()
{
    setTopMenuFont();

    for(int i = 1; i < TOP_MENU_NUMBER; i ++) {
        measurementLabelList.at(i)->installEventFilter(this);
    }
}

void TopMenu::setTopMenuFont()
{
    for(int i = 1; i <= TOP_MENU_NUMBER; i ++){
        QLabel *label = findChild<QLabel*>("label_" + QString::number(i));
        measurementLabelList.append(label);

        QString str = label->text();
        QString text1, text2;

        if(str.contains("\n") == true) {
            int index = str.indexOf("\n");
            text1 = str.left(index);
            text2 = str.right(str.length() - index - 1);

            if(i == 1 || i == TOP_MENU_NUMBER){
                label->setText("<font color=yellow face='Times New Roman' style=font-size:14pt>"
                               +text1+
                               "</font><br><font color=yellow face='Times New Roman' style=font-size:12pt>"
                               +text2+"</font>");
            }else{
                label->setText("<font color=white face='Times New Roman' style='font-size:14pt'>"
                               +text1+
                               "</font><br><font color=white face='Times New Roman' style='font-size:12pt'>"
                               +text2+"</font>");
            }
        }
    }
}

void TopMenu::initGain_angle()
{
#if QT_VERSION >= 0x050000
    ui->tableView_gain->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_gain->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

#if QT_VERSION < 0x050000
    ui->tableView_gain->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView_gain->verticalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ui->tableView_gain->horizontalHeader()->hide();
    ui->tableView_gain->verticalHeader()->hide();

    QStandardItemModel *model_gain = new QStandardItemModel(1, 2, this);
    ui->tableView_gain->setModel(model_gain);

    QFile *file = new QFile(":/json/resources/menuthree.json");
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString string = file->readAll();
    QVariantMap fourthMap = thirdMenuWidget->read_json_file(string);
    QVariantMap variantMapGain = thirdMenuWidget->get_sub_menu_map(fourthMap, "Gain", "UT Settings_General");
//    QVariantMap variantMapAngle = thirdMenuWidget->get_fourth_menu_map(fourthMap, QString("Angle"), QString("Measurement_Cursors"));
    QVariantMap variantMapAngle = thirdMenuWidget->get_sub_menu_map(fourthMap, QString("Min. Angle"), QString("Focal Law_Angle"));
    file->close();

    int decimalGain = variantMapGain["decimal"].toInt();
    QList<int> rangeListGain = thirdMenuWidget->get_spinBox_range_list(variantMapGain);
    QStringList stepListGain = thirdMenuWidget->get_spinBox_step_list(variantMapGain, "Gain");

    DoubleSpinBoxDelegate *doubleSpinBoxOne = new DoubleSpinBoxDelegate(this);
    doubleSpinBoxOne->set_number_range(rangeListGain);
    doubleSpinBoxOne->set_number_step_list(stepListGain);
    doubleSpinBoxOne->set_number_step(stepListGain.at(0));
    doubleSpinBoxOne->set_decimal_amount(decimalGain);

    QStandardItem *item_gain1 = new QStandardItem(QString::number(100, 'f', decimalGain));
    QStandardItem *item_gain2 = new QStandardItem("(" + QString::number(10, 'f', decimalGain) + ")");
    model_gain->setItem(0, 0, item_gain1);
    model_gain->setItem(0, 1, item_gain2);
    model_gain->item(0, 0)->setTextAlignment(Qt::AlignRight|Qt::AlignVCenter);
    model_gain->item(0, 1)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    model_gain->item(0, 0)->setForeground(Qt::white);
    model_gain->item(0, 1)->setForeground(Qt::yellow);
    model_gain->item(0, 0)->setFont(QFont("Times New Roman", 14));
    model_gain->item(0, 1)->setFont(QFont("Times New Roman", 10));
    ui->tableView_gain->setItemDelegate(doubleSpinBoxOne);
    ui->tableView_gain->setEditTriggers(QAbstractItemView::CurrentChanged);
    ui->tableView_gain->show();

#if QT_VERSION >= 0x050000
    ui->tableView_angle->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_angle->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
#endif

#if QT_VERSION < 0x050000
    ui->tableView_angle->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tableView_angle->verticalHeader()->setResizeMode(QHeaderView::Stretch);
#endif

    ui->tableView_angle->horizontalHeader()->hide();
    ui->tableView_angle->verticalHeader()->hide();

    QStandardItemModel *model_angle = new QStandardItemModel(1, 1, this);
    ui->tableView_angle->setModel(model_angle);

    int decimalAngle = variantMapAngle["decimal"].toInt();
    QList<int> rangeListAngle = thirdMenuWidget->get_spinBox_range_list(variantMapAngle);
//    QStringList stepList = thirdMenuWidget->get_spinBox_step_list(variantMap, "Angle");
    QStringList stepListAngle = thirdMenuWidget->get_spinBox_step_list(variantMapAngle, "Min. Angle");

    DoubleSpinBoxDelegate *doubleSpinBoxAngle = new DoubleSpinBoxDelegate(this);
    doubleSpinBoxAngle->set_number_range(rangeListAngle);
    doubleSpinBoxAngle->set_number_step_list(stepListAngle);
    doubleSpinBoxAngle->set_number_step(stepListAngle.at(0));
    doubleSpinBoxAngle->set_decimal_amount(decimalAngle);

    QStandardItem *item_angle = new QStandardItem(QString::number(70, 'f', decimalAngle));
    model_angle->setItem(0, item_angle);
    model_angle->item(0)->setTextAlignment(Qt::AlignCenter);
    model_angle->item(0)->setForeground(Qt::white);
    model_angle->item(0)->setFont(QFont("Times New Roman", 14));
    ui->tableView_angle->setItemDelegate(doubleSpinBoxAngle);
//    ui->tableView_angle->setEditTriggers(QAbstractItemView::CurrentChanged);
    ui->tableView_angle->show();
}

bool TopMenu::eventFilter(QObject *object, QEvent *event)
{
    if(object == measurementLabelList.at(1) ||
            object == measurementLabelList.at(2) ||
            object == measurementLabelList.at(3) ||
            object == measurementLabelList.at(4) ||
            object == measurementLabelList.at(5) ||
            object == measurementLabelList.at(6) ||
            object == measurementLabelList.at(7) ||
            object == measurementLabelList.at(8))
    {
        if(event->type() == QEvent::MouseButtonPress) {
            objectName = object->objectName();
            mDialog = new MeasurementDialog;
            mDialog->setModal(true);
            mDialog->setWindowFlags(Qt::FramelessWindowHint);
            mDialog->show();
            connect(mDialog, SIGNAL(labelTextChanged(QString)), this, SLOT(changeLabelText(QString)));
        }
    }
    return QWidget::eventFilter(object, event);
}

void TopMenu::changeLabelText(QString str)
{
    for(int i = 1; i < TOP_MENU_NUMBER; i++) {
        if(measurementLabelList.at(i)->objectName() == objectName ){
            QString text1, text2;
            if(str.contains("\n") == true) {
                int index = str.indexOf("\n");
                text1 = str.left(index);
                text2 = str.right(str.length() - index - 1);
                measurementLabelList.at(i)->setText("<font color=white face='Times New Roman' style='font-size:14pt'>"
                                                    +text1+
                                                    "</font><br><font color=white face='Times New Roman' style='font-size:12pt'>"
                                                    +text2+"</font>");
            } else {
                measurementLabelList.at(i)->setText("<font color=white face='Times New Roman' style='font-size:14pt'>"
                                                    +str+
                                                    "</font>");
            }
            break;
        }
    }
}
