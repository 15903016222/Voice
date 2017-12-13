#include "acg_properties_widget.h"
#include "ui_acg_properties_widget.h"

ACGPropertiesWidget::ACGPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ACGPropertiesWidget)
{
    ui->setupUi(this);
    hide();
}

ACGPropertiesWidget::~ACGPropertiesWidget()
{
    delete ui;
}
