#ifndef __USER_FIELD_MENU_H__
#define __USER_FIELD_MENU_H__

#include "base_menu.h"

namespace DplFileReportMenu {

class UserFieldMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit UserFieldMenu(Ui::BaseMenu *ui, QObject *parent = 0);
    ~UserFieldMenu();

    void show();
    void hide();

signals:

public slots:

private:
    MenuItem *m_selectItem;
    MenuItem *m_enableItem;
    MenuItem *m_labelItem;
    MenuItem *m_contentItem;
    MenuItem *m_editNoteItem;
    MenuItem *m_printItem;
};

}
#endif // __USER_FIELD_MENU_H__
