#ifndef __FORMAT_MENU_H__
#define __FORMAT_MENU_H__

#include "../base_menu.h"

namespace DplFileReportMenu {

class FormatMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FormatMenu(QWidget *parent);
    ~FormatMenu();

private:
    ComboMenuItem *m_probeWedgeItem;
    ComboMenuItem *m_inspectionInfoItem;
    ComboMenuItem *m_scanInfoItem;
    ComboMenuItem *m_encoderInfoItem;
    ComboMenuItem *m_dacTcgInfoItem;
    ComboMenuItem *m_flawRecordTableItem;

protected:
    void changeEvent(QEvent *event);
};

}
#endif // FORMATMENU_H
