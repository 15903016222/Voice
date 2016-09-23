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
    ui->setupUi(this);

    initUI();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete d_ptr;
}

void MainWindow::initUI()
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
 //   firstSecondMenu->resize_height(firstMenuNum);
    commonMenuWidget = new CommonMenuWidget(this);
    commonMenuWidget->hide();
    commonMenuButton = new CommonMenuButton(this);
    commonMenuButton->resize(40, 40);
    commonMenuButton->show();

    translator = new QTranslator(this);
    qApp->installTranslator(translator);
//    translatorChineseUI(); // default Chinese
//    firstSecondMenu->initUI();

    QObject::connect(firstSecondMenu->toolBox.at(0), SIGNAL(currentChanged(int)), this, SLOT(slot_firstMenuToolBoxCurrentChanged(int)));

    for(int i = 0; i < FIRST_MENU_NUMBER; i++)
    {
        QObject::connect(firstSecondMenu->menuList.at(i), SIGNAL(clicked(QModelIndex)), this, SLOT(slot_secondMenuItemClicked(QModelIndex)));
    }

    ui->scrollArea = new QScrollArea(ui->widget_scrollArea);
    ui->scrollArea->setFrameShape(QFrame::NoFrame);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setWidget(firstSecondMenu);

    QObject::connect(commonMenuButton->pushButton_commonMenu.at(0), SIGNAL(clicked()), this, SLOT(slot_pushButton_commonMenuClicked()));
    connect(this, SIGNAL(clickedMenuIndex(int)), this, SLOT(scroll_menu(int)));
}

void MainWindow::slot_firstMenuToolBoxCurrentChanged(int index)
{
    ui->widget_thirdMenu->setThirdMenuName(index, 0); //init
    firstMenuNum = index;

    firstSecondMenu->initSecondMenuItem(firstMenuNum);

    hiddenArrowFlag = true;

    emit clickedMenuIndex(firstMenuNum);
    arrowShowFlag();
}

void MainWindow::slot_secondMenuItemClicked(QModelIndex index)
{
    QStandardItem *item = firstSecondMenu->modelList.at(firstMenuNum)->itemFromIndex(index);
    secondMenuNum = item->row();

    firstSecondMenu->secondMenuItemClicked(firstMenuNum, index);
    ui->widget_thirdMenu->setThirdMenuName(firstMenuNum, secondMenuNum);
}

void MainWindow::on_pushButton_top_clicked()
{
    int menuTopY = firstSecondMenu->pos().y() + ui->scrollArea->geometry().y();
    int scrollTopY = ui->scrollArea->geometry().y();

    if(menuTopY < (scrollTopY -20))
    {
        ui->scrollArea->viewport()->scroll(0, 20);
    }else{
        ui->scrollArea->viewport()->scroll(0, scrollTopY - menuTopY);
    }

    arrowShowFlag();
}

void MainWindow::on_pushButton_bottom_clicked()
{
    int menuBottomY = firstSecondMenu->pos().y() + firstSecondMenu->geometry().height() + ui->scrollArea->geometry().y();
    int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();

    if((menuBottomY - 20) > scrollBottomY)
    {
        ui->scrollArea->viewport()->scroll(0, -20);
    }else{
        ui->scrollArea->viewport()->scroll(0, -(menuBottomY - scrollBottomY));
    }

    arrowShowFlag();
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    int width = event->size().width();
    int height = event->size().height();
    int oldWidth = event->oldSize().width();
    int oldHeight = event->oldSize().height();
    int menuHeight = firstSecondMenu->geometry().height();

    if(oldWidth > 0 && oldHeight > 0)
    {
        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());

        if(ui->widget_scrollArea->geometry().height() < 600)
        {
            firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), height * menuHeight / oldHeight);
        }else{
            firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
        }
        commonMenuWidget->resize(width, height * 70 / 600);
        commonMenuWidget->move(0, height * 530 / 600);
        commonMenuButton->move(width - commonMenuButton->geometry().width(), height - commonMenuButton->geometry().height());
    }else
    {
        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
        firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), height * menuHeight / this->geometry().height());
        commonMenuWidget->resize(width, height * 70 / 600);
        commonMenuWidget->move(0, height * 530 / 600);
        commonMenuButton->move(this->geometry().width() - commonMenuButton->geometry().width(), this->geometry().height() - commonMenuButton->geometry().height());
    }
    arrowShowFlag();
}

