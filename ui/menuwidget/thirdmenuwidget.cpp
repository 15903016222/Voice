#include "thirdmenuwidget.h"
#include "ui_thirdmenuwidget.h"

#include "doublespinboxdelegate.h"
#include "comboboxdelegate.h"
#include "pushbuttondelegate.h"
#include "probedialog.h"
#include "wedgedialog.h"
#include "measurementdialog.h"
#include "inputpanelcontext.h"
#include "about_dialog.h"
#include "resetconfigdialog.h"
#include "sysinfo_dialog.h"
#include "filemanagerdialog.h"

#include <QMap>
#include <QResizeEvent>
#include <QAbstractItemView>

ThirdMenuWidget::ThirdMenuWidget(QWidget *parent) :
QWidget(parent),
    ui(new Ui::ThirdMenuWidget)
{
    ui->setupUi(this);

    widget = new FirstSecondMenuWidget;
    dateTimeSetDialog = new DateTimeSetDialog(this);
    networkDialog = new NetworkDialog(this);

    height = this->geometry().height();
    languageOption = 1;
    keyboardShowFlag = false;
    opendSpinBoxIndex = -1;

    opacity = 100.0;

    init_standard_model();
    set_third_menu_name(0, 0);

    connect(ui->tableView->horizontalHeader(), SIGNAL(sectionClicked(int)), this, SLOT(onHeaderClicked(int)));

    m_mcu = Mcu::get_mcu();
    set_autoDetect_probeModel(false);

}

ThirdMenuWidget::~ThirdMenuWidget()
{
    delete ui;
}

void ThirdMenuWidget::retranslate_third_menu_ui(QString string)
{
    emit retranslate_ui(string);
    ui->retranslateUi(this);
    if(string == "Chinese") {
        languageOption = 2;
    } else if (string == "English") {
        languageOption = 1;
    }
    dateTimeSetDialog->retranslate_dialog_ui();
    networkDialog->retranslate_dialog_ui();
    set_third_menu_name(8, 1);
    set_currentDateToMenu();
    set_currentTimeToMenu();
}

void ThirdMenuWidget::init_standard_model()
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

void ThirdMenuWidget::set_third_menu_name(int i, int j)
{
    currFirstNum = i;
    currSecondNum = j;

    if(opendSpinBoxIndex >= 0) {
        disconnect_input_number();
        opendSpinBoxIndex = -1;
    }

    model->clear();
    init_standard_model();

    firstMenuString = widget->firstMenuData.at(i);
    secondMenuString = widget->get_second_menu_list(i).at(j);

    set_model_item(0, get_third_menu_list());
}

