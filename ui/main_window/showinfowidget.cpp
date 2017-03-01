#include "showinfowidget.h"
#include "ui_showinfowidget.h"

#include <QTimer>

ShowInfoWidget::ShowInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowInfoWidget)
{
    ui->setupUi(this);

    ui->label_5_showDateTime->installEventFilter(this);
    m_showDlg = false;

    init_show_time();
}

ShowInfoWidget::~ShowInfoWidget()
{
    delete ui;
}

void ShowInfoWidget::init_show_time()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(slotUpdateTime()));
    timer->start(0);
}

void ShowInfoWidget::slotUpdateTime()
{
    if(m_showDlg == false) {
        m_strDate = QDate::currentDate().toString("yyyy-MM-dd");
        m_strTime = QTime::currentTime().toString("hh:mm:ss");
    } else {
        QDate date;
        QTime time;
        if(m_count == 1) {
            date = setTimeDlg->dateEdit.at(0)->date();
            time = setTimeDlg->timeEdit.at(0)->time();
        } else {
            QString string = ui->label_5_showDateTime->text();
            m_strDate = string.left(string.indexOf(" "));
            m_strTime = string.right(string.length() - string.indexOf(" ") - 1);
            date = QDate(m_strDate.left(4).toInt(), m_strDate.mid(5, 2).toInt(), m_strDate.right(2).toInt());
            time = QTime(m_strTime.left(2).toInt(), m_strTime.mid(3, 2).toInt(), m_strTime.right(2).toInt());
        }

        QTime time1(23, 59, 59);
        if(time == time1)
        {
            date = date.addDays(1);
        }
        time = time.addSecs(1);

        m_strDate = date.toString("yyyy-MM-dd");
        m_strTime = time.toString("hh:mm:ss");
        m_count += 1;
    }

    QString dateTime;
    dateTime.append(m_strDate);
    dateTime.append(" ");
    dateTime.append(m_strTime);
    ui->label_5_showDateTime->setText(dateTime);
}

void ShowInfoWidget::slotPushButton_ok()
{   
    setTimeDlg->close();
    m_showDlg = true;
    m_count = 1;
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
