#ifndef __FFT_DISPLAY_H__
#define __FFT_DISPLAY_H__

#include <QWidget>
#include <device/device.h>

class ScanView;
class FFTScene;
class FFTItem;

namespace Ui {
class FFTDisplay;
}

class FFTDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit FFTDisplay(const DplDevice::GroupPointer &group,
                        Qt::Orientation orientation,
                        QWidget *parent = 0);
    ~FFTDisplay();

protected slots:
    void do_view_size_changed(const QSize &size);
    void do_data_event(const DplSource::BeamsPointer &beamsPointer);


protected:
    DplDevice::GroupPointer m_group;
    Qt::Orientation m_orientation;

    ScanView *m_view;
    FFTScene *m_fftScene;
    FFTItem  *m_fftItem;

    Ui::FFTDisplay *ui;


};

#endif // __FFT_DISPLAY_H__
