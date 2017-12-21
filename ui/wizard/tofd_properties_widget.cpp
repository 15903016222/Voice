#include "tofd_properties_widget.h"
#include "ui_tofd_properties_widget.h"

TOFDPropertiesWidget::TOFDPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TOFDPropertiesWidget)
{
    ui->setupUi(this);
    hide();
}

TOFDPropertiesWidget::~TOFDPropertiesWidget()
{
    delete ui;
}
