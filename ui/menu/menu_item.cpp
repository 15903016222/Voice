#include "menu_item.h"
#include "ui_menu_item.h"

#include <QKeyEvent>
#include <QDebug>

MenuItem::MenuItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItem),
    m_curStep(0)
{
    ui->setupUi(this);

    ui->nameLabel->installEventFilter(this);
    ui->doubleSpinBox->installEventFilter(this);
    ui->comboBox->installEventFilter(this);

    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(spin_event(double)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(combo_event(int)));
}

MenuItem::~MenuItem()
{
    delete ui;
}

void MenuItem::set_type(MenuItem::Type type)
{
    ui->comboBox->hide();
    ui->doubleSpinBox->hide();

    switch (type) {
    case None:
        break;
    case Spin:
        ui->doubleSpinBox->show();
        break;
    case Combo:
        ui->comboBox->show();
        break;
    default:
        break;
    }
}

void MenuItem::clean()
{
    ui->nameLabel->clear();
    ui->doubleSpinBox->clear();
    ui->comboBox->clear();
    m_curStep = 0;
}

void MenuItem::set_title(const QString &title)
{
    m_title = title;
    update_title();
}

void MenuItem::set_unit(const QString &unitName)
{
    m_unit = unitName;
    update_title();
}

void MenuItem::set_steps(QList<double> &steps)
{
     m_steps = steps;
     update_title();
}

bool MenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress) {
        qDebug () << e->type();
        if (ui->doubleSpinBox->hasFocus()
                && ! m_steps.isEmpty()) {
            qDebug()<<m_curStep;

            if ( ++m_curStep >= m_steps.size() ) {
                m_curStep = 0;
            }
            qDebug()<<m_curStep;
            ui->doubleSpinBox->setSingleStep(m_steps.at(m_curStep));
            update_title();
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
            break;
        default:
            break;
        }
        return true;
    } else if (e->type() == QEvent::FocusOut) {
        set_focus_out();
        return true;
    }

    return QWidget::eventFilter(obj, e);
}

void MenuItem::update_title()
{
    QString msg("<html><head/><body><p align=\"center\"><font size=4 color=yellow>");
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
            msg += "Δ";
            msg += QString::number(ui->doubleSpinBox->singleStep(), 'f', ui->doubleSpinBox->decimals());
        }
    }
    msg += "</p></body></html>";
    qDebug()<<msg;
    ui->nameLabel->setText(msg);
}

void MenuItem::set_focus()
{
    if ( ! ui->doubleSpinBox->isHidden() ) {
        ui->doubleSpinBox->setStyleSheet("QDoubleSpinBox{\nselection-color:black; selection-background-color: rgba(255,255,255,255);\n}");
        ui->doubleSpinBox->setFocusPolicy(Qt::WheelFocus);
        ui->doubleSpinBox->setFocus();
        ui->doubleSpinBox->setReadOnly(false);
        update_title();
    }
}

void MenuItem::set_focus_out()
{
    if ( ! ui->doubleSpinBox->isHidden() ) {
        ui->doubleSpinBox->setFocusPolicy(Qt::NoFocus);
        ui->doubleSpinBox->clearFocus();
        ui->doubleSpinBox->setReadOnly(true);
        ui->doubleSpinBox->setStyleSheet("QDoubleSpinBox{selection-background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\nstop:0.158192 rgba(0, 0, 0, 255),\nstop:0.559322 rgba(0, 130, 195, 255));\ncolor: rgb(255, 255, 255);\nborder-top:0px;\nborder-bottom:0px;\nbackground-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\nstop:0.158192 rgba(0, 0, 0, 255),\nstop:0.559322 rgba(0, 130, 195, 255));\ncolor: rgb(255, 255, 255);\nborder-top:0px;\nborder-bottom:0px;\n}");
        update_title();
    }
}

void MenuItem::add_item(const QString &text)
{
    ui->comboBox->addItem(text);
}
