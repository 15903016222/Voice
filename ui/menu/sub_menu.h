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

    void set_general_menu();
    void set_pulser_menu();
    void set_receiver_menu();
    void set_advanced_menu();

    void set_gate_menu();
    void set_alarm_menu();
    void set_output_menu();
    void set_dac_menu();
    void set_tcg_menu();

    void set_selection_menu();
    void set_colorSettings_menu();
    void set_properties_menu();

    void set_select_menu();
    void set_position_menu();
    void set_fft_menu();
    void set_part_menu();
    void set_advanced_2_menu();

    void set_spinbox_menu(MenuItem *widget, const QString &title, const QString &unit, QList<double> &steps, double min, double max, int decimals);
    void set_combobox_menu(MenuItem *widget, const QString &title, QStringList &texts);
    void set_label_menu(MenuItem *widget, const QString &title);

    MenuConfig *menuConfig;
    NetworkDialog *pNetworkDialog;
    DateTimeSetDialog *pDateTimeSetDialog;

    QList<double> stepList1;
    QList<double> stepList2;
    QList<double> stepList3;
    QList<double> stepList4;
    QList<double> stepList5;

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
