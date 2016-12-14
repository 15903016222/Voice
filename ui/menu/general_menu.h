/**
 * @file general_menu.h
 * @brief Ut Setting General Menu Bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-14
 */
#ifndef __GENERAL_MENU_H__
#define __GENERAL_MENU_H__

#include "base_menu.h"

class GeneralMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit GeneralMenu(Ui::SubMenu *ui, QObject *parent = 0);
    void show();
    void hide();

signals:

public slots:

private:

    QStringList m_utUnit;

    void gain_item();
    void start_item();
    void range_item();
    void velocity_item();
    void wedge_item();
    void ut_unit_item();
};

#endif // GENERALMENU_H
