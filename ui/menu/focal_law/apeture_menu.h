#ifndef __APETURE_MENU_H__
#define __APETURE_MENU_H__

#include "../base_menu.h"

namespace DplFocalLawMenu {

class ApetureMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ApetureMenu(QWidget *parent);
    ~ApetureMenu();

    void show();
    void hide();

private:
    SpinMenuItem *m_apetureItem;
    SpinMenuItem *m_firstElementItem;
    SpinMenuItem *m_lastElementItem;
    SpinMenuItem *m_elementStep;
};

}
#endif // __APETURE_MENU_H__
