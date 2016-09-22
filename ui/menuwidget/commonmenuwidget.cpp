#include "commonmenuwidget.h"
#include "ui_commonmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"
#include "pushbuttondelegate.h"

#include <QResizeEvent>
#include <QDebug>

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
    this->resize(800, 70);
    height = this->geometry().height();
    setCommonMenuName();

    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));

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

    ui->tableView->setStyleSheet("QTableView::item{"
        "color: yellow;"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
        "border-left:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(255, 255, 255, 255), stop:1 rgba(0, 120, 195, 255));"
        "border-right:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));}");

    for(int k = 0; k < COMMON_MENU_NUMBER; k++)
    {
        QModelIndex index = model->index(k, 0, QModelIndex());
        model->setData(index, k);
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
            model->item(0, k)->setFont(QFont("Times New Roman", 12));
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
        QList<int> rangeList;
        rangeList.append(0.00);
        rangeList.append(100.00);
        QStringList stepList;
        stepList.append("0.01");
        stepList.append("0.10");
        stepList.append("1.00");
        stepList.append("10.00");
        int decimal = 2;

        DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
        doubleSpinBox->set_number_range(rangeList);
        doubleSpinBox->set_number_step_list(stepList);
        doubleSpinBox->set_number_step(stepList.at(0));
        doubleSpinBox->set_decimal_amount(decimal);

        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString::number(0, 'f', decimal));
        model->setItem(0, k, item);
        ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
        ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
        connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(createEditorHeaderText(QStringList)), this, SLOT(set_header_text_create(QStringList)));
        connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(closeEditor(QWidget*)), this, SLOT(set_header_text_close(QWidget*)));
        break;
    }
    case 2:
    {

        ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);

        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString("On"));
        model->setItem(0, k, item);
        ui->tableView->setItemDelegateForColumn(k, comboBox);
        connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(comboBox_current_text(QString)), this, SLOT(change_related_third_menu_data(QString)));
        break;
    }
    case 3:
    {
        PushButtonDelegate *pushButton = new PushButtonDelegate(this);

        model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        QStandardItem *item = new QStandardItem(QString("on"));
        model->setItem(0, k, item);
//          model->item(0, k)->setFlags(Qt::ItemIsEnabled);
        ui->tableView->setEditTriggers(QAbstractItemView::CurrentChanged);
        ui->tableView->setItemDelegateForColumn(k, pushButton);
        break;
    }
    case 0:
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
    setCommonMenuName();
}

void CommonMenuWidget::onHeaderClicked(int index)
{
//    QString thirdMenuString;
//    if(get_third_menu_list().count() > index) {
//       thirdMenuString  = get_third_menu_list().at(index);
//    } else {
//        return;
//    }
//    QString subString = firstMenuString + "_" + secondMenuString;
//    QVariantMap subVariantMap = get_sub_menu_map(fourthMenuMap, thirdMenuString, subString);

    if(CHOICE_WIDGET_CHAR[index].toInt() == 1) {
        QModelIndex modelIndex = model->item(0, index)->index();
        ui->tableView->edit(modelIndex);

        //点击表头更改spinbox的步进及表头文字
        DoubleSpinBoxDelegate *doubleSpinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
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
    } else if(CHOICE_WIDGET_CHAR[index].toInt() == 2) {
        QModelIndex modelIndex = model->item(0, index)->index();
        ui->tableView->edit(modelIndex);
    } /*else if(subVariantMap["style"].toString().toInt() == 4) {
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
    }*/
}

void CommonMenuWidget::set_header_text_create(QStringList stringList) const
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

void CommonMenuWidget::set_header_text_close(QWidget *editor)
{
    int editorPosX = editor->x() + editor->width();
    int column = editorPosX / (width / COMMON_MENU_NUMBER) - 1;
    QString currentHeaderText = model->horizontalHeaderItem(column)->text();
    if(currentHeaderText.contains("Δ")) {
        model->setHeaderData(column, Qt::Horizontal,QString(currentHeaderText.left(currentHeaderText.indexOf("Δ"))));
    } else {
        model->setHeaderData(column, Qt::Horizontal,QString(currentHeaderText));
    }
}

void CommonMenuWidget::on_tableView_clicked(const QModelIndex &index)
{
//    QString thirdMenuString;
//    if(get_third_menu_list().count() > index.column()) {
//       thirdMenuString  = get_third_menu_list().at(index.column());
//    } else {
//        return;
//    }
//    QString subString = firstMenuString + "_" + secondMenuString;
//    QVariantMap subVariantMap = get_sub_menu_map(fourthMenuMap, thirdMenuString, subString);

//    if(subVariantMap["style"].toString().toInt() == 1) {
//        ui->tableView->edit(index);
//    } else if(subVariantMap["style"].toString().toInt() == 2) {
//        ui->tableView->edit(index);
//    }
}
