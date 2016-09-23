#include "inputpanelcontext.h"
#include "ui_inputpanelcontext.h"

InputPanelContext::InputPanelContext(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputPanelContext)
{
    ui->setupUi(this);
}

InputPanelContext::~InputPanelContext()
{
    delete ui;
}
