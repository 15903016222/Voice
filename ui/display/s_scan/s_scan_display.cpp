#include "s_scan_display.h"
#include "ui_scan_display.h"

#include "../scan_view.h"
#include "s_scan_scene.h"
#include <global.h>
#include <device/device.h>

SscanDisplay::SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScanDisplay),
    m_group(grp),
    m_view(new ScanView),
    m_scene(new SscanScene(grp, DplDevice::Device::instance()->display()->palette())),
    m_vpaItem(new VpaItem(grp)),
    m_sScan(grp->s_scan())
{
    ui->setupUi(this);
    ui->scanLayout->addWidget(m_view);
    m_view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    connect(m_view, SIGNAL(size_changed(QSize)),
            m_scene, SLOT(set_size(QSize)));
    connect(static_cast<DplDisplay::Sscan *>(m_sScan.data()),
            SIGNAL(xy_changed()),
            this, SLOT(update_rules()));
    update_rules();

    connect(m_view, SIGNAL(size_changed(QSize)),
            this, SLOT(do_view_size_changed(QSize)));

    m_view->setScene(m_scene);

    m_scene->addItem(m_vpaItem);
    m_vpaItem->update_pos();

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

void SscanDisplay::update_rules()
{
    qDebug("%s[%d]: x(%f, %f) y(%f, %f)",__func__, __LINE__, m_sScan->start_x(), m_sScan->stop_x(),
           m_sScan->start_y(), m_sScan->stop_y());
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        ui->leftRulerWidget->set_range(m_sScan->start_y(), m_sScan->stop_y());
        ui->bottomRulerWidget->set_range(m_sScan->start_x(), m_sScan->stop_x());
        ui->leftRulerWidget->set_unit("us");
    } else {
        ui->leftRulerWidget->set_range(Dpl::ns_to_s(m_sScan->start_y()) * Dpl::m_to_mm(m_group->focallawer()->specimen()->velocity()) / 2,
                                       Dpl::ns_to_s(m_sScan->stop_y()) * Dpl::m_to_mm(m_group->focallawer()->specimen()->velocity()) / 2);
        ui->bottomRulerWidget->set_range(m_sScan->start_x(), m_sScan->stop_x());
        ui->leftRulerWidget->set_unit("mm");
    }
    ui->leftRulerWidget->update();
    ui->bottomRulerWidget->update();

}

void SscanDisplay::do_view_size_changed(const QSize &size)
{
    m_scene->setSceneRect(-size.width()/2, -size.height(),
                          size.width(), size.height());
    m_vpaItem->update_pos();
}

