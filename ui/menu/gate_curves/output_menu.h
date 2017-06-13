/**
 * @file output_menu.h
 * @brief Gate/Curves ouput menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#ifndef __OUTPUT_MENU_H__
#define __OUTPUT_MENU_H__

#include "base_menu.h"

namespace DplGateCurvesMenu {

class OutputMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit OutputMenu(Ui::BaseMenu *ui, QObject *parent);
    ~OutputMenu();

    void show();
    void hide();

private:
    ComboMenuItem m_outputItem;
    ComboMenuItem m_soundItem;
    SpinMenuItem m_delayItem;
    SpinMenuItem m_holdTimeItem;
    LabelMenuItem m_groupItem;
    ComboMenuItem m_dataItem;
};

}
#endif // __OUTPUT_MENU_H__
