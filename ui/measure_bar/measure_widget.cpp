/**
 * @file measure_widget.cpp
 * @brief 测量部件
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-19
 */
#include "measure_widget.h"
#include "ui_measure_widget.h"
#include <device/device.h>

MeasureWidget::MeasureWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MeasureWidget)
{
    ui->setupUi(this);
    ui->nameLabel->installEventFilter(this);

    connect(this,
            SIGNAL(calculated(QString)),
            ui->valueLabel,
            SLOT(setText(QString)), Qt::QueuedConnection);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(do_current_group_changed(DplDevice::GroupPointer)));
    do_current_group_changed(DplDevice::Device::instance()->current_group());

}

MeasureWidget::~MeasureWidget()
{
    delete ui;
}

void MeasureWidget::set_type(Measure::Type type)
{
    QWriteLocker l(&m_rwLock);
    m_type = type;
}

QString MeasureWidget::value() const
{
    return ui->valueLabel->text();
}

void MeasureWidget::set_value(const QString &value)
{
    ui->valueLabel->setText(value);
}

bool MeasureWidget::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->nameLabel
            && event->type() == QEvent::MouseButtonPress) {
        emit clicked(this);
        return true;
    } else {
        return QWidget::eventFilter(object, event);
    }
}

void MeasureWidget::update_name_label()
{
    QString msg("<p align=\"center\"><font style='font-size:16pt' face='Arial' color=white>");
    msg += m_title;
    msg += "</font>";

    if ( !m_unit.isEmpty() ){
        msg += "<br/><font style='font-size:12pt' face='Arial' color=white>(";
        msg += m_unit;
        msg += ")</font>";
    }

    ui->nameLabel->setText(msg);
}

void MeasureWidget::do_current_group_changed(const DplDevice::GroupPointer &grp)
{
    QWriteLocker l(&m_rwLock);
    disconnect(static_cast<DplDevice::Group *>(m_group.data()),
               SIGNAL(data_event(DplSource::BeamsPointer)),
               this,
               SLOT(do_data_event()));
    m_group = grp;
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this,
            SLOT(do_data_event()),
            Qt::DirectConnection);
}

void MeasureWidget::do_data_event()
{
    QReadLocker l(&m_rwLock);
    emit calculated(Measure::instance()->calculate_str(m_group, m_type));
}
