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
#include "gate_item.h"

#include <qmath.h>

#include <QDebug>

AscanDisplay::AscanDisplay(DplDevice::GroupPointer &group, Qt::Orientation orientation, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanDisplay),
    m_group(group),
    m_ascanView(new ScanView),
    m_ascanScene(new AscanScene),
    m_gateAItem(new GateItem(Qt::red)),
    m_gateBItem(new GateItem(Qt::green)),
    m_gateIItem(new GateItem(Qt::darkCyan))
{  
    ui->setupUi(this);
    ui->ascanWidgetLayout->addWidget(m_ascanView);

    m_ascanView->setScene(m_ascanScene);

    m_ascanScene->addItem(m_gateAItem);
    m_ascanScene->addItem(m_gateBItem);
    m_ascanScene->addItem(m_gateIItem);

//    m_gateAItem->hide();
    m_gateBItem->hide();
    m_gateIItem->hide();
    m_gateAItem->set_start(0);

    if (orientation == Qt::Vertical) {
        m_ascanView->rotate(90);
    }
//    m_ascanView->scale(0.5, 0.5);

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);

    /* Gate */
    DplDevice::Gate *gate = group->gate(DplDevice::Gate::A).data();
    connect(gate, SIGNAL(changed()),
            this, SLOT(do_gate_a_changed()));
    gate = group->gate(DplDevice::Gate::B).data();
    gate = group->gate(DplDevice::Gate::I).data();

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
    m_ascanScene->set_wave(m_group->beams()->get(0)->get_wave());
}

void AscanDisplay::do_gate_a_changed()
{
    m_gateAItem->set_start(0);
}
