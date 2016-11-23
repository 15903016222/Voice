#include "ascan_layout.h"
#include "ui_ascan_layout.h"

AScanLayout::AScanLayout(QWidget *parent, int group) :
    QWidget(parent),
    ui(new Ui::AScanLayout)
{
    ui->setupUi(this);

    set_display_group(group);
}

AScanLayout::~AScanLayout()
{
    delete ui;
}

void AScanLayout::set_display_group(int group)
{
    switch (group) {
    case 8:
        break;
    case 7:
        ui->widget_A8->hide();
        break;
    case 6:
        ui->widget_A7->hide();
        ui->widget_A8->hide();
        break;
    case 5:
        ui->widget_A6->hide();
        ui->widget_A7->hide();
        ui->widget_A8->hide();
        break;
    case 4:
        ui->widget_A5->hide();
        ui->widget_A6->hide();
        ui->widget_A7->hide();
        ui->widget_A8->hide();
        break;
    case 3:
        ui->widget_A4->hide();
        ui->widget_A5->hide();
        ui->widget_A6->hide();
        ui->widget_A7->hide();
        ui->widget_A8->hide();
        break;
    case 2:
        ui->widget_A3->hide();
        ui->widget_A4->hide();
        ui->widget_A5->hide();
        ui->widget_A6->hide();
        ui->widget_A7->hide();
        ui->widget_A8->hide();
        break;
    case 1:
        ui->widget_A2->hide();
        ui->widget_A3->hide();
        ui->widget_A4->hide();
        ui->widget_A5->hide();
        ui->widget_A6->hide();
        ui->widget_A7->hide();
        ui->widget_A8->hide();
        break;
    default:
        break;
    }
}
