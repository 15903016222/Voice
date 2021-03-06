#ifndef __FILE_MENU_H__
#define __FILE_MENU_H__

#include "base_menu.h"

namespace DplFileReportMenu {

class FileMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FileMenu(Ui::BaseMenu *ui, QObject *parent);
    ~FileMenu();

    void show();
    void hide();

private:
    MenuItem *m_saveSetupItem;
    MenuItem *m_openItem;
    MenuItem *m_fileManagerItem;

private slots:
    void do_fileManagerItem_clicked();
};

}
#endif // __FILE_MENU_H__