void MainWindow::arrowShowFlag()
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
    if(hiddenCommonMenuFlag)
    {
        ui->widget_firstSecondMenu->hide();
        ui->widget_thirdMenu->hide();
        hiddenFirstSecondMenuFlag = false;
        commonMenuWidget->show();
        commonMenuButton->raise();
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonAfter.png)}");
    }else {
        commonMenuWidget->hide();
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
        hiddenFirstSecondMenuFlag = false;
    }
}

void MainWindow::updateTranslator()
{
    ui->retranslateUi(this);
    ui->widgetTopLeft->reTranslatorTopMenuUi();
    ui->widgetTopLeft->setTopMenuFont();
    firstSecondMenu->reTranslatorFirstSecondMenuUi();
    ui->widget_thirdMenu->reTranslatorThirdMenuUi();
    commonMenuWidget->reTranslatorCommonMenuUi();
}

void MainWindow::translatorChineseUI()
{
    translator->load(":/file/translator/phascanII_UI_Chinese.qm");
    updateTranslator();
}

void MainWindow::translatorEnglishUI()
{
    translator->load(":/file/translator/phascanII_UI_English.qm");
    updateTranslator();
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->frame_showPlot)
    {
        if(event->type() == QEvent::MouseButtonPress) //QEvent::MouseButtonDblClick
        {
            hiddenFirstSecondMenuFlag = !hiddenFirstSecondMenuFlag;
            if(hiddenFirstSecondMenuFlag)
            {
                ui->widget_firstSecondMenu->show();
                ui->widget_thirdMenu->show();
                commonMenuWidget->hide();
                hiddenCommonMenuFlag = false;
                ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
                firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), firstSecondMenu->geometry().height());
                commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
                arrowShowFlag();
            }else{
                ui->widget_firstSecondMenu->hide();
                ui->widget_thirdMenu->hide();
            }
        }
    }
    return QWidget::eventFilter(object, event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
    if(scrollRect.contains(event->pos()))
    {
        mainMenuStartPos = event->pos().y();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *moveEvent)
{
    QRect scrollRect = QRect(ui->widget_scrollArea->pos() + ui->widget->pos() +
                             ui->widget_firstSecondMenu->pos() + ui->widgetUSView->pos() +
                             ui->framePlot->pos() + ui->centralWidget->pos() ,ui->widget_scrollArea->size());
    if(scrollRect.contains(moveEvent->pos()))
    {
        mainMenuEndPos = moveEvent->pos().y();
        int scrollLength = mainMenuEndPos - mainMenuStartPos;
        int menuTopY = firstSecondMenu->pos().y() + ui->scrollArea->geometry().y();
        int scrollTopY = ui->scrollArea->geometry().y();
        int menuBottomY = firstSecondMenu->pos().y() + firstSecondMenu->geometry().height() + ui->scrollArea->geometry().y();
        int scrollBottomY = ui->scrollArea->geometry().y() + ui->scrollArea->geometry().height();
        if(scrollLength < 0)
        {
            if((menuBottomY + scrollLength) > scrollBottomY)
            {
                ui->scrollArea->viewport()->scroll(0, scrollLength);
            }
            else
            {
                ui->scrollArea->viewport()->scroll(0, -(menuBottomY - scrollBottomY));
            }
        }
        else
        {
            if((menuTopY + scrollLength) < scrollTopY)
            {
                ui->scrollArea->viewport()->scroll(0, scrollLength);
            }
            else
            {
                ui->scrollArea->viewport()->scroll(0, scrollTopY - menuTopY);
            }
        }
        arrowShowFlag();
    }
}

void MainWindow::scroll_menu(int index)
{
  if(index >= 4 && index < 9)
  {
    ui->scrollArea->viewport()->scroll(0, -50);
    ui->scrollArea->update();
  }
}

