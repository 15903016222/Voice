#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include <QWidget>
#include <ui/display/base_image_item.h>
#include <device/device.h>
#include <QSemaphore>

class ScanView;
class BscanScene;
class ScrollRulerWidget;
class QLabel;
class BaseCursorItem;

namespace Ui {
class BscanDisplay;
}

class BscanDisplay : public QWidget
{
    Q_OBJECT

public:
    explicit BscanDisplay(const DplDevice::GroupPointer &grp, Qt::Orientation orientation, QWidget *parent = 0);
    ~BscanDisplay();

signals:
    void update_ruler(double value);
    void update_label(const QString &time);
    void refresh_scan_env();

protected slots:

    void do_data_event(const DplSource::BeamsPointer &beams);
    void update_sound_path_ruler();

    void do_view_size_changed(const QSize &size);
    void do_refresh_scan_env();
    void do_update_ruler(double x);

    void do_update_all_item();

protected:
    Ui::BscanDisplay *ui;

    DplDevice::GroupPointer m_group;
    ScrollRulerWidget      *m_scanTypeRuler;
    ScrollRulerWidget      *m_soundPathRuler;

    ScanView         *m_bscanView;
    BscanScene       *m_bscanScene;

    BaseImageItem    *m_bscanImageItem;
    BaseCursorItem   *m_sReferneceCursorItem;
    BaseCursorItem   *m_sMeasurementCursorItem;
    BaseCursorItem   *m_uReferneceCursorItem;
    BaseCursorItem   *m_uMeasurementCursorItem;
    DplSource::BeamsPointer m_beamsPointer;

    DplSource::Axis::Driving      m_driving;                /* 扫查类型：encoder_x/y / timer*/

    Qt::Orientation  m_orientation;
    QSemaphore       m_refreshSemaphore;    /* 切换时间扫查或编码器扫查时，刷新信号量 */

    DplSource::AxisPointer      m_axisPointer;
    DplSource::EncoderPointer   m_encoderPointer;

    void init_cursor();
    void init_ruler();
    void update_scan_type_ruler(const QSize &size);
    void wait_for_refresh_finished();
    void init_scan_env();

    void draw_timer_beams(const DplSource::BeamsPointer &beams);
    void draw_encoder_beams(const DplSource::BeamsPointer &beams);
};

#endif // __B_SCAN_DISPLAY_H_
