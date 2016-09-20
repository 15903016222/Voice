#include "showinfowidget.h"
#include "ui_showinfowidget.h"

#include <QTimer>

ShowInfoWidget::ShowInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowInfoWidget)
{
    ui->setupUi(this);

    ui->label_5_showDateTime->installEventFilter(this);
    showDlg = false;

    initShowTime();

    connect(setTimeDlg.pushButton_ok.at(0), SIGNAL(clicked()), this, SLOT(slotPushButton_ok()));
}

ShowInfoWidget::~ShowInfoWidget()
{
    delete ui;
}

void ShowInfoWidget::initShowTime()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdateTime()));
    timer->start(500);
}

void ShowInfoWidget::slotUpdateTime()
{
    str_date = QDate::currentDate().toString("yyyy-MM-dd");
    str_time = QTime::currentTime().toString("hh:mm:ss");
    QString dateTime;
    dateTime.append(str_date);
    dateTime.append(" ");
    dateTime.append(str_time);
    ui->label_5_showDateTime->setText(dateTime);
}

void ShowInfoWidget::slotPushButton_ok()
{
    QTimer *timer1 = new QTimer(this);
    connect(setTimeDlg.dateEdit.at(0), SIGNAL(dateChanged(QDate)), this, SLOT(slot_dateEdit_dateChanged(QDate)));
    connect(setTimeDlg.timeEdit.at(0), SIGNAL(timeChanged(QTime)), this, SLOT(slot_timeEdit_timeChanged(QTime)));
 //   connect(timer1, SIGNAL(timeout()), this, SLOT(slotEditTime()));
    timer1->start();

    setTimeDlg.close();
}

void ShowInfoWidget::slotEditTime()
{
    QDate date = setTimeDlg.dateEdit.at(0)->date();
    QTime time = setTimeDlg.timeEdit.at(0)->time();

    QTime time1(23, 59, 59);

    if(time == time1)
    {
        date = date.addDays(1);
    }
    time = time.addSecs(1);

    str_date = date.toString("yyyy-MM-dd");
    str_time = time.toString("hh:mm:ss");
    QString dateTime;
    dateTime.append(str_date);
    dateTime.append(" ");
    dateTime.append(str_time);
    ui->label_5_showDateTime->setText(dateTime);
}

void ShowInfoWidget::slot_dateEdit_dateChanged(QDate date)
{
    timer->stop();
    str_date = date.toString("yyyy-MM-dd");
}

void ShowInfoWidget::slot_timeEdit_timeChanged(QTime time)
{
    timer->stop();
    str_time = time.toString("hh:mm:ss");
}

bool ShowInfoWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->label_5_showDateTime)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(!showDlg){
                showDlg = true;
                setTimeDlg.setWindowFlags(Qt::FramelessWindowHint);
                setTimeDlg.setModal(true);
                setTimeDlg.showNormal();
                setTimeDlg.exec();
            }
            showDlg = !showDlg;
        }
    }
    return QWidget::eventFilter(object, event);
}
