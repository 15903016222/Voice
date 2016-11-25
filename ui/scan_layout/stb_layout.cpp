#include "stb_layout.h"
#include "ui_stb_layout.h"

STBLayout::STBLayout(QWidget *parent, int group) :
    QWidget(parent),
    ui(new Ui::STBLayout)
{
    ui->setupUi(this);

    set_display_group(group);
}

STBLayout::~STBLayout()
{
    delete ui;
}

void STBLayout::set_display_group(int group)
{
    switch (group) {
    case 6:
        break;
    case 5:
        ui->widget_S4->hide();
        break;
    default:
        break;
    }
}
