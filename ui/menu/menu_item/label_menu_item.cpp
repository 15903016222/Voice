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
    ui->nameLabel->installEventFilter(this);
    set_title(title);
    set_text(text);
}

LabelMenuItem::~LabelMenuItem()
{
    delete ui;
}

void LabelMenuItem::set_title(const QString &title)
{
    QString msg("<p align=\"center\"><font style='font-size:16pt' face='Arial' color=yellow>");
    msg += title;
    msg += "</font>";
    msg += "</p>";
    ui->nameLabel->setText(msg);
    m_title = title;
}

bool LabelMenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease) {
        emit clicked();
        return true;
    }

    return QWidget::eventFilter(obj, e);
}

void LabelMenuItem::set_text(const QString &text)
{
    ui->label->setText(text);
    m_text = text;
}
