#ifndef __C_SCAN_DISPLAY_H__
#define __C_SCAN_DISPLAY_H__

#include <QWidget>
#include <device/group.h>

namespace Ui {
class ScanDisplay;
}

class ScanView;
class CscanScene;

class CscanDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit CscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~CscanDisplay();

signals:

public slots:

protected:
    Ui::ScanDisplay *ui;
    DplDevice::GroupPointer m_group;

private:
    ScanView *m_view;
    CscanScene *m_scene;
};

#endif // __C_SCAN_DISPLAY_H__
