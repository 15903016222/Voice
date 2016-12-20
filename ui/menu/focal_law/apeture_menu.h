#ifndef __APETURE_MENU_H__
#define __APETURE_MENU_H__

#include "base_menu.h"

namespace DplFocalLawMenu {

class ApetureMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ApetureMenu(Ui::BaseMenu *ui, QObject *parent);
    ~ApetureMenu();

    void show();
    void hide();

private:
    MenuItem *m_apetureItem;
    MenuItem *m_firstElementItem;
    MenuItem *m_lastElementItem;
    MenuItem *m_elementStep;
};

}
#endif // __APETURE_MENU_H__
