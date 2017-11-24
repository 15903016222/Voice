#ifndef __CURSORS_MENU_H__
#define __CURSORS_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

namespace DplMeasurementMenu {

class CursorsMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit CursorsMenu(QWidget *parent);

protected:
    void show_scan();

    void show_a_scan();
    void hide_a_scan();

    void show_b_scan();
    void hide_b_scan();

    void show_c_scan();
    void hide_c_scan();

    void show_s_scan();
    void hide_s_scan();

protected slots:
    void update_srItem();
    void update_smItem();
    void update_urItem();
    void update_umItem();
    void update_irItem();
    void update_imItem();
    void update_beamItem();

private slots:
    void update(const DplDevice::GroupPointer &grp);
    void do_selectionItem_changed(int index);
    void do_rItem_changed(double val);
    void do_mItem_changed(double val);
    void do_srItem_changed(double val);
    void do_smItem_changed(double val);
    void do_urItem_changed(double val);
    void do_umItem_changed(double val);
    void do_irItem_changed(double val);
    void do_imItem_changed(double val);
    void do_angleItem_changed(double val);

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

private:
    ComboMenuItem *m_selectionItem;

    SpinMenuItem *m_rItem;      /* %(r) */
    SpinMenuItem *m_mItem;      /* %(m) */

    SpinMenuItem *m_urItem;     /* U(r) */
    SpinMenuItem *m_umItem;     /* U(m) */

    SpinMenuItem *m_srItem;     /* S(r) */
    SpinMenuItem *m_smItem;     /* S(m) */

    SpinMenuItem *m_irItem;     /* I(r) */
    SpinMenuItem *m_imItem;     /* I(m) */

    SpinMenuItem *m_angelItem;

    DplDevice::GroupPointer m_group;
    DplMeasure::CursorPointer m_cursor;
};

}
#endif // __CURSORS_MENU_H__
