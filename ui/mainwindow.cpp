#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "lineeditdelegate.h"

#include <QResizeEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);

    init_ui();

 //   slot_setMenuOpacity(100.0);
 //   connect(ui->widget_thirdMenu, SIGNAL(opacityChanged(double)), this, SLOT(slot_setMenuOpacity(double)));

    m_rotarySecondMenuNum = 0;

    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(do_key_event(Mcu::KeyType)));
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_ui()
{
    this->resize(800, 600);

    ui->widget_firstSecondMenu->hide();
    ui->widget_thirdMenu->hide();

    ui->frame_showPlot->installEventFilter(this);
    ui->widget_thirdMenu->installEventFilter(this);

    m_firstMenuNum = 0;
    m_secondMenuNum = 0;
    m_hiddenFirstSecondMenuFlag = false;
    m_hiddenThirdMenuFlag = false;
    m_hiddenCommonMenuFlag = false;
    m_hiddenKeyboardFlag = false;

    firstSecondMenu = new FirstSecondMenuWidget(this);
#if QT_VERSION <= QT_VERSION_CHECK(5, 0, 0)
    firstSecondMenu->resize_height(m_firstMenuNum);
#endif
    commonMenuWidget = new CommonMenuWidget(this);
    commonMenuWidget->hide();
    commonMenuButton = new CommonMenuButton(this);
    commonMenuButton->resize(40, 40);
    commonMenuButton->show();

    translator = new QTranslator(this);
    qApp->installTranslator(translator);

    QObject::connect(firstSecondMenu->toolBox.at(0), SIGNAL(currentChanged(int)), this, SLOT(slot_firstMenuToolBoxCurrentChanged(int)));

    for(int i = 0; i < FIRST_MENU_NUMBER; i++) {
        QObject::connect(firstSecondMenu->menuList.at(i), SIGNAL(clicked(QModelIndex)), this, SLOT(slot_secondMenuItemClicked(QModelIndex)));
    }

    ui->scrollArea = new QScrollArea(ui->widget_scrollArea);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidget(firstSecondMenu);

    QObject::connect(commonMenuButton->pushButton_commonMenu.at(0), SIGNAL(clicked()), this, SLOT(slot_pushButton_commonMenuClicked()));
    QObject::connect(ui->iconsBarWidget, SIGNAL(keyboard_event()), this, SLOT(do_keyboard_event()));

    connect(this, SIGNAL(clickedMenuIndex(int)), this, SLOT(scroll_menu(int)));
    connect(ui->widget_thirdMenu, SIGNAL(retranslate_ui(QString)), this, SLOT(update_translator(QString)));
}

void MainWindow::do_key_event(Mcu::KeyType type)
{
    switch (type) {
    case Mcu::KEY_MENU:
        show_hidden_Menu();
        break;
    default:
        break;
    }
}

void MainWindow::slot_firstMenuToolBoxCurrentChanged(int index)
{
    ui->widget_thirdMenu->set_third_menu_name(index, 0); //init
    m_firstMenuNum = index;

    QModelIndex modelIndex = firstSecondMenu->modelList.at(index)->index(0, 0);
    firstSecondMenu->set_second_menu_item_style(m_firstMenuNum, modelIndex);

    m_hiddenArrowFlag = true;

    emit clickedMenuIndex(m_firstMenuNum);
    show_hidden_arrow();

 //   ui->widget_thirdMenu->setOpacity(ui->widget_thirdMenu->opacity);

    firstSecondMenu->menuList.at(m_firstMenuNum)->setFocus();
    m_rotarySecondMenuNum = 0;
}

void MainWindow::slot_secondMenuItemClicked(QModelIndex index)
{
    QStandardItem *item = firstSecondMenu->modelList.at(m_firstMenuNum)->itemFromIndex(index);
    m_secondMenuNum = item->row();

    firstSecondMenu->set_second_menu_item_style(m_firstMenuNum, index);
    ui->widget_thirdMenu->set_third_menu_name(m_firstMenuNum, m_secondMenuNum);

 //   ui->widget_thirdMenu->setOpacity(ui->widget_thirdMenu->opacity);
}

void MainWindow::on_pushButton_top_clicked()
{
    int menuTopY = firstSecondMenu->pos().y() + ui->scrollArea->geometry().y();
    int scrollTopY = ui->scrollArea->geometry().y();

    if(menuTopY < (scrollTopY -20)) {
        ui->scrollArea->viewport()->scroll(0, 20);
    } else {
        ui->scrollArea->viewport()->scroll(0, scrollTopY - menuTopY);
    }

    show_hidden_arrow();
}

