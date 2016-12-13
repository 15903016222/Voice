#include "a_scan_display.h"
#include "ui_a_scan_display.h"
#include "a_scan_widget.h"

AscanDisplay::AscanDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanDisplay)
{
    ui->setupUi(this);
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

void AscanDisplay::show(DplSource::BeamSource &beam)
{
    QByteArray wave;
    beam.get_wave(wave);
    ui->ascanWidget->show(wave);
}
