/**
 * @file label_menu_item.cpp
 * @brief label menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "label_menu_item.h"
#include "ui_label_menu_item.h"

LabelMenuItem::LabelMenuItem(QWidget *parent, const QString &title, const QString &text) :
    MenuItem(parent),
    ui(new Ui::LabelMenuItem)
{
    ui->setupUi(this);
    connect(ui->pushButton,
            SIGNAL(clicked()),
            this, SIGNAL(clicked()));
    set_title(title);
    set_text(text);
}

LabelMenuItem::~LabelMenuItem()
{
    delete ui;
}

void LabelMenuItem::set_title(const QString &title)
{
    ui->pushButton->setText(title);
    m_title = title;
}

void LabelMenuItem::set_text(const QString &text)
{
    ui->label->setText(text);
    m_text = text;
}
