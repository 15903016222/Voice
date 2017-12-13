#ifndef __FILE_MENU_H__
#define __FILE_MENU_H__

#include "../base_menu.h"

namespace DplFileReportMenu {

class FileMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FileMenu(QWidget *parent);
    ~FileMenu();

    void show();
    void hide();

private:
    LabelMenuItem *m_saveSetupItem;
    LabelMenuItem *m_openItem;
    LabelMenuItem *m_fileManagerItem;

    bool is_legal(const QString &name);

private slots:
    void do_saveSetupItem_clicked();
    void do_openItem_clicked();
    void do_fileManagerItem_clicked();
};

}
#endif // __FILE_MENU_H__
