#ifndef __ENCODER_MENU_H__
#define __ENCODER_MENU_H__

#include "base_menu.h"
namespace DplScanMenu {

class EncoderMenu : public BaseMenu
{
public:
    EncoderMenu(Ui::BaseMenu *ui, QObject *parent);
};

}
#endif // __ENCODER_MENU_H__
