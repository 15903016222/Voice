/**
 * @file measure_widget.cpp
 * @brief 测量部件
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-19
 */
#include "measure_widget.h"
#include <device/device.h>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

MeasureWidget::MeasureWidget(QWidget *parent) : QWidget(parent),
    m_pushBtn(new QPushButton),
    m_label(new QLabel)
{
    m_label->setFocusPolicy(Qt::NoFocus);
    m_pushBtn->setFocusPolicy(Qt::NoFocus);
    m_label->setAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    m_pushBtn->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(0);
    vbox->addWidget(m_pushBtn, 2);
    vbox->addWidget(m_label, 1);

    connect(m_pushBtn, SIGNAL(clicked(bool)),
            this, SLOT(do_pushBtn_clicked()));

    connect(this,
            SIGNAL(calculated(QString)),
            m_label,
            SLOT(setText(QString)), Qt::QueuedConnection);

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(do_current_group_changed(DplDevice::GroupPointer)));
    do_current_group_changed(DplDevice::Device::instance()->current_group());
}

MeasureWidget::~MeasureWidget()
{
}

void MeasureWidget::set_type(Measure::Type type)
{
    QWriteLocker l(&m_rwLock);
    m_type = type;
}

QString MeasureWidget::value() const
{
    return m_label->text();
}

void MeasureWidget::set_value(const QString &value)
{
    m_label->setText(value);
}

void MeasureWidget::update_title()
{
    QString msg = m_title;

    if ( !m_unit.isEmpty() ){
        msg += "\n(";
        msg += m_unit;
        msg += ")";
    }

    m_pushBtn->setText(msg);
}

void MeasureWidget::do_pushBtn_clicked()
{
    emit clicked(this);
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
