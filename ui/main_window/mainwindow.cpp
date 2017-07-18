#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <device/device.h>
#include "vinput.h"
#include "ut_setting/general_menu.h"
#include "preference/preference_menu.h"
#include <display/display.h>

#include <QDebug>
#include <QResizeEvent>
#include <QFontDatabase>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->gainMenuItem->show();
    ui->angleMenuItem->show();

    /* Device */
    DplDevice::GroupPointer group = DplDevice::Device::instance()->get_group(0);

    /* gain menu item */
    ui->gainMenuItem->set(tr("Gain"), "dB", 0, 90, 1);
    ui->gainMenuItem->set_suffix("(0.0)");
    ui->gainMenuItem->set_value(group->sample()->gain());

    /* angle menu item */
    ui->angleMenuItem->set(tr("Angle"), "&#176;", 0, 180, 1);

    /* Mcu */
    Mcu *mcu = Mcu::instance();
    connect(mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(do_key_event(Mcu::KeyType)));
    connect(mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));

    /* Main Menu */
    m_mainMenu = new MainMenu(this);
    m_mainMenu->hide();
    ui->mainMenuLayout->addWidget(m_mainMenu);
//    m_mainMenu->move(0, height() - m_mainMenu->height());
//    m_mainMenu->move(0, 176);

    /* Sub Menu */
    m_subMenu = new SubMenu(this);
    m_subMenu->hide();
    ui->subMenuLayout->addWidget(m_subMenu);
//    m_subMenu->setGeometry(m_mainMenu->width(),
//                           height()-m_subMenu->height(),
//                           width()-m_mainMenu->width(),
//                           m_subMenu->height());
//    m_subMenu->move(m_mainMenu->width(), 530);
    DplUtSettingMenu::GeneralMenu *generalMenu = dynamic_cast<DplUtSettingMenu::GeneralMenu *>(m_subMenu->get_menu(MainMenu::UTSettings_General));
    connect(generalMenu, SIGNAL(gain_changed(double)), ui->gainMenuItem, SLOT(set_value(double)));
    connect(ui->gainMenuItem, SIGNAL(value_changed(double)), generalMenu, SLOT(set_gain(double)));

    DplPreferenceMenu::PreferenceMenu *preferenceMenu = dynamic_cast<DplPreferenceMenu::PreferenceMenu *>(m_subMenu->get_menu(MainMenu::Preference_Preference));
    connect(preferenceMenu, SIGNAL(opacity_changed(double)), m_mainMenu, SLOT(set_opacity_main_menu(double)));
    connect(preferenceMenu, SIGNAL(opacity_changed(double)), m_subMenu, SLOT(set_opacity_main_menu(double)));

    connect(m_mainMenu, SIGNAL(click(MainMenu::Type)), m_subMenu, SLOT(set_menu(MainMenu::Type)));

    pVirtualKeyboard = new VirtualKeyboard;
    pVirtualKeyboard->hide();
    connect(ui->iconsBarWidget, SIGNAL(keyboard_event()), this, SLOT(do_keyboard_event()));

    QVBoxLayout *vboxLayout = new QVBoxLayout(ui->display);
    vboxLayout->setContentsMargins(0, 0, 0, 0);
    vboxLayout->setSpacing(0);
    vboxLayout->addWidget(DplDisplay::Display::get_instance());
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
    default:
        break;
    }
}

void MainWindow::update_translator(QString string)
{
//    if(string == "Chinese") {
//        translator->load(":/file/translator/phascanII_UI_Chinese.qm");
//    } else if(string == "English") {
//        translator->load(":/file/translator/phascanII_UI_English.qm");
//    }
//    ui->retranslateUi(this);
//    ui->widgetTopLeft->retranslate_top_menu_ui();
//    firstSecondMenu->retranslate_main_menu_ui(string);
//    commonMenuWidget->retranslate_common_menu_ui();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
//                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
//                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
//    if(scrollRect.contains(event->pos())) {
//        m_mainMenuStartPos = event->pos().y();
//    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *moveEvent)
{
//    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
//                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
//                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
//    if(scrollRect.contains(moveEvent->pos())) {
//        m_mainMenuEndPos = moveEvent->pos().y();
//        int scrollLength = m_mainMenuEndPos - m_mainMenuStartPos;
//        int menuTopY = firstSecondMenu->pos().y() + ui->scrollArea->geometry().y();
//        int scrollTopY = ui->scrollArea->geometry().y();
//        int menuBottomY = firstSecondMenu->pos().y() + firstSecondMenu->geometry().height() + ui->scrollArea->geometry().y();
//        int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();

//        if(scrollLength < 0) {
//            if((menuBottomY + scrollLength) > scrollBottomY) {
//                ui->scrollArea->viewport()->scroll(0, scrollLength);
//            } else  {
//                ui->scrollArea->viewport()->scroll(0, -(menuBottomY - scrollBottomY));
//            }
//        } else {
//            if((menuTopY + scrollLength) < scrollTopY) {
//                ui->scrollArea->viewport()->scroll(0, scrollLength);
//            } else {
//                ui->scrollArea->viewport()->scroll(0, scrollTopY - menuTopY);
//            }
//        }
//        show_hidden_arrow();
//    }
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
    if(m_subMenu->isHidden()) {
        m_subMenu->show();
        m_mainMenu->show();
    } else {
        m_mainMenu->hide();
        m_subMenu->hide();
    }
}

void MainWindow::do_keyboard_event()
{
    if(pVirtualKeyboard->isHidden()) {
        pVirtualKeyboard->show();
        pVirtualKeyboard->move((this->width() - pVirtualKeyboard->width()) / 2, (this->height() - pVirtualKeyboard->height()) / 2);       
    } else {
        pVirtualKeyboard->hide();
    }
}

void MainWindow::slot_setMenuOpacity(double value)
{
    QString alph = QString::number((double)(value/100), 'f', 2);
    QString bc = QString("background-color:rgba(37, 76, 124," + alph + ");");

    QString style = QString("QWidget#widget{" +bc + "border-radius:8px;}"
                            "QPushButton#pushButton_top{" + bc + "border-radius:8px;}"
                            "QPushButton#pushButton_bottom{" + bc + "border:none;}");
    setStyleSheet(style);
}

void MainWindow::do_rotary_event(Mcu::RotaryType type)
{
    if (Mcu::ROTARY_UP == type) {
        VInput::instance()->send(VInput::Key_Up);
    } else {
        VInput::instance()->send(VInput::Key_Down);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();
    int oldWidth = event->oldSize().width();
    int oldHeight = event->oldSize().height();
    int mainMenuWidth = m_mainMenu->geometry().width();
    int mainMenuHeight = m_mainMenu->geometry().height();
    int subMenuWidth = m_subMenu->geometry().width();
    int subMenuHeight = m_subMenu->geometry().height();

    if(oldWidth > 0 && oldHeight > 0) {
        m_mainMenu->resize(qRound((qreal)mainMenuWidth * width / oldWidth), qRound((qreal)mainMenuHeight * height / oldHeight));
        m_subMenu->resize(qRound((qreal)subMenuWidth * width / oldWidth), qRound((qreal)subMenuHeight * height / oldHeight));
        m_mainMenu->move(0, height - m_mainMenu->geometry().height() + 1);
        m_subMenu->move(m_mainMenu->geometry().width(), height - m_subMenu->geometry().height());
    } else {
        m_mainMenu->resize(mainMenuWidth, mainMenuHeight);
        m_subMenu->resize(subMenuWidth, subMenuHeight);
    }
    m_mainMenu->do_change_arrow();
}
