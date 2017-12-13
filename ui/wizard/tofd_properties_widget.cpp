#include "tofd_properties_widget.h"
#include "ui_tofd_properties_widget.h"

#include <QDebug>

TOFDPropertiesWidget::TOFDPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TOFDPropertiesWidget)
{
    ui->setupUi(this);
    hide();
}

TOFDPropertiesWidget::~TOFDPropertiesWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}
