/**
 * @file sub_menu.cpp
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "sub_menu.h"

#include "probedialog.h"
#include "wedgedialog.h"
#include "inputpanelcontext.h"
#include "filemanagerdialog.h"
#include "sysinfo_dialog.h"
#include "about_dialog.h"
#include "resetconfigdialog.h"
#include "networkdialog.h"
#include "datetimesetdialog.h"

/* UT Settings */
#include "ut_setting/general_menu.h"
#include "ut_setting/pulser_menu.h"
#include "ut_setting/receiver_menu.h"
#include "ut_setting/ut_advanced_menu.h"

/* Gate/Curves */
#include "gate_curves/gate_menu.h"
#include "gate_curves/alarm_menu.h"
#include "gate_curves/output_menu.h"
#include "gate_curves/dac_menu.h"
#include "gate_curves/tcg_menu.h"

/* Display */
#include "display/display_selection_menu.h"
#include "display/color_setting_menu.h"
#include "display/properties_menu.h"

/* Probe/Part */
#include "probe_part/selection_menu.h"
#include "probe_part/position_menu.h"
#include "probe_part/fft_menu.h"
#include "probe_part/part_menu.h"
#include "probe_part/advanced_menu.h"

#include <QKeyEvent>
#include <QDebug>

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);

    QVBoxLayout *layout1 = new QVBoxLayout(ui->menuItem0);
    QVBoxLayout *layout2 = new QVBoxLayout(ui->menuItem1);
    QVBoxLayout *layout3 = new QVBoxLayout(ui->menuItem2);
    QVBoxLayout *layout4 = new QVBoxLayout(ui->menuItem3);
    QVBoxLayout *layout5 = new QVBoxLayout(ui->menuItem4);
    QVBoxLayout *layout6 = new QVBoxLayout(ui->menuItem5);
    layout1->setContentsMargins(0, 0, 0, 0);
    layout2->setContentsMargins(0, 0, 0, 0);
    layout3->setContentsMargins(0, 0, 0, 0);
    layout4->setContentsMargins(0, 0, 0, 0);
    layout5->setContentsMargins(0, 0, 0, 0);
    layout6->setContentsMargins(0, 0, 0, 0);

    switchList.append(tr("On"));
    switchList.append(tr("Off"));

    init_option_stringlist();
    init_step_list();
    init_map();  

    m_preType = MainMenu::UTSettings_Pulser;
    set_menu(MainMenu::UTSettings_General);
//    m_brightness = 50.0;
//    set_brightness(m_brightness);
}

