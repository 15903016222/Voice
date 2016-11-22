#include "gain_widget.h"
#include "ui_gain_widget.h"

#include <QKeyEvent>

GainWidget::GainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GainWidget)
{
    ui->setupUi(this);

    enable_ref_gain(false);

    ui->nameLabel->installEventFilter(this);
    ui->unitLabel->installEventFilter(this);
    ui->stepLabel->installEventFilter(this);
    ui->gainDoubleSpinBox->installEventFilter(this);
}

GainWidget::~GainWidget()
{
    delete ui;
}

void GainWidget::enable_ref_gain(bool flag)
{
    if (flag) {
        ui->nameLabel->setText(tr("Gain-r"));
        ui->refGainDoubleSpinBox->show();
        ui->gainDoubleSpinBox->setAlignment(Qt::AlignRight);
    } else {
        ui->nameLabel->setText(tr("Gain"));
        ui->refGainDoubleSpinBox->hide();
        ui->gainDoubleSpinBox->setAlignment(Qt::AlignHCenter);
    }
}

bool GainWidget::eventFilter(QObject *obj, QEvent *e)
{
    if (e->type() == QEvent::MouseButtonPress) {
        if (ui->gainDoubleSpinBox->hasFocus()) {
            double step = ui->gainDoubleSpinBox->singleStep();
            if (step == 0.1) {
                step = 0.5;
            } else if (step == 0.5) {
                step = 1.0;
            } else if (step == 1.0) {
                step = 5.0;
            } else {
                step = 0.1;
            }
            ui->gainDoubleSpinBox->setSingleStep(step);
            ui->refGainDoubleSpinBox->setSingleStep(step);
            ui->stepLabel->setText("Δ"+QString::number(step, 'f', 1));
        } else {
            set_focus();
        }
        return true;
    }


    if (e->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = dynamic_cast<QKeyEvent *>(e);
        if (keyEvent->key() == Qt::Key_Enter
                || keyEvent->key() == Qt::Key_Return) {
            set_focus_out();
            return true;
        }
    } else if (e->type() == QEvent::FocusOut) {
        set_focus_out();
        return true;
    }

    return QWidget::eventFilter(obj, e);
}

void GainWidget::set_focus()
{
    ui->gainDoubleSpinBox->setStyleSheet("QDoubleSpinBox{\nselection-color:black; selection-background-color: rgba(255,255,255,255);\n}");
    ui->gainDoubleSpinBox->setFocusPolicy(Qt::StrongFocus);
    ui->gainDoubleSpinBox->setFocus();
    ui->gainDoubleSpinBox->setReadOnly(false);
}

void GainWidget::set_focus_out()
{
    ui->gainDoubleSpinBox->setFocusPolicy(Qt::NoFocus);
    ui->gainDoubleSpinBox->clearFocus();
    ui->gainDoubleSpinBox->setReadOnly(true);
    ui->gainDoubleSpinBox->setStyleSheet("QDoubleSpinBox{selection-background-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\nstop:0.158192 rgba(0, 0, 0, 255),\nstop:0.559322 rgba(0, 130, 195, 255));\ncolor: rgb(255, 255, 255);\nborder-top:0px;\nborder-bottom:0px;\nbackground-color: qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1,\nstop:0.158192 rgba(0, 0, 0, 255),\nstop:0.559322 rgba(0, 130, 195, 255));\ncolor: rgb(255, 255, 255);\nborder-top:0px;\nborder-bottom:0px;\n}");
}
