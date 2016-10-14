#include "mainwindow.h"
#include "ui_mainwindow.h"

class MainWindowPrivate
{
public:
    MainWindowPrivate(MainWindow * parent):
        q_ptr( parent )
    {

    }

    ~MainWindowPrivate()
    {

    }

protected:
    MainWindow * const q_ptr;
private:
    Q_DECLARE_PUBLIC(MainWindow)
};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    d_ptr(new MainWindowPrivate(this))
{
    m_mcu = Mcu::get_mcu();
    ui->setupUi(this);

    init_ui();

    connect(m_mcu, SIGNAL(key_event(int)), this, SLOT(keyBottom_menu(int)));
    connect(m_mcu, SIGNAL(key_event(int)), this, SLOT(keyLeft_menu(int)));
    connect(m_mcu, SIGNAL(key_event(int)), this, SLOT(keyLeft_back(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d_ptr;
}

void MainWindow::init_ui()
{
    this->resize(800, 600);

    ui->widget_firstSecondMenu->hide();
    ui->widget_thirdMenu->hide();

    ui->frame_showPlot->installEventFilter(this);
    ui->widget_thirdMenu->installEventFilter(this);

    firstMenuNum = 0;
    secondMenuNum = 0;
    hiddenFirstSecondMenuFlag = false;
    hiddenThirdMenuFlag = false;
    hiddenCommonMenuFlag = false;

    firstSecondMenu = new FirstSecondMenuWidget(this);
#if QT_VERSION <= QT_VERSION_CHECK(5, 0, 0)
    firstSecondMenu->resize_height(firstMenuNum);
#endif
    commonMenuWidget = new CommonMenuWidget(this);
    commonMenuWidget->hide();
    commonMenuButton = new CommonMenuButton(this);
    commonMenuButton->resize(40, 40);
    commonMenuButton->show();

    translator = new QTranslator(this);
    qApp->installTranslator(translator);
//    translatorChineseUI(); // default Chinese
//    firstSecondMenu->init_ui();
//    connect(ui->widget_thirdMenu, SIGNAL(translater_ZH()), this, SLOT(translatorChineseUI()));
//    connect(ui->widget_thirdMenu, SIGNAL(translater_EN()), this, SLOT(translatorEnglishUI()));

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
    connect(this, SIGNAL(clickedMenuIndex(int)), this, SLOT(scroll_menu(int)));
    connect(ui->widget_thirdMenu, SIGNAL(retranslate_ui(QString)), this, SLOT(update_translator(QString)));
}

void MainWindow::keyBottom_menu(int key)
{
    if(key == 227) {
        show_hidden_Menu();
        keyValue = 227;
    }
}

void MainWindow::keyLeft_menu(int key)
{
    if(key == 210) {
        show_hidden_Menu();
        keyValue = 210;
    }
}

void MainWindow::keyLeft_back(int key)
{
    if(key == 217) {
        switch(keyValue) {
        case 210:
            keyLeft_menu(210);
            break;
        case 227:
            keyBottom_menu(227);
            break;

        default:break;
        }
    }
}

void MainWindow::slot_firstMenuToolBoxCurrentChanged(int index)
{
    ui->widget_thirdMenu->set_third_menu_name(index, 0); //init
    firstMenuNum = index;
    QModelIndex modelIndex = firstSecondMenu->modelList.at(index)->index(0, 0);
    firstSecondMenu->set_second_menu_item_style(firstMenuNum, modelIndex);

    hiddenArrowFlag = true;

    emit clickedMenuIndex(firstMenuNum);
    show_hidden_arrow();
}

void MainWindow::slot_secondMenuItemClicked(QModelIndex index)
{
    QStandardItem *item = firstSecondMenu->modelList.at(firstMenuNum)->itemFromIndex(index);
    secondMenuNum = item->row();

    firstSecondMenu->set_second_menu_item_style(firstMenuNum, index);
    ui->widget_thirdMenu->set_third_menu_name(firstMenuNum, secondMenuNum);

    if(firstMenuNum == 8){
        if(secondMenuNum == 1){
            ui->widget_thirdMenu->set_currentDateToMenu();
            ui->widget_thirdMenu->set_currentTimeToMenu();
        }else if(secondMenuNum == 2){
            ui->widget_thirdMenu->set_currentIPToMenu();
            ui->widget_thirdMenu->set_currentSubNetToMenu();
        }
    }
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
        if(hiddenArrowFlag == false) {
              ui->pushButton_top->hide();
        } else {
            ui->pushButton_top->show();
            hiddenArrowFlag = false;
         }
    } else {
        ui->pushButton_top->show();
    }

    if(menuBottomY == scrollBottomY ) {
        if(hiddenArrowFlag == false) {
            ui->pushButton_bottom->hide();
        } else {
            ui->pushButton_bottom->show();
            hiddenArrowFlag = false;
         }
    } else {
        ui->pushButton_bottom->show();
    }
}

void MainWindow::slot_pushButton_commonMenuClicked()
{
    hiddenCommonMenuFlag = !hiddenCommonMenuFlag;
    if(hiddenCommonMenuFlag) {
        ui->widget_firstSecondMenu->hide();
        ui->widget_thirdMenu->hide();
        hiddenFirstSecondMenuFlag = false;
        commonMenuWidget->show();
        commonMenuButton->raise();
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonAfter.png)}");
    } else {
        commonMenuWidget->hide();
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
        hiddenFirstSecondMenuFlag = false;
    }
}

