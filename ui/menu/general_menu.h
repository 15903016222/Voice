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
    ~GeneralMenu();

    void show();
    void hide();

signals:

public slots:

private:
    SpinMenuItem *m_gainItem;
    SpinMenuItem *m_startItem;
    SpinMenuItem *m_rangeItem;
    SpinMenuItem *m_velocityItem;
    SpinMenuItem *m_wedgeItem;
    ComboMenuItem *m_utUnitItem;

    QStringList m_utUnit;

};

#endif // GENERALMENU_H
