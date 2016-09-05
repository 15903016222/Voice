#include "showinfowidget.h"
#include "ui_showinfowidget.h"

#include "timesetdialog.h"

#include <QTimer>
#include <QDateTime>

ShowInfoWidget::ShowInfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowInfoWidget)
{
    ui->setupUi(this);

    ui->label_5_showDateTime->installEventFilter(this);
    showDlg = false;

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

bool ShowInfoWidget::eventFilter(QObject *object, QEvent *event)
{
    if(object == ui->label_5_showDateTime)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            if(!showDlg){
                showDlg = true;
                TimeSetDialog setTimeDlg;
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

void ShowInfoWidget::slotUpdateTime()
{
    displayTime();
}
