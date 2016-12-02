#include "sub_menu.h"
#include "ui_sub_menu.h"

#include "probedialog.h"
#include "wedgedialog.h"
#include "inputpanelcontext.h"
#include "filemanagerdialog.h"
#include "sysinfo_dialog.h"
#include "about_dialog.h"
#include "resetconfigdialog.h"

#include <QKeyEvent>
#include <QDebug>

#define DIALOG_NUMBER 2
static QString DIALOG_STRING[DIALOG_NUMBER] = {
    "show_probe_dialog()",
    "show_wedge_dialog()"
};

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);

    stepList1.append(0.1);
    stepList1.append(0.5);
    stepList1.append(1.0);
    stepList1.append(2.0);
    stepList1.append(6.0);

    stepList2.append(0.10);
    stepList2.append(1.00);
    stepList2.append(10.0);
    stepList2.append(100.0);

    stepList3.append(1.00);
    stepList3.append(10.0);
    stepList3.append(100.0);
    stepList3.append(1000.0);

    stepList4.append(0.01);
    stepList4.append(0.10);
    stepList4.append(1.00);

    stepList5.append(1);
    stepList5.append(10);
    stepList5.append(100);



    menuConfig = new MenuConfig;
    pNetworkDialog = new NetworkDialog(this);
    pDateTimeSetDialog = new DateTimeSetDialog(this);

    current.insert("UT Settings", "General");

//    set_third_menu_and_connect(current.keys().at(0), current.values().at(0));
    connect_current_signal(ui->subMenu_1, "UT Settings", "General", MenuItem::Spin);
    set_general_menu();

}

SubMenu::~SubMenu()
{
    delete ui;
}

void SubMenu::set_third_menu(QString str1, QString str2)
{
//    QString str1_c = current.keys().at(0);
//    QString str2_c = current.values().at(0);

//    if(str1 != str1_c || str2 != str2_c) {
//        disconnect_previous_signals(str1_c, str2_c);
//        get_second_menu_string(str1, str2);
//        set_third_menu_and_connect(str1, str2);
//    }

}

void SubMenu::set_spinbox_menu(MenuItem *widget, const QString &title, const QString &unit, QList<double> &steps, double min, double max, int decimals)
{
    widget->set_type(MenuItem::Spin);
    widget->set_title(title);
    widget->set_unit(unit);
    widget->set_steps(steps);
    widget->set_range(min, max);
    widget->set_decimals(decimals);
}

void SubMenu::set_combobox_menu(MenuItem *widget, const QString &title, QStringList &texts)
{
    widget->set_type(MenuItem::Combo);
    widget->set_title(title);
    widget->set_combo_items(texts);
}

void SubMenu::set_label_menu(MenuItem *widget, const QString &title)
{
    widget->set_type(MenuItem::None);
    widget->set_title(title);
}

void SubMenu::set_general_menu()
{
    /* Gain menu item */
    set_spinbox_menu(ui->subMenu_1, tr("Gain"), "dB", stepList1, 0, 100, 1);

    /* Start menu item */
    set_spinbox_menu(ui->subMenu_2, tr("Start"), "mm", stepList2, 0, 1000, 2);

    /* Range menu item */
    set_spinbox_menu(ui->subMenu_3, tr("Range"), "mm", stepList2, 0, 1000, 2);

    /* Velocity menu item */
    set_spinbox_menu(ui->subMenu_4, tr("Velocity"), "m/s", stepList3, 635, 12540, 1);

    /* Wedge delay menu item */
    set_spinbox_menu(ui->subMenu_5, tr("Wedge Delay"), "μs", stepList4, 0, 1000, 2);

    /* UT Unit menu item */
    QStringList option;
    option.append(tr("Time"));
    option.append(tr("Sound Path"));
    option.append(tr("True Path"));
    set_combobox_menu(ui->subMenu_6, tr("UT Unit"), option);

}

