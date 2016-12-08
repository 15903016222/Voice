#include "sub_menu.h"
#include "ui_sub_menu.h"

#include "probedialog.h"
#include "wedgedialog.h"
#include "inputpanelcontext.h"
#include "filemanagerdialog.h"
#include "sysinfo_dialog.h"
#include "about_dialog.h"
#include "resetconfigdialog.h"
#include "networkdialog.h"
#include "datetimesetdialog.h"

#include <QKeyEvent>
#include <QDebug>

#define MATERIAL_NUMBER 24
static QString MATERIAL_STRING[MATERIAL_NUMBER] = {
    QT_TRANSLATE_NOOP("SubMenu", "Aluminum"),
    QT_TRANSLATE_NOOP("SubMenu", "Steel Common"),
    QT_TRANSLATE_NOOP("SubMenu", "Steel Stainless"),
    QT_TRANSLATE_NOOP("SubMenu", "Brass"),
    QT_TRANSLATE_NOOP("SubMenu", "Copper"),
    QT_TRANSLATE_NOOP("SubMenu", "Iron"),
    QT_TRANSLATE_NOOP("SubMenu", "Lead"),
    QT_TRANSLATE_NOOP("SubMenu", "Nylon"),
    QT_TRANSLATE_NOOP("SubMenu", "Silver"),
    QT_TRANSLATE_NOOP("SubMenu", "Gold"),
    QT_TRANSLATE_NOOP("SubMenu", "Zinc"),
    QT_TRANSLATE_NOOP("SubMenu", "Titanium"),
    QT_TRANSLATE_NOOP("SubMenu", "Tin"),
    QT_TRANSLATE_NOOP("SubMenu", "Epoxy Resin"),
    QT_TRANSLATE_NOOP("SubMenu", "Ice"),
    QT_TRANSLATE_NOOP("SubMenu", "Nickel"),
    QT_TRANSLATE_NOOP("SubMenu", "Plexiglass"),
    QT_TRANSLATE_NOOP("SubMenu", "Polystyrene"),
    QT_TRANSLATE_NOOP("SubMenu", "Orcelain"),
    QT_TRANSLATE_NOOP("SubMenu", "PVC"),
    QT_TRANSLATE_NOOP("SubMenu", "Quartz Glass"),
    QT_TRANSLATE_NOOP("SubMenu", "Rubber Vulcanized"),
    QT_TRANSLATE_NOOP("SubMenu", "Teflon"),
    QT_TRANSLATE_NOOP("SubMenu", "Water")
};

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);

    switchList.append(tr("On"));
    switchList.append(tr("Off"));

    init_option_stringlist();
    init_step_list();
    init_map();  

    m_typeMap.insert("current", UTSettings_General);

    set_general_menu(true);

//    m_brightness = 50.0;
//    set_brightness(m_brightness);
}

void SubMenu::init_map()
{
    m_map.insert(UTSettings_General, &SubMenu::set_general_menu);
    m_map.insert(UTSettings_Pulser, &SubMenu::set_pulser_menu);
    m_map.insert(UTSettings_Receiver, &SubMenu::set_receiver_menu);
    m_map.insert(UTSettings_Advanced, &SubMenu::set_advanced_menu);
    m_map.insert(GateCurves_Gate, &SubMenu::set_gate_menu);
    m_map.insert(GateCurves_Alarm, &SubMenu::set_alarm_menu);
    m_map.insert(GateCurves_Output, &SubMenu::set_output_menu);
    m_map.insert(GateCurves_DAC, &SubMenu::set_dac_menu);
    m_map.insert(GateCurves_TCG, &SubMenu::set_tcg_menu);
    m_map.insert(Display_Selection, &SubMenu::set_selection_menu);
    m_map.insert(Display_ColorSettings, &SubMenu::set_colorSettings_menu);
    m_map.insert(Displsy_Properties, &SubMenu::set_properties_menu);
    m_map.insert(ProbePart_Select, &SubMenu::set_select_menu);
    m_map.insert(ProbePart_Position, &SubMenu::set_position_menu);
    m_map.insert(ProbePart_FFT, &SubMenu::set_fft_menu);
    m_map.insert(ProbePart_Part, &SubMenu::set_part_menu);
    m_map.insert(ProbePart_Advanced, &SubMenu::set_advanced_2_menu);
    m_map.insert(FocalLaw_LawConfig, &SubMenu::set_lawConfig_menu);
    m_map.insert(FocalLaw_Angle, &SubMenu::set_angle_menu);
    m_map.insert(FocalLaw_Apeture, &SubMenu::set_apeture_menu);
    m_map.insert(FacalLaw_FocalPoint, &SubMenu::set_focalPoint_menu);
    m_map.insert(Scan_Inspection, &SubMenu::set_inspection_menu);
    m_map.insert(Scan_Encoder, &SubMenu::set_encoder_menu);
    m_map.insert(Scan_Area, &SubMenu::set_area_menu);
    m_map.insert(Scan_Start, &SubMenu::set_start_menu);
    m_map.insert(Measurement_Cursors, &SubMenu::set_cursors_menu);
    m_map.insert(Measurement_TOFD, &SubMenu::set_tofd_menu);
    m_map.insert(Measurement_FlawRecord, &SubMenu::set_flawRecord_menu);
    m_map.insert(FileReport_File, &SubMenu::set_file_menu);
    m_map.insert(FileReport_SaveMode, &SubMenu::set_saveMode_menu);
    m_map.insert(FileReport_Report, &SubMenu::set_report_menu);
    m_map.insert(FileReport_Format, &SubMenu::set_format_menu);
    m_map.insert(FileReport_UserField, &SubMenu::set_userField_menu);
    m_map.insert(Preference_Preference, &SubMenu::set_preference_menu);
    m_map.insert(Preference_System, &SubMenu::set_system_menu);
    m_map.insert(Preference_Network, &SubMenu::set_network_menu);
    m_map.insert(Preference_Service, &SubMenu::set_service_menu);
}


