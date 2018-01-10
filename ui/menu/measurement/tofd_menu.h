#ifndef __TOFD_MENU_H__
#define __TOFD_MENU_H__

#include "../base_menu.h"

namespace DplMeasurementMenu {

class TofdMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit TofdMenu(QWidget *parent);
    ~TofdMenu();

private:
    ComboMenuItem *m_selectItem;

    SpinMenuItem *m_wedgeItem;
    LabelMenuItem *m_layerDepthItem;
    LabelMenuItem *m_tofdCalItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_rangeItem;

    ComboMenuItem *m_straighteningItem;
    ComboMenuItem *m_removeLateralItem;
    SpinMenuItem *m_refPositionItem;
    ComboMenuItem *m_depthCalibrationItem;
private slots:
    void do_selectItem_changed(int index);
protected:
    void changeEvent(QEvent *e);
};

}
#endif // __TOFD_MENU_H__
