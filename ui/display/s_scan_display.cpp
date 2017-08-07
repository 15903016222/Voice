#include "s_scan_display.h"
#include "ui_s_scan_display.h"
#include <device/device.h>

SscanDisplay::SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SscanDisplay),
    m_group(grp)
{
    ui->setupUi(this);

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);

    ui->rightRulerWidget->set_type(RulerWidget::RIGHT);
    ui->rightRulerWidget->set_direction(RulerWidget::Down);

    ui->colorBarWidget->set_palette(DplDevice::Device::instance()->display()->palette());
}

SscanDisplay::~SscanDisplay()
{
    delete ui;
}
