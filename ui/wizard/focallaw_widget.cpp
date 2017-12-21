#include "focallaw_widget.h"

#include <QDebug>
#include "ui_focallaw_widget.h"

FocallawWidget::FocallawWidget(WizardSetting::E_WIZARD_TYPE type, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FocallawWidget)
{
    Q_UNUSED(type);
    ui->setupUi(this);
}

FocallawWidget::~FocallawWidget()
{
    delete ui;
}
