#ifndef __FILE_MENU_H__
#define __FILE_MENU_H__

#include "../base_menu.h"

namespace DplFileReportMenu {

class SaveFileManager;

class FileMenu : public BaseMenu
{
    Q_OBJECT
public:

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

    SaveFileManager *m_saveFileManager;
    QStringList    m_saveModeNameList;

private slots:
    void do_openItem_clicked();
    void do_saveModeItem_value_changed(int index);
    void do_saveDataItem_clicked();
    void do_fileNameItem_clicked();
    void do_fileManagerItem_clicked();

protected:
    void changeEvent(QEvent *e);

};

}
#endif // __FILE_MENU_H__
