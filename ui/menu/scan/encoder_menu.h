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
    MenuItem *m_encoderItem;
    MenuItem *m_encoderTypeItem;
    MenuItem *m_resolutionItem;
    MenuItem *m_polarityItem;
    MenuItem *m_originItem;
    MenuItem *m_presetItem;
};

}
#endif // __ENCODER_MENU_H__
