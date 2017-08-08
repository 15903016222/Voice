#include "s_scan_display.h"
#include "ui_s_scan_display.h"

#include "scan_view.h"
#include "s_scan_scene.h"

#include <device/device.h>

SscanDisplay::SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SscanDisplay),
    m_group(grp),
    m_view(new ScanView),
    m_scene(new SscanScene(DplDevice::Device::instance()->display()->palette()))
{
    ui->setupUi(this);
    ui->scanLayout->addWidget(m_view);

    connect(m_view, SIGNAL(size_changed(QSize)),
            m_scene, SLOT(set_size(QSize)));

    m_view->setScene(m_scene);

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);

    ui->rightRulerWidget->set_type(RulerWidget::RIGHT);
    ui->rightRulerWidget->set_direction(RulerWidget::Down);

    ui->colorBarWidget->set_palette(DplDevice::Device::instance()->display()->palette());


    connect(static_cast<DplSource::Beams *>(grp->beams().data()),
            SIGNAL(data_event()),
            this, SLOT(do_data_event()));
}

SscanDisplay::~SscanDisplay()
{
    delete ui;
}

void SscanDisplay::do_data_event()
{
    m_scene->show_beams(m_group->beams());
}

