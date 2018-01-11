#ifndef __CURSORS_MENU_H__
#define __CURSORS_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

class AmpRefMenuItem;
class AmpMeasMenuItem;
class UtRefMenuItem;
class UtMeasMenuItem;
class VpaMenuItem;

namespace DplMeasurementMenu {

class CursorsMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit CursorsMenu(QWidget *parent);

protected:
    void show_a_scan();
    void show_b_scan();
    void show_c_scan();
    void show_s_scan();

    void changeEvent(QEvent *e);

protected slots:
    void update_srItem();
    void update_smItem();
    void update_irItem();
    void update_imItem();

private slots:
    void update(const DplDevice::GroupPointer &grp);
    void do_selectionItem_changed(int index);
    void do_srItem_changed(double val);
    void do_smItem_changed(double val);
    void do_irItem_changed(double val);
    void do_imItem_changed(double val);

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

    AmpRefMenuItem *m_afItem;
    AmpMeasMenuItem *m_amItem;

    UtRefMenuItem *m_urItem;
    UtMeasMenuItem *m_umItem;

    SpinMenuItem *m_srItem;     /* S(r) */
    SpinMenuItem *m_smItem;     /* S(m) */

    SpinMenuItem *m_irItem;     /* I(r) */
    SpinMenuItem *m_imItem;     /* I(m) */

    VpaMenuItem *m_vpaItem;

    DplDevice::GroupPointer m_group;
    DplMeasure::CursorPointer m_cursor;
};

}
#endif // __CURSORS_MENU_H__
