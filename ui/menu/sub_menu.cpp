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

    for(int i = 0; i < MATERIAL_NUMBER; i ++) {
        materialList.append(MATERIAL_STRING[i]);
    }

    switchList;
    switchList.append(tr("On"));
    switchList.append(tr("Off"));

    init_map();

    menuConfig = new MenuConfig;
    pNetworkDialog = new NetworkDialog(this);
    pDateTimeSetDialog = new DateTimeSetDialog(this);

//    current.insert("UT Settings", "General");
    m_typeMap.insert("current", Type::UTSettings_General);
    set_third_menu(1);
//    set_third_menu_and_connect(current.keys().at(0), current.values().at(0));
//    connect_current_signal(ui->subMenu_1, "UT Settings", "General", MenuItem::Spin);
//    set_general_menu();

}

SubMenu::~SubMenu()
{
    delete ui;
}

void SubMenu::init_map()
{
//    m_map.insert(UTSettings_General, &SubMenu::set_general_menu);

    m_map[UTSettings_General] = &SubMenu::set_general_menu;
    m_map[UTSettings_Pulser] = &SubMenu::set_pulser_menu;
    m_map[UTSettings_Receiver] = &SubMenu::set_receiver_menu;
    m_map[UTSettings_Advanced] = &SubMenu::set_advanced_menu;

    m_map[GateCurves_Gate] = &SubMenu::set_gate_menu;
    m_map[GateCurves_Alarm] = &SubMenu::set_alarm_menu;
    m_map[GateCurves_Output] = &SubMenu::set_output_menu;
    m_map[GateCurves_DAC] = &SubMenu::set_dac_menu;
    m_map[GateCurves_TCG] = &SubMenu::set_tcg_menu;

    m_map[Display_Selection] = &SubMenu::set_selection_menu;
    m_map[Display_ColorSettings] = &SubMenu::set_colorSettings_menu;
    m_map[Displsy_Properties] = &SubMenu::set_properties_menu;

    m_map[ProbePart_Select] = &SubMenu::set_select_menu;
    m_map[ProbePart_Position] = &SubMenu::set_position_menu;
    m_map[ProbePart_FFT] = &SubMenu::set_fft_menu;
    m_map[ProbePart_Part] = &SubMenu::set_part_menu;
    m_map[ProbePart_Advanced] = &SubMenu::set_advanced_2_menu;

    m_map[FocalLaw_LawConfig] = &SubMenu::set_lawConfig_menu;
    m_map[FocalLaw_Angle] = &SubMenu::set_angle_menu;
    m_map[FocalLaw_Apeture] = &SubMenu::set_apeture_menu;
    m_map[FacalLaw_FocalPoint] = &SubMenu::set_focalPoint_menu;

    m_map[Scan_Inspection] = &SubMenu::set_inspection_menu;
    m_map[Scan_Encoder] = &SubMenu::set_encoder_menu;
    m_map[Scan_Area] = &SubMenu::set_area_menu;
    m_map[Scan_Start] = &SubMenu::set_start_menu;

    m_map[Measurement_Cursors] = &SubMenu::set_cursors_menu;
    m_map[Measurement_TOFD] = &SubMenu::set_tofd_menu;
    m_map[Measurement_FlawRecord] = &SubMenu::set_flawRecord_menu;

    m_map[FileReport_File] = &SubMenu::set_file_menu;
    m_map[FileReport_SaveMode] = &SubMenu::set_saveMode_menu;
    m_map[FileReport_Report] = &SubMenu::set_report_menu;
    m_map[FileReport_Format] = &SubMenu::set_format_menu;
    m_map[FileReport_UserField] = &SubMenu::set_userField_menu;

    m_map[Preference_Preference] = &SubMenu::set_preference_menu;
    m_map[Preference_System] = &SubMenu::set_system_menu;
    m_map[Preference_Network] = &SubMenu::set_network_menu;
    m_map[Preference_Service] = &SubMenu::set_service_menu;
}