void ThirdMenuWidget::choose_widget_style(int k, QVariantMap thirdMenuMap, QString thirdMenuString)
{
    if(thirdMenuMap.contains("style")) {
        switch(thirdMenuMap["style"].toString().toInt()) {
            case 0: {
                QStandardItem *item = new QStandardItem(QString(""));
                model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
                model->setItem(0, k, item);
                model->item(0, k)->setFlags(Qt::NoItemFlags);
                break;
            }
            case 1: {
                //SpinBox
                QList<int> rangeList = get_spinBox_range_list(thirdMenuMap);
                QStringList stepList = get_spinBox_step_list(thirdMenuMap);
                int decimal = thirdMenuMap["decimal"].toInt();

                DoubleSpinBoxDelegate *doubleSpinBox = new DoubleSpinBoxDelegate(this);
                doubleSpinBox->set_number_range(rangeList);
                doubleSpinBox->set_number_step_list(stepList);
                doubleSpinBox->set_number_step(stepList.at(0));
                doubleSpinBox->set_decimal_amount(decimal);

                QStandardItem *item;
                item = new QStandardItem(QString::number((rangeList.at(0) + rangeList.at(1)) / 2, 'f', decimal));

                model->setItem(0, k, item);
                ui->tableView->setItemDelegateForColumn(k, doubleSpinBox);
                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(createEditorHeaderText(QStringList)), this, SLOT(set_header_text_create(QStringList)));
                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(closeEditor(QWidget*)), this, SLOT(set_header_text_close(QWidget*)));

                if(thirdMenuString.contains("Bright")) {
                    connect(doubleSpinBox, SIGNAL(stringChanged(double)), this, SLOT(setBrightness(double)));
                }else if(thirdMenuString.contains("Opacity")) {
                    item = new QStandardItem(QString::number(100.0, 'f', 0));
                    model->setItem(0, 2, item);
                    connect(doubleSpinBox, SIGNAL(stringChanged(double)), this, SLOT(setOpacity(double)));
                }
                break;

                break;
            }
            case 2: {
                //ComboBox
                QList<QStringList> list;
                if(languageOption == 1) {
                    list = get_comboBox_option_list(thirdMenuMap);
                } else if(languageOption == 2) {
                    QVariantMap headerMap = get_translate_option_map(thirdMenuString);
                    list = get_translate_comboBox_option_list(thirdMenuMap, headerMap);
                }

                ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
                comboBox->set_comboBox_item_list(list.at(0));
                comboBox->set_model_item_list(list.at(1));
                comboBox->set_minimum_contents_length(width / 6);

                QStandardItem *item;
                item = new QStandardItem(list.at(1).at(0));

                model->setItem(0, k, item);
                ui->tableView->setItemDelegateForColumn(k, comboBox);
                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(comboBox_current_text(QString)), this, SLOT(change_related_third_menu_data(QString)));
                connect(ui->tableView->itemDelegateForColumn(k), SIGNAL(change_language(QString)), this, SLOT(retranslate_third_menu_ui(QString)));
                break;
            }
            case 3: {
                //切换字on/off
                QVariantList tmpList = thirdMenuMap["label"].toList();
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
                item = new QStandardItem(QString("Off"));

                model->setItem(0, k, item);
                model->item(0, k)->setFlags(Qt::NoItemFlags);
                ui->tableView->setItemDelegateForColumn(k, pushButton);

                if(thirdMenuString.contains("Auto Detect")) {
                    connect(pushButton, SIGNAL(switchPress(bool)), this, SLOT(set_autoDetect_probeModel(bool)));
                }
                break;
            }
            default:
                ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
                QStandardItem *item = new QStandardItem(QString(""));
                ui->tableView->setItemDelegateForColumn(k, comboBox);
                model->setItem(0, k, item);
                model->item(0, k)->setFlags(Qt::NoItemFlags);
                break;
        }
    } else {
        ComboBoxDelegate *comboBox = new ComboBoxDelegate(this);
        QStandardItem *item = new QStandardItem(QString(""));
        ui->tableView->setItemDelegateForColumn(k, comboBox);
        model->setItem(0, k, item);
        model->item(0, k)->setFlags(Qt::NoItemFlags);
    }
}

void ThirdMenuWidget::resizeEvent(QResizeEvent *event)
{
    width = event->size().width();
    height = event->size().height();
    set_third_menu_name(currFirstNum, currSecondNum);
}

QStringList ThirdMenuWidget::get_third_menu_list()
{
    QVariantList variantList;
    QVariantMap firstMap = widget->firstMenuMap[firstMenuString].toMap();
    secondMenuMap = firstMap[secondMenuString].toMap();
    if(!secondMenuMap.isEmpty() && secondMenuMap.contains("Queue_Third_Menu")) {
        QVariantMap variantMap = secondMenuMap["Queue_Third_Menu"].toMap();
        if(variantMap.isEmpty()) {
            variantList = secondMenuMap.values("Queue_Third_Menu");
        } else {
            QString string = variantMap.value("first third_menu").toString();
            QVariantMap firstThirdMenuMap = secondMenuMap[string].toMap();
            QStringList otherThirdMenuList = get_comboBox_option_list(firstThirdMenuMap).at(0);
            if(relatedMenuString == NULL || !otherThirdMenuList.contains(relatedMenuString)) {
                variantList = variantMap.values(otherThirdMenuList.at(0));
            } else {
                variantList = variantMap.values(relatedMenuString);
            }
        }
    }

    QStringList stringList = variantList.at(0).toStringList();
    return stringList;
}

