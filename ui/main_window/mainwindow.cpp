#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "device.h"
#include "vinput.h"
#include "ut_setting/general_menu.h"
#include "preference/preference_menu.h"

#include <QDebug>
#include <QResizeEvent>
#include <QFontDatabase>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Fpga */
    DplDevice::Device::get_instance()->add_group();
    DplDevice::GroupPointer group = DplDevice::Device::get_instance()->get_group(0);
    group->init();


    /* gain menu item */
    ui->gainMenuItem->set(tr("Gain"), "dB", 0, 90, 1);
    ui->gainMenuItem->set_suffix("(0.0)");
    ui->gainMenuItem->set_value(group->gain());

    /* angle menu item */
    ui->angleMenuItem->set(tr("Angle"), "&#176;", 0, 180, 1);

    /* Mcu */
    Mcu *mcu = Mcu::get_mcu();
    connect(mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(do_key_event(Mcu::KeyType)));
    connect(mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));

    /* Main Menu */
    mainMenu = new MainMenu(this);
    mainMenu->hide();
    mainMenu->move(0, 176);

    /* Sub Menu */
    subMenu = new SubMenu(this);
    subMenu->hide();;
    subMenu->move(179, 530);
    DplUtSettingMenu::GeneralMenu *generalMenu = dynamic_cast<DplUtSettingMenu::GeneralMenu *>(subMenu->get_menu(MainMenu::UTSettings_General));
    connect(generalMenu, SIGNAL(gain_changed(double)), ui->gainMenuItem, SLOT(set_value(double)));
    connect(ui->gainMenuItem, SIGNAL(value_changed(double)), generalMenu, SLOT(set_gain(double)));

    connect(mainMenu, SIGNAL(click(MainMenu::Type)), subMenu, SLOT(set_menu(MainMenu::Type)));

    DplPreferenceMenu::PreferenceMenu *preferenceMenu = dynamic_cast<DplPreferenceMenu::PreferenceMenu *>(subMenu->get_menu(MainMenu::Preference_Preference));
    connect(preferenceMenu, SIGNAL(opacity_changed(double)), mainMenu, SLOT(set_opacity_main_menu(double)));

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
        VInput::get_vinput()->send(VInput::Key_Enter);
        break;
    case Mcu::KEY_BACK:
        VInput::get_vinput()->send(VInput::Key_Esc);
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
    if(subMenu->isHidden()) {
        subMenu->show();
        mainMenu->show();
    } else {
        mainMenu->hide();
        subMenu->hide();
    }
}

void MainWindow::do_keyboard_event()
{
    m_hiddenKeyboardFlag = !m_hiddenKeyboardFlag;
    if(m_hiddenKeyboardFlag) {
        pVirtualKeyboard->show();
        pVirtualKeyboard->move((this->width() - pVirtualKeyboard->width()) / 2, (this->height() - pVirtualKeyboard->height()) / 2);       
    } else {
        pVirtualKeyboard->hide();
    }
}

void MainWindow::slot_keyboard_close_clicked()
{
    m_hiddenKeyboardFlag = false;
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
        VInput::get_vinput()->send(VInput::Key_Up);
    } else {
        VInput::get_vinput()->send(VInput::Key_Down);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();
    int oldWidth = event->oldSize().width();
    int oldHeight = event->oldSize().height();
    int mainMenuWidth = mainMenu->geometry().width();
    int mainMenuHeight = mainMenu->geometry().height();
    int subMenuWidth = subMenu->geometry().width();
    int subMenuHeight = subMenu->geometry().height();

    if(oldWidth > 0 && oldHeight > 0) {
        mainMenu->resize(qRound((qreal)mainMenuWidth * width / oldWidth), qRound((qreal)mainMenuHeight * height / oldHeight));
        subMenu->resize(qRound((qreal)subMenuWidth * width / oldWidth), qRound((qreal)subMenuHeight * height / oldHeight));
        mainMenu->move(0, height - mainMenu->geometry().height() + 1);
        subMenu->move(mainMenu->geometry().width(), height - subMenu->geometry().height());
    } else {
        mainMenu->resize(mainMenuWidth, mainMenuHeight);
        subMenu->resize(subMenuWidth, subMenuHeight);
    }
    mainMenu->do_change_arrow();
}
