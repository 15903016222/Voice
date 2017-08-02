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
    m_waveItem(new WaveItem(group->ascan())),
    m_gateAItem(new GateItem(group->gate(DplGate::Gate::A))),
    m_gateBItem(new GateItem(group->gate(DplGate::Gate::B))),
    m_gateIItem(new GateItem(group->gate(DplGate::Gate::I))),
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

    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_gates()));

    if (orientation == Qt::Vertical) {
        m_ascanView->rotate(90);
    }

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);

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

    update_gates();
}

void AscanDisplay::update_gates()
{
    m_gateAItem->set_ratio(m_ascanScene->width()/m_group->sample()->range());
    m_gateBItem->set_ratio(m_ascanScene->width()/m_group->sample()->range());
    m_gateIItem->set_ratio(m_ascanScene->width()/m_group->sample()->range());
}

