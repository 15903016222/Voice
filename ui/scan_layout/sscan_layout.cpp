#include "sscan_layout.h"
#include "ui_sscan_layout.h"

SScanLayout::SScanLayout(QWidget *parent, int group) :
    QWidget(parent),
    ui(new Ui::SScanLayout)
{
    ui->setupUi(this);

    set_display_group(group);
}

SScanLayout::~SScanLayout()
{
    delete ui;
}

void SScanLayout::set_display_group(int group)
{
    switch (group) {
    case 4:
        break;
    case 3:
        ui->widget_S4->hide();
        break;
    case 2:
        ui->widget_S3->hide();
        ui->widget_S4->hide();
        break;
    case 1:
        ui->widget_S2->hide();
        ui->widget_S3->hide();
        ui->widget_S4->hide();
        break;
    default:
        break;
    }
}
