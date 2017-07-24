#ifndef __ENCODER_MENU_H__
#define __ENCODER_MENU_H__

#include "../base_menu.h"
namespace DplScanMenu {

class EncoderMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit EncoderMenu(QWidget *parent);
    ~EncoderMenu();

private:
    ComboMenuItem *m_encoderItem;
    ComboMenuItem *m_encoderTypeItem;
    SpinMenuItem *m_resolutionItem;
    ComboMenuItem *m_polarityItem;
    SpinMenuItem *m_originItem;
    LabelMenuItem *m_presetItem;
};

}
#endif // __ENCODER_MENU_H__