void SubMenu::init_map()
{
    /* UT Setting */
    m_map.insert(MainMenu::UTSettings_General, new GeneralMenu(ui, this));
    m_map.insert(MainMenu::UTSettings_Pulser, new PulserMenu(ui, this));
    m_map.insert(MainMenu::UTSettings_Receiver, new ReceiverMenu(ui, this));
    m_map.insert(MainMenu::UTSettings_Advanced, new UtAdvancedMenu(ui, this));

    /* Gate/Curves */
    m_map.insert(MainMenu::GateCurves_Gate, new GateMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_Alarm, new AlarmMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_Output, new OutputMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_DAC, new DacMenu(ui, this));
    m_map.insert(MainMenu::GateCurves_TCG, new TcgMenu(ui, this));

    /* Display */
    m_map.insert(MainMenu::Display_Selection, new DisplaySelectionMenu(ui, this));
    m_map.insert(MainMenu::Display_ColorSettings, new ColorSettingMenu(ui, this));
    m_map.insert(MainMenu::Displsy_Properties, new PropertiesMenu(ui, this));

    /* Probe/Part */
    m_map.insert(MainMenu::ProbePart_Select,    new DplProbeMenu::SelectionMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_Position,  new DplProbeMenu::PositionMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_FFT,       new DplProbeMenu::FftMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_Part,      new DplProbeMenu::PartMenu(ui, this));
    m_map.insert(MainMenu::ProbePart_Advanced,  new DplProbeMenu::AdvancedMenu(ui, this));
//    m_map.insert(MainMenu::FocalLaw_LawConfig, &SubMenu::set_lawConfig_menu);
//    m_map.insert(MainMenu::FocalLaw_Angle, &SubMenu::set_angle_menu);
//    m_map.insert(MainMenu::FocalLaw_Apeture, &SubMenu::set_apeture_menu);
//    m_map.insert(MainMenu::FacalLaw_FocalPoint, &SubMenu::set_focalPoint_menu);
//    m_map.insert(MainMenu::Scan_Inspection, &SubMenu::set_inspection_menu);
//    m_map.insert(MainMenu::Scan_Encoder, &SubMenu::set_encoder_menu);
//    m_map.insert(MainMenu::Scan_Area, &SubMenu::set_area_menu);
//    m_map.insert(MainMenu::Scan_Start, &SubMenu::set_start_menu);
//    m_map.insert(MainMenu::Measurement_Cursors, &SubMenu::set_cursors_menu);
//    m_map.insert(MainMenu::Measurement_TOFD, &SubMenu::set_tofd_menu);
//    m_map.insert(MainMenu::Measurement_FlawRecord, &SubMenu::set_flawRecord_menu);
//    m_map.insert(MainMenu::FileReport_File, &SubMenu::set_file_menu);
//    m_map.insert(MainMenu::FileReport_SaveMode, &SubMenu::set_saveMode_menu);
//    m_map.insert(MainMenu::FileReport_Report, &SubMenu::set_report_menu);
//    m_map.insert(MainMenu::FileReport_Format, &SubMenu::set_format_menu);
//    m_map.insert(MainMenu::FileReport_UserField, &SubMenu::set_userField_menu);
//    m_map.insert(MainMenu::Preference_Preference, &SubMenu::set_preference_menu);
//    m_map.insert(MainMenu::Preference_System, &SubMenu::set_system_menu);
//    m_map.insert(MainMenu::Preference_Network, &SubMenu::set_network_menu);
//    m_map.insert(MainMenu::Preference_Service, &SubMenu::set_service_menu);
}


void SubMenu::set_menu(MainMenu::Type type)
{
    if (type == m_preType) {
        return;
    }

    BaseMenu *menu = m_map.value(m_preType);
    if (menu) {
        menu->hide();
    }

    menu = m_map.value(type);
    if(menu) {
        menu->show();
    }

    m_preType = type;
}

void SubMenu::set_lawConfig_menu(bool show)
{
//    if(show) {
//        /* Law Type Menu Item */
//        set_combobox_menu(ui->subMenu_1, tr("Law Type"), m_list_lawType);

//        /* Pulse Connection menu item */
//        QList<double> steps;
//        steps.append(1);
//        steps.append(10);
//        set_spinbox_menu(ui->subMenu_2, tr("Pulse Connection"), "mm", steps, 1, 113, 0);

//        /* Receiver Connection menu item */
//        set_spinbox_menu(ui->subMenu_3, tr("Receiver Connection"), "mm", steps, 1, 113, 0);

//        /* Wave Type Menu Item */
//        set_combobox_menu(ui->subMenu_4, tr("Wave Type"), m_list_waveType);

//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {

//    }
}

void SubMenu::set_angle_menu(bool show)
{
//    if(show) {
//        /* Min.Angle Menu Item */
//        QList<double> steps;
//        steps.append(1);
//        steps.append(5);
//        steps.append(10);
//        set_spinbox_menu(ui->subMenu_1, tr("Min.Angle"), "°", steps, 25, 75, 0);

//        /* Max.Angle Menu Item */
//        set_spinbox_menu(ui->subMenu_2, tr("Max.Angle"), "°", steps, 25, 75, 0);

//        /* Angle Step Menu Item */
//        QList<double> steps2;
//        steps2.append(1);
//        set_spinbox_menu(ui->subMenu_3, tr("Angle Step"), "°", steps2, 1, 10, 0);

//        ui->subMenu_4->set_type(MenuItem::None);
//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);

//        steps.clear();
//        steps2.clear();
//    } else {

//    }
}

