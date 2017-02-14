#ifndef __FLAW_RECORD_MENU_H__
#define __FLAW_RECORD_MENU_H__

#include "base_menu.h"

namespace DplMeasurementMenu {

class FlawRecordMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit FlawRecordMenu(Ui::BaseMenu *ui, QObject *parent);
    ~FlawRecordMenu();

    void show();
    void hide();

private slots:
    void do_comment_clicked();

private:
    LabelMenuItem *m_addDeleteItem;
    ComboMenuItem *m_flawImageItem;
    LabelMenuItem *m_commentItem;
    ComboMenuItem *m_displayTableItem;
    LabelMenuItem *m_exportRecordItem;
};

}
#endif // __FLAW_RECORD_MENU_H__
