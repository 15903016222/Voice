#ifndef __FILE_MENU_H__
#define __FILE_MENU_H__

#include "../base_menu.h"

namespace DplFileReportMenu {

class FileMenu : public BaseMenu
{
    Q_OBJECT
public:
    enum E_Storage_Type {
        SD,
        SSD,
        U
    };

    explicit FileMenu(QWidget *parent);
    ~FileMenu();

    void show();
    void hide();

private:
    LabelMenuItem *m_openItem;
    ComboMenuItem *m_storageItem;
    ComboMenuItem *m_saveModeItem;
    LabelMenuItem *m_saveDataItem;
    LabelMenuItem *m_fileNameItem;
    LabelMenuItem *m_fileManagerItem;

private slots:

    void show_input_dialog();
    void do_fileManagerItem_clicked();
    void do_saveModeItem_value_changed(int index);
    void do_saveDataItem_clicked();

};

}
#endif // __FILE_MENU_H__
