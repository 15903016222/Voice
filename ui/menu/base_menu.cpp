/**
 * @file base_menu.h
 * @brief Base Class for Third Menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */

#include "base_menu.h"
#include <QVBoxLayout>

QStringList BaseMenu::s_onOff;

BaseMenu::BaseMenu(QWidget *parent) : QWidget(parent)
{
    setMinimumHeight(70);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    m_layout0 = create_layout();
    m_layout1 = create_layout();
    m_layout2 = create_layout();
    m_layout3 = create_layout();
    m_layout4 = create_layout();
    m_layout5 = create_layout();

    if (s_onOff.isEmpty()) {
        s_onOff.append(tr("On"));
        s_onOff.append(tr("Off"));
    }
    hide();
}

BaseMenu::~BaseMenu()
{
}

QVBoxLayout *BaseMenu::create_layout()
{
    QWidget *w = new QWidget(this);
    w->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    static_cast<QHBoxLayout*>(layout())->addWidget(w, 1);
    QVBoxLayout *layout = new QVBoxLayout(w);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    return layout;
}
