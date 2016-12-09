#include "a_scan_display.h"
#include "ui_a_scan_display.h"
#include "a_scan_widget.h"

AscanDisplay::AscanDisplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AscanDisplay)
{
    ui->setupUi(this);
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
