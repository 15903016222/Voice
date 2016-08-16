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
  Qt::WindowFlags flags = Qt::Dialog | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint;
  myInputPanelDlg.setWindowFlags( flags );
  myInputPanelDlg.setModal(true);
  myInputPanelDlg.showNormal();
  myInputPanelDlg.exec();
}
