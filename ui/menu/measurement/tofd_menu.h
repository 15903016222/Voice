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
    ComboMenuItem *m_selectItem;

    MenuItem *m_wedgeItem;
    MenuItem *m_layerDepthItem;
    MenuItem *m_tofdCalItem;
    MenuItem *m_startItem;
    MenuItem *m_rangeItem;

    ComboMenuItem *m_straighteningItem;
    ComboMenuItem *m_removeLateralItem;
    MenuItem *m_refPositionItem;
    ComboMenuItem *m_depthCalibrationItem;

    void show_setting();
    void hide_setting();

    void show_analysis();
    void hide_analysis();


private slots:
    void do_select_changed(int index);
};

}
#endif // __TOFD_MENU_H__
