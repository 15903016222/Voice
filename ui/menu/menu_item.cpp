#include "menu_item.h"
#include "ui_menu_item.h"

#include <QKeyEvent>
#include <QDebug>
#include <QListView>

MenuItem::MenuItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuItem)
{
    ui->setupUi(this);

    m_type = Label;

    ui->comboBox->hide();

    ui->nameLabel->installEventFilter(this);
    ui->doubleSpinBox->installEventFilter(this);

    connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SIGNAL(spin_event(double)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SIGNAL(combo_event(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), ui->label, SLOT(setText(QString)));
}

MenuItem::~MenuItem()
{
    delete ui;
}

void MenuItem::set_type(MenuItem::Type type)
{
    m_type = type;

    ui->doubleSpinBox->hide();
    ui->label->hide();

    switch (type) {
    case Label:
        ui->label->show();
        break;
    case Spin:
        ui->doubleSpinBox->show();
        break;
    case Combo:
        ui->label->show();
        ui->comboBox->setView(new QListView());
        ui->comboBox->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);
        ui->comboBox->view()->parentWidget()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
        ui->comboBox->view()->setFocusPolicy(Qt::StrongFocus);
        ui->comboBox->view()->setFocus();
        break;
    default:
        ui->label->show();
        ui->label->clear();
        ui->nameLabel->clear();
        break;
    }

}

void MenuItem::clean()
{
    ui->nameLabel->clear();
    ui->doubleSpinBox->clear();
    ui->comboBox->clear();
    m_title.clear();
    m_unit.clear();
    ui->label->clear();
    m_labelText.clear();
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

void MenuItem::set_suffix(const QString &text)
{
    ui->doubleSpinBox->setSuffix(text);
}

void MenuItem::set_range(double min, double max)
{
    ui->doubleSpinBox->setMinimum(min);
    ui->doubleSpinBox->setMaximum(max);
}

void MenuItem::set_decimals(int prec)
{
    ui->doubleSpinBox->setDecimals(prec);
}

void MenuItem::add_combo_item(const QString &text)
{
    ui->comboBox->addItem(text);
}

void MenuItem::set_combo_items(const QStringList &texts)
{
    ui->comboBox->addItems(texts);
}

bool MenuItem::eventFilter(QObject *obj, QEvent *e)
{
    if (obj == ui->nameLabel) {
        return do_namelabel_event(e);
    } else if (obj == ui->doubleSpinBox) {
        return do_doubleSpinBox_event(e);
    }

    return QWidget::eventFilter(obj, e);
}

void MenuItem::update_title()
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

void MenuItem::update_spin_step()
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

void MenuItem::set_spin_focus()
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
}

bool MenuItem::do_namelabel_event(QEvent *e)
{
    if (e->type() != QEvent::MouseButtonRelease) {
        return QWidget::eventFilter(ui->nameLabel, e);
    }

    if(m_type == Spin) {
        if (ui->doubleSpinBox->hasFocus()) {
            update_spin_step();
        } else {
            set_spin_focus();
        }
    } else if(m_type == Combo) {
        ui->comboBox->showPopup();
    } else if(m_type == Label) {
        emit clicked();
    }
    return true;
}

bool MenuItem::do_doubleSpinBox_event(QEvent *e)
{
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
    } else if (e->type() == QEvent::FocusOut) {
        set_focus_out();
    } else {
        return QWidget::eventFilter(ui->doubleSpinBox, e);
    }
    return true;
}

bool MenuItem::do_comboBox_activated(const QString &label)
{
    ui->label->setText(label);
}

void MenuItem::set_label_text(const QString &text)
{
    ui->label->setText(text);
    m_labelText = text;
}

void MenuItem::set_spin(const QString &title, const QString &unit, double min, double max, int decimals)
{
    set_type(Spin);

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

void MenuItem::set_combo(const QString &title, const QStringList &texts)
{
    set_type(Combo);

    m_title = title;
    ui->comboBox->clear();
    ui->comboBox->addItems(texts);

    update_title();
}

void MenuItem::set_label(const QString &title)
{
    set_type(Label);

    m_title = title;

    update_title();
}

QString MenuItem::get_title()
{
    return m_title;
}

QString MenuItem::get_label_text()
{
    return m_labelText;
}
