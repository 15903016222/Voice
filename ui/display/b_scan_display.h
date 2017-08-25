#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include <QWidget>
#include <ui/display/b_scan_scene.h>
#include <device/device.h>

class ScanView;
class BWaveItem;
class ScrollRulerWidget;
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
    virtual bool set_scan_type(E_SCAN_TYPE type);

signals:
    void update_ruler();
    void update_label(const QString &time);

protected slots:

    void do_data_event(const DplSource::BeamsPointer &beams);
    void do_update_ruler();

    void update_scan_type_ruler(const QSize &size);
    virtual void update_scan_type_ruler();
    void update_sound_path_ruler();

    void do_update_label(const QString &time);

protected:
    Ui::BscanDisplay *ui;

    DplDevice::GroupPointer m_group;
    ScrollRulerWidget      *m_scanTypeRuler;
    ScrollRulerWidget      *m_soundPathRuler;

    ScanView         *m_bscanView;
    BscanScene       *m_bscanScene;

    double           m_pixPerBeam;          /* 每条beam用多少个像素表示 */
    double           m_scanTypeRulerStart;  /* 标尺开始（mm / s） */
    double           m_scanTypeRulerEnd;    /* 标尺结束（mm / s） */

    E_SCAN_TYPE      m_type;                /* 扫查类型：encoder / time */
    int              m_currentBeamIndex;    /* 当前beam的index */

    double           m_currentTimeCount;    /* 秒 */
    QLabel           *m_timeShowLabel;

    virtual void init_ruler();

};

#endif // __B_SCAN_DISPLAY_H_
