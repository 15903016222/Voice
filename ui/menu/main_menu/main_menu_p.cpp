#include "main_menu_p.h"

#define ITEM_HEIHT (45)

MainMenuPrivate::MainMenuPrivate(MainMenu *parent) : QObject(parent),
    m_mainMenu(new QListWidget(parent)),
    m_utSettingMenu(new QListWidget(parent)),
    m_gateCurvesMenu(new QListWidget(parent)),
    m_displayMenu(new QListWidget(parent)),
    m_probePartMenu(new QListWidget(parent)),
    m_focallawMenu(new QListWidget(parent)),
    m_scanMenu(new QListWidget(parent)),
    m_measureMenu(new QListWidget(parent)),
    m_fileReportMenu(new QListWidget(parent)),
    m_preferenceMenu(new QListWidget(parent)),
    m_curSubMenu(m_utSettingMenu),
    m_topSpaceItem(new QSpacerItem(20, 100, QSizePolicy::Maximum, QSizePolicy::Expanding))
{
    init_mainMenu();
    init_utSettingMenu();
    init_gateCurevesMenu();
    init_displayMenu();
    init_probePartMenu();
    init_focallawMenu();
    init_scanMenu();
    init_measureMenu();
    init_fileReportMenu();
    init_preferenceMenu();
}

void MainMenuPrivate::set_opacity(double val)
{
    static_cast<QGraphicsOpacityEffect *>(m_mainMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_utSettingMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_gateCurvesMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_displayMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_probePartMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_focallawMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_scanMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_measureMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_fileReportMenu->graphicsEffect())->setOpacity(val/100);
    static_cast<QGraphicsOpacityEffect *>(m_preferenceMenu->graphicsEffect())->setOpacity(val/100);
}

void MainMenuPrivate::do_currentRowChanged(int row)
{
    m_curSubMenu->hide();
    if (row == 0) {
        m_curSubMenu = m_utSettingMenu;
    } else if (row == 1) {
        m_curSubMenu = m_gateCurvesMenu;
    } else if (row == 2) {
        m_curSubMenu = m_displayMenu;
    } else if (row == 3) {
        m_curSubMenu = m_probePartMenu;
    } else if (row == 4) {
        m_curSubMenu = m_focallawMenu;
    } else if (row == 5) {
        m_curSubMenu = m_scanMenu;
    } else if (row == 6) {
        m_curSubMenu = m_measureMenu;
    } else if (row == 7) {
        m_curSubMenu = m_fileReportMenu;
    } else if (row == 8) {
        m_curSubMenu = m_preferenceMenu;
    }

    if (ITEM_HEIHT*row + ITEM_HEIHT*m_curSubMenu->count() > static_cast<QWidget *>(parent())->height()) {
        m_topSpaceItem->changeSize(20, static_cast<QWidget *>(parent())->height() - ITEM_HEIHT*m_curSubMenu->count(),
                                   QSizePolicy::Expanding, QSizePolicy::Fixed);
    } else {
        m_topSpaceItem->changeSize(20, ITEM_HEIHT*row,
                                   QSizePolicy::Expanding, QSizePolicy::Fixed);
    }

    m_curSubMenu->setCurrentRow(-1);
    m_curSubMenu->show();
}

void MainMenuPrivate::do_subMenu_pressed()
{
    emit static_cast<MainMenu *>(parent())->type_changed(static_cast<MainMenu::Type>(m_curSubMenu->currentItem()->type()));
}

