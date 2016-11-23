#include "abc_layout.h"
#include "ui_abc_layout.h"

ABCLayout::ABCLayout(QWidget *parent, int group) :
    QWidget(parent),
    ui(new Ui::ABCLayout)
{
    ui->setupUi(this);

    set_display_group(group);
}

ABCLayout::~ABCLayout()
{
    delete ui;
}

void ABCLayout::set_display_group(int group)
{
    switch (group) {
    case 3:
        break;
    case 2:
        ui->widget_A3->hide();
        ui->widget_B3->hide();
        ui->widget_C3->hide();
        break;
    case 1:
        ui->widget_A3->hide();
        ui->widget_A2->hide();
        ui->widget_B3->hide();
        ui->widget_B2->hide();
        ui->widget_C3->hide();
        ui->widget_C2->hide();
        break;
    default:
        break;
    }
}
