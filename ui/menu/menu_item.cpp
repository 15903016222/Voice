#include "menu_item.h"
#include "ui_menu_item.h"

#include <QKeyEvent>
#include <QDebug>
#include <QListView>

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

//    ui->comboBox->setLineEdit(new QLineEdit());
//    ui->comboBox->lineEdit()->setAlignment(Qt::AlignCenter);
//    ui->comboBox->lineEdit()->setReadOnly(true);
}

MenuItem::~MenuItem()
{
    delete ui;
}

void MenuItem::set_type(MenuItem::Type type)
{
    ui->comboBox->hide();
    ui->doubleSpinBox->hide();
    ui->label->hide();

    switch (type) {
    case None:
        ui->label->show();
        break;
    case Spin:
        ui->doubleSpinBox->show();
        break;
    case Combo:
        ui->comboBox->show();
        ui->comboBox->setView(new QListView());
        ui->comboBox->view()->parentWidget()->setAttribute(Qt::WA_TranslucentBackground);
        ui->comboBox->view()->parentWidget()->setWindowFlags(Qt::Popup | Qt::FramelessWindowHint);
        ui->comboBox->view()->setFocusPolicy(Qt::StrongFocus);
        ui->comboBox->view()->setFocus();
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

void MenuItem::set_steps(const QList<double> &steps)
{
     m_steps = steps;
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
    if (e->type() == QEvent::MouseButtonPress) {
        if(!ui->doubleSpinBox->isHidden()) {
            if (ui->doubleSpinBox->hasFocus()
                && ! m_steps.isEmpty()) {
                update_step();
            } else {
                set_focus();
            }
        } else if(!ui->comboBox->isHidden()) {
            QMouseEvent *event = new QMouseEvent(QEvent::MouseButtonDblClick, QPoint(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
            QApplication::sendEvent(ui->comboBox, event);
        } else if(!ui->label->isHidden()) {
            emit clicked();
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

void MenuItem::update_step()
{
    if ( ++m_curStep >= m_steps.size() ) {
        m_curStep = 0;
    }
    ui->doubleSpinBox->setSingleStep(m_steps.at(m_curStep));
    update_title();
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
        ui->doubleSpinBox->setStyleSheet("QDoubleSpinBox{"
                                         "color: rgb(255, 255, 255);"
                                         "border-top:0px;"
                                         "border-bottom:0px;"
                                         "font: 13pt 'Century Gothic';"
                                         "color: white;"
                                         "selection-color: white;"
                                         "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
                                         "selection-background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.4 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));"
                                         "border-left:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(255, 255, 255, 255), stop:1 rgba(0, 120, 195, 255));"
                                         "border-right:1px solid qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0.3 rgba(0, 0, 0, 255), stop:1 rgba(0, 120, 195, 255));}");
        update_title();
    }
}

void MenuItem::set_label_text(const QString &text)
{
    ui->label->setText(text);
    m_labelText = text;
}
