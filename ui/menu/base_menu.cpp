/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "base_menu.h"
#include "ui_base_menu.h"

QStringList BaseMenu::s_onOff;

BaseMenu::BaseMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseMenu)
{
    ui->setupUi(this);

    if (s_onOff.isEmpty()) {
        s_onOff.append(tr("On"));
        s_onOff.append(tr("Off"));
    }
    hide();
}

BaseMenu::~BaseMenu()
{
    delete ui;
}
