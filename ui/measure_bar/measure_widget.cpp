#include "measure_widget.h"
#include "ui_measure_widget.h"

MeasureWidget::MeasureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureWidget)
{
    ui->setupUi(this);
    ui->nameLabel->installEventFilter(this);
}

MeasureWidget::~MeasureWidget()
{
    delete ui;
}

QString MeasureWidget::value() const
{
    return ui->valueLabel->text();
}

void MeasureWidget::set_value(const QString &value)
{
    ui->valueLabel->setText(value);
}

bool MeasureWidget::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->nameLabel
            && event->type() == QEvent::MouseButtonPress) {
        emit clicked(this);
        return true;
    } else {
        return QWidget::eventFilter(object, event);
    }
}

void MeasureWidget::update_name_label()
{
    QString msg("<p align=\"center\"><font style='font-size:16pt' face='Arial' color=white>");
    msg += m_title;
    msg += "</font>";

    if ( !m_unit.isEmpty() ){
        msg += "<br/><font style='font-size:12pt' face='Arial' color=white>(";
        msg += m_unit;
        msg += ")</font>";
    }

    ui->nameLabel->setText(msg);
}