void MainWindow::on_pushButton_bottom_clicked()
{
    int menuBottomY = firstSecondMenu->pos().y() + firstSecondMenu->geometry().height() + ui->scrollArea->geometry().y();
    int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();

    if((menuBottomY - 20) > scrollBottomY) {
        ui->scrollArea->viewport()->scroll(0, -20);
    } else {
        ui->scrollArea->viewport()->scroll(0, -(menuBottomY - scrollBottomY));
    }

    show_hidden_arrow();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();
    int oldWidth = event->oldSize().width();
    int oldHeight = event->oldSize().height();
    int menuHeight = firstSecondMenu->geometry().height();

    if(oldWidth > 0 && oldHeight > 0) {
        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());

        if(ui->widget_scrollArea->geometry().height() < 600) {
            firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), height * menuHeight / oldHeight);
        } else {
            firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
        }
        commonMenuWidget->resize(width, height * 70 / 600);
        commonMenuWidget->move(0, height * 530 / 600);
        commonMenuButton->move(width - commonMenuButton->geometry().width(), height - commonMenuButton->geometry().height());
    } else {
        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
        firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), height * menuHeight / this->geometry().height());
        commonMenuWidget->resize(width, height * 70 / 600);
        commonMenuWidget->move(0, height * 530 / 600);
        commonMenuButton->move(this->geometry().width() - commonMenuButton->geometry().width(), this->geometry().height() - commonMenuButton->geometry().height());
    }
    show_hidden_arrow();
}

void MainWindow::show_hidden_arrow()
{
    int menuTopY = firstSecondMenu->pos().y() + ui->scrollArea->geometry().y();
    int scrollTopY = ui->scrollArea->geometry().y();
    int menuBottomY = firstSecondMenu->pos().y() + firstSecondMenu->geometry().height() + ui->scrollArea->geometry().y();
    int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();

    if(menuTopY == scrollTopY) {
        if(m_hiddenArrowFlag == false) {
              ui->pushButton_top->hide();
        } else {
            ui->pushButton_top->show();
            m_hiddenArrowFlag = false;
         }
    } else {
        ui->pushButton_top->show();
    }

    if(menuBottomY == scrollBottomY ) {
        if(m_hiddenArrowFlag == false) {
            ui->pushButton_bottom->hide();
        } else {
            ui->pushButton_bottom->show();
            m_hiddenArrowFlag = false;
         }
    } else {
        ui->pushButton_bottom->show();
    }
}

void MainWindow::slot_pushButton_commonMenuClicked()
{
    m_hiddenCommonMenuFlag = !m_hiddenCommonMenuFlag;
    if(m_hiddenCommonMenuFlag) {
        ui->widget_firstSecondMenu->hide();
        ui->widget_thirdMenu->hide();
        if(ui->widget_thirdMenu->opendSpinBoxIndex >= 0) {
            ui->widget_thirdMenu->opendSpinBoxIndex = -1;
        }
        m_hiddenFirstSecondMenuFlag = false;
        commonMenuWidget->show();
        commonMenuButton->raise();
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonAfter.png)}");
    } else {
        commonMenuWidget->hide();
        if(commonMenuWidget->opendSpinBoxIndex >= 0) {
            commonMenuWidget->opendSpinBoxIndex = -1;
        }
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
        m_hiddenFirstSecondMenuFlag = false;
    }
}

