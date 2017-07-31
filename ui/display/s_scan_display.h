#ifndef __S_SCAN_DISPLAY_H__
#define __S_SCAN_DISPLAY_H__

#include <QWidget>
#include <device/group.h>

namespace Ui {
class SscanDisplay;
}

class SscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit SscanDisplay(DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~SscanDisplay();

private:
    Ui::SscanDisplay *ui;
    DplDevice::GroupPointer m_group;
};

#endif // __S_SCAN_DISPLAY_H__
