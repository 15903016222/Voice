/**
 * @file combo_menu_item.cpp
 * @brief combo box menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "combo_menu_item.h"

#include <QPushButton>
#include <QMenu>
#include <QLabel>
#include <QVBoxLayout>
#include <QDebug>

ComboMenuItem::ComboMenuItem(QWidget *parent, const QString &title) :
    MenuItem(parent),
    m_menu(new QMenu(this)),
    m_action(NULL),
    m_pushBtn(new QPushButton(title, this)),
    m_label(new QLabel(this))
{    
    update_layout(m_pushBtn, m_label);
    m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_pushBtn->setFocusPolicy(Qt::NoFocus);

    m_menu->setMinimumWidth(width());

    connect(m_pushBtn, SIGNAL(clicked(bool)),
            this, SLOT(do_pushBtn_clicked(bool)));
    connect(m_menu, SIGNAL(triggered(QAction*)),
            this, SLOT(do_triggered(QAction*)));
}

ComboMenuItem::~ComboMenuItem()
{
}

void ComboMenuItem::set_title(const QString &title)
{
    m_pushBtn->setText(title);
}

void ComboMenuItem::add_item(const QString &text, const QString &toolTip)
{
    QAction *action = new QAction(text, this);
    action->setToolTip(toolTip);
    if (!m_action) {
        m_action = action;
        m_label->setText(m_action->text());
    }
    m_menu->addAction(action);
}

void ComboMenuItem::add_items(const QStringList &texts)
{
    for (int i = 0; i < texts.count(); ++i) {
        add_item(texts[i], "Hello world");
    }
}

void ComboMenuItem::set_current_index(int index)
{
    QAction *action = m_menu->actions().value(index);
    if (action) {
        m_action = action;
        m_label->setText(m_action->text());
    }
}

int ComboMenuItem::current_index() const
{
    return m_menu->actions().indexOf(m_action);
}

QString ComboMenuItem::current_text() const
{
    return m_action->text();
}

void ComboMenuItem::clear()
{
    qDeleteAll(m_menu->actions());
}

void ComboMenuItem::do_pushBtn_clicked(bool checked)
{
    Q_UNUSED(checked);

    m_menu->show();
    m_menu->hide();
    QPoint point = mapToGlobal(QPoint(0,0));
    point.setY(point.y() - m_menu->height());
    if (m_action) {
        m_menu->setActiveAction(m_action);
    }
    m_menu->exec(point);
}

void ComboMenuItem::do_triggered(QAction *action)
{
    m_action = action;
    m_label->setText(m_action->text());
    emit value_changed(current_index());
}
