#include "showinfowidget.h"
#include "ui_showinfowidget.h"

#include <QTimer>

ShowInfoWidget::ShowInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowInfoWidget)
{
    ui->setupUi(this);

  //  timer = new QTimer(this);
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
    QDateTime time = QDateTime::currentDateTime();

    QString str_time = time.toString("yyyy-MM-dd hh:mm:ss");

    ui->label_5_showDateTime->setText(str_time);
}

void ShowInfoWidget::slotPushButton_ok()
{
    timer->stop();
    connect(timer, SIGNAL(timeout()), this, SLOT(slotEditTime()));
    timer->start(1000);

    setTimeDlg.close();
}

void ShowInfoWidget::slotEditTime()
{
//    date = setTimeDlg.dateEdit.at(0)->date();
//    time = setTimeDlg.timeEdit.at(0)->time();
//    QTime time1(23, 59, 59);

//    if(time == time1)
//    {
//     date = date.addDays(1);
//    }
//    time = time.addSecs(1);

//    str_date = date.toString("yyyy-MM-dd");
//    str_time = time.toString("hh:mm:ss");

//    dateTime.append(str_date);
//    dateTime.append(" ");
//    dateTime.append(str_time);
//    ui->label_5_showDateTime->setText(dateTime);
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
