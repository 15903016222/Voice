#ifndef __FLAW_RECORD_MENU_H__
#define __FLAW_RECORD_MENU_H__

#include "base_menu.h"

namespace DplMeasurementMenu {

class FlawRecordMenu : public BaseMenu
{
    Q_OBJECT
public:
    FlawRecordMenu(Ui::BaseMenu *ui, QObject *parent);

private slots:
    void do_comment_clicked();
};

}
#endif // __FLAW_RECORD_MENU_H__
