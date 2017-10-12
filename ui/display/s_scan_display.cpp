#include "s_scan_display.h"
#include "ui_scan_display.h"

#include "s_scan_scene.h"
#include "scan_view.h"
#include "base_scan_scene.h"
#include "c_scan_encoder_scene.h"
#include "c_scan_time_scene.h"
#include <device/device.h>

SscanDisplay::SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanDisplay),
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

    connect(static_cast<DplDevice::Group *>(grp.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    ui->titleLabel->setText(QString("S-Scan|Grp%1").arg(m_group->index()+1));
}

SscanDisplay::~SscanDisplay()
{
    delete ui;
    delete m_view;
    delete m_scene;
}

void SscanDisplay::do_data_event(const DplSource::BeamsPointer &beams)
{
    m_scene->set_beams(beams);
}