void SubMenu::set_pulser_menu()
{
    /* Tx/Rx Mode menu item */
    QStringList option1;
    option1.append(tr("PC"));
    option1.append(tr("PE"));
    option1.append(tr("TT"));
    option1.append(tr("TOFD"));
    set_combobox_menu(ui->subMenu_1, tr("Tx/Rx Mode"), option1);

    /* Pulser menu item */
    set_spinbox_menu(ui->subMenu_2, tr("Pulser"), "", stepList5, 1, 113, 0);

    /* Voltage menu item */
    QStringList option2;
    option2.append(tr("50V"));
    option2.append(tr("100V"));
    option2.append(tr("200V"));
    set_combobox_menu(ui->subMenu_3, tr("Voltage"), option2);

    /* PW menu item */
    QList<double> steps;
    steps.append(2.5);
    steps.append(10);
    steps.append(25);
    set_spinbox_menu(ui->subMenu_4, tr("PW"), "ns", steps, 30, 500, 1);

    /* PRF menu item */
    QStringList option3;
    option3.append(tr("Auto Max"));
    option3.append(tr("Max/2"));
    option3.append(tr("Optimum"));
    option3.append(tr("UserDef"));
    set_combobox_menu(ui->subMenu_5, tr("PRF"), option3);

    ui->subMenu_6->set_type(MenuItem::None);

}

