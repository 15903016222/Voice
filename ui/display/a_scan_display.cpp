#include "a_scan_display.h"
#include "ui_a_scan_display.h"
#include "a_scan_widget.h"

#include <qmath.h>

#include <QDebug>

AscanDisplay::AscanDisplay(DplDevice::GroupPointer &group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanDisplay)
{  
    ui->setupUi(this);

    m_group = group;
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(do_ut_unit_changed(DplDevice::Group::UtUnit)));

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);
    ui->leftRulerWidget->set_direction(RulerWidget::Down);
    ui->leftRulerWidget->set_range(0, 100);
    ui->leftRulerWidget->set_unit("(%)");
    ui->leftRulerWidget->set_backgroup_color(QColor("#ffff7f"));
    ui->leftRulerWidget->update();
}

AscanDisplay::~AscanDisplay()
{
    delete ui;
}

void AscanDisplay::show(DplSource::Beam &beam)
{
    QByteArray wave;
    beam.get_wave(wave);
    ui->ascanWidget->show(wave);
}

void AscanDisplay::do_ut_unit_changed(DplDevice::Group::UtUnit unit)
{
    double start = m_group->start() / 1000;         /*单位(us)*/
    double end = (start + m_group->range()) / 1000; /*单位(us)*/

    if (DplDevice::Group::Time == unit) {
        ui->bottomRulerWidget->set_unit("(us)");
        ui->bottomRulerWidget->set_backgroup_color(QColor("#F9CCE2"));
    } else{
        ui->bottomRulerWidget->set_unit("(mm)");
        start *= m_group->velocity() / (2 * 1000);
        end   *= m_group->velocity() / (2 * 1000);
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