void SubMenu::set_third_menu(int num)
{
    for(int i = 0; i < 6; i ++) {
        MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
        widget->clean();
    }
    get_main_menu_type((Type)num);
    run_fun(m_typeMap.value("previous"), false);
    run_fun((Type)num, true);
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

void SubMenu::run_fun(Type type, bool value)
{
    QMap<Type, Function>::const_iterator it = m_map.find(type);
    if(it != m_map.end()) {
        Function pFun = m_map.value(type);
        if(pFun) {
            return (this->*pFun)(value);
        }
    }
}

void SubMenu::get_main_menu_type(Type type)
{
    if(m_typeMap.find("previous") != m_typeMap.end()) {
        m_typeMap.remove("prevoius");
    }
    m_typeMap.insert("previous", m_typeMap.value("current"));
    m_typeMap.remove("current");
    m_typeMap.insert("current", type);
}

void SubMenu::set_general_menu(bool show)
{
    if(show) {
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
        set_combobox_menu(ui->subMenu_6, tr("UT Unit"), m_list_utUnit);
    } else {

    }
}

void SubMenu::set_pulser_menu(bool show)
{
    if(show) {
        /* Tx/Rx Mode menu item */
        set_combobox_menu(ui->subMenu_1, tr("Tx/Rx Mode"), m_list_txrxMode);

        /* Pulser menu item */
        set_spinbox_menu(ui->subMenu_2, tr("Pulser"), "", stepList5, 1, 113, 0);

        /* Voltage menu item */
        set_combobox_menu(ui->subMenu_3, tr("Voltage"), m_list_voltage);

        /* PW menu item */
        QList<double> steps;
        steps.append(2.5);
        steps.append(10);
        steps.append(25);
        set_spinbox_menu(ui->subMenu_4, tr("PW"), "ns", steps, 30, 500, 1);

        /* PRF menu item */
        set_combobox_menu(ui->subMenu_5, tr("PRF"), m_list_prf);

        ui->subMenu_6->set_type(MenuItem::None);
        steps.clear();
    } else {

    }
}

void SubMenu::set_receiver_menu(bool show)
{
    if(show) {
        /* Receiver menu item */
        set_label_menu(ui->subMenu_1, tr("Receiver"));

        /* Filter menu item */
        set_combobox_menu(ui->subMenu_2, tr("Filter"), m_list_filter);

        /* Rectifier menu item */
        set_combobox_menu(ui->subMenu_3, tr("Rectifier"), m_list_rectifier);

        /* Video Filter menu item */
        set_combobox_menu(ui->subMenu_4, tr("Video Filter"), switchList);

        /* Averaging menu item */
        set_combobox_menu(ui->subMenu_5, tr("Averaging"), m_list_averaging);

        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_advanced_menu(bool show)
{
    if(show) {
        /* Set 80% menu item */
        set_combobox_menu(ui->subMenu_1, tr("Set 80%"), switchList);

        /* dB Ref. menu item */
        set_combobox_menu(ui->subMenu_2, tr("dB Ref."), switchList);

        /* Point Qty. menu item */
        set_combobox_menu(ui->subMenu_3, tr("Point Qty."), m_list_pointQty);

        /* Scale Factor menu item */
        set_label_menu(ui->subMenu_4, tr("Scale Factor"));

        /* Sum Gain menu item */
        set_spinbox_menu(ui->subMenu_5, tr("Sum Gain"), "dB", stepList1, 0, 100, 1);

        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_gate_menu(bool show)
{
    if(show) {
        /* Gate menu item */
        set_combobox_menu(ui->subMenu_1, tr("Gate"), m_list_gate);

        /* Start menu item */
        set_spinbox_menu(ui->subMenu_2, tr("Start"), "mm", stepList2, 0, 16000, 2);

        /* Width menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Width"), "mm", stepList6, 0.05, 525, 2);

        /* Threshold menu item */
        QList<double> steps2;
        steps2.append(1);
        steps2.append(10);
        set_spinbox_menu(ui->subMenu_4, tr("Threshold"), "%", steps2, 0, 100, 0);

        /* Synchro menu item */
        set_combobox_menu(ui->subMenu_5, tr("Synchro"), m_list_synchro);

        /* Measure Mode menu item */
        set_combobox_menu(ui->subMenu_6, tr("Measure Mode"), m_list_measureMode);

        steps2.clear();
    } else {

    }

}

void SubMenu::set_alarm_menu(bool show)
{
    if(show) {
        /* Alarm menu item */
        set_combobox_menu(ui->subMenu_1, tr("Alarm"), m_list_alarm);

        /* Switch menu item */
        set_combobox_menu(ui->subMenu_2, tr("Switch"), switchList);

        /* Group menu item */
        set_combobox_menu(ui->subMenu_3, tr("Group"), m_list_group);

        /* Condition Factor menu item */
        set_combobox_menu(ui->subMenu_4, tr("Condition"), m_list_condition);

        /* Operator menu item */
        set_combobox_menu(ui->subMenu_5, tr("Operator"), m_list_operator);

        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_output_menu(bool show)
{
    if(show) {
        /* Output menu item */
        set_combobox_menu(ui->subMenu_1, tr("Output"), m_list_output);

        /* Sound menu item */
        set_combobox_menu(ui->subMenu_2, tr("Sound"), m_list_sound);

        /* Delay menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Delay"), "mm", stepList6, 0, 5000, 2);

        /* Hold Time menu item */
        set_spinbox_menu(ui->subMenu_4, tr("Hold Time"), "%", stepList6, 0, 5000, 2);

        /* Group menu item */
        set_label_menu(ui->subMenu_5, tr("Group"));

        /* Data menu item */
        set_combobox_menu(ui->subMenu_6, tr("Data"), m_list_data);
    } else {

    }
}

void SubMenu::set_dac_menu(bool show)
{
    if(show) {
        QString option;
        QList<double> steps;

        /* Mode menu item */
        set_combobox_menu(ui->subMenu_1, tr("Mode"), m_list_mode);

        if(option == "Setting") {

            /* Curve No. menu item */
            steps.append(1);
            set_spinbox_menu(ui->subMenu_2, tr("Curve No."), "", steps, 1, 5, 0);

            /* Curve X menu item */
            set_combobox_menu(ui->subMenu_3, tr("Curve X"), m_list_curveX);

            /* dB Offset menu item */
            set_spinbox_menu(ui->subMenu_4, tr("dB Offset"), "dB", stepList1, -40, 40, 1);

            /* Ref.Gain menu item */
            set_spinbox_menu(ui->subMenu_5, tr("Ref.Gain"), "dB", stepList1, -40, 40, 1);

            /* Switch menu item */
            set_combobox_menu(ui->subMenu_6, tr("Switch"), switchList);
        } else if(option == "Edit") {

            /* Point menu item */
            set_combobox_menu(ui->subMenu_2, tr("Point"), m_list_point);

            /* Position menu item */
            set_spinbox_menu(ui->subMenu_3, tr("Position"), "", stepList6, 0, 10000, 2);

            /* Add Point menu item */
            set_label_menu(ui->subMenu_4, tr("Add Point"));

            /* Delete Point menu item */
            set_label_menu(ui->subMenu_5, tr("Delete Point"));

            ui->subMenu_6->set_type(MenuItem::None);
        }
        steps.clear();
    } else {

    }
}

void SubMenu::set_tcg_menu(bool show)
{
    if(show) {
        QString option;
        QList<double> steps;

        /* Mode menu item */
        set_combobox_menu(ui->subMenu_1, tr("Mode"), m_list_mode);

        if(option == "Setting") {

            /* Curve No. menu item */
            steps.append(1);
            set_spinbox_menu(ui->subMenu_2, tr("Curve No."), "", steps, 1, 5, 0);

            /* Curve X menu item */
            set_combobox_menu(ui->subMenu_3, tr("Curve X"), m_list_curveX);

            /* dB Offset menu item */
            set_spinbox_menu(ui->subMenu_4, tr("dB Offset"), "dB", stepList1, -40, 40, 1);

            /* Switch menu item */
            set_combobox_menu(ui->subMenu_5, tr("Switch"), switchList);

            ui->subMenu_6->set_type(MenuItem::None);
        } else if(option == "Edit") {

            /* Point menu item */
            set_combobox_menu(ui->subMenu_2, tr("Point"), m_list_point);

            /* Position menu item */
            set_spinbox_menu(ui->subMenu_3, tr("Position"), "", stepList6, 0, 10000, 2);

            /* Gain menu item */
            set_spinbox_menu(ui->subMenu_3, tr("Gain"), "dB", stepList1, 0, 100, 1);

            /* Add Point menu item */
            set_label_menu(ui->subMenu_5, tr("Add Point"));

            /* Delete Point menu item */
            set_label_menu(ui->subMenu_6, tr("Delete Point"));
        }
        steps.clear();
    } else {

    }
}

void SubMenu::set_selection_menu(bool show)
{
    if(show) {
        /* Group menu item */
        set_combobox_menu(ui->subMenu_1, tr("Group"), m_list_group2);

        /* Display menu item */
        set_combobox_menu(ui->subMenu_2, tr("Display"), m_list_display);

        /* C-Scan Source menu item */
        set_combobox_menu(ui->subMenu_3, tr("C-Scan Source"), m_list_cScanSource);

        /* Min.Thickness menu item */
        set_spinbox_menu(ui->subMenu_4, tr("Min.Thickness"), "mm", stepList6, 0.05, 20000, 2);

        /* Max.Thickness menu item */
        set_spinbox_menu(ui->subMenu_5, tr("Max.Thickness"), "mm", stepList6, 0.06, 20000, 2);

        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_colorSettings_menu(bool show)
{
    if(show) {
        /* Amplitude menu item */
        set_label_menu(ui->subMenu_1, tr("Amplitude"));

        /* Depth menu item */
        set_label_menu(ui->subMenu_2, tr("Depth"));

        /* TOFD menu item */
        set_label_menu(ui->subMenu_3, tr("TOFD"));

        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_properties_menu(bool show)
{
    if(show) {
        QString option;

        /* Scan menu item */
        set_combobox_menu(ui->subMenu_1, tr("Scan"), m_list_scan);

        if(option == "A-Scan") {

            /* Color menu item */
            set_combobox_menu(ui->subMenu_2, tr("Color"), m_list_color);

            /* Envelope menu item */
            set_combobox_menu(ui->subMenu_3, tr("Envelope"), m_list_envelope);

            /* Peak Holding menu item */
            set_combobox_menu(ui->subMenu_4, tr("Peak Holding"), switchList);

            /* Reference Holding menu item */
            set_combobox_menu(ui->subMenu_5, tr("Reference Holding"), switchList);

            ui->subMenu_6->set_type(MenuItem::None);
        } else if(option == "B-Scan") {

            /* Compression menu item */
            set_combobox_menu(ui->subMenu_2, tr("Compression"), switchList);

            ui->subMenu_3->set_type(MenuItem::None);
            ui->subMenu_4->set_type(MenuItem::None);
            ui->subMenu_5->set_type(MenuItem::None);
            ui->subMenu_6->set_type(MenuItem::None);

        } else if(option == "C-Scan") {

            /* Ratio 1:1 menu item */
            set_combobox_menu(ui->subMenu_2, tr("Ratio 1:1"), switchList);

            /* C-Scan Mode menu item */
            set_combobox_menu(ui->subMenu_3, tr("C-Scan Mode"), m_list_cScanMode);

            /* Compression menu item */
            set_combobox_menu(ui->subMenu_4, tr("Compression"), switchList);

            ui->subMenu_5->set_type(MenuItem::None);
            ui->subMenu_6->set_type(MenuItem::None);

        }
    } else {

    }
}

void SubMenu::set_select_menu(bool show)
{
    if(show) {
        /* Group menu item */
        set_combobox_menu(ui->subMenu_1, tr("Group"), m_list_group3);

        /* Group Mode menu item */
        set_combobox_menu(ui->subMenu_2, tr("Group Mode"), m_list_groupMode);

        /* Probe menu item */
        set_label_menu(ui->subMenu_3, tr("Probe"));
        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_probe_dialog()));

        /* Wedge menu item */
        set_label_menu(ui->subMenu_4, tr("Wedge"));
        connect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_wedge_dialog()));

        /* Define menu item */
        set_combobox_menu(ui->subMenu_5, tr("Define"), m_list_define);

        /* Auto Detect menu item */
        set_combobox_menu(ui->subMenu_6, tr("Auto Detect"), switchList);
//        connect(ui->subMenu_6, SIGNAL(combo_event(QString)), this, SLOT(auto_detect_probe(QString)));
    } else {
        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_probe_dialog()));
        disconnect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_wedge_dialog()));
//        disconnect(ui->subMenu_6, SIGNAL(combo_event(QString)), this, SLOT(auto_detect_probe(QString)));
    }
}

void SubMenu::set_position_menu(bool show)
{
    if(show) {
        /* Scan Offset menu item */
        QList<double> steps;
        steps.append(0.1);
        steps.append(1.0);
        steps.append(5.0);
        steps.append(10.0);
        set_spinbox_menu(ui->subMenu_1, tr("Scan Offset"), "mm", steps, -10000, 10000, 1);

        /* Index Offset menu item */
        set_spinbox_menu(ui->subMenu_2, tr("Index Offset"), "mm", steps, -10000, 10000, 1);

        /* Skew menu item */
        set_combobox_menu(ui->subMenu_3, tr("Skew"), m_list_skew);

        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
        steps.clear();
    } else {

    }
}

void SubMenu:: set_fft_menu(bool show)
{
    if(show) {
        /* Gain menu item */
        set_spinbox_menu(ui->subMenu_1, tr("Gain"), "dB", stepList1, 0, 100, 1);

        /* Start menu item */
        set_spinbox_menu(ui->subMenu_2, tr("Start"), "mm", stepList2, 0, 16000, 2);

        /* Width menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Width"), "mm", stepList3, 0.05, 525, 2);

        /* Switch menu item */
        set_combobox_menu(ui->subMenu_4, tr("Switch"), switchList);

        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_part_menu(bool show)
{
    if(show) {
        /* Geometry menu item */
        set_combobox_menu(ui->subMenu_1, tr("Geometry"), m_list_geometry);

        /* Thickness menu item */
        set_spinbox_menu(ui->subMenu_2, tr("Thickness"), "mm", stepList6, 0.05, 1000, 2);

        /* Diameter menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Diameter"), "mm", stepList6, 0.05, 525, 2);

        /* Material menu item */
        set_combobox_menu(ui->subMenu_4, tr("Material"), m_list_material);

        /* Overlay menu item */
        set_combobox_menu(ui->subMenu_5, tr("Overlay"), switchList);

        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_advanced_2_menu(bool show)
{
    if(show) {
        /* Load Part menu item */
        set_label_menu(ui->subMenu_1, tr("Load Part"));

        /* Clear Part menu item */
        set_label_menu(ui->subMenu_2, tr("Clear Part"));

        ui->subMenu_3->set_type(MenuItem::None);
        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_lawConfig_menu(bool show)
{
    if(show) {
        /* Law Type Menu Item */
        set_combobox_menu(ui->subMenu_1, tr("Law Type"), m_list_lawType);

        /* Pulse Connection menu item */
        QList<double> steps;
        steps.append(1);
        steps.append(10);
        set_spinbox_menu(ui->subMenu_2, tr("Pulse Connection"), "mm", steps, 1, 113, 0);

        /* Receiver Connection menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Receiver Connection"), "mm", steps, 1, 113, 0);

        /* Wave Type Menu Item */
        set_combobox_menu(ui->subMenu_4, tr("Wave Type"), m_list_waveType);

        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_angle_menu(bool show)
{
    if(show) {
        /* Min.Angle Menu Item */
        QList<double> steps;
        steps.append(1);
        steps.append(5);
        steps.append(10);
        set_spinbox_menu(ui->subMenu_1, tr("Min.Angle"), "°", steps, 25, 75, 0);

        /* Max.Angle Menu Item */
        set_spinbox_menu(ui->subMenu_2, tr("Max.Angle"), "°", steps, 25, 75, 0);

        /* Angle Step Menu Item */
        QList<double> steps2;
        steps2.append(1);
        set_spinbox_menu(ui->subMenu_3, tr("Angle Step"), "°", steps2, 1, 10, 0);

        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);

        steps.clear();
        steps2.clear();
    } else {

    }
}

void SubMenu::set_apeture_menu(bool show)
{
    if(show) {
        /* Apeture Menu Item */
        QList<double> steps;
        steps.append(1);
        steps.append(5);
        set_spinbox_menu(ui->subMenu_1, tr("Apeture"), "", steps, 0, 64, 0);

        /* First Element menu item */
        set_spinbox_menu(ui->subMenu_2, tr("First Element"), "", steps, 1, 64, 0);

        /* Last Element menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Last Element"), "", steps, 1, 64, 0);

        /* Element Step Menu Item */
        set_spinbox_menu(ui->subMenu_4, tr("Element Step"), "", steps, 1, 32, 0);

        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
        steps.clear();
    } else {

    }
}

void SubMenu::set_focalPoint_menu(bool show)
{
    if(show) {
        /* Type Menu Item */
        set_combobox_menu(ui->subMenu_1, tr("Type"), m_list_type);

        /* Position Start menu item */
        set_spinbox_menu(ui->subMenu_2, tr("Position Start"), "mm", stepList6, 0, 1000, 2);

        /* Position End menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Position End"), "mm", stepList6, 1, 1000, 2);

        /* Offset Start Menu Item */
        set_spinbox_menu(ui->subMenu_4, tr("Offset Start"), "mm", stepList6, 0, 1000, 2);

        /* Offset End Menu Item */
        set_spinbox_menu(ui->subMenu_5, tr("Offset End"), "mm", stepList6, 1, 1000, 2);

        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_inspection_menu(bool show)
{
    if(show) {
        /* Scan Menu Item */
        set_combobox_menu(ui->subMenu_1, tr("Scan"), m_list_scan2);

        /* Type menu item */
        set_combobox_menu(ui->subMenu_2, tr("Type"), m_list_type2);

        /* Max Scan Speed menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Max Scan Speed"), "m/s", stepList2, 0, 1000, 2);

        /* Max Scan Speed(rpm) Menu Item */
        set_spinbox_menu(ui->subMenu_4, tr("Max Scan Speed(rpm)"), "m/s", stepList2, 0, 1000, 0);

        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_encoder_menu(bool show)
{
    if(show) {
        /* Encoder Menu Item */
        set_combobox_menu(ui->subMenu_1, tr("Encoder"), m_list_encoder);

        /* Encoder Type menu item */
        set_combobox_menu(ui->subMenu_2, tr("Encoder Type"), m_list_encoderType);

        /* Resolution menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Resolution"), "Step/mm", stepList2, 0.01, 10000, 2);

        /* Polarity Menu Item */
        set_combobox_menu(ui->subMenu_4, tr("Polarity"), m_list_polarity);

        /* Origin Menu Item */
        set_spinbox_menu(ui->subMenu_5, tr("Origin"), "mm", stepList2, 0, 1000, 2);

        /* Preset Menu Item */
        set_label_menu(ui->subMenu_6, tr("Preset"));
    } else {

    }
}

void SubMenu::set_area_menu(bool show)
{
    if(show) {
        /* Scan Start Menu Item */
        QList<double> steps;
        steps.append(10.00);
        steps.append(100.00);
        steps.append(1000.00);
        steps.append(10000.00);
        set_spinbox_menu(ui->subMenu_1, tr("Scan Start"), "mm", steps, 0, 10000, 2);

        /* Scan End menu item */
        set_spinbox_menu(ui->subMenu_2, tr("Scan End"), "mm", steps, 0, 10000, 2);

        /* Scan Resolution menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Scan Resolution"), "mm", stepList6, 0, 100, 2);

        /* Index Start Menu Item */
        set_spinbox_menu(ui->subMenu_4, tr("Index Start"), "mm", steps, 0, 10000, 2);

        /* Index End Menu Item */
        set_spinbox_menu(ui->subMenu_5, tr("Index End"), "mm", steps, 0, 10000, 2);

        /* Index Resolution Menu Item */
        set_spinbox_menu(ui->subMenu_6, tr("Index Resolution"), "mm", stepList6, 0, 100, 2);
        steps.clear();
    } else {

    }
}

void SubMenu::set_start_menu(bool show)
{
    if(show) {
        /* Start Menu Item */
        set_spinbox_menu(ui->subMenu_1, tr("Scan"), "mm", stepList2, 0, 10000, 2);

        /* Pause menu item */
        set_combobox_menu(ui->subMenu_2, tr("Pause"), switchList);

        ui->subMenu_3->set_type(MenuItem::None);
        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {

    }
}

void SubMenu::set_cursors_menu(bool show)
{
    if(show) {
        QString option;
        QList<double> steps1;
        steps1.append(0.1);
        steps1.append(1.0);
        steps1.append(10.0);

        QList<double> steps2;
        steps2.append(0.1);
        steps2.append(0.5);
        steps2.append(1.0);
        steps2.append(5.0);

        /* Selection menu item */
        set_combobox_menu(ui->subMenu_1, tr("Selection"), m_list_selection);

        if(option == "A-Scan") {

            /* %(r) menu item */
            set_spinbox_menu(ui->subMenu_2, tr("%(r)"), "%", steps1, 0, 100, 1);

            /* %(m) menu item */
            set_spinbox_menu(ui->subMenu_3, tr("%(m)"), "%", steps1, 0, 100, 1);

            /* U(r) menu item */
            set_spinbox_menu(ui->subMenu_4, tr("U(r)"), "mm", stepList6, 0, 2000, 2);

            /* U(m) menu item */
            set_spinbox_menu(ui->subMenu_5, tr("U(m)"), "mm", stepList6, 0, 2000, 2);

            ui->subMenu_6->set_type(MenuItem::None);
        } else if(option == "B-Scan") {

            /* S(r) menu item */
            set_spinbox_menu(ui->subMenu_2, tr("S(r)"), "s", steps2, 0, 10000, 1);

            /* S(m) menu item */
            set_spinbox_menu(ui->subMenu_3, tr("S(m)"), "s", steps2, 0, 10000, 1);

            /* U(r) menu item */
            set_spinbox_menu(ui->subMenu_4, tr("U(r)"), "mm", stepList6, 0, 2000, 2);

            /* U(m) menu item */
            set_spinbox_menu(ui->subMenu_5, tr("U(m)"), "mm", stepList6, 0, 2000, 2);

            ui->subMenu_6->set_type(MenuItem::None);

        } else if(option == "C-Scan") {

            /* S(r) menu item */
            set_spinbox_menu(ui->subMenu_2, tr("S(r)"), "s", steps2, 0, 10000, 1);

            /* S(m) menu item */
            set_spinbox_menu(ui->subMenu_3, tr("S(m)"), "s", steps2, 0, 10000, 1);

            /* I(r) menu item */
            set_spinbox_menu(ui->subMenu_4, tr("I(r)"), "mm", steps2, 0, 2000, 1);

            /* I(m) menu item */
            set_spinbox_menu(ui->subMenu_5, tr("I(m)"), "mm", steps2, 0, 2000, 1);

            ui->subMenu_6->set_type(MenuItem::None);

        } else if(option == "S-Scan") {
            /* Angle menu item */
            QList<double> steps3;
            steps3.append(1);
            set_spinbox_menu(ui->subMenu_2, tr("Angle"), "°", steps3, 25, 75, 0);

            /* U(r) menu item */
            set_spinbox_menu(ui->subMenu_3, tr("U(r)"), "mm", stepList6, 0, 2000, 2);

            /* U(m) menu item */
            set_spinbox_menu(ui->subMenu_4, tr("U(m)"), "mm", stepList6, 0, 2000, 2);

            /* I(r) menu item */
            set_spinbox_menu(ui->subMenu_5, tr("I(r)"), "mm", steps2, 0, 2000, 1);

            /* I(m) menu item */
            set_spinbox_menu(ui->subMenu_6, tr("I(m)"), "mm", steps2, 0, 2000, 1);
        }
        steps1.clear();
        steps2.clear();
    } else {

    }
}

void SubMenu::set_tofd_menu(bool show)
{
    if(show) {
        QString option;
        QList<double> steps;
        steps.append(0.1);
        steps.append(1.0);
        steps.append(10.0);
        steps.append(100.0);

        /* Select menu item */
        set_combobox_menu(ui->subMenu_1, tr("Select"), m_list_select);

        if(option == "TOFD Settings") {

            /* Wedge Sep. menu item */
            set_spinbox_menu(ui->subMenu_2, tr("Wedge Sep."), "mm", steps, 0, 10000, 1);

            /* Layer Depth menu item */
            set_label_menu(ui->subMenu_3, tr("Layer Depth"));

            /* TOFD Calculator menu item */
            set_label_menu(ui->subMenu_4, tr("TOFD Calculator"));

            /* Start menu item */
            set_spinbox_menu(ui->subMenu_5, tr("Start"), "mm", stepList2, 0, 16000, 2);

            /* Range menu item */
            set_spinbox_menu(ui->subMenu_6, tr("Range"), "mm", stepList2, 0, 16000, 2);
        } else if(option == "TOFD Analysis") {

            /* Straightening menu item */
            set_combobox_menu(ui->subMenu_2, tr("Straightening"), switchList);

            /* Remove Lateral menu item */
            set_combobox_menu(ui->subMenu_3, tr("Remove Lateral"), switchList);

            /* Ref.Position menu item */
            set_spinbox_menu(ui->subMenu_4, tr("Ref.Position"), "mm", stepList6, 0, 2000, 2);

            /* Depth Calibration menu item */
            set_combobox_menu(ui->subMenu_5, tr("Depth Calibration"), switchList);

            ui->subMenu_6->set_type(MenuItem::None);

        }
    } else {

    }
}

void SubMenu::set_flawRecord_menu(bool show)
{
    if(show) {
        /* Add/Delete Menu Item */
        set_label_menu(ui->subMenu_1, tr("Add/Delete"));

        /* Flaw Image menu item */
        set_combobox_menu(ui->subMenu_2, tr("Flaw Image"), switchList);

        /* Comment menu item */
        set_label_menu(ui->subMenu_3, tr("Comment"));
        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Display Table Menu Item */
        set_combobox_menu(ui->subMenu_4, tr("Display Table"), switchList);

        /* Export Record Menu Item */
        set_label_menu(ui->subMenu_5, tr("Export Record"));

        ui->subMenu_6->set_type(MenuItem::None);
    } else {
        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
    }
}

void SubMenu::set_file_menu(bool show)
{
    if(show) {
        /* Save Setup As Menu Item */
        set_label_menu(ui->subMenu_1, tr("Save Setup As"));

        /* Open menu item */
        set_label_menu(ui->subMenu_2, tr("Open"));

        /* File Manager menu item */
        set_label_menu(ui->subMenu_3, tr("File Manager"));
        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_filemanager_dialog()));

        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {
        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_filemanager_dialog()));
    }
}

void SubMenu::set_saveMode_menu(bool show)
{
    if(show) {
        /* Storage Menu Item */
        set_combobox_menu(ui->subMenu_1, tr("Storage"), m_list_storage);

        /* Save Mode menu item */
        set_combobox_menu(ui->subMenu_2, tr("Save Mode"), m_list_saveMode);

        /* Save Data menu item */
        set_label_menu(ui->subMenu_3, tr("Save Data"));

        /* File Name menu item */
        set_label_menu(ui->subMenu_4, tr("File Name"));
        connect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {
        disconnect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
    }
}

void SubMenu::set_report_menu(bool show)
{
    if(show) {
        /* Template Menu Item */
        set_label_menu(ui->subMenu_1, tr("Template"));

        /* Report Name menu item */
        set_label_menu(ui->subMenu_2, tr("Report Name"));
        connect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Customer menu item */
        set_label_menu(ui->subMenu_3, tr("Customer"));
        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Part Name Menu Item */
        set_label_menu(ui->subMenu_4, tr("Part Name"));
        connect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Part Number item */
        set_label_menu(ui->subMenu_5, tr("Part Number"));
        connect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Create menu item */
        set_label_menu(ui->subMenu_6, tr("Create"));
    } else {
        disconnect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
        disconnect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
        disconnect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
    }
}

void SubMenu::set_format_menu(bool show)
{
    if(show) {
        /* Probe/Wedge Info Menu Item */
        set_combobox_menu(ui->subMenu_1, tr("Probe/Wedge Info"), switchList);

        /* Inspection Info menu item */
        set_combobox_menu(ui->subMenu_2, tr("Inspection Info"), switchList);

        /* Scan Info menu item */
        set_combobox_menu(ui->subMenu_3, tr("Scan Info"), switchList);

        /* Encoder Info Menu Item */
        set_combobox_menu(ui->subMenu_4, tr("Encoder Info"), switchList);

        /* DAC/TCG Info Number item */
        set_combobox_menu(ui->subMenu_5, tr("DAC/TCG Info"), switchList);

        /* Flaw Record Table menu item */
        set_combobox_menu(ui->subMenu_6, tr("Flaw Record Table"), switchList);
    } else {

    }
}

void SubMenu::set_userField_menu(bool show)
{
    if(show) {
        /* Select Menu Item */
        set_combobox_menu(ui->subMenu_1, tr("Select"), m_list_select2);

        /* Enable menu item */
        set_combobox_menu(ui->subMenu_2, tr("Enable"), switchList);

        /* Label menu item */
        set_label_menu(ui->subMenu_3, tr("Label"));
        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Content Menu Item */
        set_label_menu(ui->subMenu_4, tr("Content"));
        connect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Edit Note Number item */
        set_label_menu(ui->subMenu_5, tr("Edit Note"));
        connect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

        /* Print menu item */
        set_label_menu(ui->subMenu_6, tr("Print"));
    } else {
        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
        disconnect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
        disconnect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
    }
}

void SubMenu::set_preference_menu(bool show)
{
    if(show) {
        /* Units menu item */
        set_combobox_menu(ui->subMenu_1, tr("Units"), m_list_units);

        /* Bright menu item */
        QList<double> steps;
        steps.append(1);
        steps.append(10);
        set_spinbox_menu(ui->subMenu_2, tr("Bright"), "%", steps, 1, 100, 0);
        connect(ui->subMenu_2, SIGNAL(spin_event(double)), this, SLOT(set_brightness(double)));

        /* Opacity menu item */
        set_spinbox_menu(ui->subMenu_3, tr("Opacity"), "%", steps, 1, 100, 0);

        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);

        steps.clear();
    } else {
        disconnect(ui->subMenu_2, SIGNAL(spin_event(double)), this, SLOT(set_brightness(double)));
    }
}

void SubMenu::set_system_menu(bool show)
{
    if(show) {

        /* Clock Set menu item */
        set_label_menu(ui->subMenu_1, tr("Clock Set"));
        connect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_time_dialog()));
        ui->subMenu_1->set_label_text(QTime::currentTime().toString("hh:mm:ss"));

        /* Date Set menu item */
        set_label_menu(ui->subMenu_2, tr("Date Set"));
        connect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_date_dialog()));
        ui->subMenu_2->set_label_text(QDate::currentDate().toString("yyyy-MM-dd"));

        /* Language menu item */
        set_combobox_menu(ui->subMenu_3, tr("Language"), m_list_language);

        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {
        disconnect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_time_dialog()));
        disconnect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_date_dialog()));
    }
}

void SubMenu::set_network_menu(bool show)
{
    if(show) {

        /* IP Address menu item */
        set_label_menu(ui->subMenu_1, tr("IP Address"));
        connect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_ip_address_dialog()));
        ui->subMenu_1->set_label_text("192.168.1.1");

        /* Subnet Mask menu item */
        set_label_menu(ui->subMenu_2, tr("Subnet Mask"));
        connect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_subnet_mask_dialog()));
        ui->subMenu_2->set_label_text("255.255.255.0");

        ui->subMenu_3->set_type(MenuItem::None);
        ui->subMenu_4->set_type(MenuItem::None);
        ui->subMenu_5->set_type(MenuItem::None);
        ui->subMenu_6->set_type(MenuItem::None);
    } else {        
        disconnect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_ip_address_dialog()));
        disconnect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_subnet_mask_dialog()));
    }
}

