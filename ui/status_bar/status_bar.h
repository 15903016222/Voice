#ifndef __STATUS_BAR__
#define __STATUS_BAR__

#include <QWidget>
#include <device/device.h>
#include <source/scan.h>
#include <source/encoder.h>
#include <QReadWriteLock>

namespace Ui {
class StatusBar;
}

class StatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit StatusBar(QWidget *parent = 0);
    ~StatusBar();

protected slots:
    void do_timeout();
    void do_current_group_changed(const DplDevice::GroupPointer &grp);
    void do_scan_mode_changed(DplSource::Scan::Mode mode);
    void do_data_event(const DplSource::BeamsPointer &beams);
    void do_encoder_text_changed();
    void do_acquisition_rate_changed();

signals:
    void encoder_text_changed();

private:
    Ui::StatusBar *ui;
    QTimer *m_timer;
    DplDevice::GroupPointer m_group;
    DplSource::Scan *m_scan;

    QString m_scanEncStr;
    QString m_indexEncStr;
    QReadWriteLock m_encStringRWLock;
};

#endif // __STATUS_BAR__
