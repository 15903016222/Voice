#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "vinput.h"

#include <QDebug>
#include <QResizeEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QList<double> steps;
    steps.append(0.1);
    steps.append(0.5);
    steps.append(1.0);
    steps.append(5.0);

    /* gain menu item */
    ui->gainMenuItem->set_type(MenuItem::Spin);
    ui->gainMenuItem->set_title("Gain");
    ui->gainMenuItem->set_unit("dB");
    ui->gainMenuItem->set_steps(steps);
    ui->gainMenuItem->set_suffix("(0.0)");

    /* angle menu item */
    ui->angleMenuItem->set_type(MenuItem::Spin);
    ui->angleMenuItem->set_title(tr("Angle"));
    ui->angleMenuItem->set_unit("&#176;");
    ui->angleMenuItem->set_steps(steps);

    Mcu *mcu = Mcu::get_mcu();
    connect(mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(do_key_event(Mcu::KeyType)));
    connect(mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));

    mainMenu = new MainMenu(this);
    mainMenu->hide();
    mainMenu->move(0, 176);

    subMenu = new SubMenu(this);
    subMenu->hide();;
    subMenu->move(179, 530);

    connect(mainMenu, SIGNAL(click(MainMenu::Type)), subMenu, SLOT(set_menu(MainMenu::Type)));
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