void SubMenu::set_apeture_menu(bool show)
{
//    if(show) {
//        /* Apeture Menu Item */
//        QList<double> steps;
//        steps.append(1);
//        steps.append(5);
//        set_spinbox_menu(ui->subMenu_1, tr("Apeture"), "", steps, 0, 64, 0);

//        /* First Element menu item */
//        set_spinbox_menu(ui->subMenu_2, tr("First Element"), "", steps, 1, 64, 0);

//        /* Last Element menu item */
//        set_spinbox_menu(ui->subMenu_3, tr("Last Element"), "", steps, 1, 64, 0);

//        /* Element Step Menu Item */
//        set_spinbox_menu(ui->subMenu_4, tr("Element Step"), "", steps, 1, 32, 0);

//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//        steps.clear();
//    } else {

//    }
}

void SubMenu::set_focalPoint_menu(bool show)
{
//    if(show) {
//        /* Type Menu Item */
//        set_combobox_menu(ui->subMenu_1, tr("Type"), m_list_type);

//        /* Position Start menu item */
//        set_spinbox_menu(ui->subMenu_2, tr("Position Start"), "mm", stepList6, 0, 1000, 2);

//        /* Position End menu item */
//        set_spinbox_menu(ui->subMenu_3, tr("Position End"), "mm", stepList6, 1, 1000, 2);

//        /* Offset Start Menu Item */
//        set_spinbox_menu(ui->subMenu_4, tr("Offset Start"), "mm", stepList6, 0, 1000, 2);

//        /* Offset End Menu Item */
//        set_spinbox_menu(ui->subMenu_5, tr("Offset End"), "mm", stepList6, 1, 1000, 2);

//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {

//    }
}

void SubMenu::set_inspection_menu(bool show)
{
//    if(show) {
//        /* Scan Menu Item */
//        set_combobox_menu(ui->subMenu_1, tr("Scan"), m_list_scan2);

//        /* Type menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Type"), m_list_type2);

//        /* Max Scan Speed menu item */
//        set_spinbox_menu(ui->subMenu_3, tr("Max Scan Speed"), "m/s", stepList2, 0, 1000, 2);

//        /* Max Scan Speed(rpm) Menu Item */
//        set_spinbox_menu(ui->subMenu_4, tr("Max Scan Speed(rpm)"), "m/s", stepList2, 0, 1000, 0);

//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {

//    }
}

void SubMenu::set_encoder_menu(bool show)
{
//    if(show) {
//        /* Encoder Menu Item */
//        set_combobox_menu(ui->subMenu_1, tr("Encoder"), m_list_encoder);

//        /* Encoder Type menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Encoder Type"), m_list_encoderType);

//        /* Resolution menu item */
//        set_spinbox_menu(ui->subMenu_3, tr("Resolution"), "Step/mm", stepList2, 0.01, 10000, 2);

//        /* Polarity Menu Item */
//        set_combobox_menu(ui->subMenu_4, tr("Polarity"), m_list_polarity);

//        /* Origin Menu Item */
//        set_spinbox_menu(ui->subMenu_5, tr("Origin"), "mm", stepList2, 0, 1000, 2);

//        /* Preset Menu Item */
//        set_label_menu(ui->subMenu_6, tr("Preset"));
//    } else {

//    }
}

void SubMenu::set_area_menu(bool show)
{
//    if(show) {
//        /* Scan Start Menu Item */
//        QList<double> steps;
//        steps.append(10.00);
//        steps.append(100.00);
//        steps.append(1000.00);
//        steps.append(10000.00);
//        set_spinbox_menu(ui->subMenu_1, tr("Scan Start"), "mm", steps, 0, 10000, 2);

//        /* Scan End menu item */
//        set_spinbox_menu(ui->subMenu_2, tr("Scan End"), "mm", steps, 0, 10000, 2);

//        /* Scan Resolution menu item */
//        set_spinbox_menu(ui->subMenu_3, tr("Scan Resolution"), "mm", stepList6, 0, 100, 2);

//        /* Index Start Menu Item */
//        set_spinbox_menu(ui->subMenu_4, tr("Index Start"), "mm", steps, 0, 10000, 2);

//        /* Index End Menu Item */
//        set_spinbox_menu(ui->subMenu_5, tr("Index End"), "mm", steps, 0, 10000, 2);

//        /* Index Resolution Menu Item */
//        set_spinbox_menu(ui->subMenu_6, tr("Index Resolution"), "mm", stepList6, 0, 100, 2);
//        steps.clear();
//    } else {

//    }
}

