#include "fft_display.h"
#include "ui_fft_display.h"
#include "fft_scene.h"
#include "fft_item.h"

#include "../base/scan_view.h"

FFTDisplay::FFTDisplay(const DplDevice::GroupPointer &group,
                       Qt::Orientation orientation,
                       QWidget *parent) :
    QWidget(parent),
    m_group(group),
    m_orientation(orientation),
    m_view(new ScanView),
    m_fftScene(new FFTScene),
    m_fftItem(new FFTItem),
    ui(new Ui::FFTDisplay)
{
    ui->setupUi(this);
    ui->fftVLayout->addWidget(m_view);
    m_view->setScene(m_fftScene);
    m_fftScene->addItem(m_fftItem);

    connect(static_cast<DplDevice::Group *> (m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)),
            Qt::DirectConnection);

    connect(m_view, SIGNAL(size_changed(QSize)),
            this, SLOT(do_view_size_changed(QSize)));

    connect(this, SIGNAL(update_ruler()), this, SLOT(do_update_ruler()));

    connect(m_fftItem, SIGNAL(wave_changed()), this, SLOT(do_update_ruler()));
}


FFTDisplay::~FFTDisplay()
{
    QWriteLocker l(&m_locker);
    disconnect(static_cast<DplDevice::Group *> (m_group.data()),
            SIGNAL(data_event(DplSource::BeamsPointer)),
            this, SLOT(do_data_event(DplSource::BeamsPointer)));

    delete m_view;
    delete m_fftScene;
    delete ui;
}


void FFTDisplay::do_view_size_changed(const QSize &size)
{
    if (m_orientation == Qt::Horizontal) {
        m_fftScene->setSceneRect(-size.width()/2, -size.height()/2,
                                   size.width(), size.height());
        m_fftItem->set_size(size);
    } else {
        m_fftScene->setSceneRect(-size.height()/2, -size.width()/2 + 1,
                                   size.height(), size.width());
        m_fftItem->set_size(QSize(size.height(), size.width()));
    }
}

void FFTDisplay::do_data_event(const DplSource::BeamsPointer &beamsPointer)
{
    QWriteLocker l(&m_locker);
    m_fftItem->draw(beamsPointer->get(0)->wave(), m_group);
    emit update_ruler();
}

void FFTDisplay::do_update_ruler()
{
    update_bottom_ruler();
}
