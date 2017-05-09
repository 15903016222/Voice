/**
 * @file sub_menu.cpp
 * @brief Third menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "sub_menu.h"

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseMenu),
    m_generalMenu(ui, this),
    m_pulserMenu(ui, this),
    m_receiverMenu(ui, this),
    m_utAdvanceMenu(ui, this),
    m_gateMenu(ui, this),
    m_alarmMenu(ui, this),
    m_outputMenu(ui, this),
    m_dacMenu(ui, this),
    m_tcgMenu(ui, this),
    m_selectionMenu(ui, this),
    m_colorSettingMenu(ui, this),
    m_propertiesMenu(ui, this),
    m_probeSelectionMenu(ui, this),
    m_positionMenu(ui, this),
    m_fftMenu(ui, this),
    m_partMenu(ui, this),
    m_advanceMenu(ui, this),
    m_lawConfigMenu(ui, this),
    m_angleMenu(ui, this),
    m_apetureMenu(ui, this),
    m_focalPointMenu(ui, this),
    m_inspectionMenu(ui, this),
    m_encoderMenu(ui, this),
    m_areaMenu(ui, this),
    m_startmenu(ui, this),
    m_cursorsMenu(ui, this),
    m_tofdMenu(ui, this),
    m_flawRecordMenu(ui, this),
    m_fileMenu(ui, this),
    m_saveModeMenu(ui, this),
    m_reportMenu(ui, this),
    m_formatmenu(ui, this),
    m_userFieldMenu(ui, this),
    m_preferenceMenu(ui, this),
    m_systemMenu(ui, this),
    m_networkMenu(ui, this)
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

    init_map();  

    m_preType = MainMenu::UTSettings_Pulser;
    set_menu(MainMenu::UTSettings_General);

    m_opacityEffect = new QGraphicsOpacityEffect;
    set_opacity_main_menu(80);
}

void SubMenu::init_map()
{
    /* UT Setting */
    m_map.insert(MainMenu::UTSettings_General,  &m_generalMenu);
    m_map.insert(MainMenu::UTSettings_Pulser,   &m_pulserMenu);
    m_map.insert(MainMenu::UTSettings_Receiver, &m_receiverMenu);
    m_map.insert(MainMenu::UTSettings_Advanced, &m_utAdvanceMenu);

    /* Gate/Curves */
    m_map.insert(MainMenu::GateCurves_Gate,     &m_gateMenu);
    m_map.insert(MainMenu::GateCurves_Alarm,    &m_alarmMenu);
    m_map.insert(MainMenu::GateCurves_Output,   &m_outputMenu);
    m_map.insert(MainMenu::GateCurves_DAC,      &m_dacMenu);
    m_map.insert(MainMenu::GateCurves_TCG,      &m_tcgMenu);

    /* Display */
    m_map.insert(MainMenu::Display_Selection,   &m_selectionMenu);
    m_map.insert(MainMenu::Display_ColorSettings,   &m_colorSettingMenu);
    m_map.insert(MainMenu::Displsy_Properties,  &m_propertiesMenu);

    /* Probe/Part */
    m_map.insert(MainMenu::ProbePart_Select,    &m_probeSelectionMenu);
    m_map.insert(MainMenu::ProbePart_Position,  &m_positionMenu);
    m_map.insert(MainMenu::ProbePart_FFT,       &m_fftMenu);
    m_map.insert(MainMenu::ProbePart_Part,      &m_partMenu);
    m_map.insert(MainMenu::ProbePart_Advanced,  &m_advanceMenu);

    /* Focal Law */
    m_map.insert(MainMenu::FocalLaw_LawConfig,  &m_lawConfigMenu);
    m_map.insert(MainMenu::FocalLaw_Angle,      &m_angleMenu);
    m_map.insert(MainMenu::FocalLaw_Apeture,    &m_apetureMenu);
    m_map.insert(MainMenu::FacalLaw_FocalPoint, &m_focalPointMenu);

    /* Scan */
    m_map.insert(MainMenu::Scan_Inspection,     &m_inspectionMenu);
    m_map.insert(MainMenu::Scan_Encoder,        &m_encoderMenu);
    m_map.insert(MainMenu::Scan_Area,           &m_areaMenu);
    m_map.insert(MainMenu::Scan_Start,          &m_startmenu);

    /* Measurement */
    m_map.insert(MainMenu::Measurement_Cursors, &m_cursorsMenu);
    m_map.insert(MainMenu::Measurement_TOFD,    &m_tofdMenu);
    m_map.insert(MainMenu::Measurement_FlawRecord,  &m_flawRecordMenu);

    /* File/Report */
    m_map.insert(MainMenu::FileReport_File,     &m_fileMenu);
    m_map.insert(MainMenu::FileReport_SaveMode, &m_saveModeMenu);
    m_map.insert(MainMenu::FileReport_Report,   &m_reportMenu);
    m_map.insert(MainMenu::FileReport_Format,   &m_formatmenu);
    m_map.insert(MainMenu::FileReport_UserField,&m_userFieldMenu);

    /* Preference */
    m_map.insert(MainMenu::Preference_Preference, &m_preferenceMenu);
    m_map.insert(MainMenu::Preference_System,   &m_systemMenu);
    m_map.insert(MainMenu::Preference_Network,  &m_networkMenu);
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

SubMenu::~SubMenu()
{
    delete ui;
}

void SubMenu::set_opacity_main_menu(double value)
{
    qreal alpha = value / 100;
    m_opacityEffect->setOpacity(alpha);
    ui->widget->setGraphicsEffect(m_opacityEffect);
}
