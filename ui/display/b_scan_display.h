#ifndef __B_SCAN_DISPLAY_H_
#define __B_SCAN_DISPLAY_H_

#include <QWidget>
#include <QSemaphore>

#include <ui/display/base_image_item.h>
#include <ui/display/base_cursor_item.h>
#include <device/device.h>
#include <mcu/mcu.h>


class ScanView;
class BWaveItem;
class ScrollRulerWidget;
class QLabel;
class BaseCursorItem;
class BscanScene;

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
    void cursor_visible_changed(bool flag);

protected slots:

    void do_data_event(const DplSource::BeamsPointer &beams);
    void update_sound_path_ruler();

    void do_view_size_changed(const QSize &size);
    void do_refresh_scan_env();
    void do_update_ruler(double x);

    void do_mcu_key_event(Mcu::KeyType type);
    void do_cursor_visible_changed(bool flag);

    /**
     * @brief do_ultrasound_reference_changed 处理引用光标在超声轴位置变化
     * @param value         位置值（ns）
     */
    void do_ultrasound_reference_changed(double value);

    /**
     * @brief do_ultrasound_measurement_changed 处理测量光标在超声轴位置变化
     * @param value         位置值（ns）
     */
    void do_ultrasound_measurement_changed(double value);

    /**
     * @brief do_scan_reference_changed 处理引用光标在扫查轴位置变化
     * @param value         位置（mm）
     */
    void do_scan_reference_changed(double value);

    /**
     * @brief do_scan_measurement_changed   处理测量光标在扫擦轴位置变化
     * @param value     位置（mm）
     */
    void do_scan_measurement_changed(double value);

    /**
     * @brief do_value_changed  处理光标拖动后，数值变化处理
     * @param value             变化后的数值
     */
    void do_value_changed(double value);

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

    volatile bool m_cursorVisible;

    DplMeasure::CursorPointer   m_cursorPointer;

    void init_cursor();
    void init_cursor_connection();
    void init_ruler();
    void update_scan_type_ruler(const QSize &size);
    void wait_for_refresh_finished();
    void init_scan_env();

    void draw_timer_beams(const DplSource::BeamsPointer &beams);
    void draw_encoder_beams(const DplSource::BeamsPointer &beams);

    void cal_cursor_info(double value, BaseCursorItem::S_CURSOR_INFO &cursorInfo);
    void update_cursor_info();
};

#endif // __B_SCAN_DISPLAY_H_
