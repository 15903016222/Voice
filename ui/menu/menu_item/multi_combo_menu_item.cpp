#include "multi_combo_menu_item.h"

#include <QMenu>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

MultiComboMenuItem::MultiComboMenuItem(const QString &title, QWidget *parent) : MenuItem(parent),
    m_menu(new QMenu(this)),
    m_pushBtn(new QPushButton(title, this)),
    m_label(new QLabel(this))
{
    update_layout(m_pushBtn, m_label);
    m_label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    m_pushBtn->setFocusPolicy(Qt::NoFocus);

    m_menu->setMinimumWidth(width());

    connect(m_pushBtn, SIGNAL(clicked(bool)),
            this, SLOT(do_pushBtn_clicked()));
    connect(m_menu, SIGNAL(triggered(QAction*)),
            this, SLOT(do_triggered(QAction*)));
}

MultiComboMenuItem::~MultiComboMenuItem()
{
}

void MultiComboMenuItem::add_item(const QString &text)
{
    QAction *act = new QAction(text, this);
    act->setCheckable(true);
    m_menu->addAction(act);
}

void MultiComboMenuItem::add_items(const QStringList &texts)
{
    for (int i = 0; i < texts.count(); ++i) {
        add_item(texts[i]);
    }
}

void MultiComboMenuItem::clear()
{
    QList<QAction*> actions = m_menu->actions();
    foreach (QAction *act, actions) {
        delete act;
    }
}

int MultiComboMenuItem::value() const
{
    QList<QAction *> actions = m_menu->actions();
    int ret = 0;
    for (int i = 0; i < actions.count(); ++i) {
        ret |= (actions[i]->isChecked())<<i;
    }
    return ret;
}

void MultiComboMenuItem::set_value(int value)
{
    QList<QAction *> actions = m_menu->actions();
    for (int i = 0; i < actions.count(); ++i) {
        actions[i]->setChecked(value&(1<<i));
    }
    update_label();
}

void MultiComboMenuItem::do_triggered(QAction *act)
{
    update_label();
    emit triggered(m_menu->actions().indexOf(act), act->isChecked());
}

void MultiComboMenuItem::do_pushBtn_clicked()
{
    m_menu->show();
    m_menu->hide();
    QPoint point = mapToGlobal(QPoint(0, 0));
    point.setY(point.y() - m_menu->height());
    m_menu->exec(point);
}

void MultiComboMenuItem::update_label()
{
    QString msg;
    QList<QAction *> actions = m_menu->actions();
    for (int i = 0; i < actions.count(); ++i) {
        if (!actions[i]->isChecked()) {
            continue;
        }
        if (!msg.isEmpty()) {
            msg.append(",");
        }
        msg.append(actions[i]->text());
    }
    m_label->setText(msg);
}
