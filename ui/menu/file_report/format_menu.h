#ifndef __FORMAT_MENU_H__
#define __FORMAT_MENU_H__

#include "base_menu.h"

namespace DplFileReportMenu {

class FormatMenu : public BaseMenu
{
public:
    explicit FormatMenu(Ui::BaseMenu *ui, QObject *parent);
    ~FormatMenu();

    void show();
    void hide();

private:
    ComboMenuItem *m_probeWedgeItem;
    ComboMenuItem *m_inspectionInfoItem;
    ComboMenuItem *m_scanInfoItem;
    ComboMenuItem *m_encoderInfoItem;
    ComboMenuItem *m_dacTcgInfoItem;
    ComboMenuItem *m_flawRecordTableItem;

};

}
#endif // FORMATMENU_H
