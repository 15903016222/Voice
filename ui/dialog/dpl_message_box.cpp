#include "dpl_message_box.h"
#include "ui_dpl_message_box.h"

#include <QDebug>
#include <QShowEvent>
#include <QPainter>

#define MAX_TIME_COUNT  1500

DplMessageBox::DplMessageBox(QMessageBox::Icon icon,
                             const QString &title,
                             const QString &info,
                             QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DplMessageBox),
      m_timer(new QTimer)
{
    ui->setupUi(this);

    m_icon = icon;
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);       /* 设置窗口背景透明 */

    connect(m_timer, SIGNAL(timeout()), this, SLOT(do_timer_timeout()));

    ui->titleLabel->setStyleSheet("QLabel{color: white;}");
    ui->titleLabel->setText(title);
    ui->infoLabel->setText(info);
    ui->iconLabel->setScaledContents(true);

    set_icon();
}

DplMessageBox::~DplMessageBox()
{
    delete m_timer;
    delete ui;
}

void DplMessageBox::showEvent(QShowEvent *event)
{
    if(m_icon == QMessageBox::Warning
            || m_icon == QMessageBox::Information) {
        m_timer->start(MAX_TIME_COUNT);
    }

    QDialog::showEvent(event);
}

void DplMessageBox::paintEvent(QPaintEvent *event)
{
    /* 圆角实现，并且需设置窗口背景透明 setAttribute(Qt::WA_TranslucentBackground); */
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);  /* 反锯齿; */
    painter.setBrush(QBrush(QColor(0, 130, 195)));
    painter.setPen(Qt::transparent);
    QRect rect = this->rect();
    rect.setWidth(rect.width());
    rect.setHeight(rect.height());
    painter.drawRoundedRect(rect, 8, 8);

    QWidget::paintEvent(event);
}


void DplMessageBox::do_timer_timeout()
{
    m_timer->stop();
    accept();
}

void DplMessageBox::on_okPushButton_clicked()
{
    accept();
}

void DplMessageBox::on_cancelPushButton_clicked()
{
    reject();
}

void DplMessageBox::set_icon()
{
    ui->iconLabel->setStyleSheet("background-color:white");

    switch (m_icon) {
    case QMessageBox::Warning:
    {
        QPixmap pixMap("://resource/messageBox/alert.png");
        ui->iconLabel->setPixmap(pixMap);
        ui->okPushButton->hide();
        ui->cancelPushButton->hide();
        break;
    }
    case QMessageBox::Information:
    {
        QPixmap pixMap("://resource/messageBox/info.png");
        ui->iconLabel->setPixmap(pixMap);
        ui->okPushButton->hide();
        ui->cancelPushButton->hide();
        break;
    }
    case QMessageBox::Question:
    {
        QPixmap pixMap("://resource/messageBox/question.png");
        ui->iconLabel->setPixmap(pixMap);
        break;
    }
    default:
        QPixmap pixMap("://resource/messageBox/alert.png");
        ui->iconLabel->setPixmap(pixMap);
        break;
    }
}

