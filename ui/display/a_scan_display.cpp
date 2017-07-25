/**
 * @file a_scan_display.cpp
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "global.h"
#include "a_scan_display.h"
#include "ui_a_scan_display.h"

#include "scan_view.h"
#include "a_scan_scene.h"
#include "wave_item.h"
#include "gate_item.h"

#include <qmath.h>

#include <QDebug>

AscanDisplay::AscanDisplay(DplDevice::GroupPointer &group, Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanDisplay),
    m_group(group),
    m_ascanView(new ScanView),
    m_ascanScene(new AscanScene),
    m_waveItem(new WaveItem),
    m_gateAItem(new GateItem(Qt::red)),
    m_gateBItem(new GateItem(Qt::green)),
    m_gateIItem(new GateItem(Qt::darkCyan)),
    m_orientation(orientation)
{  
    ui->setupUi(this);
    ui->ascanWidgetLayout->addWidget(m_ascanView);

    connect(m_ascanView, SIGNAL(size_changed(QSize)),
            this, SLOT(do_ascanView_size_changed(QSize)));

    qDebug() << "view Rect: " << m_ascanView->rect();

    m_ascanView->setScene(m_ascanScene);

    m_ascanScene->addItem(m_waveItem);

    m_ascanScene->addItem(m_gateAItem);
    m_ascanScene->addItem(m_gateBItem);
    m_ascanScene->addItem(m_gateIItem);

    m_gateAItem->hide();
    m_gateBItem->hide();
    m_gateIItem->hide();

    if (orientation == Qt::Vertical) {
        m_ascanView->rotate(90);
    }
//    m_ascanView->scale(0.5, 0.5);

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);

    /* Gate */
    connect(group->gate(DplGate::Gate::A).data(),
            SIGNAL(changed()),
            this, SLOT(do_gateA_changed()));
    connect(group->gate(DplGate::Gate::B).data(),
            SIGNAL(changed()),
            this, SLOT(do_gateB_changed()));
    connect(group->gate(DplGate::Gate::I).data(),
            SIGNAL(changed()),
            this, SLOT(do_gateI_changed()));
    connect(group->sample().data(), SIGNAL(start_changed(float)),
            this, SLOT(do_sample_changed()));
    connect(group->sample().data(), SIGNAL(range_changed(float)),
            this, SLOT(do_sample_changed()));


    /* source setting */
    DplSource::BeamsPointer beams = m_group->beams();
    connect(static_cast<DplSource::Beams *>(beams.data()),
            SIGNAL(data_event()),
            this,
            SLOT(do_data_event()));

    ui->titleLabel->setText(QString("A-Scan|Grp")+QString::number(m_group->index()+1));
}

AscanDisplay::~AscanDisplay()
{
    delete ui;
    delete m_ascanView;
    delete m_ascanScene;
}

void AscanDisplay::do_data_event()
{
    m_waveItem->set_wave(m_group->beams()->get(0)->get_wave());
}

void AscanDisplay::update_gateItem(const DplGate::GatePointer &gate, GateItem *gateItem)
{
    gateItem->setVisible(gate->is_visible());

    gateItem->set_ratio(m_waveItem->size().width() / m_group->sample()->range());

    gateItem->set_start(gate->start() - m_group->sample()->start());

    gateItem->set_width(gate->width());
}

void AscanDisplay::do_gateA_changed()
{
    update_gateItem(m_group->gate(DplGate::Gate::A), m_gateAItem);
}

void AscanDisplay::do_gateB_changed()
{
    update_gateItem(m_group->gate(DplGate::Gate::B), m_gateBItem);
}

void AscanDisplay::do_gateI_changed()
{
    update_gateItem(m_group->gate(DplGate::Gate::I), m_gateIItem);
}

void AscanDisplay::do_sample_changed()
{
    update_gateItem(m_group->gate(DplGate::Gate::A), m_gateAItem);
    update_gateItem(m_group->gate(DplGate::Gate::B), m_gateBItem);
    update_gateItem(m_group->gate(DplGate::Gate::I), m_gateIItem);
}

void AscanDisplay::do_ascanView_size_changed(const QSize &size)
{
    if (m_orientation == Qt::Horizontal) {
        m_ascanScene->setSceneRect(-size.width()/2, -size.height()/2,
                                   size.width(), size.height());
        m_waveItem->set_size(size);
    } else {
        m_ascanScene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                                   size.height(), size.width());
        m_waveItem->set_size(QSize(size.height(), size.width()));
    }
    do_gateA_changed();
    do_gateB_changed();
    do_gateI_changed();
}