void MainWindow::update_translator(QString string)
{
    if(string == "Chinese") {
        translator->load(":/file/translator/phascanII_UI_Chinese.qm");
    } else if(string == "English") {
        translator->load(":/file/translator/phascanII_UI_English.qm");        
    }
    ui->retranslateUi(this);
    ui->widgetTopLeft->retranslate_top_menu_ui();
    ui->widgetTopLeft->set_top_menu_font();
    firstSecondMenu->retranslate_main_menu_ui(string);
    commonMenuWidget->retranslate_common_menu_ui();

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
    if(scrollRect.contains(event->pos())) {
        m_mainMenuStartPos = event->pos().y();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *moveEvent)
{
    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
    if(scrollRect.contains(moveEvent->pos())) {
        m_mainMenuEndPos = moveEvent->pos().y();
        int scrollLength = m_mainMenuEndPos - m_mainMenuStartPos;
        int menuTopY = firstSecondMenu->pos().y() + ui->scrollArea->geometry().y();
        int scrollTopY = ui->scrollArea->geometry().y();
        int menuBottomY = firstSecondMenu->pos().y() + firstSecondMenu->geometry().height() + ui->scrollArea->geometry().y();
        int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();

        if(scrollLength < 0) {
            if((menuBottomY + scrollLength) > scrollBottomY) {
                ui->scrollArea->viewport()->scroll(0, scrollLength);
            } else  {
                ui->scrollArea->viewport()->scroll(0, -(menuBottomY - scrollBottomY));
            }
        } else {
            if((menuTopY + scrollLength) < scrollTopY) {
                ui->scrollArea->viewport()->scroll(0, scrollLength);
            } else {
                ui->scrollArea->viewport()->scroll(0, scrollTopY - menuTopY);
            }
        }
        show_hidden_arrow();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Alt) {
        show_hidden_Menu();
    }
    return QMainWindow::keyPressEvent(event);
}

void MainWindow::show_hidden_Menu()
{
    m_hiddenFirstSecondMenuFlag = !m_hiddenFirstSecondMenuFlag;
    if(m_hiddenFirstSecondMenuFlag) {
        ui->widget_firstSecondMenu->show();
        ui->widget_thirdMenu->show();
        commonMenuWidget->hide();
        m_hiddenCommonMenuFlag = false;
        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
        firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), firstSecondMenu->geometry().height());
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
        show_hidden_arrow();

        firstSecondMenu->menuList.at(m_firstMenuNum)->setFocus();

    } else {
        ui->widget_firstSecondMenu->hide();
        ui->widget_thirdMenu->hide();
        if(ui->widget_thirdMenu->opendSpinBoxIndex >= 0) {
            ui->widget_thirdMenu->opendSpinBoxIndex = -1;
        }
    }
}

void MainWindow::scroll_menu(int index)
{
    if(index >= 4 && index < 9) {
        ui->scrollArea->viewport()->scroll(0, -50);
        ui->scrollArea->update();
    }
}

void MainWindow::do_keyboard_event()
{
    m_hiddenKeyboardFlag = !m_hiddenKeyboardFlag;
    if(m_hiddenKeyboardFlag) {
        pVirtualKeyboard = new VirtualKeyboard;
//        pVirtualKeyboard->setModal(false);
//        pVirtualKeyboard->showNormal();
        pVirtualKeyboard->show();

        connect(pVirtualKeyboard, SIGNAL(close_keyboard()), this, SLOT(slot_keyboard_close_clicked()));
        connect(pVirtualKeyboard, SIGNAL(input_number(QString)), this, SLOT(do_input_number(QString)));
//        ui->widget_thirdMenu->open_spinbox_persistent_editor(ui->widget_thirdMenu->opendSpinBoxIndex);
        if(ui->widget_thirdMenu->opendSpinBoxIndex >= 0) {
            ui->widget_thirdMenu->m_keyboardShowFlag = true;
            pVirtualKeyboard->open_persistent_editor(ui->widget_thirdMenu->pModel, ui->widget_thirdMenu->pTableView, ui->widget_thirdMenu->opendSpinBoxIndex);
        } else if(ui->widgetTopLeft->opendSpinBoxIndex >= 0 && ui->widgetTopLeft->opendSpinBoxIndex < 2) {
            ui->widgetTopLeft->m_keyboardShowFlag = true;
            pVirtualKeyboard->open_persistent_editor(ui->widgetTopLeft->pGain, ui->widgetTopLeft->pTableViewGain, ui->widgetTopLeft->opendSpinBoxIndex);
        } else if(ui->widgetTopLeft->opendSpinBoxIndex == 2) {
            ui->widgetTopLeft->m_keyboardShowFlag = true;
            pVirtualKeyboard->open_persistent_editor(ui->widgetTopLeft->pAngle, ui->widgetTopLeft->pTableViewAngle, ui->widgetTopLeft->opendSpinBoxIndex);
        } else if(commonMenuWidget->opendSpinBoxIndex >= 0) {
            commonMenuWidget->m_keyboardShowFlag = true;
            pVirtualKeyboard->open_persistent_editor(commonMenuWidget->model, commonMenuWidget->pTableView, commonMenuWidget->opendSpinBoxIndex);
        }

    } else {
        pVirtualKeyboard->close();
        slot_keyboard_close_clicked();
    }
}

