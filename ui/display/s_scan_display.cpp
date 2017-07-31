#include "s_scan_display.h"
#include "ui_s_scan_display.h"

SscanDisplay::SscanDisplay(DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SscanDisplay),
    m_group(grp)
{
    ui->setupUi(this);

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);
    ui->rightRulerWidget->set_type(RulerWidget::RIGHT);

    ui->colorBarWidget->load_file("/opt/mercury/palette/ONDT_Amplitude.pal");
}

SscanDisplay::~SscanDisplay()
{
    delete ui;
}
