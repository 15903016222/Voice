#include "sub_menu.h"
#include "ui_sub_menu.h"

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);
}

SubMenu::~SubMenu()
{
    delete ui;
}
