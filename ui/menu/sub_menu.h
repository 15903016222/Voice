/**
 * @file sub_menu.h
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __SUB_MENU_H__
#define __SUB_MENU_H__

#include "main_menu.h"
#include "mcu.h"

#include <QTreeWidgetItem>
#include <QMap>

#include "base_menu.h"

namespace Ui {
class BaseMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();

public slots:
    void set_menu(MainMenu::Type type);

private slots:
    void show_ip_address_dialog();
    void show_subnet_mask_dialog();
    void show_info_dialog();
    void show_about_dialog();
    void show_date_dialog();
    void show_time_dialog();
    void show_resetconfig_dialog();
    void set_brightness(double value);
    void auto_detect_probe(QString string);
    void do_probe_event(const Probe &probe);

private:
    Ui::BaseMenu *ui;

    void init_map();

    QList<int> get_dialog_value_list(QString string, QString symbol);

    Mcu *pMcu;


    QMap<MainMenu::Type, BaseMenu*> m_map;

    double m_brightness;  

    MainMenu::Type m_preType;
};

#endif // SUB_MENU_H