void SubMenu::set_start_menu(bool show)
{
//    if(show) {
//        /* Start Menu Item */
//        set_spinbox_menu(ui->subMenu_1, tr("Scan"), "mm", stepList2, 0, 10000, 2);

//        /* Pause menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Pause"), switchList);

//        ui->subMenu_3->set_type(MenuItem::None);
//        ui->subMenu_4->set_type(MenuItem::None);
//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {

//    }
}

void SubMenu::set_cursors_menu(bool show)
{
//    if(show) {
//        QString option;
//        QList<double> steps1;
//        steps1.append(0.1);
//        steps1.append(1.0);
//        steps1.append(10.0);

//        QList<double> steps2;
//        steps2.append(0.1);
//        steps2.append(0.5);
//        steps2.append(1.0);
//        steps2.append(5.0);

//        /* Selection menu item */
//        set_combobox_menu(ui->subMenu_1, tr("Selection"), m_list_selection);

//        if(option == "A-Scan") {

//            /* %(r) menu item */
//            set_spinbox_menu(ui->subMenu_2, tr("%(r)"), "%", steps1, 0, 100, 1);

//            /* %(m) menu item */
//            set_spinbox_menu(ui->subMenu_3, tr("%(m)"), "%", steps1, 0, 100, 1);

//            /* U(r) menu item */
//            set_spinbox_menu(ui->subMenu_4, tr("U(r)"), "mm", stepList6, 0, 2000, 2);

//            /* U(m) menu item */
//            set_spinbox_menu(ui->subMenu_5, tr("U(m)"), "mm", stepList6, 0, 2000, 2);

//            ui->subMenu_6->set_type(MenuItem::None);
//        } else if(option == "B-Scan") {

//            /* S(r) menu item */
//            set_spinbox_menu(ui->subMenu_2, tr("S(r)"), "s", steps2, 0, 10000, 1);

//            /* S(m) menu item */
//            set_spinbox_menu(ui->subMenu_3, tr("S(m)"), "s", steps2, 0, 10000, 1);

//            /* U(r) menu item */
//            set_spinbox_menu(ui->subMenu_4, tr("U(r)"), "mm", stepList6, 0, 2000, 2);

//            /* U(m) menu item */
//            set_spinbox_menu(ui->subMenu_5, tr("U(m)"), "mm", stepList6, 0, 2000, 2);

//            ui->subMenu_6->set_type(MenuItem::None);

//        } else if(option == "C-Scan") {

//            /* S(r) menu item */
//            set_spinbox_menu(ui->subMenu_2, tr("S(r)"), "s", steps2, 0, 10000, 1);

//            /* S(m) menu item */
//            set_spinbox_menu(ui->subMenu_3, tr("S(m)"), "s", steps2, 0, 10000, 1);

//            /* I(r) menu item */
//            set_spinbox_menu(ui->subMenu_4, tr("I(r)"), "mm", steps2, 0, 2000, 1);

//            /* I(m) menu item */
//            set_spinbox_menu(ui->subMenu_5, tr("I(m)"), "mm", steps2, 0, 2000, 1);

//            ui->subMenu_6->set_type(MenuItem::None);

//        } else if(option == "S-Scan") {
//            /* Angle menu item */
//            QList<double> steps3;
//            steps3.append(1);
//            set_spinbox_menu(ui->subMenu_2, tr("Angle"), "°", steps3, 25, 75, 0);

//            /* U(r) menu item */
//            set_spinbox_menu(ui->subMenu_3, tr("U(r)"), "mm", stepList6, 0, 2000, 2);

//            /* U(m) menu item */
//            set_spinbox_menu(ui->subMenu_4, tr("U(m)"), "mm", stepList6, 0, 2000, 2);

//            /* I(r) menu item */
//            set_spinbox_menu(ui->subMenu_5, tr("I(r)"), "mm", steps2, 0, 2000, 1);

//            /* I(m) menu item */
//            set_spinbox_menu(ui->subMenu_6, tr("I(m)"), "mm", steps2, 0, 2000, 1);
//        }
//        steps1.clear();
//        steps2.clear();
//    } else {

//    }
}

