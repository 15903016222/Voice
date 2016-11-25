#include "measure_bar.h"
#include "ui_measure_bar.h"

#include <QDebug>

MeasureBar :: MeasureBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureBar)
{
    ui->setupUi(this);
}

MeasureBar::~MeasureBar()
{
    delete(ui);
}
