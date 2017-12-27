/**
 * @file network_menu.h
 * @brief network menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#ifndef __NETWORK_MENU_H__
#define __NETWORK_MENU_H__

#include "../base_menu.h"

namespace DplPreferenceMenu {

class NetworkManager;

class NetworkMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit NetworkMenu(QWidget *parent);
    ~NetworkMenu();

    void show();
    void hide();

private:
    LabelMenuItem *m_ipItem;
    LabelMenuItem *m_maskItem;

private slots:
    void show_ip_address_dialog();
    void show_subnet_mask_dialog();

protected:
    void changeEvent(QEvent *event);

private:
    NetworkManager  *m_networkManager;
    void retranslate_ui();
};

}
#endif // __NETWORK_MENU_H__
