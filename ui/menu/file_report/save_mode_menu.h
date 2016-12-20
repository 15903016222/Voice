#ifndef __SAVE_MODE_MENU_H__
#define __SAVE_MODE_MENU_H__

#include "base_menu.h"

namespace DplFileReportMenu {

class SaveModeMenu : public BaseMenu
{
public:
    explicit SaveModeMenu(Ui::BaseMenu *ui, QObject *parent);
    ~SaveModeMenu();

    void show();
    void hide();

private:
    MenuItem *m_storageItem;
    MenuItem *m_saveModeItem;
    MenuItem *m_saveDataItem;
    MenuItem *m_fileName;
};

}
#endif // __SAVE_MODE_MENU_H__
