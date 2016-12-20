#ifndef __PROPERTIES_MENU_H__
#define __PROPERTIES_MENU_H__

#include "base_menu.h"

namespace DplDisplayMenu {

class PropertiesMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit PropertiesMenu(Ui::BaseMenu *ui, QObject *parent);
    ~PropertiesMenu();

    void show();
    void hide();

private:

    MenuItem *m_scanItem;

    MenuItem *m_colorItem;
    MenuItem *m_envelopItem;
    MenuItem *m_peakHoldingItem;
    MenuItem *m_referenceholdingItem;

    MenuItem *m_compressionItem;
    MenuItem *m_ratioItem;
    MenuItem *m_cScanModeItem;

    void show_a_scan();
    void show_b_scan();
    void show_c_scan();

private slots:
    void do_mode_changed(int i);
};

}
#endif // __PROPERTIES_MENU_H__
