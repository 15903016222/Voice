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

    ComboMenuItem *m_scanItem;

    ComboMenuItem *m_colorItem;
    ComboMenuItem *m_envelopItem;
    ComboMenuItem *m_peakHoldingItem;
    ComboMenuItem *m_referenceholdingItem;

    ComboMenuItem *m_compressionItem;
    ComboMenuItem *m_ratioItem;
    ComboMenuItem *m_cScanModeItem;

    void show_a_scan();
    void show_b_scan();
    void show_c_scan();

private slots:
    void do_mode_changed(int i);
};

}
#endif // __PROPERTIES_MENU_H__
