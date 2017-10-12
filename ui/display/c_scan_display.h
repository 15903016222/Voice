#ifndef __C_SCAN_DISPLAY_H__
#define __C_SCAN_DISPLAY_H__

#include <QWidget>
#include <device/group.h>
#include <QSemaphore>

namespace Ui {
class ScanDisplay;
}

class ScanView;
class BaseScanScene;
class ScrollRulerWidget;

class CscanDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit CscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent = 0);
    ~CscanDisplay();

signals:
    void refresh_scan_env();
    void update_ruler(double value);

public slots:
    void do_data_event(const DplSource::BeamsPointer &beams);
    void do_refresh_scan_env();
    void do_view_size_changed(const QSize &size);
    void do_update_ruler(double value);

protected:
    Ui::ScanDisplay         *ui;
    DplDevice::GroupPointer m_group;
    ScanView                *m_view;
    BaseScanScene           *m_scene;

    Qt::Orientation     m_orientation;
    ScrollRulerWidget   *m_scanTypeRuler;       /* 时间扫查（s）/编码器扫擦（mm） */
    ScrollRulerWidget   *m_lawTypeRuler;    /* 一维扫查：该标尺为度数（扫查类型：扇扫）或阵元数（扫查方式：线性）；
                                             二维扫查，该标尺为步进轴 */

    QSemaphore             m_refreshSemaphore;

    DplFocallaw::ScanCnf::Mode      m_focallawMode;
    DplFocallaw::ScanCnfPointer     m_scanCnfPointer;


    virtual void init_ruler();
    void update_scan_type_ruler(const QSize &size);
    void update_law_type_ruler();
    void wait_for_refresh_finished();
    void init_scan_env();
    bool focallaw_mode_changed();
    void draw_timer_beams(const DplSource::BeamsPointer &beams);
    void draw_encoder_beams(const DplSource::BeamsPointer &beams);



};

#endif // __C_SCAN_DISPLAY_H__
