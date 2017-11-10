#ifndef __S_SCAN_DISPLAY_H__
#define __S_SCAN_DISPLAY_H__

#include <QWidget>
#include <device/group.h>

namespace Ui {
class ScanDisplay;
}

class ScanView;
class SscanScene;

class SscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit SscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~SscanDisplay();

protected slots:
    void do_data_event(const DplSource::BeamsPointer &beams);

protected:
    Ui::ScanDisplay *ui;
    DplDevice::GroupPointer m_group;

protected slots:
    void update_rules();

private:
    ScanView *m_view;
    SscanScene *m_scene;
    DplDisplay::SscanPointer m_sScan;
};

#endif // __S_SCAN_DISPLAY_H__
