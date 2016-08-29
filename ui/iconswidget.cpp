#include "iconswidget.h"
#include "ui_iconswidget.h"

IconsWidget::IconsWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::IconsWidget)
{
  ui->setupUi(this);
}

IconsWidget::~IconsWidget()
{
  delete ui;
}

void IconsWidget::iconsWidgetRetranslateUi()
{
  ui->retranslateUi(this);
}


void IconsWidget::on_pushButton_keyboard_clicked()
{
  MyInputPanel myInputPanelDlg;
  myInputPanelDlg.setWindowFlags(Qt::FramelessWindowHint);
  myInputPanelDlg.setModal(true);
  myInputPanelDlg.showNormal();
  myInputPanelDlg.exec();
}

void IconsWidget::showBattery()
{
#if 0
  SYSTEM_POWER_STATUS systemPowerSatus;
  GetSystemPowerStatus(&systemPowerSatus);
  int remaindPower = (int)systemPowerSatus.BatteryLifePercent;

  if(remaindPower > 75)
  {
    QPixmap pixmapBattery(":/file/resources/battery2.jpg");
    ui->label_2->setPixmap(pixmapBattery);
  }
  else if(remaindPower > 50 && remaindPower <= 75)
  {
    QPixmap pixmapBattery(":/file/resources/BatteryIcon2.png");
    ui->label_1->setPixmap(pixmapBattery);
  }
  else if(remaindPower > 25 && remaindPower <= 50)
  {
    QPixmap pixmapBattery(":/file/resources/BatteryIcon1.png");
    ui->label_1->setPixmap(pixmapBattery);
  }
  else if(remaindPower > 0 && remaindPower <= 25)
  {
    QPixmap pixmapBattery(":/file/resources/BatteryIcon1.png");
    ui->label_1->setPixmap(pixmapBattery);
  }
  else
  {
    QPixmap pixmapBattery(":/file/resources/BatteryIcon1.png");
    ui->label_2->setPixmap(pixmapBattery);
  }
#endif
}
