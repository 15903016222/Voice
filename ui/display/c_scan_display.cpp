#include "c_scan_display.h"
#include "ui_scan_display.h"

#include "scan_view.h"
#include "c_scan_scene.h"

#include <device/device.h>

CscanDisplay::CscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanDisplay),
    m_group(grp),
    m_view(new ScanView),
    m_scene(new CscanScene(DplDevice::Device::instance()->display()->palette()))
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

    ui->titleLabel->setText(QString("C-Scan|Grp%1").arg(m_group->index()+1));
}

CscanDisplay::~CscanDisplay()
{
    delete ui;
    delete m_view;
    delete m_scene;
}
