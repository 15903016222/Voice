#ifndef __SAVE_MODE_MENU_H__
#define __SAVE_MODE_MENU_H__

#include "base_menu.h"

namespace DplFileReportMenu {

class SaveModeMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit SaveModeMenu(Ui::BaseMenu *ui, QObject *parent);
    ~SaveModeMenu();

    void show();
    void hide();

private:
    ComboMenuItem m_storageItem;
    ComboMenuItem m_saveModeItem;
    LabelMenuItem m_saveDataItem;
    LabelMenuItem m_fileNameItem;

private slots:
    void show_input_dialog();

};

}
#endif // __SAVE_MODE_MENU_H__
