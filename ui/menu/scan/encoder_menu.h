#ifndef __ENCODER_MENU_H__
#define __ENCODER_MENU_H__

#include "base_menu.h"
namespace DplScanMenu {

class EncoderMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit EncoderMenu(Ui::BaseMenu *ui, QObject *parent);
    ~EncoderMenu();

    void show();
    void hide();

private:
    ComboMenuItem *m_encoderItem;
    ComboMenuItem *m_encoderTypeItem;
    SpinMenuItem *m_resolutionItem;
    ComboMenuItem *m_polarityItem;
    SpinMenuItem *m_originItem;
    MenuItem *m_presetItem;
};

}
#endif // __ENCODER_MENU_H__
