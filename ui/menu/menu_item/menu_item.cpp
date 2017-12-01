/**
 * @file menu_item.cpp
 * @brief menu item base class
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "menu_item.h"

#include <QVBoxLayout>

MenuItem::MenuItem(QWidget *parent) : QWidget(parent)
{}

void MenuItem::update_layout(QWidget *w1, QWidget *w2)
{
    w1->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    w2->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);
    vbox->addWidget(w1, 2);
    vbox->addWidget(w2, 1);
}