void SubMenu::set_tofd_menu(bool show)
{
//    if(show) {
//        QString option;
//        QList<double> steps;
//        steps.append(0.1);
//        steps.append(1.0);
//        steps.append(10.0);
//        steps.append(100.0);

//        /* Select menu item */
//        set_combobox_menu(ui->subMenu_1, tr("Select"), m_list_select);

//        if(option == "TOFD Settings") {

//            /* Wedge Sep. menu item */
//            set_spinbox_menu(ui->subMenu_2, tr("Wedge Sep."), "mm", steps, 0, 10000, 1);

//            /* Layer Depth menu item */
//            set_label_menu(ui->subMenu_3, tr("Layer Depth"));

//            /* TOFD Calculator menu item */
//            set_label_menu(ui->subMenu_4, tr("TOFD Calculator"));

//            /* Start menu item */
//            set_spinbox_menu(ui->subMenu_5, tr("Start"), "mm", stepList2, 0, 16000, 2);

//            /* Range menu item */
//            set_spinbox_menu(ui->subMenu_6, tr("Range"), "mm", stepList2, 0, 16000, 2);
//        } else if(option == "TOFD Analysis") {

//            /* Straightening menu item */
//            set_combobox_menu(ui->subMenu_2, tr("Straightening"), switchList);

//            /* Remove Lateral menu item */
//            set_combobox_menu(ui->subMenu_3, tr("Remove Lateral"), switchList);

//            /* Ref.Position menu item */
//            set_spinbox_menu(ui->subMenu_4, tr("Ref.Position"), "mm", stepList6, 0, 2000, 2);

//            /* Depth Calibration menu item */
//            set_combobox_menu(ui->subMenu_5, tr("Depth Calibration"), switchList);

//            ui->subMenu_6->set_type(MenuItem::None);

//        }
//    } else {

//    }
}

void SubMenu::set_flawRecord_menu(bool show)
{
//    if(show) {
//        /* Add/Delete Menu Item */
//        set_label_menu(ui->subMenu_1, tr("Add/Delete"));

//        /* Flaw Image menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Flaw Image"), switchList);

//        /* Comment menu item */
//        set_label_menu(ui->subMenu_3, tr("Comment"));
//        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Display Table Menu Item */
//        set_combobox_menu(ui->subMenu_4, tr("Display Table"), switchList);

//        /* Export Record Menu Item */
//        set_label_menu(ui->subMenu_5, tr("Export Record"));

//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {
//        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//    }
}

void SubMenu::set_file_menu(bool show)
{
//    if(show) {
//        /* Save Setup As Menu Item */
//        set_label_menu(ui->subMenu_1, tr("Save Setup As"));

//        /* Open menu item */
//        set_label_menu(ui->subMenu_2, tr("Open"));

//        /* File Manager menu item */
//        set_label_menu(ui->subMenu_3, tr("File Manager"));
//        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_filemanager_dialog()));

//        ui->subMenu_4->set_type(MenuItem::None);
//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {
//        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_filemanager_dialog()));
//    }
}

void SubMenu::set_saveMode_menu(bool show)
{
//    if(show) {
//        /* Storage Menu Item */
//        set_combobox_menu(ui->subMenu_1, tr("Storage"), m_list_storage);

//        /* Save Mode menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Save Mode"), m_list_saveMode);

//        /* Save Data menu item */
//        set_label_menu(ui->subMenu_3, tr("Save Data"));

//        /* File Name menu item */
//        set_label_menu(ui->subMenu_4, tr("File Name"));
//        connect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {
//        disconnect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//    }
}

void SubMenu::set_report_menu(bool show)
{
//    if(show) {
//        /* Template Menu Item */
//        set_label_menu(ui->subMenu_1, tr("Template"));

//        /* Report Name menu item */
//        set_label_menu(ui->subMenu_2, tr("Report Name"));
//        connect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Customer menu item */
//        set_label_menu(ui->subMenu_3, tr("Customer"));
//        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Part Name Menu Item */
//        set_label_menu(ui->subMenu_4, tr("Part Name"));
//        connect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Part Number item */
//        set_label_menu(ui->subMenu_5, tr("Part Number"));
//        connect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Create menu item */
//        set_label_menu(ui->subMenu_6, tr("Create"));
//    } else {
//        disconnect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//        disconnect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//        disconnect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//    }
}