void MainWindow::slot_keyboard_close_clicked()
{
//    if(ui->widget_thirdMenu->opendSpinBoxIndex >= 0) {
//        ui->widget_thirdMenu->close_spinbox_persistent_editor(ui->widget_thirdMenu->opendSpinBoxIndex);
//    }
    if(ui->widget_thirdMenu->opendSpinBoxIndex >= 0) {
        pVirtualKeyboard->close_persistent_editor(ui->widget_thirdMenu->pModel, ui->widget_thirdMenu->pTableView, ui->widget_thirdMenu->opendSpinBoxIndex);
        ui->widget_thirdMenu->m_keyboardShowFlag = false;
    } else if(ui->widgetTopLeft->opendSpinBoxIndex >= 0) {
        pVirtualKeyboard->close_persistent_editor(ui->widgetTopLeft->pGain, ui->widgetTopLeft->pTableViewGain, ui->widgetTopLeft->opendSpinBoxIndex);
        ui->widgetTopLeft->m_keyboardShowFlag = false;
    } else if(ui->widgetTopLeft->opendSpinBoxIndex == 2) {
        pVirtualKeyboard->close_persistent_editor(ui->widgetTopLeft->pAngle, ui->widgetTopLeft->pTableViewAngle, ui->widgetTopLeft->opendSpinBoxIndex);
        ui->widgetTopLeft->m_keyboardShowFlag = false;
    } else if(commonMenuWidget->opendSpinBoxIndex >= 0) {
        pVirtualKeyboard->close_persistent_editor(commonMenuWidget->model, commonMenuWidget->pTableView, commonMenuWidget->opendSpinBoxIndex);
        commonMenuWidget->m_keyboardShowFlag = false;
    }
    m_hiddenKeyboardFlag = false;
    disconnect(pVirtualKeyboard, SIGNAL(close_keyboard()), this, SLOT(slot_keyboard_close_clicked()));
    disconnect(pVirtualKeyboard, SIGNAL(input_number(QString)), this, SLOT(do_input_number(QString)));
}

void MainWindow::do_input_number(QString string)
{
    if(ui->widget_thirdMenu->opendSpinBoxIndex >= 0) {
        pVirtualKeyboard->input_lineedit_data(ui->widget_thirdMenu->pTableView, string, ui->widget_thirdMenu->opendSpinBoxIndex);
    } else if(ui->widgetTopLeft->opendSpinBoxIndex >= 0) {
        pVirtualKeyboard->input_lineedit_data(ui->widgetTopLeft->pTableViewGain, string, ui->widgetTopLeft->opendSpinBoxIndex);
    } else if(ui->widgetTopLeft->opendSpinBoxIndex == 2) {
        pVirtualKeyboard->input_lineedit_data(ui->widgetTopLeft->pTableViewAngle, string, ui->widgetTopLeft->opendSpinBoxIndex);
    } else if(commonMenuWidget->opendSpinBoxIndex >= 0) {
        pVirtualKeyboard->input_lineedit_data(commonMenuWidget->pTableView, string, commonMenuWidget->opendSpinBoxIndex);
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
    if(firstSecondMenu->menuList.at(m_firstMenuNum)->hasFocus()) {
        if (type == Mcu::ROTARY_UP) {
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Up, Qt::NoModifier);
            QApplication::sendEvent(firstSecondMenu->menuList.at(m_firstMenuNum), event);

            if(m_rotarySecondMenuNum > 0){
                m_rotarySecondMenuNum--;
            }
        } else {
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Down, Qt::NoModifier);
            QApplication::sendEvent(firstSecondMenu->menuList.at(m_firstMenuNum), event);

            if(m_firstMenuNum == 0 || m_firstMenuNum == 4 || m_firstMenuNum == 5 || m_firstMenuNum == 6 || m_firstMenuNum == 8){
                if(m_rotarySecondMenuNum < 3){
                    m_rotarySecondMenuNum++;
                }
            }else if(m_firstMenuNum == 1 || m_firstMenuNum == 3 || m_firstMenuNum == 7){
                if(m_rotarySecondMenuNum < 4){
                    m_rotarySecondMenuNum++;
                }
            }else if(m_firstMenuNum == 2){
                if(m_rotarySecondMenuNum < 2){
                    m_rotarySecondMenuNum++;
                }
            }
        }
    }
}

void MainWindow::key_sure(Mcu::KeyType key)
{
    if(firstSecondMenu->menuList.at(m_firstMenuNum)->hasFocus()) {
        if(key == Mcu::KEY_SURE) {
            ui->widget_thirdMenu->set_third_menu_name(m_firstMenuNum, m_rotarySecondMenuNum);
        }
    }
}

