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
    mainMenu->move(0, 175);

    subMenu = new SubMenu(this);
    subMenu->hide();;
    subMenu->move(179, 530);

//    menuBar = new MenuBar(this);
//    menuBar->hide();
//    menuBar->move(0, 90);

    connect(mainMenu, SIGNAL(click_main_menu(int)), subMenu, SLOT(set_third_menu(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init_ui()
{
//    ui->widget_firstSecondMenu->hide();
//    ui->widget_thirdMenu->hide();

//    ui->frame_showPlot->installEventFilter(this);
//    ui->widget_thirdMenu->installEventFilter(this);

//    m_firstMenuNum = 0;
//    m_secondMenuNum = 0;
    m_hiddenFirstSecondMenuFlag = false;
//    m_hiddenThirdMenuFlag = false;
//    m_hiddenCommonMenuFlag = false;
//    m_hiddenKeyboardFlag = false;

//    firstSecondMenu = new FirstSecondMenuWidget(this);
//#if QT_VERSION <= QT_VERSION_CHECK(5, 0, 0)
//    firstSecondMenu->resize_height(m_firstMenuNum);
//#endif
//    commonMenuWidget = new CommonMenuWidget(this);
//    commonMenuWidget->hide();
//    commonMenuButton = new CommonMenuButton(this);
//    commonMenuButton->resize(40, 40);
//    commonMenuButton->show();

//    pVirtualKeyboard = new VirtualKeyboard(this);
//    pVirtualKeyboard->hide();

//    translator = new QTranslator(this);
//    qApp->installTranslator(translator);

//    QObject::connect(firstSecondMenu->toolBox.at(0), SIGNAL(currentChanged(int)), this, SLOT(slot_firstMenuToolBoxCurrentChanged(int)));

//    for(int i = 0; i < FIRST_MENU_NUMBER; i++) {
//        QObject::connect(firstSecondMenu->menuList.at(i), SIGNAL(clicked(QModelIndex)), this, SLOT(slot_secondMenuItemClicked(QModelIndex)));
//    }

//    ui->scrollArea = new QScrollArea(ui->widget_scrollArea);
//    ui->scrollArea->setFrameShape(QFrame::NoFrame);
//    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->scrollArea->setWidget(firstSecondMenu);

//    QObject::connect(commonMenuButton->pushButton_commonMenu.at(0), SIGNAL(clicked()), this, SLOT(slot_pushButton_commonMenuClicked()));
//    QObject::connect(ui->iconsBarWidget, SIGNAL(keyboard_event()), this, SLOT(do_keyboard_event()));

//    connect(this, SIGNAL(clickedMenuIndex(int)), this, SLOT(scroll_menu(int)));
//    connect(ui->widget_thirdMenu, SIGNAL(retranslate_ui(QString)), this, SLOT(update_translator(QString)));
//    connect(pVirtualKeyboard, SIGNAL(close_keyboard()), this, SLOT(slot_keyboard_close_clicked()));
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
        VInput::get_vinput()->send(VInput::Key_Back);
        break;
    default:
        break;
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//    int width = event->size().width();
//    int height = event->size().height();
//    int oldWidth = event->oldSize().width();
//    int oldHeight = event->oldSize().height();
//    int menuHeight = firstSecondMenu->geometry().height();

//    if(oldWidth > 0 && oldHeight > 0) {
//        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());

//        if(ui->widget_scrollArea->geometry().height() < 600) {
//            firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), height * menuHeight / oldHeight);
//        } else {
//            firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
//        }
//        commonMenuWidget->resize(width, height * 70 / 600);
//        commonMenuWidget->move(0, height * 530 / 600);
//        commonMenuButton->move(width - commonMenuButton->geometry().width(), height - commonMenuButton->geometry().height());
//    } else {
//        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
//        firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), height * menuHeight / this->geometry().height());
//        commonMenuWidget->resize(width, height * 70 / 600);
//        commonMenuWidget->move(0, height * 530 / 600);
//        commonMenuButton->move(this->geometry().width() - commonMenuButton->geometry().width(), this->geometry().height() - commonMenuButton->geometry().height());
//    }
//    show_hidden_arrow();
}

void MainWindow::show_hidden_arrow()
{
//    int menuTopY = firstSecondMenu->pos().y() + ui->scrollArea->geometry().y();
//    int scrollTopY = ui->scrollArea->geometry().y();
//    int menuBottomY = firstSecondMenu->pos().y() + firstSecondMenu->geometry().height() + ui->scrollArea->geometry().y();
//    int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();

//    if(menuTopY == scrollTopY) {
//        if(m_hiddenArrowFlag == false) {
//              ui->pushButton_top->hide();
//        } else {
//            ui->pushButton_top->show();
//            m_hiddenArrowFlag = false;
//         }
//    } else {
//        ui->pushButton_top->show();
//    }

//    if(menuBottomY == scrollBottomY ) {
//        if(m_hiddenArrowFlag == false) {
//            ui->pushButton_bottom->hide();
//        } else {
//            ui->pushButton_bottom->show();
//            m_hiddenArrowFlag = false;
//         }
//    } else {
//        ui->pushButton_bottom->show();
//    }
}

void MainWindow::slot_pushButton_commonMenuClicked()
{
//    m_hiddenCommonMenuFlag = !m_hiddenCommonMenuFlag;
//    if(m_hiddenCommonMenuFlag) {
//        ui->widget_firstSecondMenu->hide();
//        ui->widget_thirdMenu->hide();
//        m_hiddenFirstSecondMenuFlag = false;
//        commonMenuWidget->show();
//        commonMenuButton->raise();
//        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonAfter.png)}");
//    } else {
//        commonMenuWidget->hide();
//        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
//        m_hiddenFirstSecondMenuFlag = false;
//    }
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
    }
    return QMainWindow::keyPressEvent(event);
}

void MainWindow::show_hidden_Menu()
{
    m_hiddenFirstSecondMenuFlag = !m_hiddenFirstSecondMenuFlag;
    if(m_hiddenFirstSecondMenuFlag) {
//        ui->widget_firstSecondMenu->show();
//        ui->widget_thirdMenu->show();
//        commonMenuWidget->hide();
//        m_hiddenCommonMenuFlag = false;
//        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
//        firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), firstSecondMenu->geometry().height());
//        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
//        show_hidden_arrow();

//        firstSecondMenu->menuList.at(m_firstMenuNum)->setFocus();
//        menuBar->show();
        subMenu->show();
        mainMenu->show();

    } else {
        mainMenu->hide();
//        menuBar->hide();
        subMenu->hide();
        qDebug() << "hide";
//        ui->widget_firstSecondMenu->hide();
//        ui->widget_thirdMenu->hide();
    }
}

void MainWindow::scroll_menu(int index)
{
//    if(index >= 4 && index < 9) {
//        ui->scrollArea->viewport()->scroll(0, -50);
//        ui->scrollArea->update();
//    }
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

