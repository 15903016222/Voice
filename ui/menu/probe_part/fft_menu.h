#ifndef __FFT_MENU_H__
#define __FFT_MENU_H__

#include "base_menu.h"

namespace DplProbeMenu {

class FftMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FftMenu(Ui::BaseMenu *ui, QObject *parent);
    ~FftMenu();

    void show();
    void hide();

private:
    SpinMenuItem *m_gainItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_widthItem;
    ComboMenuItem *m_switchItem;
};

}
#endif // __FFT_MENU_H__
