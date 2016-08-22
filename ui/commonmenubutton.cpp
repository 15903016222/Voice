#include "commonmenubutton.h"
#include "ui_commonmenubutton.h"

CommonMenuButton::CommonMenuButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CommonMenuButton)
{
    ui->setupUi(this);
    pushButton_commonMenu.append(ui->pushButton);
}

CommonMenuButton::~CommonMenuButton()
{
    delete ui;
}
