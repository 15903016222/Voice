#include "thirdmenuwidget.h"
#include "ui_thirdmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"
#include "pushbuttondelegate.h"
#include "probedialog.h"
#include "wedgedialog.h"
#include "myinputpanel.h"
#include "measurementdialog.h"
#include "inputpanelcontext.h"
#include "verticalsliderdialog.h"

ThirdMenuWidget::ThirdMenuWidget(QWidget *parent) :
QWidget(parent),
	ui(new Ui::ThirdMenuWidget)
{
	ui->setupUi(this);

	widget = new FirstSecondMenuWidget;

	QFile *fileOne = new QFile(":/json/resources/menutwo.json");
    fileOne->open(QIODevice::ReadOnly | QIODevice::Text);
    QString stringOne = fileOne->readAll();

    thirdMenuMap = read_json_file(stringOne);
	fileOne->close();

    QFile *fileTwo = new QFile(":/json/resources/menuthree.json");
    fileTwo->open(QIODevice::ReadOnly | QIODevice::Text);
    QString stringTwo = fileTwo->readAll();

    fourthMenuMap = read_json_file(stringTwo);
    fileTwo->close();

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
    height = this->geometry().height();
    ui->tableView->horizontalHeader()->setFixedHeight(height * 45 / 70);
    ui->tableView->verticalHeader()->setDefaultSectionSize(height * 25 / 70);
    ui->tableView->verticalHeader()->hide();
    ui->tableView->horizontalHeader()->setDefaultAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
        "{font: 13pt 'Times New Roman';"
        "background-color: rgba(0, 130, 195, 255);"
        "color: rgba(255, 255, 255, 255);"
        "border: 0px solid black;"
        "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(255, 255, 255, 255));"
        "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1, stop:0.158192 rgba(0, 130, 195, 255), stop:0.559322 rgba(0, 0, 0, 255));}");

    ui->tableView->setStyleSheet("QTableView::item"
        "{font: 12pt 'Times New Roman';"
        "color: yellow;"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
        "border-left:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(255, 255, 255, 255), stop:1 rgba(0, 120, 195, 255));"
        "border-right:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));}");

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

    firstMenuString = widget->firstMenuData.at(i);
    secondMenuString = widget->get_second_menu_list(i).at(j);
    QStringList thirdStringList = get_third_menu_list();
    set_model_item(0, thirdStringList.count());
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
            case 0: {
                QStandardItem *item = new QStandardItem(QString(""));
                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                model->setItem(0, k, item);
                model->item(0, k)->setFlags(Qt::NoItemFlags);
                break;
            }
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
                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(closeEditor(QWidget*)), this, SLOT(set_header_text_close(QWidget*)));
//                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(closeEditorHeaderText(QModelIndex)), this, SLOT(set_header_text_close(const QModelIndex)));
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
    setThirdMenuName(currFirstNum, currSecondNum);
}

QVariantMap ThirdMenuWidget::read_json_file(QString string)
{
    QJson::Parser parser;
    bool ok;
    QVariant variant = parser.parse(string.toUtf8(), &ok);
    QVariantMap variantMap = variant.toMap();

    return variantMap;
}

QStringList ThirdMenuWidget::get_third_menu_list()
{
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
}

