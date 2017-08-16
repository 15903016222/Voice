#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include <QWidget>

#include <device/device.h>

class ScanView;
class BscanScene;
class BWaveItem;
class RulerWidget;
class QTimer;
class QLabel;

namespace Ui {
class BscanDisplay;
}

class BscanDisplay : public QWidget
{
    Q_OBJECT

public:

    enum E_SCAN_TYPE{
        TIME,
        ENCODER
    };

public:
    explicit BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent = 0);
    ~BscanDisplay();

    bool set_current_beam(unsigned int index);
    bool set_scan_type(E_SCAN_TYPE type);

protected slots:
    void do_data_event();
    void update_scan_type_ruler(const QSize &size);
    virtual void update_scan_type_ruler();
    void update_sound_path_ruler();
    void do_timer_time_outed();

protected:
    Ui::BscanDisplay *ui;
    DplDevice::GroupPointer m_group;
    RulerWidget      *m_scanTypeRuler;
    RulerWidget      *m_soundPathRuler;
    ScanView         *m_bscanView;
    double           m_pixPerBeam;  /* 每条beam用多少个像素表示 */
    double           m_scanTypeRulerStart;
    double           m_scanTypeRulerEnd;
    BscanScene       *m_bscanScene;
    E_SCAN_TYPE      m_type;
    int              m_currentBeamIndex;
    QTimer           *m_timer;
    double           m_currentTimeCount;    /* 秒 */
    QLabel           *m_timeShowLabel;

    virtual void init_ruler();

};

#endif // __B_SCAN_DISPLAY_H_
