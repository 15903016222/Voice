/**
 * @file spin_menu_item.cpp
 * @brief spin menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "spin_menu_item.h"
#include "ui_spin_menu_item.h"

#include <qmath.h>
#include <QKeyEvent>
#include <QDebug>

SpinMenuItem::SpinMenuItem(QWidget *parent) :
    MenuItem(parent),
    ui(new Ui::SpinMenuItem)
{
    ui->setupUi(this);

    ui->nameLabel->installEventFilter(this);
    ui->lineEdit->installEventFilter(this);

    m_value = 0;
    m_min = 0;
    m_max = 100;
    m_step = 1;
    m_decimals = 0;
    update_value();
}

SpinMenuItem::~SpinMenuItem()
{
    delete ui;
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

    QString msg="[0-9]";
    if (prec > 0) {
        msg += "[.][0-9]";
        msg += QString::number(prec);
    }
    QRegExp rx(msg);
    QValidator *validator = new QRegExpValidator(rx, this);
    ui->lineEdit->setValidator(validator);

    update_value();
}

void SpinMenuItem::set_step(double step)
{
    m_baseStep = step;
    m_step = step;
    update_title();
}

bool SpinMenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease) {
        if (ui->lineEdit->hasFocus()) {
            update_spin_step();
        } else {
            set_focus();
        }
        return true;
    }

    if (e->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(e);
        switch (keyEvent->key()) {
        case Qt::Key_Escape:
        case Qt::Key_Back:
        case Qt::Key_Cancel:
        case Qt::Key_Enter:
        case Qt::Key_Return:
            set_focus_out();
            return true;
            break;
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
        set_focus_out();
        return true;
    }

    return QWidget::eventFilter(obj, e);
}

void SpinMenuItem::update_title()
{
    QString msg("<p align=\"center\"><font style='font-size:16pt' face='Arial' color=yellow>");
    msg += m_title;
    msg += "</font>";

    if (!m_unit.isEmpty()){
        msg += "<br/>(";
        msg += m_unit;
        msg += ")";
    }

    if (ui->lineEdit->hasFocus()) {
        if (m_unit.size()) {
            msg += " ";
        }
        msg += "&Delta;";
        msg += QString::number(m_step, 'f', m_decimals);
    }

    msg += "</p>";
    ui->nameLabel->setText(msg);
}

void SpinMenuItem::update_spin_step()
{
    m_step *= 10;

    if (m_step >= m_max) {
        m_step = m_baseStep;
    }

    update_title();
}

void SpinMenuItem::set_focus()
{
    ui->lineEdit->setStyleSheet("QLineEdit{\nselection-color:black; selection-background-color: rgba(255,255,255,255);\n}");
    ui->lineEdit->setFocusPolicy(Qt::WheelFocus);
    ui->lineEdit->setFocus();
    ui->lineEdit->setReadOnly(false);
    update_title();
}

void SpinMenuItem::set_focus_out()
{
    ui->lineEdit->setFocusPolicy(Qt::NoFocus);
    ui->lineEdit->clearFocus();
    ui->lineEdit->setReadOnly(true);
    ui->lineEdit->setStyleSheet("QLineEdit{"
                                "color: rgb(255, 255, 255);"
                                "border-top:0px;"
                                "border-bottom:0px;"
                                "font: 14pt 'Arial';"
                                "color: white;"
                                "selection-color: white;"
                                "selection-background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.559322 rgba(0, 130, 195, 255));color: rgb(255, 255, 255);"
                                "background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.559322 rgba(0, 130, 195, 255));"
                                "border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));"
                                "border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));}");
    update_title();
}

void SpinMenuItem::update_value()
{
    ui->lineEdit->setText(QString::number(m_value, 'f', m_decimals) + m_suffix);
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

void SpinMenuItem::set(const QString &title, const QString &unit, double min, double max, int decimals, double step)
{
    m_title = title;
    m_unit = unit;

    m_min = min;
    m_max = max;

    m_baseStep = step;
    m_step = step;

    set_decimals(decimals);

    update_title();
}
