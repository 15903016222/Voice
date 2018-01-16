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
//                                    font-weight:bold;
    if(flag) {
        setStyleSheet(QString("QLabel#titleLabel{ \
                                background-image: url(%1); \
                                color: %2;   \
                                font: 25pt; \
                                border-style: outset; \
                                }").arg(m_backGroundPath.at((int)flag)).arg(SELECTED));
    } else {
        setStyleSheet(QString("QLabel#titleLabel{ \
                                background-image: url(%1); \
                                color: %2;   \
                                font: 25pt; \
                                border-style: outset; \
                                }").arg(m_backGroundPath.at((int)flag)).arg(UNSELECTED));
    }
}