QStringList ThirdMenuWidget::get_translate_third_menu_list()
{
    QStringList tmpList = get_third_menu_list();
    QStringList stringList;
    QVariantMap firstTranslateMap = widget->translateChineseMap[firstMenuString].toMap();
    QVariantMap secondMap = firstTranslateMap[secondMenuString].toMap();
    for(int index = 0; index < tmpList.count(); index ++) {
        QString thirdMenuString = tmpList.at(index);
        if(secondMap.value(thirdMenuString).toMap().isEmpty()) {
            stringList.append(secondMap.value(thirdMenuString).toString());
        } else {
            QVariantMap comboBoxHeaderMap = secondMap.value(thirdMenuString).toMap();
            stringList.append(comboBoxHeaderMap.value(thirdMenuString).toString());
        }
    }
    return stringList;
}

void ThirdMenuWidget::onHeaderClicked(int index)
{
    QString thirdMenuString;
    QStringList thirdMenuList = get_third_menu_list();
    if(thirdMenuList.count() > index) {
       thirdMenuString  = thirdMenuList.at(index);
    } else {
        return;
    }

    QVariantMap thirdMenuMap = secondMenuMap[thirdMenuString].toMap();
    QString currentHeaderText =  model->horizontalHeaderItem(index)->text();

    switch(thirdMenuMap["style"].toString().toInt()) {
    case 1: {
        //点击表头更改spinbox的步进及表头文字
        DoubleSpinBoxDelegate *doubleSpinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
        QString headerText;

        if(currentHeaderText.contains("Δ")) {
            headerText = currentHeaderText.left(currentHeaderText.indexOf("Δ"));
        } else {
            headerText = currentHeaderText;
        }

        QString currentStep = doubleSpinBox->get_number_step();
        int stepIndex = 0;
        QStringList stringList = doubleSpinBox->stepList;
        for(int i = 0; i < stringList.count(); i ++) {
            if(currentStep == stringList.at(i)) {
                stepIndex = i;
                break;
            }
        }

        QModelIndex modelIndex = model->item(0, index)->index();
        if(opendSpinBoxIndex >= 0) {
            change_persistent_editor(modelIndex);
        }

        if(keyboardShowFlag) {
            model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex)));
        } else if(!doubleSpinBox->editFlag) {
            ui->tableView->edit(modelIndex);
            model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex)));
        } else {
            if(stepIndex == (stringList.count() - 1)) {
                doubleSpinBox->set_number_step(stringList.at(0));
                model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(0)));
            } else {
                doubleSpinBox->set_number_step(stringList.at(stepIndex + 1));
                model->setHeaderData(index, Qt::Horizontal, QString(headerText + "Δ" + stringList.at(stepIndex + 1)));
            }
        }
        if(opendSpinBoxIndex != index) {
            opendSpinBoxIndex = index;
            connect(this, SIGNAL(send_string_to_delegate(QString)), ui->tableView->itemDelegateForColumn(opendSpinBoxIndex), SLOT(input_number_to_lineedit(QString)));
            if(keyboardShowFlag) {
//                doubleSpinBox->closeEditor(doubleSpinBox->spinBoxList.at(doubleSpinBox->spinBoxList.count() -1));
                ui->tableView->openPersistentEditor(modelIndex);
            }
        }
        break;
    }
    case 2: {
        ComboBoxDelegate *comboBox = static_cast<ComboBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));        
        QModelIndex modelIndex = model->item(0, index)->index();
        ui->tableView->edit(modelIndex);
        QPoint point = QPoint();
        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonDblClick, point, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(comboBox->comboBoxList.at(comboBox->comboBoxList.count() - 1), event);

        break;
    }
    case 3: {
        PushButtonDelegate *pushButton = static_cast<PushButtonDelegate*>(ui->tableView->itemDelegateForColumn(index));
        QModelIndex modelIndex = model->item(0, index)->index();
        pushButton->change_button_text(modelIndex);
        model->setData(modelIndex, pushButton->buttonMap.value(modelIndex)->text, Qt::EditRole);
        break;
    }
    case 4: {
        //点击表头弹出探头选择对话框
        ProbeDialog *probeDialog = new ProbeDialog(this);
        probeDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        probeDialog->show();

        probeIndex = index;
        connect(probeDialog, SIGNAL(probeChanged(QString)), this, SLOT(select_probe(QString)));
        break;
    }
    case 5: {
        //点击表头弹出楔块选择对话框
        WedgeDialog *wedgeDialog = new WedgeDialog(this);
        wedgeDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        wedgeDialog->show();

        wedgeIndex = index;
        connect(wedgeDialog, SIGNAL(wedgeChanged(QString)), this, SLOT(select_wedge(QString)));
        break;
    }
    case 6: {
        //点击表头弹出软键盘
        InputPanelContext *inputPanel = new InputPanelContext(this);
        inputPanel->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        inputPanel->show();

        inputIndex = index;
        QString text = model->item(0, index)->text();
        inputPanel->set_item_current_text(text);
        connect(inputPanel, SIGNAL(textEditFinished(QString)), this, SLOT(set_edited_text(QString)));
        break;
    }
    case 7: {
        //点击表头弹出测量值选择对话框
        MeasurementDialog *measurementDialog = new MeasurementDialog(this);
        measurementDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        measurementDialog->show();

        measurementIndex = index;
        connect(measurementDialog, SIGNAL(labelTextChanged(QString)), this, SLOT(change_measurement_label(QString)));
        break;
    }
    case 11: {
        //点击表头弹出文件管理对话框
        FileManagerDialog *fileManagerDialog = new FileManagerDialog(this);
        fileManagerDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        fileManagerDialog->show();

        break;
    }
    case 14: {
        connect(this, SIGNAL(send_dialog_title_content(QMap<QString, QString>)), networkDialog, SLOT(set_dialog_title(QMap<QString, QString>)));
        connect(this, SIGNAL(send_spinbox_value(QList<int>)), networkDialog, SLOT(set_spinbox_value(QList<int>)));

        QVariantMap mapOne = widget->translateChineseMap["Preference"].toMap();
        QVariantMap mapTwo = mapOne["Network"].toMap();
        QList<int> valueList = get_dialog_value_list(index, ".");
        QMap<QString, QString> map;

        if(currentHeaderText.contains("IP Address")) {
            map["IP Address"] = "IP Address";
        } else if(currentHeaderText.contains(mapTwo.value("IP Address").toString())){
            map["IP Address"] = mapTwo.value("IP Address").toString();
        } else if(currentHeaderText.contains("Subnet Mask")) {
            map["Subnet Mask"] = "Subnet Mask";
        } else if(currentHeaderText.contains(mapTwo.value("Subnet Mask").toString())) {
            map["Subnet Mask"] = mapTwo.value("Subnet Mask").toString();            
        }
        emit send_dialog_title_content(map);
        emit send_spinbox_value(valueList);

        networkDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        networkDialog->show();

        networkIndex = index;
        connect(networkDialog, SIGNAL(currentIPChanged(QString)), this, SLOT(set_ip(QString)));
        break;
    }
    case 15: {
        Ui::Dialog::SysInfoDialog *infoDialog = new Ui::Dialog::SysInfoDialog(this);
        infoDialog->exec();
        break;
    }
    case 16: {
        Ui::Dialog::AboutDialog *aboutDialog = new Ui::Dialog::AboutDialog(this);
        aboutDialog->exec();
        break;
    }
    case 18: {
        connect(this, SIGNAL(send_dialog_title_content(QMap<QString, QString>)), dateTimeSetDialog, SLOT(set_dialog_title(QMap<QString, QString>)));
        connect(this, SIGNAL(send_spinbox_value(QList<int>)), dateTimeSetDialog, SLOT(set_spinbox_value(QList<int>)));

        QMap<QString, QString> map;
        QList<int> valueList;
        QVariantMap mapOne = widget->translateChineseMap["Preference"].toMap();
        QVariantMap mapTwo = mapOne["System"].toMap();        

        if(currentHeaderText.contains("Clock Set")) {
            valueList = get_dialog_value_list(index, ":");
            map["Clock Set"] = "Clock Set";
        } else if(currentHeaderText.contains(mapTwo.value("Clock Set").toString())){
            valueList = get_dialog_value_list(index, ":");
            map["Clock Set"] = mapTwo.value("Clock Set").toString();
        } else if(currentHeaderText.contains("Date Set")) {
            valueList = get_dialog_value_list(index, "-");
            map["Date Set"] = "Date Set";
        } else if(currentHeaderText.contains(mapTwo.value("Date Set").toString())) {
            valueList = get_dialog_value_list(index, "-");
            map["Date Set"] = mapTwo.value("Date Set").toString();            
        }

        emit send_dialog_title_content(map);
        emit send_spinbox_value(valueList);

        dateTimeSetDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        dateTimeSetDialog->show();

        dateTimeSetIndex = index;
        connect(dateTimeSetDialog, SIGNAL(currentDateTimeChanged(QString)), this, SLOT(set_date(QString)));
        break;
    }
    case 19: {
        ResetConfigDialog *resetConfigDialog = new ResetConfigDialog(this);
        resetConfigDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
        resetConfigDialog->show();
        break;
    }
    default: {
        break;
        }
    }


    if(thirdMenuMap["style"].toString().toInt() != 1 && opendSpinBoxIndex >= 0) {
        disconnect_input_number();
        opendSpinBoxIndex = -1;
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
    QStringList thirdMenuList = get_third_menu_list();
    if(thirdMenuList.count() > index.column()) {
       thirdMenuString  =thirdMenuList.at(index.column());
    } else {
        return;
    }

    QVariantMap thirdMenuMap = secondMenuMap[thirdMenuString].toMap();

    if(thirdMenuMap["style"].toString().toInt() == 1) {
        int column = index.column();
        if(!keyboardShowFlag) {
            ui->tableView->edit(index);
        }

        if(opendSpinBoxIndex >= 0) {
            change_persistent_editor(index);
        }
        if(opendSpinBoxIndex != column) {
            opendSpinBoxIndex = column;
            connect(this, SIGNAL(send_string_to_delegate(QString)), ui->tableView->itemDelegateForColumn(opendSpinBoxIndex), SLOT(input_number_to_lineedit(QString)));
            if(keyboardShowFlag) {
                ui->tableView->openPersistentEditor(index);
            }
        }

    } else if(thirdMenuMap["style"].toString().toInt() == 2) {
        ComboBoxDelegate *comboBox = static_cast<ComboBoxDelegate*>(ui->tableView->itemDelegateForColumn(index.column()));
        ui->tableView->edit(index);
        QPoint point = QPoint();
        QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonPress, point, Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
        QApplication::sendEvent(comboBox->comboBoxList.at(comboBox->comboBoxList.count() - 1), event);
    }

    if(thirdMenuMap["style"].toString().toInt() != 1 && opendSpinBoxIndex >= 0) {
        disconnect_input_number();
        opendSpinBoxIndex = -1;
    }
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

QStringList ThirdMenuWidget::get_spinBox_step_list(QVariantMap variantMap)
{
    QVariantList tmpList = variantMap["steps"].toList();
    QStringList stepList;
    if(tmpList.size() != 0) {
        for(int index = 0; index < tmpList.size(); index ++) {
            stepList.append(tmpList.at(index).toStringList());
        }
    } else {
        stepList.append("");
    }
    return stepList;
}

QList<QStringList> ThirdMenuWidget::get_comboBox_option_list(QVariantMap variantMap)
{
    QStringList optionList,abbreviationList;
    QList<QStringList> list;
    QVariantList tmpList = variantMap["options"].toList();

    for(int index = 0; index < tmpList.count(); index ++) {
        optionList.append(tmpList.at(index).toStringList());
    }

    abbreviationList = get_abbreviate_comboBox_option_list(optionList);
    list.append(optionList);
    list.append(abbreviationList);
    return list;
}

QVariantMap ThirdMenuWidget::get_translate_option_map(QString thirdMenuString)
{
    QVariantMap firstTranslateMap = widget->translateChineseMap[firstMenuString].toMap();
    QVariantMap secondMap = firstTranslateMap[secondMenuString].toMap();
    QVariantMap comboBoxHeaderMap = secondMap[thirdMenuString].toMap();
    return comboBoxHeaderMap;
}

QList<QStringList> ThirdMenuWidget::get_translate_comboBox_option_list(QVariantMap variantMapEng, QVariantMap variantMapTran)
{
    QStringList optionList,abbreviationList;
    QList<QStringList> list;
    QVariantMap optionMap = variantMapTran["options"].toMap();
    QStringList tmpList = get_comboBox_option_list(variantMapEng).at(0);

    for(int index = 0; index < tmpList.count(); index ++) {
        optionList.append(optionMap.value(tmpList.at(index)).toString());
    }

    abbreviationList = get_abbreviate_comboBox_option_list(optionList);
    list.append(optionList);
    list.append(abbreviationList);
    return list;
}

QStringList ThirdMenuWidget::get_abbreviate_comboBox_option_list(QStringList stringList)
{
    QStringList abbreviationList;
    int length = 0;
    QString maxString = "";

    for(int index = 0; index < stringList.count(); index ++) {
        QString string = stringList.at(index);
        int tmpLength = string.length();
        if(tmpLength > length) {
            length = tmpLength;
            maxString = string;
        }
    }

    if(ui->tableView->horizontalHeader()->fontMetrics().width(maxString) >= width / 6) {
        for(int index = 0; index < stringList.count(); index ++) {
            QString string = stringList.at(index);
            abbreviationList.append(string.left(string.indexOf(" ")));
        }
    } else {
        abbreviationList = stringList;
    }

    return abbreviationList;
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
            newString = leftText + "\n" + rightText;
        }
    } else {
        newString = string;
    }
    return newString;
}

