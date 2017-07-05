/**
 * @file a_scan_hdisplay.cpp
 * @brief A扫横向显示
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "global.h"
#include "a_scan_hdisplay.h"
#include "ui_a_scan_hdisplay.h"
#include "a_scan_hwidget.h"

#include <qmath.h>

#include <QDebug>

AscanHDisplay::AscanHDisplay(DplDevice::GroupPointer &group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanHDisplay)
{  
    ui->setupUi(this);

    m_group = group;

    /* ruler setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_bottom_ruler()));
    connect(static_cast<DplDevice::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_bottom_ruler()));
    connect(static_cast<DplDevice::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_bottom_ruler()));
    update_bottom_ruler();

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);
    ui->leftRulerWidget->set_direction(RulerWidget::Down);
    ui->leftRulerWidget->set_range(0, 100);
    ui->leftRulerWidget->set_unit("(%)");
    ui->leftRulerWidget->set_backgroup_color(QColor("#ffff7f"));
    ui->leftRulerWidget->update();

    /* source setting */
    DplSource::BeamsPointer beams = m_group->beams();
    connect(static_cast<DplSource::Beams *>(beams.data()),
            SIGNAL(data_event()),
            this,
            SLOT(update()));

    ui->titleLabel->setText(QString("A-Scan|Grp")+QString::number(m_group->index()+1));
}

AscanHDisplay::~AscanHDisplay()
{
    qDebug()<<__func__<<__LINE__;
    delete ui;
}

void AscanHDisplay::update()
{
    ui->ascanWidget->show(m_group->beams()->get(0)->get_wave());
}

void AscanHDisplay::update_bottom_ruler()
{
    double start = m_group->sample()->start();
    double end = (start + m_group->sample()->range());

    start = Dpl::ns_to_us(start);
    end = Dpl::ns_to_us(end);

    DplDevice::Group::UtUnit unit = m_group->ut_unit();

    if (DplDevice::Group::Time == unit) {
        ui->bottomRulerWidget->set_unit("(us)");
        ui->bottomRulerWidget->set_backgroup_color(QColor("#F9CCE2"));
    } else {
        ui->bottomRulerWidget->set_unit("(mm)");
        start *= m_group->sample()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
        start /= 2;
        end *= m_group->sample()->velocity() * Dpl::m_to_mm(1) / Dpl::s_to_us(1);
        end /= 2;
        ui->bottomRulerWidget->set_backgroup_color(QColor("#f29cb1"));
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            ui->bottomRulerWidget->set_backgroup_color(QColor("#ff00ff"));
        }
    }

    ui->bottomRulerWidget->set_range(start, end);

    ui->bottomRulerWidget->update();
}
