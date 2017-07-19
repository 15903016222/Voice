#include "status_bar.h"
#include "ui_status_bar.h"

#include <QTime>
#include <QTimer>

StatusBar::StatusBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatusBar),
    m_timer(new QTimer)
{
    ui->setupUi(this);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_timeout()));
    m_timer->start(1000);
}

StatusBar::~StatusBar()
{
    delete m_timer;
    delete ui;
}

void StatusBar::do_timeout()
{
//    m_strDate = QDate::currentDate().toString("yyyy-MM-dd");
    ui->timeLabel->setText(QDateTime::currentDateTime().toString("MM-dd hh:mm:ss"));
}