void SubMenu::set_receiver_menu()
{
    /* Receiver menu item */
    set_label_menu(ui->subMenu_1, tr("Receiver"));

    /* Filter menu item */
    QStringList option1;
    option1.append(tr("none"));
    option1.append(tr("1M"));
    option1.append(tr("1.5M-2.5M"));
    option1.append(tr("3-5M"));
    option1.append(tr("7.5M"));
    option1.append(tr("more than 10M"));
    set_combobox_menu(ui->subMenu_2, tr("Filter"), option1);

    /* Rectifier menu item */
    QStringList option2;
    option2.append(tr("RF"));
    option2.append(tr("FW"));
    option2.append(tr("HW+"));
    option2.append(tr("HW-"));
    set_combobox_menu(ui->subMenu_3, tr("Rectifier"), option2);

    /* Video Filter menu item */
    QStringList option3;
    option3.append(tr("On"));
    option3.append(tr("Off"));
    set_combobox_menu(ui->subMenu_4, tr("Video Filter"), option3);

    /* Averaging menu item */
    QStringList option4;
    option4.append(tr("1"));
    option4.append(tr("2"));
    option4.append(tr("4"));
    option4.append(tr("8"));
    option4.append(tr("16"));
    set_combobox_menu(ui->subMenu_5, tr("Averaging"), option4);

    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_advanced_menu()
{
    /* Set 80% menu item */
    QStringList option1;
    option1.append(tr("On"));
    option1.append(tr("Off"));
    set_combobox_menu(ui->subMenu_1, tr("Set 80%"), option1);

    /* dB Ref. menu item */
    QStringList option2;
    option2.append(tr("On"));
    option2.append(tr("Off"));
    set_combobox_menu(ui->subMenu_2, tr("dB Ref."), option2);

    /* Point Qty. menu item */
    QStringList option3;
    option3.append(tr("Auto"));
    option3.append(tr("160"));
    option3.append(tr("320"));
    option3.append(tr("640"));
    option3.append(tr("UserDef"));
    set_combobox_menu(ui->subMenu_3, tr("Point Qty."), option3);

    /* Scale Factor menu item */
    set_label_menu(ui->subMenu_4, tr("Scale Factor"));

    /* Sum Gain menu item */
    set_spinbox_menu(ui->subMenu_5, tr("Sum Gain"), "dB", stepList1, 0, 100, 1);

    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_gate_menu()
{
    /* Gate menu item */
    QStringList option1;
    option1.append(tr("A"));
    option1.append(tr("B"));
    option1.append(tr("I"));
    option1.append(tr("Off"));
    set_combobox_menu(ui->subMenu_1, tr("Gate"), option1);

    /* Start menu item */
    set_spinbox_menu(ui->subMenu_2, tr("Start"), "mm", stepList2, 0, 16000, 2);

    /* Width menu item */
    QList<double> steps;
    steps.append(0.01);
    steps.append(0.10);
    steps.append(1.0);
    steps.append(10.0);
    set_spinbox_menu(ui->subMenu_3, tr("Width"), "mm", steps, 0.05, 525, 2);

    /* Threshold menu item */
    QList<double> steps2;
    steps2.append(1);
    steps2.append(10);
    set_spinbox_menu(ui->subMenu_4, tr("Threshold"), "%", steps2, 0, 100, 0);

    /* Synchro menu item */
    QStringList option2;
    option2.append(tr("Gate A"));
    option2.append(tr("Gate I"));
    option2.append(tr("Pulse"));
    set_combobox_menu(ui->subMenu_5, tr("Synchro"), option2);

    /* Measure Mode menu item */
    QStringList option3;
    option3.append(tr("Edge"));
    option3.append(tr("Peak"));
    set_combobox_menu(ui->subMenu_6, tr("Measure Mode"), option3);

}

void SubMenu::set_alarm_menu()
{
    /* Alarm menu item */
    QStringList option1;
    option1.append(tr("Alarm 1"));
    option1.append(tr("Alarm 2"));
    option1.append(tr("Alarm 3"));
    set_combobox_menu(ui->subMenu_1, tr("Alarm"), option1);

    /* Switch menu item */
    QStringList option2;
    option2.append(tr("On"));
    option2.append(tr("Off"));
    set_combobox_menu(ui->subMenu_2, tr("Switch"), option2);

    /* Group menu item */
    QStringList option3;
    option3.append(tr("Group1"));
    option3.append(tr("All"));
    option3.append(tr("None"));
    set_combobox_menu(ui->subMenu_3, tr("Group"), option3);

    /* Condition Factor menu item */
    QStringList option4;
    option4.append(tr("None"));
    option4.append(tr("Gate A"));
    option4.append(tr("Gate B"));
    option4.append(tr("Gate I"));
    option4.append(tr("Not Gate A"));
    option4.append(tr("Not Gate B"));
    option4.append(tr("Not Gate I"));
    option4.append(tr(">Max.Thickness"));
    option4.append(tr("<Min.Thickness"));
    set_combobox_menu(ui->subMenu_4, tr("Condition"), option4);

    /* Operator menu item */
    QStringList option5;
    option5.append(tr("And"));
    option5.append(tr("Or"));
    set_combobox_menu(ui->subMenu_5, tr("Operator"), option5);

    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_output_menu()
{
    /* Output menu item */
    QStringList option1;
    option1.append(tr("Alarm 1"));
    option1.append(tr("Alarm 2"));
    option1.append(tr("Alarm 3"));
    option1.append(tr("Analog 1"));
    option1.append(tr("Analog 2"));
    set_combobox_menu(ui->subMenu_1, tr("Output"), option1);

    /* Sound menu item */
    QStringList option2;
    option2.append(tr("Off No Sound"));
    option2.append(tr("300Hz Audio Output at 300Hz"));
    option2.append(tr("600Hz Audio Output at 600Hz"));
    option2.append(tr("1000Hz Audio Output at 1000Hz"));
    option2.append(tr("5000Hz Audio Output at 5000Hz"));
    set_combobox_menu(ui->subMenu_2, tr("Sound"), option2);

    /* Delay menu item */
    QList<double> steps;
    steps.append(0.10);
    steps.append(1.0);
    steps.append(10.0);
    set_spinbox_menu(ui->subMenu_3, tr("Delay"), "mm", steps, 0, 5000, 2);

    /* Hold Time menu item */
    set_spinbox_menu(ui->subMenu_4, tr("Hold Time"), "%", steps, 0, 5000, 2);

    /* Group menu item */
    set_label_menu(ui->subMenu_5, tr("Group"));

    /* Data menu item */
    QStringList option3;
    option3.append(tr("A%"));
    option3.append(tr("B%"));
    option3.append(tr("None"));
    set_combobox_menu(ui->subMenu_6, tr("Data"), option3);

}

void SubMenu::set_dac_menu()
{

}

void SubMenu::set_tcg_menu()
{

}

void SubMenu::set_selection_menu()
{
    /* Group menu item */
    QStringList option1;
    option1.append(tr("All"));
    option1.append(tr("Current"));
    set_combobox_menu(ui->subMenu_1, tr("Group"), option1);

    /* Display menu item */
    QStringList option2;
    option2.append(tr("A A-Scan"));
    option2.append(tr("B B-Scan"));
    option2.append(tr("C C-Scan"));
    option2.append(tr("S S-Scan"));
    option2.append(tr("A-B A-Scan B-Scan"));
    option2.append(tr("A-S A-Scan S-Scan"));
    option2.append(tr("A-B-C A-Scan B-Scan C-Scan"));
    option2.append(tr("A-B-S A-Scan B-Scan S-Scan"));
    option2.append(tr("A-S-[C] A-Scan S-Scan [C-Scan]"));
    option2.append(tr("S-A-A-A S-Scan A-Scan A-Scan A-Scan"));
    option2.append(tr("S-A-C-C S-Scan A-Scan C-Scan C-Scan"));
    set_combobox_menu(ui->subMenu_2, tr("Display"), option2);

    /* C-Scan Source menu item */
    QStringList option3;
    option3.append(tr("A%"));
    option3.append(tr("B%"));
    option3.append(tr("Thickness"));
    option3.append(tr("I/"));
    set_combobox_menu(ui->subMenu_3, tr("C-Scan Source"), option3);

    /* Min.Thickness menu item */
    QList<double> steps;
    steps.append(0.01);
    steps.append(0.10);
    steps.append(1.0);
    steps.append(10.0);
    set_spinbox_menu(ui->subMenu_4, tr("Min.Thickness"), "mm", steps, 0.05, 20000, 2);

    /* Max.Thickness menu item */
    set_spinbox_menu(ui->subMenu_5, tr("Max.Thickness"), "mm", steps, 0.05, 20000, 2);

    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_colorSettings_menu()
{
    /* Amplitude menu item */
    set_label_menu(ui->subMenu_1, tr("Amplitude"));

    /* Depth menu item */
    set_label_menu(ui->subMenu_2, tr("Depth"));

    /* TOFD menu item */
    set_label_menu(ui->subMenu_3, tr("TOFD"));

    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);

}

void SubMenu::set_properties_menu()
{

}

void SubMenu::set_select_menu()
{

}

void SubMenu::set_position_menu()
{

}

void SubMenu:: set_fft_menu()
{

}

void SubMenu::set_third_menu_and_connect(QString str1, QString str2)
{
    QStringList thirdMenuList = menuConfig->get_third_menu_list(menuConfig->menuMap, str1, str2);

    for(int i = 0; i < thirdMenuList.count(); i ++) {
        MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
        widget->clean();

        QString str = thirdMenuList.at(i);
        QVariantMap map = menuConfig->get_third_menu_map(menuConfig->menuMap, str1, str2, str);

        widget->set_title(str);

        if(menuConfig->get_style(map) == 1) {
            widget->set_type(MenuItem::Spin);
            widget->set_unit(menuConfig->get_spinBox_unit(map));
            widget->set_steps(menuConfig->get_spinBox_step_list(map));
            widget->set_decimals(menuConfig->get_spinBox_decimal(map));
            QList<double> rangeList = menuConfig->get_spinBox_range_list(map);
            widget->set_range(rangeList.at(0), rangeList.at(1));

            connect_current_signal(widget, str2, str, MenuItem::Spin);
        } else if(menuConfig->get_style(map) == 2) {
            widget->set_type(MenuItem::Combo);
            widget->set_combo_items(menuConfig->get_comboBox_option_list(map));

            connect_current_signal(widget, str2, str, MenuItem::Combo);
        } else {
            widget->set_type(MenuItem::None);
            connect_current_signal(widget, str2, str, MenuItem::None);
        }
    }

    for(int i = thirdMenuList.count(); i < 6; i ++) {
        MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
        widget->clean();
        widget->set_type(MenuItem::Combo);
    }
}

void SubMenu::disconnect_previous_signals(QString str1, QString str2)
{
    QStringList list = menuConfig->get_third_menu_list(menuConfig->menuMap, str1, str2);
    for(int i = 0; i < list.count(); i ++) {
//        MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
        QString str3 = list.at(i);
        QVariantMap map = menuConfig->get_third_menu_map(menuConfig->menuMap, str1, str2, str3);

        if(menuConfig->get_style(map) == 1) {
            qDebug() << "disconnect";
//            disconnect(widget, SIGNAL(spin_event(double)), , SLOT());
        } else if(menuConfig->get_style(map) == 2) {
//            disconnect(widget, SIGNAL(combo_event(int)), , SLOT());
            qDebug() << "disconnect";
        } else {
//            disconnect(widget, SIGNAL(click()), , SLOT());
        }
    }
}

void SubMenu::get_second_menu_string(QString str1, QString str2)
{
    qDebug() << "str1" << str1 << "str2" << str2;
    if(!previous.isEmpty()) {
        previous.clear();
    }
    previous.insert(current.keys().at(0), current.values().at(0));
    current.clear();
    current.insert(str1, str2);
}

void SubMenu::connect_current_signal(MenuItem *widget, QString str2, QString str3, MenuItem::Type type)
{
    if(type == MenuItem::Spin) {
//        connect(widget, SIGNAL(spin_event(double)), , SLOT());
    } else if(type == MenuItem::Combo) {
//        connect(widget, SIGNAL(combo_event(double)), , SLOT());
    } else {
//        connect(widget, SIGNAL(click()), , SLOT());
        if(str2 == "Select" && str3 == "Probe") {
            QByteArray ba = DIALOG_STRING[0].toLatin1();
            char *ch = ba.data();
            qDebug() << ch;
            connect(widget, SIGNAL(clicked()), this, ch);

        }
    }

    qDebug()<<SIGNAL(clicked());
}

void SubMenu::show_probe_dialog()
{
    qDebug() << "run";
    ProbeDialog probeDialog;
    probeDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    probeDialog.exec();

//    connect(probeDialog, SIGNAL(probeChanged(QString)), this, SLOT(select_probe(QString)));
}

void SubMenu::show_wedge_dialog()
{
    WedgeDialog wedgeDialog;
    wedgeDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    wedgeDialog.exec();

//    connect(wedgeDialog, SIGNAL(wedgeChanged(QString)), this, SLOT(select_wedge(QString)));
}

void SubMenu::show_input_dialog()
{
    InputPanelContext inputPanel;
    inputPanel.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    inputPanel.exec();

//    QString text = pModel->item(0, index)->text();
//    inputPanel->set_item_current_text(text);
//    connect(inputPanel, SIGNAL(textEditFinished(QString)), this, SLOT(set_edited_text(QString)));
}

void SubMenu::show_filemanager_dialog()
{
    FileManagerDialog fileManagerDialog;
    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    fileManagerDialog.exec();
}

void SubMenu::show_network_dialog()
{
//    QVariantMap mapOne = pFirstSecondMenuWidget->translateChineseMap["Preference"].toMap();
//    QVariantMap mapTwo = mapOne["Network"].toMap();
//    QList<int> valueList = get_dialog_value_list(index, ".");
    QMap<QString, QString> map;

//    if(currentHeaderText.contains("IP Address")) {
//        map["IP Address"] = "IP Address";
//    } else if(currentHeaderText.contains(mapTwo.value("IP Address").toString())){
//        map["IP Address"] = mapTwo.value("IP Address").toString();
//    } else if(currentHeaderText.contains("Subnet Mask")) {
//        map["Subnet Mask"] = "Subnet Mask";
//    } else if(currentHeaderText.contains(mapTwo.value("Subnet Mask").toString())) {
//        map["Subnet Mask"] = mapTwo.value("Subnet Mask").toString();
//    }

//    pNetworkDialog->set_dialog_title(map);
//    pNetworkDialog->set_spinbox_value(valueList);

    pNetworkDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    pNetworkDialog->exec();

//    m_networkIndex = index;
//    connect(pNetworkDialog, SIGNAL(currentIP_subNetChanged(QString)), this, SLOT(set_ip_subNet(QString)));
}

void SubMenu::show_info_dialog()
{
    Ui::Dialog::SysInfoDialog *infoDialog = new Ui::Dialog::SysInfoDialog(this);
    infoDialog->exec();
}

void SubMenu::show_about_dialog()
{
    Ui::Dialog::AboutDialog *aboutDialog = new Ui::Dialog::AboutDialog(this);
    aboutDialog->exec();
}

void SubMenu::show_datetime_dialog()
{
    QMap<QString, QString> map;
    QList<int> valueList;
//    QVariantMap mapOne = pFirstSecondMenuWidget->translateChineseMap["Preference"].toMap();
//    QVariantMap mapTwo = mapOne["System"].toMap();

//    if(currentHeaderText.contains("Clock Set")) {
//        valueList = get_dialog_value_list(index, ":");
//        map["Clock Set"] = "Clock Set";
//    } else if(currentHeaderText.contains(mapTwo.value("Clock Set").toString())){
//        valueList = get_dialog_value_list(index, ":");
//        map["Clock Set"] = mapTwo.value("Clock Set").toString();
//    } else if(currentHeaderText.contains("Date Set")) {
//        valueList = get_dialog_value_list(index, "-");
//        map["Date Set"] = "Date Set";
//    } else if(currentHeaderText.contains(mapTwo.value("Date Set").toString())) {
//        valueList = get_dialog_value_list(index, "-");
//        map["Date Set"] = mapTwo.value("Date Set").toString();
//    }

//    pDateTimeSetDialog->set_dialog_title(map);
//    pDateTimeSetDialog->set_spinbox_value(valueList);

    pDateTimeSetDialog->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    pDateTimeSetDialog->show();

//    m_dateTimeSetIndex = index;
//    connect(pDateTimeSetDialog, SIGNAL(currentDateTimeChanged(QString)), this, SLOT(set_time(QString)));
}

void SubMenu::show_resetconfig_dialog()
{
    ResetConfigDialog resetConfigDialog;
    resetConfigDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    resetConfigDialog.exec();
}

//void ThirdMenuWidget::set_currentTime()
//{
//    if(pDateTimeSetDialog->m_strTime == NULL) {
//        pModel->item(0, 0)->setText(QTime::currentTime().toString("hh:mm:ss"));
//    } else {
//        pModel->item(0, 0)->setText(pDateTimeSetDialog->m_strTime);
//    }

//    if(pDateTimeSetDialog->m_strDate == NULL) {
//        pModel->item(0, 1)->setText(QDate::currentDate().toString("yyyy-MM-dd"));
//    } else {
//        pModel->item(0, 1)->setText(pDateTimeSetDialog->m_strDate);
//    }
//}

//void ThirdMenuWidget::select_probe(QString string)
//{
//    if(!string.isEmpty()){
//        QString probeModel = string.left(string.length() - 4);
//        for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
//            if(i == m_probeIndex) {
//                pModel->item(0, i)->setText(probeModel);
//                break;
//            }
//        }
//    }
//}

//void ThirdMenuWidget::select_wedge(QString string)
//{
//    if(!string.isEmpty()){
//        QString wedgeModel = string.left(string.length() - 4);
//        for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
//            if(i == m_wedgeIndex) {
//                pModel->item(0, i)->setText(wedgeModel);
//                break;
//            }
//        }
//    }
//}

//void ThirdMenuWidget::set_edited_text(QString string)
//{
//    for(int i = 0; i < THIRD_MENU_NUMBER; i ++) {
//        if(i == m_inputIndex) {
//            pModel->item(0, i)->setText(string);
//            break;
//        }
//    }
//}

//void ThirdMenuWidget::setBrightness(double value)
//{
//    m_brightness = value;

//    pMcu->set_brightness((char)m_brightness);
//}

//void ThirdMenuWidget::set_autoDetect_probeModel(bool flag)
//{
//    if(!flag){
//        pMcu->notify_started();
//        pMcu->query_probe();
//        connect(pMcu, SIGNAL(probe_event(const Probe&)), this, SLOT(do_probe_event(const Probe&)));
//    }else{
//    }
//}

//void ThirdMenuWidget::set_time(QString value)
//{
//    pModel->item(0, m_dateTimeSetIndex)->setText(value);
//}

//void ThirdMenuWidget::set_ip_subNet(QString value)
//{
//    pModel->item(0, m_networkIndex)->setText(value);
//}

//void ThirdMenuWidget::do_probe_event(const Probe &probe)
//{
//    pModel->item(0, 2)->setText(probe.model());
//}

//QList<int> ThirdMenuWidget::get_dialog_value_list(int index, QString str)
//{
//    QList<int> valueList;
//    QString string = pModel->item(0, index)->text();
//    QString tmpString = string;
//    int tmpIndex = 0;
//    for(int i = 0; i < string.length(); i ++) {
//        if(QString(string.at(i)) == str) {
//            valueList.append(tmpString.left(i - tmpIndex).toInt());
//            tmpString = tmpString.right(string.count() - i - 1);
//            tmpIndex = i + 1;
//        }
//        if(i == string.length() - 1) {
//            valueList.append(tmpString.toInt());
//        }
//    }
//    return valueList;
//}
