#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#include <QGlib/Connect>
#include <QGlib/Error>
#include <QGst/Pipeline>
#include <QGst/ElementFactory>
#include <QGst/Bus>
#include <QGst/Message>

class MainWindowPrivate
{
public:
  MainWindowPrivate(MainWindow * parent):
    q_ptr( parent )
  {

  }

  ~MainWindowPrivate()
  {
    if(pipeline)
    {
      pipeline->setState(QGst::StateNull);
      pipeline.clear();
    }
  }

public:
  void handlePipelineStateChange(const QGst::StateChangedMessagePtr & scm)
  {
    switch (scm->newState()) {
    case QGst::StatePlaying:
      //start the timer when the pipeline starts playing
      break;
    case QGst::StatePaused:
      //stop the timer when the pipeline pauses
      if(scm->oldState() == QGst::StatePlaying) {

      }
      break;
    default:
      break;
    }
  }
  //  Members
protected:
  QGst::PipelinePtr pipeline;
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
  linkPluginsToConnectDevice();

  ui->widget_firstSecondMenu->hide();
  ui->widget_thirdMenu->hide();

  ui->frame_showPlot->installEventFilter(this);
  ui->widget_thirdMenu->installEventFilter(this);

  firstSecondMenu = new FirstSecondMenuWidget(this);
  commonMenuWidget = new CommonMenuWidget(this);
  commonMenuButton = new CommonMenuButton(this);
  commonMenuButton->show();

  firstMenuNum = 0;
  secondMenuNum = 0;
  hiddenSecondMenuFlag = false;
  hiddenThirdMenuFlag = false;
  hiddenCommonMenuFlag = false;

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

}

void MainWindow::slot_firstMenuToolBoxCurrentChanged(int index)
{
  ui->widget_thirdMenu->setThirdMenuName(index, 0); //init
  firstMenuNum = index;

  firstSecondMenu->initSecondMenuItem(firstMenuNum);

  arrowShowFlag();
}

void MainWindow::slot_secondMenuItemClicked(QModelIndex index)
{
  QStandardItem *item = firstSecondMenu->modelList.at(firstMenuNum)->itemFromIndex(index);
  secondMenuNum = item->row();

  firstSecondMenu->secondMenuItemClicked(firstMenuNum, index);
  ui->widget_thirdMenu->setThirdMenuName(firstMenuNum, secondMenuNum);
}

void MainWindow::linkPluginsToConnectDevice()
{
  if(!d_ptr->pipeline)
  {
    d_ptr->pipeline = QGst::Pipeline::create();

    QGst::ElementPtr bin;
    QGst::ElementPtr videosink;

    try {
      bin = QGst::Bin::fromDescription("sathidsrc vid=0xc251 pid=0x1707 !satanyscandec name=devicedec !satarender");

      videosink = QGst::ElementFactory::make("qt5videosink");

      ui->widgetUSView->setVideoSink(videosink);

      // watch the bus
      QGst::BusPtr bus = d_ptr->pipeline->bus();
      bus->addSignalWatch();
      QGlib::connect(bus, "message", this, &MainWindow::onGstBusMessage );

      d_ptr->pipeline->add(bin);
      d_ptr->pipeline->add(videosink);
      bin->link(videosink);

    } catch(const QGlib::Error & error){
      QMessageBox::critical(this, tr("Programer Error"), tr("One ore more required elements are missing, Please try reinstall. Aborting..."));
    }
  }

  if(d_ptr->pipeline)
  {
    d_ptr->pipeline->setState(QGst::StatePlaying);
  }
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
    commonMenuButton->resize(width * 25 / 800, height * 25 /600);
    commonMenuButton->move(width - commonMenuButton->geometry().width(), height - commonMenuButton->geometry().height());
  }else
  {
    ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
    firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), height * menuHeight / this->geometry().height());
    commonMenuWidget->resize(width, height * 70 / 600);
    commonMenuWidget->move(0, height * 530 / 600);
    commonMenuButton->resize(25, 25);
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

  if(menuTopY == scrollTopY)
  {
    ui->pushButton_top->hide();
  }else{
    ui->pushButton_top->show();
  }

  if(menuBottomY == scrollBottomY )
  {
    ui->pushButton_bottom->hide();
  }else{
    ui->pushButton_bottom->show();
  }
}

void MainWindow::slot_pushButton_commonMenuClicked()
{
  hiddenCommonMenuFlag = !hiddenCommonMenuFlag;
  if(!hiddenCommonMenuFlag)
  {
    ui->widget_firstSecondMenu->hide();
    ui->widget_thirdMenu->hide();
    commonMenuWidget->show();

    commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonBefore.png)}");
  }else {
    commonMenuWidget->hide();
    commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonAfter.png)}");
  }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
  if(object == ui->frame_showPlot)
  {
    if(event->type() == QEvent::MouseButtonDblClick)
    {
      static bool flagShowPlotState = true;
      flagShowPlotState = !flagShowPlotState;

      if(!flagShowPlotState)
      {
        ui->widget_firstSecondMenu->show();
        ui->widget_thirdMenu->show();
        commonMenuWidget->hide();
        hiddenCommonMenuFlag = true;

        ui->scrollArea->resize(ui->widget_scrollArea->geometry().width(), ui->widget_scrollArea->geometry().height());
        firstSecondMenu->resize(ui->widget_scrollArea->geometry().width(), firstSecondMenu->geometry().height());
        commonMenuButton->pushButton_commonMenu.at(0)->setStyleSheet("QPushButton{border-image:url(:/file/resources/buttonAfter.png)}");
        arrowShowFlag();
      }else{
        ui->widget_firstSecondMenu->hide();
        ui->widget_thirdMenu->hide();
        commonMenuWidget->show();
      }
    }
  }
  return QWidget::eventFilter(object, event);
}

void MainWindow::onGstBusMessage(const QGst::MessagePtr &message)
{
  switch (message->type()) {
  case QGst::MessageEos: //End of stream. We reached the end of the file.
    d_ptr->pipeline->setState(QGst::StateNull);
    break;
  case QGst::MessageError: //Some error occurred.
    d_ptr->pipeline->setState(QGst::StateNull);

    QMessageBox::information(this, tr("Runtime hint"), tr("Connected device error. Did you connect the device!"));

    d_ptr->pipeline.clear();
    ui->widgetUSView->releaseVideoSink();
    break;
  case QGst::MessageStateChanged: //The element in message->source() has changed state
    if (message->source() == d_ptr->pipeline) {
      d_ptr->handlePipelineStateChange(message.staticCast<QGst::StateChangedMessage>());
    }
    break;
  default:
    break;
  }
}
