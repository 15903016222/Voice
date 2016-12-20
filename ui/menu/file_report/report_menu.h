#ifndef __REPORT_MENU_H__
#define __REPORT_MENU_H__

#include "base_menu.h"

namespace DplFileReportMenu {

class ReportMenu : public BaseMenu
{
public:
    explicit ReportMenu(Ui::BaseMenu *ui, QObject *parent);
    ~ReportMenu();

    void show();
    void hide();

private:
    MenuItem *m_templateItem;
    MenuItem *m_reportNameItem;
    MenuItem *m_customerItem;
    MenuItem *m_partNameItem;
    MenuItem *m_partNumberItem;
    MenuItem *m_createItem;
};

}
#endif // __REPORT_MENU_H__