void ThirdMenuWidget::onHeaderClicked(int index)
{
    QString thirdMenuString;
    if(get_third_menu_list().count() > index) {
       thirdMenuString  = get_third_menu_list().at(index);
    } else {
        return;
    }
    QString subString = firstMenuString + "_" + secondMenuString;
    QVariantMap subVariantMap = get_sub_menu_map(fourthMenuMap, thirdMenuString, subString);

    if(subVariantMap["style"].toString().toInt() == 1) {
        QModelIndex modelIndex = model->item(0, index)->index();
        ui->tableView->edit(modelIndex);

        //点击表头更改spinbox的步进及表头文字
        DoubleSpinBoxDelegate *doubleSpinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
        QString currentHeaderText =  model->horizontalHeaderItem(index)->text();
        QString currentStep = doubleSpinBox->get_number_step();
        int stepIndex = 0;
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
            model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(0)));
        } else {
            doubleSpinBox->set_number_step(stringList.at(stepIndex + 1));
            model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex + 1)));
        }

        if(currentHeaderText.contains("Bright")) {
            VerticalSliderDialog *verticalSliderDialog = new VerticalSliderDialog(this);
            verticalSliderDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
            verticalSliderDialog->show();

            brightIndex = index;
            QString text = model->item(0, brightIndex)->text();
            verticalSliderDialog->setBrightValue(text);
            connect(verticalSliderDialog->slider.at(0), SIGNAL(valueChanged(int)), this, SLOT(setBrightValue(int)));
        }
    } else if(subVariantMap["style"].toString().toInt() == 2) {
        QModelIndex modelIndex = model->item(0, index)->index();
        ui->tableView->edit(modelIndex);
    } else if(subVariantMap["style"].toString().toInt() == 4) {
        //点击表头弹出探头选择对话框
        ProbeDialog *probeDialog = new ProbeDialog(this);
        probeDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        probeDialog->show();
    } else if(subVariantMap["style"].toString().toInt() == 5) {
        //点击表头弹出楔块选择对话框
        WedgeDialog *wedgeDialog = new WedgeDialog(this);
        wedgeDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        wedgeDialog->show();
    } else if(subVariantMap["style"].toString().toInt() == 6) {
        //点击表头弹出软键盘
        InputPanelContext *inputPanel = new InputPanelContext(this);
        inputPanel->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        inputPanel->show();

        inputIndex = index;
        connect(this, SIGNAL(inputItemCurrentText(QString)), inputPanel, SLOT(set_item_current_text(QString)));
        QString text = model->item(0, index)->text();
        emit inputItemCurrentText(text);
        connect(inputPanel, SIGNAL(textEditFinished(QString)), this, SLOT(set_edited_text(QString)));

    } else if(subVariantMap["style"].toString().toInt() == 7) {
        //点击表头弹出测量值选择对话框
        MeasurementDialog *measurementDialog = new MeasurementDialog(this);
        measurementDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        measurementDialog->show();

        measurementIndex = index;
        connect(measurementDialog, SIGNAL(labelTextChanged(QString)), this, SLOT(change_measurement_label(QString)));
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
    model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(1)));
}

void ThirdMenuWidget::set_header_text_close(QWidget *editor)
{
    int editorPosX = editor->x() + editor->width();
    int column = editorPosX / (width / THIRD_MENU_NUMBER) - 1;
    QString currentHeaderText = model->horizontalHeaderItem(column)->text();
    if(currentHeaderText.contains("Δ")) {
        model->setHeaderData(column, Qt::Horizontal, QString(currentHeaderText.left(currentHeaderText.indexOf("Δ"))));
    } else {
        model->setHeaderData(column, Qt::Horizontal, QString(currentHeaderText));
    }
}

void ThirdMenuWidget::on_tableView_clicked(const QModelIndex &index)
{
    QString thirdMenuString;
    if(get_third_menu_list().count() > index.column()) {
       thirdMenuString  = get_third_menu_list().at(index.column());
    } else {
        return;
    }
    QString subString = firstMenuString + "_" + secondMenuString;
    QVariantMap subVariantMap = get_sub_menu_map(fourthMenuMap, thirdMenuString, subString);

    if(subVariantMap["style"].toString().toInt() == 1) {
        ui->tableView->edit(index);
    } else if(subVariantMap["style"].toString().toInt() == 2) {
        ui->tableView->edit(index);
    }
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
    Q_UNUSED(index);
    QString newString;
    if(ui->tableView->horizontalHeader()->fontMetrics().width(string) >= width / 6) {
        QString leftText, rightText;
        if(string.contains(" ")) {
            int blankIndex = string.indexOf(" ");
            leftText = string.left(blankIndex);
            rightText = string.right(string.length() - blankIndex - 1);
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
    if(!variantMap.isEmpty() && variantMap.contains("first third_menu") && variantMap.contains(string)) {
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
            model->item(0, k)->setFont(QFont("Times New Roman", 12));
        } else {
            model->setHeaderData(k, Qt::Horizontal, "");
            ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
            QStandardItem *item = new QStandardItem(QString(tr("")));
            ui->tableView->setItemDelegateForColumn(k, comboBox);
            model->setItem(0, k, item);
            model->item(0, k)->setFlags(Qt::NoItemFlags);
        }
    }
}

void ThirdMenuWidget::change_measurement_label(QString string)
{
    for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
        if(i == measurementIndex) {
            model->setHeaderData(measurementIndex, Qt::Horizontal, string);
            break;
        }
    }
}

void ThirdMenuWidget::set_edited_text(QString string)
{
    for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
        if(i == inputIndex) {
            model->item(0, i)->setText(string);
            break;
        }
    }
}

void ThirdMenuWidget::setBrightValue(int value)
{
    for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
        if(i == brightIndex) {
            QString brightValue;
            brightValue.append(QString::number((double)value, 'f', 0));
            model->item(0, i)->setText(brightValue);
            break;
        }
    }
}