void SubMenu::set_service_menu(bool show)
{
    if(show) {
        /* System Information Menu Item */
        set_label_menu(ui->subMenu_1, tr("System Information"));
        connect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_info_dialog()));

        /* Cert Import menu item */
        set_combobox_menu(ui->subMenu_2, tr("Cert Import"), m_list_certImport);

        /* SW Update menu item */
        set_label_menu(ui->subMenu_3, tr("SW Update"));

        /* HW Update Menu Item */
        set_label_menu(ui->subMenu_4, tr("HW Update"));

        /* Reset Configuration Number item */
        set_label_menu(ui->subMenu_5, tr("Reset Configuration"));
        connect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));

        /* About menu item */
        set_label_menu(ui->subMenu_6, tr("About"));
        connect(ui->subMenu_6, SIGNAL(clicked()), this, SLOT(show_about_dialog()));
    } else {
        disconnect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_info_dialog()));
        disconnect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));
        disconnect(ui->subMenu_6, SIGNAL(clicked()), this, SLOT(show_about_dialog()));
    }
}

void SubMenu::init_option_stringlist()
{

    m_list_utUnit.append(tr("Time"));
    m_list_utUnit.append(tr("Sound Path"));
    m_list_utUnit.append(tr("True Path"));

    m_list_txrxMode.append(tr("PC"));
    m_list_txrxMode.append(tr("PE"));
    m_list_txrxMode.append(tr("TT"));
    m_list_txrxMode.append(tr("TOFD"));

    m_list_voltage.append(tr("50V"));
    m_list_voltage.append(tr("100V"));
    m_list_voltage.append(tr("200V"));

    m_list_prf.append(tr("Auto Max"));
    m_list_prf.append(tr("Max/2"));
    m_list_prf.append(tr("Optimum"));
    m_list_prf.append(tr("UserDef"));

    m_list_filter.append(tr("none"));
    m_list_filter.append(tr("1M"));
    m_list_filter.append(tr("1.5M-2.5M"));
    m_list_filter.append(tr("3-5M"));
    m_list_filter.append(tr("7.5M"));
    m_list_filter.append(tr("more than 10M"));

    m_list_rectifier.append(tr("RF"));
    m_list_rectifier.append(tr("FW"));
    m_list_rectifier.append(tr("HW+"));
    m_list_rectifier.append(tr("HW-"));

    m_list_averaging.append(tr("1"));
    m_list_averaging.append(tr("2"));
    m_list_averaging.append(tr("4"));
    m_list_averaging.append(tr("8"));
    m_list_averaging.append(tr("16"));

    m_list_pointQty.append(tr("Auto"));
    m_list_pointQty.append(tr("160"));
    m_list_pointQty.append(tr("320"));
    m_list_pointQty.append(tr("640"));
    m_list_pointQty.append(tr("UserDef"));

    m_list_gate.append(tr("A"));
    m_list_gate.append(tr("B"));
    m_list_gate.append(tr("I"));
    m_list_gate.append(tr("Off"));

    m_list_synchro.append(tr("Gate A"));
    m_list_synchro.append(tr("Gate I"));
    m_list_synchro.append(tr("Pulse"));


    m_list_measureMode.append(tr("Edge"));
    m_list_measureMode.append(tr("Peak"));

    m_list_alarm.append(tr("Alarm 1"));
    m_list_alarm.append(tr("Alarm 2"));
    m_list_alarm.append(tr("Alarm 3"));

    m_list_group.append(tr("Group1"));
    m_list_group.append(tr("All"));
    m_list_group.append(tr("None"));

    m_list_condition.append(tr("None"));
    m_list_condition.append(tr("Gate A"));
    m_list_condition.append(tr("Gate B"));
    m_list_condition.append(tr("Gate I"));
    m_list_condition.append(tr("Not Gate A"));
    m_list_condition.append(tr("Not Gate B"));
    m_list_condition.append(tr("Not Gate I"));
    m_list_condition.append(tr(">Max.Thickness"));
    m_list_condition.append(tr("<Min.Thickness"));

    m_list_operator.append(tr("And"));
    m_list_operator.append(tr("Or"));

    m_list_output.append(tr("Alarm 1"));
    m_list_output.append(tr("Alarm 2"));
    m_list_output.append(tr("Alarm 3"));
    m_list_output.append(tr("Analog 1"));
    m_list_output.append(tr("Analog 2"));

    m_list_sound.append(tr("Off No Sound"));
    m_list_sound.append(tr("300Hz Audio Output at 300Hz"));
    m_list_sound.append(tr("600Hz Audio Output at 600Hz"));
    m_list_sound.append(tr("1000Hz Audio Output at 1000Hz"));
    m_list_sound.append(tr("5000Hz Audio Output at 5000Hz"));

    m_list_data.append(tr("A%"));
    m_list_data.append(tr("B%"));
    m_list_data.append(tr("None"));

    m_list_mode.append(tr("Settings"));
    m_list_mode.append(tr("Edit"));

    m_list_curveX.append("1");
    m_list_curveX.append("2");
    m_list_curveX.append("3");
    m_list_curveX.append("4");
    m_list_curveX.append("5");

    m_list_point.append("1");

    m_list_group2.append(tr("All"));
    m_list_group2.append(tr("Current"));

    m_list_display.append(tr("A A-Scan"));
    m_list_display.append(tr("B B-Scan"));
    m_list_display.append(tr("C C-Scan"));
    m_list_display.append(tr("S S-Scan"));
    m_list_display.append(tr("A-B A-Scan B-Scan"));
    m_list_display.append(tr("A-S A-Scan S-Scan"));
    m_list_display.append(tr("A-B-C A-Scan B-Scan C-Scan"));
    m_list_display.append(tr("A-B-S A-Scan B-Scan S-Scan"));
    m_list_display.append(tr("A-S-[C] A-Scan S-Scan [C-Scan]"));
    m_list_display.append(tr("S-A-A-A S-Scan A-Scan A-Scan A-Scan"));
    m_list_display.append(tr("S-A-C-C S-Scan A-Scan C-Scan C-Scan"));

    m_list_cScanSource.append(tr("A%"));
    m_list_cScanSource.append(tr("B%"));
    m_list_cScanSource.append(tr("Thickness"));
    m_list_cScanSource.append(tr("I/"));

    m_list_scan.append(tr("A-Scan"));
    m_list_scan.append(tr("B-Scan"));
    m_list_scan.append(tr("C-Scan"));

    m_list_color.append(tr("Blue"));
    m_list_color.append(tr("Green"));
    m_list_color.append(tr("Red"));
    m_list_color.append(tr("Yellow"));
    m_list_color.append(tr("Black"));
    m_list_color.append(tr("White"));

    m_list_envelope.append(tr("None"));
    m_list_envelope.append(tr("Infinite"));

    m_list_cScanMode.append(tr("Sectorial"));
    m_list_cScanMode.append(tr("Linear"));

    m_list_group3.append(tr("Add"));
    m_list_group3.append(tr("1"));
    m_list_group3.append(tr("2"));
    m_list_group3.append(tr("3"));
    m_list_group3.append(tr("4"));
    m_list_group3.append(tr("5"));
    m_list_group3.append(tr("6"));
    m_list_group3.append(tr("7"));
    m_list_group3.append(tr("8"));
    m_list_group3.append(tr("Remove"));

    m_list_groupMode.append(tr("UT (PA Connector)"));
    m_list_groupMode.append(tr("PA (Phassed Array)"));
    m_list_groupMode.append(tr("UT1 (Conventional UT)"));
    m_list_groupMode.append(tr("UT2 (Conventional UT)"));

    m_list_define.append(tr("Probe"));
    m_list_define.append(tr("Wedge"));

    m_list_skew.append("0°");
    m_list_skew.append("90°");
    m_list_skew.append("180°");
    m_list_skew.append("270°");

    m_list_geometry.append(tr("Plate"));
    m_list_geometry.append(tr("ID"));
    m_list_geometry.append(tr("OD"));

    for(int i = 0; i < MATERIAL_NUMBER; i ++) {
        m_list_material.append(MATERIAL_STRING[i]);
    }

    m_list_lawType.append(tr("Azimuthal"));
    m_list_lawType.append(tr("Linear"));

    m_list_waveType.append(tr("LW"));
    m_list_waveType.append(tr("SW"));

    m_list_type.append(tr("True Depth"));
    m_list_type.append(tr("Half Path"));
    m_list_type.append(tr("Projection"));
    m_list_type.append(tr("Focal Plane"));
    m_list_type.append(tr("DDF"));

    m_list_scan2.append(tr("Time"));
    m_list_scan2.append(tr("Encoder 1"));
    m_list_scan2.append(tr("Encoder 2"));

    m_list_type2.append(tr("One Line"));
    m_list_type2.append(tr("Raster Scan"));
    m_list_type2.append(tr("Helicoidal Scan"));

    m_list_encoder.append(tr("Encoder 1"));
    m_list_encoder.append(tr("Encoder 2"));

    m_list_encoderType.append(tr("Up"));
    m_list_encoderType.append(tr("Down"));
    m_list_encoderType.append(tr("Quad"));

    m_list_polarity.append(tr("Normal"));
    m_list_polarity.append(tr("Reverse"));

    m_list_selection.append(tr("A-Scan"));
    m_list_selection.append(tr("B-Scan"));
    m_list_selection.append(tr("C-Scan"));
    m_list_selection.append(tr("S-Scan"));

    m_list_select.append(tr("TOFD Settings"));
    m_list_select.append(tr("TOFD Analysis"));

    m_list_storage.append(tr("SD"));
    m_list_storage.append(tr("SSG"));
    m_list_storage.append(tr("U Storage"));

    m_list_saveMode.append(tr("Inspection Data"));
    m_list_saveMode.append(tr("Inspection Table"));
    m_list_saveMode.append(tr("Screen"));
    m_list_saveMode.append(tr("Report"));

    m_list_select2.append("1");
    m_list_select2.append("2");
    m_list_select2.append("3");
    m_list_select2.append("4");
    m_list_select2.append("5");
    m_list_select2.append("6");
    m_list_select2.append("7");
    m_list_select2.append("8");
    m_list_select2.append("9");
    m_list_select2.append("10");

    m_list_units.append("Millimeters");
    m_list_units.append("Inches");

    m_list_language.append("English");
    m_list_language.append("Chinese");

    m_list_certImport.append(tr("U-Disk"));
    m_list_certImport.append(tr("Network"));
}