void MainMenuPrivate::init_mainMenu()
{
    m_mainMenu->setObjectName("main_menu");
    m_mainMenu->setMinimumWidth(125);
    m_mainMenu->setMaximumWidth(125);
    set_common(m_mainMenu);
    new QListWidgetItem(tr("Ut Settings"), m_mainMenu);
    new QListWidgetItem(tr("Gate/Curves"), m_mainMenu);
    new QListWidgetItem(tr("Display"), m_mainMenu);
    new QListWidgetItem(tr("Probe/Part"), m_mainMenu);
    new QListWidgetItem(tr("Focallaw"), m_mainMenu);
    new QListWidgetItem(tr("Scan"), m_mainMenu);
    new QListWidgetItem(tr("Measurement"), m_mainMenu);
    new QListWidgetItem(tr("File/Report"), m_mainMenu);
    new QListWidgetItem(tr("Preference"), m_mainMenu);

    connect(m_mainMenu, SIGNAL(currentRowChanged(int)),
            this, SLOT(do_currentRowChanged(int)));
    m_mainMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_utSettingMenu()
{
    set_common(m_utSettingMenu);
    new QListWidgetItem(tr("General"), m_utSettingMenu, MainMenu::UTSettings_General);
    new QListWidgetItem(tr("Pulser"), m_utSettingMenu, MainMenu::UTSettings_Pulser);
    new QListWidgetItem(tr("Receiver"), m_utSettingMenu, MainMenu::UTSettings_Receiver);
    new QListWidgetItem(tr("Advanced"), m_utSettingMenu, MainMenu::UTSettings_Advanced);

    connect(m_utSettingMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_gateCurevesMenu()
{
    set_common(m_gateCurvesMenu);
    m_gateCurvesMenu->hide();
    new QListWidgetItem(tr("Gate"), m_gateCurvesMenu, MainMenu::GateCurves_Gate);
    new QListWidgetItem(tr("Alarm"), m_gateCurvesMenu, MainMenu::GateCurves_Alarm);
    new QListWidgetItem(tr("Analog"), m_gateCurvesMenu, MainMenu::GateCurves_Analog);
    new QListWidgetItem("DAC", m_gateCurvesMenu, MainMenu::GateCurves_DAC);
    new QListWidgetItem("TCG", m_gateCurvesMenu, MainMenu::GateCurves_TCG);

    connect(m_gateCurvesMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_displayMenu()
{
    set_common(m_displayMenu);
    m_displayMenu->hide();
    new QListWidgetItem(tr("Selection"), m_displayMenu, MainMenu::Display_Selection);
    new QListWidgetItem(tr("Color"), m_displayMenu, MainMenu::Display_ColorSettings);
    new QListWidgetItem(tr("Properties"), m_displayMenu, MainMenu::Displsy_Properties);

    connect(m_displayMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_probePartMenu()
{
    set_common(m_probePartMenu);
    m_probePartMenu->hide();
    new QListWidgetItem(tr("Select"), m_probePartMenu, MainMenu::ProbePart_Select);
    new QListWidgetItem(tr("Position"), m_probePartMenu, MainMenu::ProbePart_Position);
    new QListWidgetItem("FFT", m_probePartMenu, MainMenu::ProbePart_FFT);
    new QListWidgetItem(tr("Part"), m_probePartMenu, MainMenu::ProbePart_Part);
    new QListWidgetItem(tr("Advanced"), m_probePartMenu, MainMenu::ProbePart_Advanced);

    connect(m_probePartMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_focallawMenu()
{
    set_common(m_focallawMenu);
    m_focallawMenu->hide();
    new QListWidgetItem(tr("Law Config"), m_focallawMenu, MainMenu::FocalLaw_LawConfig);
    new QListWidgetItem(tr("Angle"), m_focallawMenu, MainMenu::FocalLaw_Angle);
    new QListWidgetItem(tr("Aperture"), m_focallawMenu, MainMenu::FocalLaw_Aperture);
    new QListWidgetItem(tr("Focal Point"), m_focallawMenu, MainMenu::FocalLaw_FocalPoint);

    connect(m_focallawMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_scanMenu()
{
    set_common(m_scanMenu);
    m_scanMenu->hide();
    new QListWidgetItem(tr("Inspection"), m_scanMenu, MainMenu::Scan_Inspection);
    new QListWidgetItem(tr("Encoder"), m_scanMenu, MainMenu::Scan_Encoder);
    new QListWidgetItem(tr("Area"), m_scanMenu, MainMenu::Scan_Area);
    new QListWidgetItem(tr("Start"), m_scanMenu, MainMenu::Scan_Start);

    connect(m_scanMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_measureMenu()
{
    set_common(m_measureMenu);
    m_measureMenu->hide();
    new QListWidgetItem(tr("Cursors"), m_measureMenu, MainMenu::Measurement_Cursors);
    new QListWidgetItem("TOFD", m_measureMenu, MainMenu::Measurement_TOFD);
    new QListWidgetItem(tr("Flaw Record"), m_measureMenu, MainMenu::Measurement_FlawRecord);

    connect(m_measureMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_fileReportMenu()
{
    set_common(m_fileReportMenu);
    m_fileReportMenu->hide();
    new QListWidgetItem(tr("File"), m_fileReportMenu, MainMenu::FileReport_File);
    new QListWidgetItem(tr("Report"), m_fileReportMenu, MainMenu::FileReport_Report);
    new QListWidgetItem(tr("Format"), m_fileReportMenu, MainMenu::FileReport_Format);
    new QListWidgetItem(tr("User Field"), m_fileReportMenu, MainMenu::FileReport_UserField);

    connect(m_fileReportMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}

void MainMenuPrivate::init_preferenceMenu()
{
    set_common(m_preferenceMenu);
    m_preferenceMenu->hide();
    new QListWidgetItem(tr("Preference"), m_preferenceMenu, MainMenu::Preference_Preference);
    new QListWidgetItem(tr("System"), m_preferenceMenu, MainMenu::Preference_System);
    new QListWidgetItem(tr("Network"), m_preferenceMenu, MainMenu::Preference_Network);

    connect(m_preferenceMenu, SIGNAL(pressed(QModelIndex)),
            this, SLOT(do_subMenu_pressed()));
}
