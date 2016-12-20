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
    MenuItem *m_probeWedgeItem;
    MenuItem *m_inspectionInfoItem;
    MenuItem *m_scanInfoItem;
    MenuItem *m_encoderInfoItem;
    MenuItem *m_dacTcgInfoItem;
    MenuItem *m_flawRecordTableItem;

};

}
#endif // FORMATMENU_H