void SubMenu::init_step_list()
{
    stepList1.append(0.1);
    stepList1.append(0.5);
    stepList1.append(1.0);
    stepList1.append(2.0);
    stepList1.append(6.0);

    stepList2.append(0.01);
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

    stepList6.append(0.01);
    stepList6.append(0.10);
    stepList6.append(1.00);
    stepList6.append(10.00);

}

void SubMenu::show_probe_dialog()
{
    ProbeDialog probeDialog;
    probeDialog.exec();
    QString string = probeDialog.get_current_item_text();
    if(!string.isEmpty()){
        ui->subMenu_3->set_label_text(string.left(string.length() - 4));
    }
}

void SubMenu::show_wedge_dialog()
{
    WedgeDialog wedgeDialog;
    wedgeDialog.exec();
    QString string = wedgeDialog.get_current_item_text();
    if(!string.isEmpty()){
        ui->subMenu_4->set_label_text(string.left(string.length() - 4));
    }
}

void SubMenu::show_input_dialog()
{
    InputPanelContext inputPanel;
    MenuItem *widget = qobject_cast<MenuItem*>(sender());
    inputPanel.set_item_current_text(widget->get_label_text());
    inputPanel.exec();
    widget->set_label_text(inputPanel.get_text());
}

void SubMenu::show_filemanager_dialog()
{
    FileManagerDialog fileManagerDialog;
    fileManagerDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    fileManagerDialog.exec();
}


