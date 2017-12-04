#include "main_menu_p.h"

#define ITEM_HEIHT (44.44)

MainMenuPrivate::MainMenuPrivate(QWidget *parent) : QObject(parent),
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
    m_topSpaceItem(new QSpacerItem(20, 100, QSizePolicy::Maximum, QSizePolicy::Expanding)),
    m_bottomSpaceItem(new QSpacerItem(20, 100, QSizePolicy::Maximum, QSizePolicy::Expanding))
{
    init_menu();
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

    m_topSpaceItem->changeSize(20, row*44, QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_bottomSpaceItem->changeSize(20, 40, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_curSubMenu->show();
}

void MainMenuPrivate::init_menu()
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

void MainMenuPrivate::init_mainMenu()
{
    m_mainMenu->setObjectName("main_menu");
    m_mainMenu->setFocusPolicy(Qt::WheelFocus);
    m_mainMenu->setMinimumWidth(130);
    m_mainMenu->setMaximumWidth(130);
    m_mainMenu->setMinimumHeight(400);
    connect(m_mainMenu, SIGNAL(currentRowChanged(int)),
            this, SLOT(do_currentRowChanged(int)));
    new QListWidgetItem(tr("Ut Settings"), m_mainMenu);
    new QListWidgetItem(tr("Gate/Curves"), m_mainMenu);
    new QListWidgetItem(tr("Display"), m_mainMenu);
    new QListWidgetItem(tr("Probe/Part"), m_mainMenu);
    new QListWidgetItem(tr("Focallaw"), m_mainMenu);
    new QListWidgetItem(tr("Scan"), m_mainMenu);
    new QListWidgetItem(tr("Measurement"), m_mainMenu);
    new QListWidgetItem(tr("File/Report"), m_mainMenu);
    new QListWidgetItem(tr("Preference"), m_mainMenu);
    m_mainMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_utSettingMenu()
{
    m_utSettingMenu->setMinimumHeight(ITEM_HEIHT*4);
    m_utSettingMenu->setMaximumHeight(ITEM_HEIHT*4);
    new QListWidgetItem(tr("General"), m_utSettingMenu);
    new QListWidgetItem(tr("Pulser"), m_utSettingMenu);
    new QListWidgetItem(tr("Receiver"), m_utSettingMenu);
    new QListWidgetItem(tr("Advanced"), m_utSettingMenu);
    m_utSettingMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_gateCurevesMenu()
{
    m_gateCurvesMenu->setMinimumHeight(ITEM_HEIHT*6);
    m_gateCurvesMenu->setMaximumHeight(ITEM_HEIHT*6);
    m_gateCurvesMenu->hide();
    new QListWidgetItem(tr("Gate"), m_gateCurvesMenu);
    new QListWidgetItem(tr("Alarm"), m_gateCurvesMenu);
    new QListWidgetItem(tr("Output"), m_gateCurvesMenu);
    new QListWidgetItem(tr("Analog"), m_gateCurvesMenu);
    new QListWidgetItem("DAC", m_gateCurvesMenu);
    new QListWidgetItem("TCG", m_gateCurvesMenu);
    m_gateCurvesMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_displayMenu()
{
    m_displayMenu->setMinimumHeight(ITEM_HEIHT*3);
    m_displayMenu->setMaximumHeight(ITEM_HEIHT*3);
    m_displayMenu->hide();
    new QListWidgetItem(tr("Selection"), m_displayMenu);
    new QListWidgetItem(tr("Color"), m_displayMenu);
    new QListWidgetItem(tr("Properties"), m_displayMenu);
    m_displayMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_probePartMenu()
{
    m_probePartMenu->setMinimumHeight(ITEM_HEIHT*5);
    m_probePartMenu->setMaximumHeight(ITEM_HEIHT*5);
    m_probePartMenu->hide();
    new QListWidgetItem(tr("Select"), m_probePartMenu);
    new QListWidgetItem(tr("Position"), m_probePartMenu);
    new QListWidgetItem("FFT", m_probePartMenu);
    new QListWidgetItem(tr("Part"), m_probePartMenu);
    new QListWidgetItem(tr("Advanced"), m_probePartMenu);
    m_probePartMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_focallawMenu()
{
    m_focallawMenu->setMinimumHeight(ITEM_HEIHT*4);
    m_focallawMenu->setMaximumHeight(ITEM_HEIHT*4);
    m_focallawMenu->hide();
    new QListWidgetItem(tr("Law Config"), m_focallawMenu);
    new QListWidgetItem(tr("Angle"), m_focallawMenu);
    new QListWidgetItem(tr("Apeture"), m_focallawMenu);
    new QListWidgetItem(tr("Focal Point"), m_focallawMenu);
    m_focallawMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_scanMenu()
{
    m_scanMenu->setMinimumHeight(ITEM_HEIHT*4);
    m_scanMenu->setMaximumHeight(ITEM_HEIHT*4);
    m_scanMenu->hide();
    new QListWidgetItem(tr("Inspection"), m_scanMenu);
    new QListWidgetItem(tr("Encoder"), m_scanMenu);
    new QListWidgetItem(tr("Area"), m_scanMenu);
    new QListWidgetItem(tr("Start"), m_scanMenu);
    m_scanMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_measureMenu()
{
    m_measureMenu->setMinimumHeight(ITEM_HEIHT*3);
    m_measureMenu->setMaximumHeight(ITEM_HEIHT*3);
    m_measureMenu->hide();
    new QListWidgetItem(tr("Cursors"), m_measureMenu);
    new QListWidgetItem("TOFD", m_measureMenu);
    new QListWidgetItem(tr("Flaw Record"), m_measureMenu);
    m_measureMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_fileReportMenu()
{
    m_fileReportMenu->setMinimumHeight(ITEM_HEIHT*5);
    m_fileReportMenu->setMaximumHeight(ITEM_HEIHT*5);
    m_fileReportMenu->hide();
    new QListWidgetItem(tr("File"), m_fileReportMenu);
    new QListWidgetItem(tr("Save Mode"), m_fileReportMenu);
    new QListWidgetItem(tr("Report"), m_fileReportMenu);
    new QListWidgetItem(tr("Format"), m_fileReportMenu);
    new QListWidgetItem(tr("User Field"), m_fileReportMenu);
    m_fileReportMenu->setCurrentRow(0);
}

void MainMenuPrivate::init_preferenceMenu()
{
    m_preferenceMenu->setMinimumHeight(ITEM_HEIHT*3);
    m_preferenceMenu->setMaximumHeight(ITEM_HEIHT*3);
    m_preferenceMenu->hide();
    new QListWidgetItem(tr("Preference"), m_preferenceMenu);
    new QListWidgetItem(tr("System"), m_preferenceMenu);
    new QListWidgetItem(tr("Network"), m_preferenceMenu);
    m_preferenceMenu->setCurrentRow(0);
}
