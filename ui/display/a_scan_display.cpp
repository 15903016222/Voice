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

    /* ruler setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_bottom_ruler()));
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(start_changed(double)),
            this,
            SLOT(update_bottom_ruler()));
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(range_changed(double)),
            this,
            SLOT(update_bottom_ruler()));

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);
    ui->leftRulerWidget->set_direction(RulerWidget::Down);
    ui->leftRulerWidget->set_range(0, 100);
    ui->leftRulerWidget->set_unit("(%)");
    ui->leftRulerWidget->set_backgroup_color(QColor("#ffff7f"));
    ui->leftRulerWidget->update();

    /* source setting */
    DplSource::BeamGroupPointer beamGroup = m_group->get_beam_group();
    connect(static_cast<DplSource::BeamGroup *>(beamGroup.data()),
            SIGNAL(data_event()),
            this,
            SLOT(update()));

    ui->titleLabel->setText(QString("A-Scan|Grp")+QString::number(m_group->index()+1));
}

AscanDisplay::~AscanDisplay()
{
    qDebug()<<__func__<<__LINE__;
    delete ui;
}

void AscanDisplay::update()
{
    DplSource::BeamGroupPointer beamGroup = m_group->get_beam_group();
    QByteArray wave;
    beamGroup->get(0)->get_wave(wave);
    ui->ascanWidget->show(wave);
}

void AscanDisplay::update_bottom_ruler()
{
    double start = m_group->start() / 1000;         /*单位(us)*/
    double end = (start + m_group->range()) / 1000; /*单位(us)*/
    DplDevice::Group::UtUnit unit = m_group->ut_unit();

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
