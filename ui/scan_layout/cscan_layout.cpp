#include "cscan_layout.h"
#include "ui_cscan_layout.h"

CScanLayout::CScanLayout(QWidget *parent, int group) :
    QWidget(parent),
    ui(new Ui::CScanLayout)
{
    ui->setupUi(this);

    set_display_group(group);
}

CScanLayout::~CScanLayout()
{
    delete ui;
}

void CScanLayout::set_display_group(int group)
{
    switch (group) {
    case 4:
        break;
    case 3:
        ui->widget_C4->hide();
        break;
    case 2:
        ui->widget_C3->hide();
        ui->widget_C4->hide();
        break;
    case 1:
        ui->widget_C1->hide();
        ui->widget_C3->hide();
        ui->widget_C4->hide();
        break;
    default:
        break;
    }
}
