#include "a_scan_vdisplay.h"
#include "ui_a_scan_vdisplay.h"
#include "a_scan_vwidget.h"

#include <qmath.h>

#include <QDebug>

AscanVDisplay::AscanVDisplay(DplDevice::GroupPointer &group, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanVDisplay)
{  
    ui->setupUi(this);

    m_group = group;

    /* ruler setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_left_ruler()));
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(start_changed(double)),
            this,
            SLOT(update_left_ruler()));
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(range_changed(double)),
            this,
            SLOT(update_left_ruler()));

    ui->bottomRulerWidget->set_range(0, 100);
    ui->bottomRulerWidget->set_unit("(%)");
    ui->bottomRulerWidget->set_backgroup_color(QColor("#ffff7f"));

    ui->leftRulerWidget->set_type(RulerWidget::LEFT);

    /* source setting */
    DplSource::BeamsPointer beams = m_group->beams();
    connect(static_cast<DplSource::Beams *>(beams.data()),
            SIGNAL(data_event()),
            this,
            SLOT(update()));

    ui->titleLabel->setText(QString("A-Scan|Grp")+QString::number(m_group->index()+1));
}

AscanVDisplay::~AscanVDisplay()
{
    qDebug()<<__func__<<__LINE__;
    delete ui;
}

void AscanVDisplay::update()
{
    ui->ascanWidget->show(m_group->beams()->get(0)->get_wave());
//    ui->leftRulerWidget->update();
}

void AscanVDisplay::update_left_ruler()
{
    double start = m_group->start() / 1000;         /*单位(us)*/
    double end = (start + m_group->range()) / 1000; /*单位(us)*/
    DplDevice::Group::UtUnit unit = m_group->ut_unit();

    if (DplDevice::Group::Time == unit) {
        ui->leftRulerWidget->set_unit("(us)");
        ui->leftRulerWidget->set_backgroup_color(QColor("#F9CCE2"));
    } else{
        ui->leftRulerWidget->set_unit("(mm)");
        start *= m_group->velocity() / (2 * 1000);
        end   *= m_group->velocity() / (2 * 1000);
        ui->leftRulerWidget->set_backgroup_color(QColor("#f29cb1"));
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            ui->leftRulerWidget->set_backgroup_color(QColor("#ff00ff"));
        }
    }

    ui->leftRulerWidget->set_range(start, end);

    ui->leftRulerWidget->update();
}
