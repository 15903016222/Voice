#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <device/device.h>
#include "../vinput/vinput.h"
#include "../display/display_widget.h"
#include "../menu/ut_setting/general_menu.h"
#include "../menu/preference/preference_menu.h"
#include "../menu/probe_part/fft_menu.h"

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

    qDebug("%s[%d]: ",__func__, __LINE__);
//    DplPreferenceMenu::PreferenceMenu *preferenceMenu = dynamic_cast<DplPreferenceMenu::PreferenceMenu *>(m_subMenu->get_menu(MainMenu::Preference_Preference));
//    connect(preferenceMenu, SIGNAL(opacity_changed(double)),
//            m_mainMenu, SLOT(set_opacity(double)));
    qDebug("%s[%d]: ",__func__, __LINE__);

    /* virtual keyboard */
    m_virtualKeyboard->hide();
    connect(ui->iconsBarWidget, SIGNAL(keyboard_event()), this, SLOT(do_keyboard_event()));

    ui->displayLayout->addWidget(new DplUi::DisplayWidget(DplDevice::Device::instance()->display(), this));
}

MainWindow::~MainWindow()
{
    delete ui;
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
    case Mcu::KEY_DB:
        m_subMenu->set_menu(MainMenu::UTSettings_General);
        ui->gainMenuItem->set_edit(true);
        break;
    case Mcu::KEY_GATE:
        m_subMenu->set_menu(MainMenu::GateCurves_Gate);
        m_subMenu->setFocus();
        break;
    default:
        break;
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
