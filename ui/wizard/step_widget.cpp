#include "step_widget.h"
#include "ui_step_widget.h"

#include <QPainter>
#include <QDebug>

static const QString SELECTED("rgb(170, 255, 0)");
static const QString UNSELECTED("white");

StepWidget::StepWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StepWidget),
    m_selected(false)
{
    ui->setupUi(this);

    set_selected(m_selected);

}

StepWidget::~StepWidget()
{
    delete ui;
}

void StepWidget::set_title(const QString &title)
{
    ui->titleLabel->setText(title);
}

void StepWidget::set_back_ground(const QStringList &list)
{
    m_backGroundPath = list;
}

void StepWidget::set_selected(bool flag)
{
    if(flag) {
        setStyleSheet(QString("QLabel#titleLabel{ \
                                background-color:rgb(0, 130, 195); \
                                color: %1;   \
                                font: 26pt; \
                                font-weight:bold; \
                                border-style: outset; \
                                }").arg(SELECTED));
    } else {
        setStyleSheet(QString("QLabel#titleLabel{ \
                                background-color:rgb(0, 130, 195); \
                                color: %1;   \
                                font: 26pt; \
                                font-weight:bold; \
                                border-style: outset; \
                                }").arg(UNSELECTED));
    }
}
