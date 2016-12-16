/**
 * @file spin_menu_item.cpp
 * @brief spin menu item
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "spin_menu_item.h"
#include "ui_spin_menu_item.h"

#include <QKeyEvent>

SpinMenuItem::SpinMenuItem(QWidget *parent) :
    MenuItem(parent, MenuItem::Spin),
    ui(new Ui::SpinMenuItem)
{
    ui->setupUi(this);

    ui->nameLabel->installEventFilter(this);
    ui->doubleSpinBox->installEventFilter(this);

    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(value_changed(double)));
}

SpinMenuItem::~SpinMenuItem()
{
    delete ui;
}

void SpinMenuItem::set_title(const QString &title)
{
    m_title = title;
    update_title();
}

void SpinMenuItem::set_unit(const QString &unitName)
{
    m_unit = unitName;
    update_title();
}

void SpinMenuItem::set_suffix(const QString &text)
{
    ui->doubleSpinBox->setSuffix(text);
}

void SpinMenuItem::set_range(double min, double max)
{
    ui->doubleSpinBox->setMinimum(min);
    ui->doubleSpinBox->setMaximum(max);
}

void SpinMenuItem::set_decimals(int prec)
{
    ui->doubleSpinBox->setDecimals(prec);
}

bool SpinMenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonRelease) {
        if (ui->doubleSpinBox->hasFocus()) {
            update_spin_step();
        } else {
            set_focus();
        }
        return true;
    }

    if (e->type() == QEvent::KeyPress
            || e->type() == QEvent::KeyRelease) {
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(e);
        switch (keyEvent->key()) {
        case Qt::Key_Escape:
        case Qt::Key_Back:
        case Qt::Key_Cancel:
        case Qt::Key_Enter:
        case Qt::Key_Return:
            set_focus_out();
            return true;
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
    QString msg("<p align=\"center\"><font size=4 color=yellow>");
    msg += m_title;
    msg += "</font>";
    if ( ! ui->doubleSpinBox->isHidden() ) {
        if (!m_unit.isEmpty()){
            msg += "<br/>(";
            msg += m_unit;
            msg += ")";
        }

        if (ui->doubleSpinBox->hasFocus()) {
            if (m_unit.size()) {
                msg += " ";
            }
            msg += "&Delta;";
            msg += QString::number(ui->doubleSpinBox->singleStep(), 'f', ui->doubleSpinBox->decimals());
        }
    }
    msg += "</p>";
    ui->nameLabel->setText(msg);
}

void SpinMenuItem::update_spin_step()
{
    double step = ui->doubleSpinBox->singleStep() * 10;

    if (step >= ui->doubleSpinBox->maximum()) {
        step = 1;
        for(int i=0; i < ui->doubleSpinBox->decimals(); ++i) {
            step /= 10.0;
        }
    }

    ui->doubleSpinBox->setSingleStep(step);

    update_title();
}

void SpinMenuItem::set_focus()
{
    ui->doubleSpinBox->setStyleSheet("QDoubleSpinBox{\nselection-color:black; selection-background-color: rgba(255,255,255,255);\n}");
    ui->doubleSpinBox->setFocusPolicy(Qt::WheelFocus);
    ui->doubleSpinBox->setFocus();
    ui->doubleSpinBox->setReadOnly(false);
    update_title();
}

void SpinMenuItem::set_focus_out()
{
    ui->doubleSpinBox->setFocusPolicy(Qt::NoFocus);
    ui->doubleSpinBox->clearFocus();
    ui->doubleSpinBox->setReadOnly(true);
    ui->doubleSpinBox->setStyleSheet("QDoubleSpinBox{"
                                     "color: rgb(255, 255, 255);"
                                     "border-top:0px;"
                                     "border-bottom:0px;"
                                     "font: 13pt 'Century Gothic';"
                                     "color: white;"
                                     "selection-color: white;"
                                     "selection-background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.559322 rgba(0, 130, 195, 255));color: rgb(255, 255, 255);"
                                     "background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0.158192 rgba(0, 0, 0, 255), stop:0.559322 rgba(0, 130, 195, 255));"
                                     "border-left:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1, stop:0.158192 rgba(255, 255, 255, 255), stop:0.757062 rgba(0, 130, 195, 255));"
                                     "border-right:1px solid qlineargradient(spread:pad, x1:0.5, y1:0.15, x2:0.5, y2:1,stop:0.158192 rgba(0, 0, 0, 255), stop:0.757062 rgba(0, 130, 195, 255));}");
    update_title();
}

void SpinMenuItem::set(const QString &title, const QString &unit, double min, double max, int decimals)
{
    m_title = title;
    m_unit = unit;

    if (decimals == 2) {
        ui->doubleSpinBox->setSingleStep(0.01);
    } else if (decimals == 1) {
        ui->doubleSpinBox->setSingleStep(0.1);
    } else {
        ui->doubleSpinBox->setSingleStep(1);
    }

    ui->doubleSpinBox->setMinimum(min);
    ui->doubleSpinBox->setMaximum(max);
    ui->doubleSpinBox->setDecimals(decimals);

    update_title();
}

double SpinMenuItem::get_current_value() const
{
    return ui->doubleSpinBox->value();
}
