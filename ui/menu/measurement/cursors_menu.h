#ifndef __CURSORS_MENU_H__
#define __CURSORS_MENU_H__

#include "../base_menu.h"

class AmpRefMenuItem;
class AmpMeasMenuItem;
class UtRefMenuItem;
class UtMeasMenuItem;
class ScanRefMenuItem;
class ScanMeasMenuItem;
class IndexRefMenuItem;
class IndexMeasMenuItem;
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

    void update_selectionItem();

    void changeEvent(QEvent *e);

private slots:
    void do_selectionItem_changed(int index);

private:
    ComboMenuItem *m_selectionItem;

    AmpRefMenuItem *m_afItem;
    AmpMeasMenuItem *m_amItem;

    UtRefMenuItem *m_urItem;
    UtMeasMenuItem *m_umItem;

    ScanRefMenuItem *m_srItem;
    ScanMeasMenuItem *m_smItem;

    IndexRefMenuItem *m_irItem;
    IndexMeasMenuItem *m_imItem;

    VpaMenuItem *m_vpaItem;
};

}
#endif // __CURSORS_MENU_H__
