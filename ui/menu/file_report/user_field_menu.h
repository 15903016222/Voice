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
    ComboMenuItem m_selectItem;
    ComboMenuItem m_enableItem;
    LabelMenuItem m_labelItem;
    LabelMenuItem m_contentItem;
    LabelMenuItem m_editNoteItem;
    LabelMenuItem m_printItem;

private slots:
    void show_input_dialog();
};

}
#endif // __USER_FIELD_MENU_H__
