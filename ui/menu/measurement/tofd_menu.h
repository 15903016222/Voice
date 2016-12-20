#ifndef __TOFD_MENU_H__
#define __TOFD_MENU_H__

#include "base_menu.h"

namespace DplMeasurementMenu {

class TofdMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit TofdMenu(Ui::BaseMenu *ui, QObject *parent);
    ~TofdMenu();

    void show();
    void hide();

private:
    MenuItem *m_straighteningItem;
    MenuItem *m_removeLateralItem;
    MenuItem *m_refPositionItem;
    MenuItem *m_depthCalibrationItem;

    void show_analysis();
    void hide_analysis();

private slots:
    void do_select_changed(int index);
};

}
#endif // __TOFD_MENU_H__
