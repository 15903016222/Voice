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

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);

    menuConfig = new MenuConfig;
    pNetworkDialog = new NetworkDialog(this);
    pDateTimeSetDialog = new DateTimeSetDialog(this);

    current.insert("UT Settings", "General");

    set_third_menu_and_connect(current.keys().at(0), current.values().at(0));

}

SubMenu::~SubMenu()
{
    delete ui;
}

void SubMenu::set_third_menu(QString str1, QString str2)
{
    QString str1_c = current.keys().at(0);
    QString str2_c = current.values().at(0);

    if(str1 != str1_c || str2 != str2_c) {
        disconnect_previous_signals(str1_c, str2_c);
        get_second_menu_string(str1, str2);
        set_third_menu_and_connect(str1, str2);
    }

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
            connect(widget, SIGNAL(clicked()), this, SLOT(show_probe_dialog()));
        }
    }
}

void SubMenu::show_probe_dialog()
{
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
