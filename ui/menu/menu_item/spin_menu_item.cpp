/**
 * @file spin_menu_item.cpp
 * @brief spin menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "spin_menu_item.h"

#include <qmath.h>
#include <QKeyEvent>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QTextCodec>

SpinMenuItem::SpinMenuItem(QWidget *parent, const QString &title,
                           const QString &unit) : MenuItem(parent),
    m_pushBtn(new QPushButton(this)),
    m_lineEdit(new QLineEdit(this)),
    m_title(title),
    m_unit(unit),
    m_value(0),
    m_min(0),
    m_max(100),
    m_step(1),
    m_baseStep(1),
    m_decimals(0)
{
    m_pushBtn->setFocusPolicy(Qt::NoFocus);
    m_lineEdit->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    update_layout(m_pushBtn, m_lineEdit);

    m_lineEdit->installEventFilter(this);

    update_title();
    update_value();

    set_edit(false);

    connect(m_pushBtn, SIGNAL(clicked(bool)),
            this, SLOT(do_pushBtn_clicked()));
    connect(m_lineEdit, SIGNAL(textEdited(QString)),
            this, SLOT(check_number_validity(QString)));
}

void SpinMenuItem::set_range(double min, double max)
{
    m_min = min;
    m_max = max;
    if (m_value > m_max) {
        m_value = m_max;
    } else if (m_value < m_min) {
        m_value = m_min;
    }
    update_value();
}

void SpinMenuItem::set_decimals(int prec)
{
    m_decimals = prec;

    m_step = m_baseStep;

    QDoubleValidator *validator = new QDoubleValidator(m_min, m_max, prec, this);
    m_lineEdit->setValidator(validator);

    update_value();
}

void SpinMenuItem::set_step(double step)
{
    m_baseStep = step;
    m_step = step;
    update_title();
}

void SpinMenuItem::set_edit(bool flag)
{
    if ( flag ) {
        m_lineEdit->setFocusPolicy(Qt::WheelFocus);
        m_lineEdit->setFocus();
        m_lineEdit->setReadOnly(false);
    } else {
        m_lineEdit->setFocusPolicy(Qt::NoFocus);
        m_lineEdit->clearFocus();
        m_lineEdit->setReadOnly(true);
    }
    update_title();
}

void SpinMenuItem::set_value(double value)
{
    if (qFuzzyCompare(m_value, value)) {
        return;
    }

    if (value > m_max) {
        m_value = m_max;
    } else if (value < m_min) {
        m_value = m_min;
    } else {
        m_value = value;
    }
    update_value();
    emit value_changed(m_value);
}

bool SpinMenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (!isEnabled()) {
        return false;
    }

    if (e->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        switch (keyEvent->key()) {
        case Qt::Key_Escape:
        case Qt::Key_Back:
        case Qt::Key_Cancel:
        case Qt::Key_Enter:
        case Qt::Key_Return:
        {
            update_value();
            set_edit(false);
            return true;
            break;
        }
        case Qt::Key_Up:
            add();
            break;
        case Qt::Key_Down:
            sub();
            break;
        default:
            break;
        }
    } else if (e->type() == QEvent::FocusOut) {
        if(obj->objectName() == m_lineEdit->objectName()) {
            set_edit(false);
        }
    } else if (e->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent *>(e);
        if (wheelEvent->delta() > 0) {
            add();
        } else if(wheelEvent->delta() < 0) {
            sub();
        }
    }

    return QWidget::eventFilter(obj, e);
}

void SpinMenuItem::update_title()
{
    QString msg = m_title;

    if (!m_unit.isEmpty()) {
        msg += "\n(" + m_unit + ")";
    }

    if (m_lineEdit->hasFocus()) {
        if (m_unit.isEmpty()) {
            msg += "\n";
        }

        msg += QString::fromUtf8("Δ") + QString::number(m_step, 'f', m_decimals);
    }

    m_pushBtn->setText(msg);
}

void SpinMenuItem::update_spin_step()
{
    m_step *= 10;

    if (m_step >= m_max) {
        m_step = m_baseStep;
    }

    update_title();
}

void SpinMenuItem::update_value()
{
    m_lineEdit->setText(QString::number(m_value, 'f', m_decimals) + m_suffix);
}

void SpinMenuItem::add()
{
    if (m_value + m_step > m_max) {
        if (m_value == m_max) {
            return;
        } else {
            m_value = m_max;
        }
    } else {
        m_value += m_step;
    }

    update_value();

    emit value_changed(m_value);
}

void SpinMenuItem::sub()
{
    if (m_value - m_step < m_min) {
        if (m_value == m_min) {
            return;
        } else {
            m_value = m_min;
        }
    } else {
        m_value -= m_step;
    }

    update_value();

    emit value_changed(m_value);
}

void SpinMenuItem::check_number_validity(const QString &text)
{
    if(text.toDouble() > m_max || text.toDouble() < m_min) {
        m_lineEdit->backspace();
        QString value = m_lineEdit->text();
        m_value = value.toDouble();
    } else {
        m_value = text.toDouble();
    }
}

void SpinMenuItem::do_pushBtn_clicked()
{
    if (m_lineEdit->hasFocus()) {
        update_spin_step();
    } else {
        set_edit(true);
    }
}