void SubMenu::show_ip_address_dialog()
{
    NetworkDialog *ipAddress = new NetworkDialog(this);
    QMap<QString, QString> map;
    map.insert("IP Address", ui->subMenu_1->get_title());
    ipAddress->set_dialog_title(map);
    ipAddress->set_spinbox_value(get_dialog_value_list(ui->subMenu_1->get_label_text(), QString(".")));
    ipAddress->exec();
    ui->subMenu_1->set_label_text(ipAddress->get_ip());
    delete ipAddress;
}

void SubMenu::show_subnet_mask_dialog()
{
    NetworkDialog *subnetMask = new NetworkDialog(this);
    QMap<QString, QString> map;
    map.insert("Subnet Mask", ui->subMenu_2->get_title());
    subnetMask->set_dialog_title(map);
    subnetMask->set_spinbox_value(get_dialog_value_list(ui->subMenu_2->get_label_text(), QString(".")));
    subnetMask->exec();
    ui->subMenu_2->set_label_text(subnetMask->get_subnet());
    delete subnetMask;
}

void SubMenu::show_info_dialog()
{
    Ui::Dialog::SysInfoDialog *infoDialog = new Ui::Dialog::SysInfoDialog(this);
    infoDialog->exec();
    delete infoDialog;
}

void SubMenu::show_about_dialog()
{
    Ui::Dialog::AboutDialog *aboutDialog = new Ui::Dialog::AboutDialog(this);
    aboutDialog->exec();
    delete aboutDialog;
}