void SubMenu::set_format_menu(bool show)
{
//    if(show) {
//        /* Probe/Wedge Info Menu Item */
//        set_combobox_menu(ui->subMenu_1, tr("Probe/Wedge Info"), switchList);

//        /* Inspection Info menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Inspection Info"), switchList);

//        /* Scan Info menu item */
//        set_combobox_menu(ui->subMenu_3, tr("Scan Info"), switchList);

//        /* Encoder Info Menu Item */
//        set_combobox_menu(ui->subMenu_4, tr("Encoder Info"), switchList);

//        /* DAC/TCG Info Number item */
//        set_combobox_menu(ui->subMenu_5, tr("DAC/TCG Info"), switchList);

//        /* Flaw Record Table menu item */
//        set_combobox_menu(ui->subMenu_6, tr("Flaw Record Table"), switchList);
//    } else {

//    }
}

void SubMenu::set_userField_menu(bool show)
{
//    if(show) {
//        /* Select Menu Item */
//        set_combobox_menu(ui->subMenu_1, tr("Select"), m_list_select2);

//        /* Enable menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Enable"), switchList);

//        /* Label menu item */
//        set_label_menu(ui->subMenu_3, tr("Label"));
//        connect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Content Menu Item */
//        set_label_menu(ui->subMenu_4, tr("Content"));
//        connect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Edit Note Number item */
//        set_label_menu(ui->subMenu_5, tr("Edit Note"));
//        connect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));

//        /* Print menu item */
//        set_label_menu(ui->subMenu_6, tr("Print"));
//    } else {
//        disconnect(ui->subMenu_3, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//        disconnect(ui->subMenu_4, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//        disconnect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_input_dialog()));
//    }
}

void SubMenu::set_preference_menu(bool show)
{
//    if(show) {
//        /* Units menu item */
//        set_combobox_menu(ui->subMenu_1, tr("Units"), m_list_units);

//        /* Bright menu item */
//        QList<double> steps;
//        steps.append(1);
//        steps.append(10);
//        set_spinbox_menu(ui->subMenu_2, tr("Bright"), "%", steps, 1, 100, 0);
//        connect(ui->subMenu_2, SIGNAL(spin_event(double)), this, SLOT(set_brightness(double)));

//        /* Opacity menu item */
//        set_spinbox_menu(ui->subMenu_3, tr("Opacity"), "%", steps, 1, 100, 0);

//        ui->subMenu_4->set_type(MenuItem::None);
//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);

//        steps.clear();
//    } else {
//        disconnect(ui->subMenu_2, SIGNAL(spin_event(double)), this, SLOT(set_brightness(double)));
//    }
}

void SubMenu::set_system_menu(bool show)
{
//    if(show) {

//        /* Clock Set menu item */
//        set_label_menu(ui->subMenu_1, tr("Clock Set"));
//        connect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_time_dialog()));
//        ui->subMenu_1->set_label_text(QTime::currentTime().toString("hh:mm:ss"));

//        /* Date Set menu item */
//        set_label_menu(ui->subMenu_2, tr("Date Set"));
//        connect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_date_dialog()));
//        ui->subMenu_2->set_label_text(QDate::currentDate().toString("yyyy-MM-dd"));

//        /* Language menu item */
//        set_combobox_menu(ui->subMenu_3, tr("Language"), m_list_language);

//        ui->subMenu_4->set_type(MenuItem::None);
//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {
//        disconnect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_time_dialog()));
//        disconnect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_date_dialog()));
//    }
}

