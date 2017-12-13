#include "tcg_properties_widget.h"
#include "ui_tcg_properties_widget.h"

#include <QDebug>

TCGPropertiesWidget::TCGPropertiesWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TCGPropertiesWidget)
{
    ui->setupUi(this);
    hide();
}

TCGPropertiesWidget::~TCGPropertiesWidget()
{
    qDebug() << "[" << __FUNCTION__ << "]" << "destructor";
    delete ui;
}
