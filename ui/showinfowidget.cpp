#include "showinfowidget.h"
#include "ui_showinfowidget.h"

#include <QTimer>
#include <QDateTime>

ShowInfoWidget::ShowInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowInfoWidget)
{
    ui->setupUi(this);

    initShowTime();
}

ShowInfoWidget::~ShowInfoWidget()
{
    delete ui;
}

void ShowInfoWidget::displayTime()
{
    QDateTime time = QDateTime::currentDateTime();
    QString str_time = time.toString("yyyy-MM-dd hh:mm:ss");
    ui->label_5_showDateTime->setText(str_time);
}

void ShowInfoWidget::initShowTime()
{
    displayTime();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdateTime()));
    timer->start(500);
}

void ShowInfoWidget::slotUpdateTime()
{
    displayTime();
}
