#ifndef __PROPERTIES_MENU_H__
#define __PROPERTIES_MENU_H__

#include "base_menu.h"

namespace DplDisplayMenu {

class PropertiesMenu : public BaseMenu
{
    Q_OBJECT
public:
    PropertiesMenu(Ui::BaseMenu *ui, QObject *parent);

    void show();
    void hide();

private:
    MenuItem *m_compressionItem;
    MenuItem *m_ratioItem;
    MenuItem *m_cScanModeItem;

private slots:
    void do_mode_changed(int i);
};

}
#endif // __PROPERTIES_MENU_H__
