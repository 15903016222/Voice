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

  commonMenuWidget = new CommonMenuWidget(this);
  commonMenuWidget->move(0, 530);

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

  firstMenuNum = 0;
  secondMenuNum = 0;
  hiddenSecondMenuFlag = false;
  hiddenThirdMenuFlag = false;

  QObject::connect(ui->widget_firstSecondMenu->toolBox.at(0), SIGNAL(currentChanged(int)), this, SLOT(slot_setThirdMenuName(int)));

  for(int i = 0; i < FIRST_MENU_NUMBER; i++)
  {
    QObject::connect(ui->widget_firstSecondMenu->menuList.at(i), SIGNAL(clicked(QModelIndex)), this, SLOT(slot_secondMenuItemClicked(QModelIndex)));
  }
}

void MainWindow::slot_setThirdMenuName(int index)
{
  if(ui->widget_firstSecondMenu->hideTopMenu)
  {
    firstMenuNum = index + 4;
  }else{
    firstMenuNum = index;
  }
  ui->widget_thirdMenu->setThirdMenuName(firstMenuNum, 0); //init
}

void MainWindow::slot_secondMenuItemClicked(QModelIndex index)
{
  QStandardItem *item = ui->widget_firstSecondMenu->modelList.at(firstMenuNum)->itemFromIndex(index);

  secondMenuNum = item->row();

  for(int j = 0; j < SECOND_MENU_NUMBER; j++)
  {
    QModelIndex modelIndex = ui->widget_firstSecondMenu->modelList.at(firstMenuNum)->index(j, 0);
    QStandardItem *item = ui->widget_firstSecondMenu->modelList.at(firstMenuNum)->itemFromIndex(modelIndex);
    if(modelIndex == index){
      item->setForeground(QBrush(Qt::red));
    }else{
      item->setForeground(QBrush(Qt::yellow));
    }
  }
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

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
  if(object == ui->frame_showPlot)
  {
    if(event->type() == QEvent::MouseButtonDblClick)
    {
      static bool flagShowPlotState = true;
      flagShowPlotState = !flagShowPlotState;
      if (!flagShowPlotState) {
        ui->widget_firstSecondMenu->show();
        ui->widget_thirdMenu->show();
        commonMenuWidget->hide();
      }else {
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