void MainWindow::update_translator(QString string)
{
    if(string == "Chinese") {
        translator->load(":/file/translator/phascanII_UI_Chinese.qm");
        ui->retranslateUi(this);
        ui->widgetTopLeft->retranslate_top_menu_ui();
        ui->widgetTopLeft->set_top_menu_font();
        firstSecondMenu->retranslate_main_menu_ui(string);
//        ui->widget_thirdMenu->retranslate_third_menu_ui(string);
        commonMenuWidget->retranslate_common_menu_ui();
    } else if(string == "English") {
        translator->load(":/file/translator/phascanII_UI_English.qm");
        ui->retranslateUi(this);
        ui->widgetTopLeft->retranslate_top_menu_ui();
        ui->widgetTopLeft->set_top_menu_font();
        firstSecondMenu->retranslate_main_menu_ui(string);
//        ui->widget_thirdMenu->retranslate_third_menu_ui(string);
        commonMenuWidget->retranslate_common_menu_ui();
    }
}

#ifdef WIN32
bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->frame_showPlot) {
        if(event->type() == QEvent::MouseButtonPress) {//QEvent::MouseButtonDblClick
            show_hidden_Menu();
        }
    }
    return QWidget::eventFilter(object, event);
}
#endif

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
    if(scrollRect.contains(event->pos())) {
        mainMenuStartPos = event->pos().y();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *moveEvent)
{
    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
    if(scrollRect.contains(moveEvent->pos())) {
        mainMenuEndPos = moveEvent->pos().y();
        int scrollLength = mainMenuEndPos - mainMenuStartPos;
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

void MainWindow::show_hidden_Menu()
{
    hiddenFirstSecondMenuFlag = !hiddenFirstSecondMenuFlag;
    if(hiddenFirstSecondMenuFlag) {
        ui->widget_firstSecondMenu->show();
        ui->widget_thirdMenu->show();
        commonMenuWidget->hide();
        hiddenCommonMenuFlag = false;
        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
        firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), firstSecondMenu->geometry().height());
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
        show_hidden_arrow();
    } else {
        ui->widget_firstSecondMenu->hide();
        ui->widget_thirdMenu->hide();
    }
}

void MainWindow::scroll_menu(int index)
{
    if(index >= 4 && index < 9) {
        ui->scrollArea->viewport()->scroll(0, -50);
        ui->scrollArea->update();
    }
}

