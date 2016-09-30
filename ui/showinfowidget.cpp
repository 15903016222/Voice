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

    QString string1 = "border-right:1px solid qlineargradient(spread:reflect, x1:0, y1:0, x2:0, y2:0.5, stop:0.2 rgba(210, 150, 0, 255), stop:0.5 rgba(0, 0, 0, 255));" ;
    QString string2 = "border-left:1px solid qlineargradient(spread:reflect, x1:0, y1:0,x2:0, y2:0.5, stop:0.2 rgba(210, 150, 0, 255), stop:0.5 rgba(255, 255, 255, 255));";
    ui->label_1->setStyleSheet("QLabel{" + string1 + "}");
    ui->label_6->setStyleSheet("QLabel{" + string2 + "}");
    ui->label_2->setStyleSheet("QLabel{" + string1 + string2 + "}");
    ui->label_3->setStyleSheet("QLabel{" + string1 + string2 + "}");
    ui->label_4->setStyleSheet("QLabel{" + string1 + string2 + "}");
    ui->label_5_showDateTime->setStyleSheet("QLabel{" + string1 + string2 + "}");
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
    if(showDlg == false) {
        str_date = QDate::currentDate().toString("yyyy-MM-dd");
        str_time = QTime::currentTime().toString("hh:mm:ss");
    } else {
        QDate date;
        QTime time;
        if(count == 1) {
            date = setTimeDlg->dateEdit.at(0)->date();
            time = setTimeDlg->timeEdit.at(0)->time();
        } else {
            QString string = ui->label_5_showDateTime->text();
            str_date = string.left(string.indexOf(" "));
            str_time = string.right(string.length() - string.indexOf(" ") - 1);
            date = QDate(str_date.left(4).toInt(), str_date.mid(5, 2).toInt(), str_date.right(2).toInt());
            time = QTime(str_time.left(2).toInt(), str_time.mid(3, 2).toInt(), str_time.right(2).toInt());
        }

        QTime time1(23, 59, 59);
        if(time == time1)
        {
            date = date.addDays(1);
        }
        time = time.addSecs(1);

        str_date = date.toString("yyyy-MM-dd");
        str_time = time.toString("hh:mm:ss");
        count += 1;
    }

    QString dateTime;
    dateTime.append(str_date);
    dateTime.append(" ");
    dateTime.append(str_time);
    ui->label_5_showDateTime->setText(dateTime);
}

void ShowInfoWidget::slotPushButton_ok()
{   
    setTimeDlg->close();
    showDlg = true;
    count = 1;
    timer->start(1000);
}

bool ShowInfoWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->label_5_showDateTime) {
        if(event->type() == QEvent::MouseButtonPress) {
            setTimeDlg = new TimeSetDialog(this);
            setTimeDlg->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
            setTimeDlg->setModal(true);
            setTimeDlg->show();
            connect(this, SIGNAL(currentDateTime(QString)), setTimeDlg, SLOT(set_date_and_time(QString)));
            emit currentDateTime(ui->label_5_showDateTime->text());
            connect(setTimeDlg->pushButton_ok.at(0), SIGNAL(clicked()), this, SLOT(slotPushButton_ok()));
        }
    }
    return QWidget::eventFilter(object, event);
}