void SubMenu::set_third_menu(int num)
{
    for(int i = 0; i < 6; i ++) {
        MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
        widget->clean();
    }
    run_fun((Type)num);
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

void SubMenu::run_fun(Type type)
{
    QMap<Type, Function>::const_iterator it = m_map.find(type);
    if(it != m_map.end()) {
        Function pFun = m_map.value(type);
        if(pFun) {
            return (this->*pFun)();
        }
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

void SubMenu::get_second_menu_string(Type type)
{
    if(m_typeMap.find("previous") != m_typeMap.end()) {
        m_typeMap.remove("prevoius");
    }
    m_typeMap.insert("previous", m_typeMap.value("current"));
    m_typeMap.remove("current");
    m_typeMap.insert("current", type);
}

void SubMenu::connect_current_signal(MenuItem *widget, QString str2, QString str3, MenuItem::Type type)
{
    if(type == MenuItem::Spin) {
//        connect(widget, SIGNAL(spin_event(double)), , SLOT());
    } else if(type == MenuItem::Combo) {
//        connect(widget, SIGNAL(combo_event(double)), , SLOT());
    } else {
//        connect(widget, SIGNAL(click()), , SLOT());
//        if(str2 == "Select" && str3 == "Probe") {
//            QByteArray ba = DIALOG_STRING[0].toLatin1();
//            char *ch = ba.data();
//            qDebug() << ch;
//            connect(widget, SIGNAL(clicked()), this, ch);

//        }
    }

    qDebug()<<SIGNAL(clicked());
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
    set_combobox_menu(ui->subMenu_4, tr("Video Filter"), switchList);

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
    set_combobox_menu(ui->subMenu_1, tr("Set 80%"), switchList);

    /* dB Ref. menu item */
    set_combobox_menu(ui->subMenu_2, tr("dB Ref."), switchList);

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
    set_combobox_menu(ui->subMenu_2, tr("Switch"), switchList);

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
    steps.append(1.00);
    steps.append(10.00);
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
    steps.append(1.00);
    steps.append(10.00);
    set_spinbox_menu(ui->subMenu_4, tr("Min.Thickness"), "mm", steps, 0.05, 20000, 2);

    /* Max.Thickness menu item */
    set_spinbox_menu(ui->subMenu_5, tr("Max.Thickness"), "mm", steps, 0.06, 20000, 2);

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
    /* Group menu item */
    QStringList option1;
    option1.append(tr("Add"));
    option1.append(tr("1"));
    option1.append(tr("2"));
    option1.append(tr("3"));
    option1.append(tr("4"));
    option1.append(tr("5"));
    option1.append(tr("6"));
    option1.append(tr("7"));
    option1.append(tr("8"));
    option1.append(tr("Remove"));
    set_combobox_menu(ui->subMenu_1, tr("Group"), option1);

    /* Group Mode menu item */
    QStringList option2;
    option2.append(tr("UT (PA Connector)"));
    option2.append(tr("PA (Phassed Array)"));
    option2.append(tr("UT1 (Conventional UT)"));
    option2.append(tr("UT2 (Conventional UT)"));
    set_combobox_menu(ui->subMenu_2, tr("Group Mode"), option2);

    /* Probe menu item */
    set_label_menu(ui->subMenu_3, tr("Probe"));

    /* Wedge menu item */
    set_label_menu(ui->subMenu_4, tr("Wedge"));

    /* Define menu item */
    QStringList option3;
    option3.append(tr("Probe"));
    option3.append(tr("Wedge"));
    set_combobox_menu(ui->subMenu_5, tr("Define"), option3);

    /* Auto Detect menu item */
    set_combobox_menu(ui->subMenu_6, tr("Auto Detect"), switchList);
}

void SubMenu::set_position_menu()
{
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
    QStringList option;
    option.append("0°");
    option.append("90°");
    option.append("180°");
    option.append("270°");
    set_combobox_menu(ui->subMenu_3, tr("Skew"), option);

    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu:: set_fft_menu()
{
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
}

void SubMenu::set_part_menu()
{
    /* Geometry menu item */
    QStringList option1;
    option1.append(tr("Plate"));
    option1.append(tr("ID"));
    option1.append(tr("OD"));
    set_combobox_menu(ui->subMenu_1, tr("Geometry"), option1);

    /* Thickness menu item */
    QList<double> steps;
    steps.append(0.10);
    steps.append(1.00);
    steps.append(10.00);
    set_spinbox_menu(ui->subMenu_2, tr("Thickness"), "mm", steps, 0.05, 1000, 2);

    /* Diameter menu item */
    set_spinbox_menu(ui->subMenu_3, tr("Diameter"), "mm", steps, 0.05, 525, 2);

    /* Material menu item */
    set_combobox_menu(ui->subMenu_4, tr("Material"), materialList);

    /* Overlay menu item */
    set_combobox_menu(ui->subMenu_5, tr("Overlay"), switchList);

    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_advanced_2_menu()
{
    /* Load Part menu item */
    set_label_menu(ui->subMenu_1, tr("Load Part"));

    /* Clear Part menu item */
    set_label_menu(ui->subMenu_2, tr("Clear Part"));

    ui->subMenu_3->set_type(MenuItem::None);
    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_lawConfig_menu()
{
    /* Law Type Menu Item */
    QStringList option1;
    option1.append(tr("Azimuthal"));
    option1.append(tr("Linear"));
    set_combobox_menu(ui->subMenu_1, tr("Law Type"), option1);

    /* Pulse Connection menu item */
    QList<double> steps;
    steps.append(1);
    steps.append(10);
    set_spinbox_menu(ui->subMenu_2, tr("Pulse Connection"), "mm", steps, 1, 113, 0);

    /* Receiver Connection menu item */
    set_spinbox_menu(ui->subMenu_3, tr("Receiver Connection"), "mm", steps, 1, 113, 0);

    /* Wave Type Menu Item */
    QStringList option2;
    option2.append(tr("LW"));
    option2.append(tr("SW"));
    set_combobox_menu(ui->subMenu_4, tr("Wave Type"), option2);

    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_angle_menu()
{
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

}

void SubMenu::set_apeture_menu()
{
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
}

void SubMenu::set_focalPoint_menu()
{
    /* Type Menu Item */
    QStringList option1;
    option1.append(tr("True Depth"));
    option1.append(tr("Half Path"));
    option1.append(tr("Projection"));
    option1.append(tr("Focal Plane"));
    option1.append(tr("DDF"));
    set_combobox_menu(ui->subMenu_1, tr("Type"), option1);

    /* Position Start menu item */
    QList<double> steps;
    steps.append(0.01);
    steps.append(0.10);
    steps.append(1.00);
    steps.append(10.00);
    set_spinbox_menu(ui->subMenu_2, tr("Position Start"), "mm", steps, 0, 1000, 2);

    /* Position End menu item */
    set_spinbox_menu(ui->subMenu_3, tr("Position End"), "mm", steps, 1, 1000, 2);

    /* Offset Start Menu Item */
    set_spinbox_menu(ui->subMenu_4, tr("Offset Start"), "mm", steps, 0, 1000, 2);

    /* Offset End Menu Item */
    set_spinbox_menu(ui->subMenu_5, tr("Offset End"), "mm", steps, 1, 1000, 2);

    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_inspection_menu()
{
    /* Scan Menu Item */
    QStringList option1;
    option1.append(tr("Time"));
    option1.append(tr("Encoder 1"));
    option1.append(tr("Encoder 2"));
    set_combobox_menu(ui->subMenu_1, tr("Scan"), option1);

    /* Type menu item */
    QStringList option2;
    option2.append(tr("One Line"));
    option2.append(tr("Raster Scan"));
    option2.append(tr("Helicoidal Scan"));
    set_combobox_menu(ui->subMenu_2, tr("Type"), option2);

    /* Max Scan Speed menu item */
    set_spinbox_menu(ui->subMenu_3, tr("Max Scan Speed"), "m/s", stepList2, 0, 1000, 2);

    /* Max Scan Speed(rpm) Menu Item */
    set_spinbox_menu(ui->subMenu_4, tr("Max Scan Speed(rpm)"), "m/s", stepList2, 0, 1000, 0);

    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_encoder_menu()
{
    /* Encoder Menu Item */
    QStringList option1;
    option1.append(tr("Encoder 1"));
    option1.append(tr("Encoder 2"));
    set_combobox_menu(ui->subMenu_1, tr("Encoder"), option1);

    /* Encoder Type menu item */
    QStringList option2;
    option2.append(tr("Up"));
    option2.append(tr("Down"));
    option2.append(tr("Quad"));
    set_combobox_menu(ui->subMenu_2, tr("Encoder Type"), option2);

    /* Resolution menu item */
    set_spinbox_menu(ui->subMenu_3, tr("Resolution"), "Step/mm", stepList2, 0.01, 10000, 2);

    /* Polarity Menu Item */
    QStringList option3;
    option3.append(tr("Normal"));
    option3.append(tr("Reverse"));
    set_combobox_menu(ui->subMenu_4, tr("Polarity"), option3);

    /* Origin Menu Item */
    set_spinbox_menu(ui->subMenu_5, tr("Origin"), "mm", stepList2, 0, 1000, 2);

    /* Preset Menu Item */
    set_label_menu(ui->subMenu_6, tr("Preset"));
}

void SubMenu::set_area_menu()
{
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
    QList<double> steps2;
    steps2.append(0.01);
    steps2.append(0.10);
    steps2.append(1.00);
    steps2.append(10.00);
    set_spinbox_menu(ui->subMenu_3, tr("Scan Resolution"), "mm", steps2, 0, 100, 2);

    /* Index Start Menu Item */
    set_spinbox_menu(ui->subMenu_4, tr("Index Start"), "mm", steps, 0, 10000, 2);

    /* Index End Menu Item */
    set_spinbox_menu(ui->subMenu_5, tr("Index End"), "mm", steps, 0, 10000, 2);

    /* Index Resolution Menu Item */
    set_spinbox_menu(ui->subMenu_6, tr("Index Resolution"), "mm", steps2, 0, 100, 2);
}

void SubMenu::set_start_menu()
{
    /* Start Menu Item */
    set_spinbox_menu(ui->subMenu_1, tr("Scan"), "mm", stepList2, 0, 10000, 2);

    /* Pause menu item */
    set_combobox_menu(ui->subMenu_2, tr("Pause"), switchList);

    ui->subMenu_3->set_type(MenuItem::None);
    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_cursors_menu()
{

}

void SubMenu::set_tofd_menu()
{

}

void SubMenu::set_flawRecord_menu()
{
    /* Add/Delete Menu Item */
    set_label_menu(ui->subMenu_1, tr("Add/Delete"));

    /* Flaw Image menu item */
    set_combobox_menu(ui->subMenu_2, tr("Flaw Image"), switchList);

    /* Comment menu item */
    set_label_menu(ui->subMenu_3, tr("Comment"));

    /* Display Table Menu Item */
    set_combobox_menu(ui->subMenu_4, tr("Display Table"), switchList);

    /* Export Record Menu Item */
    set_label_menu(ui->subMenu_5, tr("Export Record"));

    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_file_menu()
{
    /* Save Setup As Menu Item */
    set_label_menu(ui->subMenu_1, tr("Save Setup As"));

    /* Open menu item */
    set_label_menu(ui->subMenu_2, tr("Open"));

    /* File Manager menu item */
    set_label_menu(ui->subMenu_3, tr("File Manager"));

    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_saveMode_menu()
{
    /* Storage Menu Item */
    QStringList option1;
    option1.append(tr("SD"));
    option1.append(tr("SSG"));
    option1.append(tr("U Storage"));
    set_combobox_menu(ui->subMenu_1, tr("Storage"), option1);

    /* Save Mode menu item */
    QStringList option2;
    option2.append(tr("Inspection Data"));
    option2.append(tr("Inspection Table"));
    option2.append(tr("Screen"));
    option2.append(tr("Report"));
    set_combobox_menu(ui->subMenu_2, tr("Save Mode"), option2);

    /* Save Data menu item */
    set_label_menu(ui->subMenu_3, tr("Save Data"));

    /* File Name menu item */
    set_label_menu(ui->subMenu_4, tr("File Name"));

    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_report_menu()
{
    /* Template Menu Item */
    set_label_menu(ui->subMenu_1, tr("Template"));

    /* Report Name menu item */
    set_label_menu(ui->subMenu_2, tr("Report Name"));

    /* Customer menu item */
    set_label_menu(ui->subMenu_3, tr("Customer"));

    /* Part Name Menu Item */
    set_label_menu(ui->subMenu_4, tr("Part Name"));

    /* Part Number item */
    set_label_menu(ui->subMenu_5, tr("Part Number"));

    /* Create menu item */
    set_label_menu(ui->subMenu_6, tr("Create"));
}

void SubMenu::set_format_menu()
{
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
}

void SubMenu::set_userField_menu()
{
    /* Select Menu Item */
    QStringList option1;
    option1.append("1");
    option1.append("2");
    option1.append("3");
    option1.append("4");
    option1.append("5");
    option1.append("6");
    option1.append("7");
    option1.append("8");
    option1.append("9");
    option1.append("10");
    set_combobox_menu(ui->subMenu_1, tr("Select"), option1);

    /* Enable menu item */
    set_combobox_menu(ui->subMenu_2, tr("Enable"), switchList);

    /* Label menu item */
    set_label_menu(ui->subMenu_3, tr("Label"));

    /* Content Menu Item */
    set_label_menu(ui->subMenu_4, tr("Content"));

    /* Edit Note Number item */
    set_label_menu(ui->subMenu_5, tr("Edit Note"));

    /* Print menu item */
    set_label_menu(ui->subMenu_6, tr("Print"));
}

void SubMenu::set_preference_menu()
{
    /* Units menu item */
    QStringList option1;
    option1.append("Millimeters");
    option1.append("Inches");
    set_combobox_menu(ui->subMenu_1, tr("Units"), option1);

    /* Bright menu item */
    QList<double> steps;
    steps.append(1);
    steps.append(10);
    set_spinbox_menu(ui->subMenu_2, tr("Bright"), "%", steps, 1, 100, 0);

    /* Opacity menu item */
    set_spinbox_menu(ui->subMenu_3, tr("Opacity"), "%", steps, 1, 100, 0);

    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_system_menu()
{
    /* Clock Set menu item */
    set_label_menu(ui->subMenu_1, tr("Clock Set"));

    /* Date Set menu item */
    set_label_menu(ui->subMenu_2, tr("Date Set"));

    /* Language menu item */
    QStringList option1;
    option1.append("English");
    option1.append("Chinese");
    set_combobox_menu(ui->subMenu_3, tr("Language"), option1);

    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_network_menu()
{
    /* IP Address menu item */
    set_label_menu(ui->subMenu_1, tr("IP Address"));

    /* Subnet Mask menu item */
    set_label_menu(ui->subMenu_2, tr("Subnet Mask"));

    ui->subMenu_3->set_type(MenuItem::None);
    ui->subMenu_4->set_type(MenuItem::None);
    ui->subMenu_5->set_type(MenuItem::None);
    ui->subMenu_6->set_type(MenuItem::None);
}

void SubMenu::set_service_menu()
{
    /* System Information Menu Item */
    set_label_menu(ui->subMenu_1, tr("System Information"));

    /* Cert Import menu item */
    QStringList option;
    option.append(tr("U-Disk"));
    option.append(tr("Network"));
    set_combobox_menu(ui->subMenu_2, tr("Cert Import"), option);

    /* SW Update menu item */
    set_label_menu(ui->subMenu_3, tr("SW Update"));

    /* HW Update Menu Item */
    set_label_menu(ui->subMenu_4, tr("HW Update"));

    /* Reset Configuration Number item */
    set_label_menu(ui->subMenu_5, tr("Reset Configuration"));

    /* About menu item */
    set_label_menu(ui->subMenu_6, tr("About"));
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
