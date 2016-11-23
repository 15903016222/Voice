#include "ascan_layout.h"
#include "ui_ascan_layout.h"

AScanLayout::AScanLayout(QWidget *parent, int group) :
    QWidget(parent),
    ui(new Ui::AScanLayout)
{
    ui->setupUi(this);

}

AScanLayout::~AScanLayout()
{
    delete ui;
}
