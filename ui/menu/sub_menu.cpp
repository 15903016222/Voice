#include "sub_menu.h"
#include "ui_sub_menu.h"

#include <QDebug>

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);
    menuConfig = new MenuConfig;

    set_third_menu("UT Settings", "General");
}

SubMenu::~SubMenu()
{
    delete ui;
}

void SubMenu::set_third_menu(QString str1, QString str2)
{
    QStringList thirdMenuList = menuConfig->get_third_menu_list(menuConfig->menuMap, str1, str2);
    qDebug() << thirdMenuList;
    qDebug() << str1 << str2;

//    if(menuConfig->get_style(thirdMenuMap1) == 1) {
//        ui->subMenu_1->set_type(MenuItem::Spin);
//        ui->subMenu_1->set_title(thirdMenuList.at(0));
//        ui->subMenu_1->set_unit(menuConfig->get_spinBox_unit(thirdMenuMap1));
//        ui->subMenu_1->set_steps(menuConfig->get_spinBox_step_list(thirdMenuMap1));
//        ui->subMenu_1->set_decimals(menuConfig->get_spinBox_decimal(thirdMenuMap1));
//        ui->subMenu_1->set_range(menuConfig->get_spinBox_range_list(thirdMenuMap1).at(0), menuConfig->get_spinBox_range_list(thirdMenuMap1).at(1));
//    }


    for(int i = 0; i < 6; i ++) {
        MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
        widget->clean();
        if(i < thirdMenuList.count()) {
            QString str = thirdMenuList.at(i);
            qDebug() << str;
            QVariantMap thirdMenuMap = menuConfig->get_third_menu_map(menuConfig->menuMap, str1, str2, str);
            set_third_menu_content(widget, thirdMenuMap);
            widget->set_title(str);
        } else {
            qDebug() << "none";
            widget->set_type(MenuItem::Combo);
        }
    }

}

void SubMenu::set_third_menu_content(MenuItem *widget, QVariantMap map)
{
    if(menuConfig->get_style(map) == 1) {
        widget->set_type(MenuItem::Spin);
        widget->set_unit(menuConfig->get_spinBox_unit(map));
        widget->set_steps(menuConfig->get_spinBox_step_list(map));
        widget->set_decimals(menuConfig->get_spinBox_decimal(map));
        QList<double> rangeList = menuConfig->get_spinBox_range_list(map);
        widget->set_range(rangeList.at(0), rangeList.at(1));
    } else if(menuConfig->get_style(map) == 2) {
        widget->set_type(MenuItem::Combo);
        widget->set_combo_items(menuConfig->get_comboBox_option_list(map));
    } else {
        widget->set_type(MenuItem::Combo);
    }
}