void SubMenu::show_time_dialog()
{
    DateTimeSetDialog *timeDialog = new DateTimeSetDialog(this);
    QMap<QString, QString> map;
    map.insert("Clock Set", ui->subMenu_1->get_title());
    timeDialog->set_dialog_title(map);
    timeDialog->set_spinbox_value(get_dialog_value_list(ui->subMenu_1->get_label_text(), QString(":")));
    timeDialog->exec();
    ui->subMenu_1->set_label_text(timeDialog->get_time());
    delete timeDialog;
}

void SubMenu::show_date_dialog()
{
    DateTimeSetDialog *dateDialog = new DateTimeSetDialog(this);
    QMap<QString, QString> map;
    map.insert("Date Set", ui->subMenu_2->get_title());
    dateDialog->set_dialog_title(map);
    dateDialog->set_spinbox_value(get_dialog_value_list(ui->subMenu_2->get_label_text(), QString("-")));
    dateDialog->exec();
    ui->subMenu_2->set_label_text(dateDialog->get_date());
    delete dateDialog;
}

void SubMenu::show_resetconfig_dialog()
{
    ResetConfigDialog resetConfigDialog;
    resetConfigDialog.setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
    resetConfigDialog.exec();
}

SubMenu::~SubMenu()
{
    stepList1.clear();
    stepList2.clear();
    stepList3.clear();
    stepList4.clear();
    stepList5.clear();
    stepList6.clear();

    switchList.clear();
    m_list_utUnit.clear();
    m_list_txrxMode.clear();
    m_list_voltage.clear();
    m_list_prf.clear();
    m_list_filter.clear();
    m_list_rectifier.clear();
    m_list_averaging.clear();
    m_list_pointQty.clear();
    m_list_gate.clear();
    m_list_synchro.clear();
    m_list_measureMode.clear();
    m_list_alarm.clear();
    m_list_group.clear();
    m_list_condition.clear();
    m_list_operator.clear();
    m_list_output.clear();
    m_list_sound.clear();
    m_list_data.clear();
    m_list_mode.clear();
    m_list_curveX.clear();
    m_list_point.clear();
    m_list_group2.clear();
    m_list_display.clear();
    m_list_cScanSource.clear();
    m_list_scan.clear();
    m_list_color.clear();
    m_list_envelope.clear();
    m_list_cScanMode.clear();
    m_list_group3.clear();
    m_list_groupMode.clear();
    m_list_define.clear();
    m_list_skew.clear();
    m_list_geometry.clear();
    m_list_material.clear();
    m_list_lawType.clear();
    m_list_waveType.clear();
    m_list_type.clear();
    m_list_scan2.clear();
    m_list_type2.clear();
    m_list_encoder.clear();
    m_list_encoderType.clear();
    m_list_polarity.clear();
    m_list_selection.clear();
    m_list_select.clear();
    m_list_storage.clear();
    m_list_saveMode.clear();
    m_list_select2.clear();
    m_list_units.clear();

    delete ui;
}

void SubMenu::set_brightness(double value)
{
    m_brightness = value;

    pMcu->set_brightness((char)m_brightness);
}

void SubMenu::auto_detect_probe(QString string)
{
    if(string == "On"){
        pMcu->notify_started();
        pMcu->query_probe();
        connect(pMcu, SIGNAL(probe_event(const Probe&)), this, SLOT(do_probe_event(const Probe&)));
    }else{
    }
}

void SubMenu::do_probe_event(const Probe &probe)
{
    ui->subMenu_3->set_label_text(probe.model());
}

QList<int> SubMenu::get_dialog_value_list(QString string, QString symbol)
{
    QList<int> valueList;
    QString tmpString = string;
    int tmpIndex = 0;
    for(int i = 0; i < string.length(); i ++) {
        if(QString(string.at(i)) == symbol) {
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
