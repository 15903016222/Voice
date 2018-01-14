#ifndef __CURSORS_MENU_H__
#define __CURSORS_MENU_H__

#include "../base_menu.h"
#include <device/device.h>

class AmpRefMenuItem;
class AmpMeasMenuItem;
class UtRefMenuItem;
class UtMeasMenuItem;
class ScanRefMenuItem;
class ScanMeasMenuItem;
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
    void update_irItem();
    void update_imItem();

private slots:
    void update(const DplDevice::GroupPointer &grp);
    void do_selectionItem_changed(int index);
    void do_irItem_changed(double val);
    void do_imItem_changed(double val);

private:
    ComboMenuItem *m_selectionItem;

    AmpRefMenuItem *m_afItem;
    AmpMeasMenuItem *m_amItem;

    UtRefMenuItem *m_urItem;
    UtMeasMenuItem *m_umItem;

    ScanRefMenuItem *m_srItem;
    ScanMeasMenuItem *m_smItem;

    SpinMenuItem *m_irItem;     /* I(r) */
    SpinMenuItem *m_imItem;     /* I(m) */

    VpaMenuItem *m_vpaItem;

    DplDevice::GroupPointer m_group;
    DplMeasure::CursorPointer m_cursor;
};

}
#endif // __CURSORS_MENU_H__
