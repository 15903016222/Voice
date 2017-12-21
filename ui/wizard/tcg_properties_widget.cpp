#include "tcg_properties_widget.h"
#include "ui_tcg_properties_widget.h"

TCGPropertiesWidget::TCGPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCGPropertiesWidget)
{
    ui->setupUi(this);
    hide();
}

TCGPropertiesWidget::~TCGPropertiesWidget()
{
    delete ui;
}