void ThirdMenuWidget::change_related_third_menu_data(QString str)
{
    QString string;
    QVariantMap variantMap = secondMenuMap["Queue_Third_Menu"].toMap();

    if(!variantMap.isEmpty() && variantMap.contains("first third_menu")) {
        if(languageOption == 1) {
            if(variantMap.contains(str)) {
                string = str;
            }
        } else if(languageOption == 2) {
             QVariantMap tranMap = get_translate_option_map(variantMap.value("first third_menu").toString());
             QVariantMap optionMap = tranMap["options"].toMap();
             string = optionMap.key(str);
        }
        relatedMenuString = string;
        QVariantList variantList = variantMap.values(string);
        QStringList thirdStringList = variantList.at(0).toStringList();

        set_model_item(1, thirdStringList);
    }
}

void ThirdMenuWidget::set_model_item(int startIndex, QStringList thirdMenuList)
{
    for(int k = startIndex; k < THIRD_MENU_NUMBER; k ++) {
        if(thirdMenuList.count() >= k + 1) {
            QString thirdMenuString = thirdMenuList.at(k);
            QVariantMap thirdMenuMap = secondMenuMap[thirdMenuString].toMap();
            QString newThirdMenuString;

            if(languageOption == 1) {
                newThirdMenuString = set_long_contents_header(k, thirdMenuString);

            } else if(languageOption == 2) {
                QString thirdMenuStringTran = get_translate_third_menu_list().at(k);
                newThirdMenuString = set_long_contents_header(k, thirdMenuStringTran);
            }

            if(thirdMenuMap.contains("unit")) {
                model->setHeaderData(k, Qt::Horizontal, QString(newThirdMenuString + "\n(" + thirdMenuMap["unit"].toString() + ")"));
            } else {
                model->setHeaderData(k, Qt::Horizontal, newThirdMenuString);
            }

            choose_widget_style(k, thirdMenuMap, thirdMenuString);

            model->horizontalHeaderItem(k)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
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

void ThirdMenuWidget::set_currentDateToMenu()
{
    if(dateTimeSetDialog->str_date == NULL) {
        model->item(0, 1)->setText(QDate::currentDate().toString("yyyy-MM-dd"));
    } else {
        model->item(0, 1)->setText(dateTimeSetDialog->str_date);
    }
}

void ThirdMenuWidget::set_currentTimeToMenu()
{
    if(dateTimeSetDialog->str_time == NULL) {
        model->item(0, 0)->setText(QTime::currentTime().toString("hh:mm:ss"));
    } else {
        model->item(0, 0)->setText(dateTimeSetDialog->str_time);
    }
}

void ThirdMenuWidget::set_currentIPToMenu()
{
    model->item(0, 0)->setText("192.168.1.1");
}

void ThirdMenuWidget::set_currentSubNetToMenu()
{
    model->item(0, 1)->setText("255.255.255.0");
}

void ThirdMenuWidget::set_currentOpacity()
{
    QString opacityValue = QString::number(opacity, 'f', 0);
    model->item(0, 2)->setText(opacityValue);
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

void ThirdMenuWidget::select_probe(QString string)
{
    if(!string.isEmpty()){
        QString probeModel = string.left(string.length() - 4);
        for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
            if(i == probeIndex) {
                model->item(0, i)->setText(probeModel);
                break;
            }
        }
    }
}

void ThirdMenuWidget::select_wedge(QString string)
{
    if(!string.isEmpty()){
        QString wedgeModel = string.left(string.length() - 4);
        for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
            if(i == wedgeIndex) {
                model->item(0, i)->setText(wedgeModel);
                break;
            }
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

void ThirdMenuWidget::setBrightness(double value)
{
    int brightnessValue = (int)value;
    m_mcu->set_brightness((char)brightnessValue);
}

void ThirdMenuWidget::setOpacity(double value)
{
    emit opacityChanged(value);

    QString alph = QString::number((double)(value/100), 'f', 2);
    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section"
        "{font: 13pt 'Times New Roman';"
        "background-color: rgba(0, 130, 195, " + alph + ");"
        "color: rgba(255, 255, 255, 255);"
        "border: 0px solid black;"
        "border-left:1px solid qlineargradient(spread:reflect, x1:0.49435, y1:0.068, x2:0.50565, y2:0.75, "
        "stop:0.158192 rgba(0, 130, 195," + alph + "), stop:0.559322 rgba(255, 255, 255, " + alph + "));"
        "border-right:1px solid qlineargradient(spread:reflect, x1:0.5, y1:0.028, x2:0.5, y2:1,"
        "stop:0.158192 rgba(0, 130, 195," + alph + "), stop:0.559322 rgba(0, 0, 0, " + alph + "));}");

    ui->tableView->setStyleSheet("QTableView::item"
        "{font: 12pt 'Times New Roman';"
        "color: yellow;"
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.4 rgba(0, 0, 0, " + alph + "), "
        "stop:1 rgba(0, 120, 195, "+ alph + "));"
        "border-left:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(255, 255, 255, " + alph + "),"
        " stop:1 rgba(0, 120, 195, "+ alph + "));"
        "border-right:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(0, 0, 0, " + alph + "),"
        "stop:1 rgba(0, 120, 195, "+ alph + "));}");

    opacity = value;
}

void ThirdMenuWidget::set_autoDetect_probeModel(bool flag)
{
    if(!flag){
        m_mcu->notify_started();
        m_mcu->query_probe();
        connect(m_mcu, SIGNAL(probe_event(const Probe&)), this, SLOT(do_probe_event(const Probe&)));
    }else{
    }
}

void ThirdMenuWidget::set_date(QString str_date)
{
    model->item(0, dateTimeSetIndex)->setText(str_date);
}

void ThirdMenuWidget::set_time(QString str_time)
{
    model->item(0, dateTimeSetIndex)->setText(str_time);
}

void ThirdMenuWidget::set_ip(QString str_ip)
{
    model->item(0, networkIndex)->setText(str_ip);
}

void ThirdMenuWidget::set_subNet(QString str_subNet)
{
    model->item(0, networkIndex)->setText(str_subNet);
}

void ThirdMenuWidget::do_probe_event(const Probe &probe)
{
    model->item(0, 2)->setText(probe.model());
}

QList<int> ThirdMenuWidget::get_dialog_value_list(int index, QString str)
{
    QList<int> valueList;
    QString string = model->item(0, index)->text();
    QString tmpString = string;
    int tmpIndex = 0;
    for(int i = 0; i < string.length(); i ++) {
        if(QString(string.at(i)) == str) {
            valueList.append(tmpString.left(i - tmpIndex).toInt());
            tmpString = tmpString.right(string.count() - i - 1);
            tmpIndex = i + 1;
        }
        if(i == string.length() - 1) {
            valueList.append(tmpString.toInt());
        }
    }
    return valueList;
}

void ThirdMenuWidget::open_spinbox_persistent_editor(int index)
{    
    keyboardShowFlag = true;
    if(opendSpinBoxIndex >= 0) {
        DoubleSpinBoxDelegate *spinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
        if(!spinBox->editFlag) {
            const QModelIndex modelIndex = model->item(0, index)->index();
            ui->tableView->openPersistentEditor(modelIndex);
        }
    }
}

void ThirdMenuWidget::close_spinbox_persistent_editor(int index)
{
    DoubleSpinBoxDelegate *spinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(index));
    keyboardShowFlag = false;
    if(spinBox->editFlag) {
        QModelIndex modelIndex = model->item(0, index)->index();
        ui->tableView->closePersistentEditor(modelIndex);
        set_header_text_close(spinBox->spinBoxList.at(spinBox->spinBoxList.count() -1));
        spinBox->editFlag = false;
        spinBox->inputCount = 0;
        disconnect(this, SIGNAL(send_string_to_delegate(QString)), ui->tableView->itemDelegateForColumn(opendSpinBoxIndex), SLOT(input_number_to_lineedit(QString)));
    }
}

void ThirdMenuWidget::input_spinbox_number(QString string)
{
    if(opendSpinBoxIndex >= 0) {
        DoubleSpinBoxDelegate *spinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(opendSpinBoxIndex));
        if(spinBox->editFlag) {
//            QModelIndex modelIndex = model->item(0, opendSpinBoxIndex)->index();
//            ui->tableView->edit(modelIndex);
//            spinBox->spinBoxList.at(spinBox->spinBoxList.count() -1)->setFocusPolicy(Qt::StrongFocus);
//            spinBox->spinBoxList.at(spinBox->spinBoxList.count() -1)->setFocus();
//            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_1, Qt::NoModifier);
//            QCoreApplication::sendEvent(spinBox->spinBoxList.at(spinBox->spinBoxList.count() -1), event);

            emit send_string_to_delegate(string);
            spinBox->inputCount += 1;
        }
    }
}

void ThirdMenuWidget::change_persistent_editor(QModelIndex modelIndex)
{
    if(keyboardShowFlag) {
        QModelIndex modelIndexLast = model->item(0, opendSpinBoxIndex)->index();
        DoubleSpinBoxDelegate *spinBox = static_cast<DoubleSpinBoxDelegate*>(ui->tableView->itemDelegateForColumn(opendSpinBoxIndex));

        ui->tableView->closePersistentEditor(modelIndexLast);
        set_header_text_close(spinBox->spinBoxList.at(spinBox->spinBoxList.count() -1));
        spinBox->spinBoxList.at(spinBox->spinBoxList.count() -1)->clearFocus();
        spinBox->editFlag = false;
        spinBox->inputCount = 0;
//        ui->tableView->edit(modelIndex);
//        ui->tableView->openPersistentEditor(modelIndex);
//        spinBox->closeEditor(static_cast<QWidget*>(spinBox->spinBoxList.at(spinBox->spinBoxList.count() -1)));
    }
    disconnect_input_number();
}

void ThirdMenuWidget::disconnect_input_number()
{
    disconnect(this, SIGNAL(send_string_to_delegate(QString)), ui->tableView->itemDelegateForColumn(opendSpinBoxIndex), SLOT(input_number_to_lineedit(QString)));
}
