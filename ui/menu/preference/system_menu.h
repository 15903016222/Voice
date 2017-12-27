/**
 * @file system_menu.h
 * @brief system menu bar
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-21
 */
#ifndef __SYSTEM_MENU_H__
#define __SYSTEM_MENU_H__

#include"../base_menu.h"
#include <QTimer>
#include <QDateTime>

namespace DplPreferenceMenu {

class SystemMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit SystemMenu(QWidget *parent);
    ~SystemMenu();

    void show();
    void hide();

private:
    LabelMenuItem *m_dateItem;
    LabelMenuItem *m_timeItem;
    LabelMenuItem *m_certItem;
    LabelMenuItem *m_updateItem;
    LabelMenuItem *m_resetCfgItem;
    LabelMenuItem *m_infoItem;

private slots:
    void show_time_dialog();
    void show_date_dialog();
    void show_cert_import_dialog();
    void show_update_dialog();
    void show_resetconfig_dialog();
    void show_info_dialog();
    void do_time_out();

private:
    QTimer  *m_timer;
    bool set_date_time(const QDateTime &dateTime);
    void init_date_time();
    void retranslate_ui();

protected:
    void changeEvent(QEvent *event);
};

}
#endif // __SYSTEM_MENU_H__
