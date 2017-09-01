#ifndef __ENCODER_MENU_H__
#define __ENCODER_MENU_H__

#include "../base_menu.h"
#include <source/scan.h>

namespace DplScanMenu {

class EncoderMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit EncoderMenu(QWidget *parent);
    ~EncoderMenu();

protected slots:
    void do_encoderItem_changed(int pos);
    void do_encoderTypeItem_changed(int pos);
    void do_resolutionItem_changed(double val);
    void do_polarityItem_changed(int pos);
    void do_originItem_changed(double val);

private:
    ComboMenuItem *m_encoderItem;
    ComboMenuItem *m_encoderTypeItem;
    SpinMenuItem *m_resolutionItem;
    ComboMenuItem *m_polarityItem;
    SpinMenuItem *m_originItem;
    LabelMenuItem *m_presetItem;

    DplSource::EncoderPointer m_enc;
};

}
#endif // __ENCODER_MENU_H__
