#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <device/device.h>
#include "../vinput/vinput.h"
#include "../display/display_widget.h"
#include "../menu/ut_setting/general_menu.h"
#include "../menu/preference/preference_menu.h"
#include "../menu/probe_part/fft_menu.h"
#include "../ui/wizard/wizard.h"

#include <global.h>

#include <QDebug>
#include <QResizeEvent>
#include <QFontDatabase>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_virtualKeyboard(new VirtualKeyboard)
{
    load_style_sheet("/opt/mercury/qss/default.qss");

    ui->setupUi(this);

    ui->gainMenuItem->show();
    ui->angleMenuItem->show();

    /* Device */
    DplDevice::GroupPointer group = DplDevice::Device::instance()->get_group(0);

    /* gain menu item */
    ui->gainMenuItem->set_title(tr("Gain"));
    ui->gainMenuItem->set_unit(tr("dB"));
    ui->gainMenuItem->set(0, 110, 1, 0.1);
    ui->gainMenuItem->set_suffix("(0.0)");
    ui->gainMenuItem->set_value(group->sample()->gain());

    /* angle menu item */
    ui->angleMenuItem->set_title(tr("Angle"));
    ui->angleMenuItem->set_unit(DEGREE_STR);
    ui->angleMenuItem->set(0, 180, 1);

    /* Mcu */
    Mcu *mcu = Mcu::instance();
    connect(mcu, SIGNAL(key_event(Mcu::KeyType)),
            this, SLOT(do_key_event(Mcu::KeyType)));
    connect(mcu, SIGNAL(rotary_event(Mcu::RotaryType)),
            this, SLOT(do_rotary_event(Mcu::RotaryType)));

    /* Menu */
    m_mainMenu = new MainMenu(this);
    m_subMenu = new SubMenu(this);
    m_mainMenu->hide();
    ui->subMenuLayout->addWidget(m_subMenu);
    connect(m_mainMenu, SIGNAL(type_changed(MainMenu::Type)),
            m_subMenu, SLOT(set_menu(MainMenu::Type)));

    DplUtSettingMenu::GeneralMenu *generalMenu = dynamic_cast<DplUtSettingMenu::GeneralMenu *>(m_subMenu->get_menu(MainMenu::UTSettings_General));
    connect(generalMenu, SIGNAL(gain_changed(double)), ui->gainMenuItem, SLOT(set_value(double)));
    connect(ui->gainMenuItem, SIGNAL(value_changed(double)), generalMenu, SLOT(set_gain(double)));
    DplProbeMenu::FftMenu *fftMenu = dynamic_cast<DplProbeMenu::FftMenu *>(m_subMenu->get_menu(MainMenu::ProbePart_FFT));
    connect(fftMenu, SIGNAL(gain_changed(double)), ui->gainMenuItem, SLOT(set_value(double)));

    DplPreferenceMenu::PreferenceMenu *preferenceMenu = dynamic_cast<DplPreferenceMenu::PreferenceMenu *>(m_subMenu->get_menu(MainMenu::Preference_Preference));
    connect(preferenceMenu, SIGNAL(opacity_changed(double)),
            m_mainMenu, SLOT(set_opacity(double)));

    /* virtual keyboard */
    m_virtualKeyboard->hide();
    connect(ui->iconsBarWidget, SIGNAL(keyboard_event()), this, SLOT(do_keyboard_event()));

    ui->displayLayout->addWidget(new DplUi::DisplayWidget(DplDevice::Device::instance()->display(), this));

    m_wizard = new Wizard(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_style_sheet(const QString &fileName)
{
    QFile file(fileName);
    if(file.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(file.readAll());
        file.close();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::RightButton) {
        show_hidden_Menu();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Alt) {
        show_hidden_Menu();
        return;
    }
    return QMainWindow::keyPressEvent(event);
}

void MainWindow::do_key_event(Mcu::KeyType type)
{
    switch (type) {
    case Mcu::KEY_MENU:
        show_hidden_Menu();
        break;
    case Mcu::KEY_SURE:
        VInput::instance()->send(VInput::Key_Enter);
        break;
    case Mcu::KEY_BACK:
        VInput::instance()->send(VInput::Key_Esc);
        break;
    case Mcu::KEY_CURSOR:
        m_wizard->show();
        break;
    case Mcu::KEY_FREEZE: {
        if (DplDevice::Device::instance()->is_running()) {
            DplDevice::Device::instance()->stop();
        } else {
            DplDevice::Device::instance()->start();
        }
    }
        break;
    case Mcu::KEY_START:
        DplSource::Source::instance()->restart();
        break;
    default:
        break;
    }
}

void MainWindow::show_hidden_Menu()
{
    if(m_mainMenu->isHidden()) {
        m_mainMenu->setGeometry(0,
                                ui->measureBar->height()+ui->statusBar->height()+15,
                                m_mainMenu->width(),
                                height() - ui->measureBar->height() - ui->statusBar->height() - m_subMenu->height()-15);
        m_mainMenu->show();
    } else {
        m_mainMenu->hide();
    }
}

void MainWindow::do_keyboard_event()
{
    if(m_virtualKeyboard->isHidden()) {
        m_virtualKeyboard->show();
        m_virtualKeyboard->move((this->width() - m_virtualKeyboard->width()) / 2, (this->height() - m_virtualKeyboard->height()) / 2);
    } else {
        m_virtualKeyboard->hide();
    }
}

void MainWindow::do_rotary_event(Mcu::RotaryType type)
{
    if (Mcu::ROTARY_UP == type) {
        VInput::instance()->send(VInput::Key_Up);
    } else {
        VInput::instance()->send(VInput::Key_Down);
    }
}
