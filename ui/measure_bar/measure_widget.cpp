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

QString MeasureWidget::name() const
{
    return ui->nameLabel->text();
}

void MeasureWidget::set_type(MeasureDialog::MeasureType type)
{
    MeasureDialog dlg(this, type);
    m_type = type;
    ui->nameLabel->setText(dlg.get_type_string());
}

void MeasureWidget::set_value(const QString &value)
{
    ui->valueLabel->setText(value);
}

bool MeasureWidget::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->nameLabel
            && event->type() == QEvent::MouseButtonPress) {
        MeasureDialog dialog(this, m_type);
        if (dialog.exec() == MeasureDialog::Accepted) {
            set_type(dialog.get_type());
        }
        return true;
    } else {
        return QWidget::eventFilter(object, event);
    }
}

