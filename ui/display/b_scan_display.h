#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include <QWidget>

#include <device/device.h>

class ScanView;
class BscanScene;
class BWaveItem;

namespace Ui {
class BscanDisplay;
}

class BscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit BscanDisplay(DplDevice::GroupPointer &group, QWidget *parent = 0);
    ~BscanDisplay();

protected slots:
    void do_data_event();

protected:
    DplDevice::GroupPointer m_group;

private:
    Ui::BscanDisplay *ui;
    ScanView         *m_bscanView;
    BscanScene       *m_bscanScene;
    BWaveItem        *m_bWaveItem;


};

#endif // __B_SCAN_DISPLAY_H_
