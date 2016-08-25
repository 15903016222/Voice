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
