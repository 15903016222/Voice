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

signals:
    void paint_event();

protected slots:
    void do_start_paint_thread();

protected:
    Ui::ScanDisplay *ui;
    DplDevice::GroupPointer m_group;

private:
    ScanView *m_view;
    SscanScene *m_scene;
};

#endif // __S_SCAN_DISPLAY_H__
