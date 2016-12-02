#ifndef SUB_MENU_H
#define SUB_MENU_H

#include "menu_item.h"
#include "menu_config.h"
#include "networkdialog.h"
#include "datetimesetdialog.h"

#include <QWidget>
#include <QTreeWidgetItem>
#include <QMap>

namespace Ui {
class SubMenu;
}

class SubMenu : public QWidget
{
    Q_OBJECT

public:
    explicit SubMenu(QWidget *parent = 0);
    ~SubMenu();
    QMap<QString, QString> previous;
    QMap<QString, QString> current;

private:
    Ui::SubMenu *ui;

    void set_third_menu_and_connect(QString str1, QString str2);
    void disconnect_previous_signals(QString str1, QString str2);
    void get_second_menu_string(QString str1, QString str2);
    void connect_current_signal(MenuItem *widget, QString str2, QString str3, MenuItem::Type type);

    MenuConfig *menuConfig;
    NetworkDialog *pNetworkDialog;
    DateTimeSetDialog *pDateTimeSetDialog;

private slots:
    void set_third_menu(QString str1, QString str2);
    void show_probe_dialog();
    void show_wedge_dialog();
    void show_input_dialog();
    void show_filemanager_dialog();
    void show_network_dialog();
    void show_info_dialog();
    void show_about_dialog();
    void show_datetime_dialog();
    void show_resetconfig_dialog();

};

#endif // SUB_MENU_H