void SubMenu::set_network_menu(bool show)
{
//    if(show) {

//        /* IP Address menu item */
//        set_label_menu(ui->subMenu_1, tr("IP Address"));
//        connect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_ip_address_dialog()));
//        ui->subMenu_1->set_label_text("192.168.1.1");

//        /* Subnet Mask menu item */
//        set_label_menu(ui->subMenu_2, tr("Subnet Mask"));
//        connect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_subnet_mask_dialog()));
//        ui->subMenu_2->set_label_text("255.255.255.0");

//        ui->subMenu_3->set_type(MenuItem::None);
//        ui->subMenu_4->set_type(MenuItem::None);
//        ui->subMenu_5->set_type(MenuItem::None);
//        ui->subMenu_6->set_type(MenuItem::None);
//    } else {
//        disconnect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_ip_address_dialog()));
//        disconnect(ui->subMenu_2, SIGNAL(clicked()), this, SLOT(show_subnet_mask_dialog()));
//    }
}

void SubMenu::set_service_menu(bool show)
{
//    if(show) {
//        /* System Information Menu Item */
//        set_label_menu(ui->subMenu_1, tr("System Information"));
//        connect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_info_dialog()));

//        /* Cert Import menu item */
//        set_combobox_menu(ui->subMenu_2, tr("Cert Import"), m_list_certImport);

//        /* SW Update menu item */
//        set_label_menu(ui->subMenu_3, tr("SW Update"));

//        /* HW Update Menu Item */
//        set_label_menu(ui->subMenu_4, tr("HW Update"));

//        /* Reset Configuration Number item */
//        set_label_menu(ui->subMenu_5, tr("Reset Configuration"));
//        connect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));

//        /* About menu item */
//        set_label_menu(ui->subMenu_6, tr("About"));
//        connect(ui->subMenu_6, SIGNAL(clicked()), this, SLOT(show_about_dialog()));
//    } else {
//        disconnect(ui->subMenu_1, SIGNAL(clicked()), this, SLOT(show_info_dialog()));
//        disconnect(ui->subMenu_5, SIGNAL(clicked()), this, SLOT(show_resetconfig_dialog()));
//        disconnect(ui->subMenu_6, SIGNAL(clicked()), this, SLOT(show_about_dialog()));
//    }
}

void SubMenu::init_option_stringlist()
{
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

void SubMenu::show_input_dialog()
{
//    InputPanelContext inputPanel;
//    MenuItem *widget = qobject_cast<MenuItem*>(sender());
//    inputPanel.set_item_current_text(widget->get_label_text());
//    inputPanel.exec();
//    widget->set_label_text(inputPanel.get_text());
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
//    map.insert("IP Address", ui->subMenu_1->get_title());
    ipAddress->set_dialog_title(map);
//    ipAddress->set_spinbox_value(get_dialog_value_list(ui->subMenu_1->get_label_text(), QString(".")));
    ipAddress->exec();
//    ui->subMenu_1->set_label_text(ipAddress->get_ip());
    delete ipAddress;
}

void SubMenu::show_subnet_mask_dialog()
{
    NetworkDialog *subnetMask = new NetworkDialog(this);
    QMap<QString, QString> map;
//    map.insert("Subnet Mask", ui->subMenu_2->get_title());
    subnetMask->set_dialog_title(map);
//    subnetMask->set_spinbox_value(get_dialog_value_list(ui->subMenu_2->get_label_text(), QString(".")));
    subnetMask->exec();
//    ui->subMenu_2->set_label_text(subnetMask->get_subnet());
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
//    map.insert("Clock Set", ui->subMenu_1->get_title());
    timeDialog->set_dialog_title(map);
//    timeDialog->set_spinbox_value(get_dialog_value_list(ui->subMenu_1->get_label_text(), QString(":")));
    timeDialog->exec();
//    ui->subMenu_1->set_label_text(timeDialog->get_time());
    delete timeDialog;
}

void SubMenu::show_date_dialog()
{
    DateTimeSetDialog *dateDialog = new DateTimeSetDialog(this);
    QMap<QString, QString> map;
//    map.insert("Date Set", ui->subMenu_2->get_title());
    dateDialog->set_dialog_title(map);
//    dateDialog->set_spinbox_value(get_dialog_value_list(ui->subMenu_2->get_label_text(), QString("-")));
    dateDialog->exec();
//    ui->subMenu_2->set_label_text(dateDialog->get_date());
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
//    ui->subMenu_3->set_label_text(probe.model());
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
