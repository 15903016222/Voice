/**
 * @file a_scan_display.cpp
 * @brief A扫显示布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "global.h"
#include "a_scan_display.h"
#include "ui_a_scan_display.h"
#include "a_scan_view.h"

#include <qmath.h>

#include <QDebug>

AscanDisplay::AscanDisplay(DplDevice::GroupPointer &group, AscanView *ascanWidget, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanDisplay),
    m_group(group),
    m_ascanWidget(ascanWidget)
{  
    ui->setupUi(this);
    ui->ascanWidgetLayout->addWidget(ascanWidget);

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);

    /* source setting */
    DplSource::BeamsPointer beams = m_group->beams();
    connect(static_cast<DplSource::Beams *>(beams.data()),
            SIGNAL(data_event()),
            this,
            SLOT(do_data_event()));

    ui->titleLabel->setText(QString("A-Scan|Grp")+QString::number(m_group->index()+1));

//    connect(static_cast<DplDevice::Gate *>(m_group->gate()))
}

AscanDisplay::~AscanDisplay()
{
    delete ui;
    delete m_ascanWidget;
}

void AscanDisplay::do_data_event()
{
    m_ascanWidget->set_wave(m_group->beams()->get(0)->get_wave());
}
