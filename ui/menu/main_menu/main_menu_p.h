#ifndef __MAIN_MENU_P_H__
#define __MAIN_MENU_P_H__

#include "main_menu.h"
#include <QListWidget>
#include <QSpacerItem>

class MainMenuPrivate : public QObject
{
    Q_OBJECT
public:
    MainMenuPrivate(MainMenu *parent);

    /* attribution */
    QListWidget *m_mainMenu;
    QListWidget *m_utSettingMenu;
    QListWidget *m_gateCurvesMenu;
    QListWidget *m_displayMenu;
    QListWidget *m_probePartMenu;
    QListWidget *m_focallawMenu;
    QListWidget *m_scanMenu;
    QListWidget *m_measureMenu;
    QListWidget *m_fileReportMenu;
    QListWidget *m_preferenceMenu;
    QListWidget *m_curSubMenu;
    QSpacerItem *m_topSpaceItem;
    QSpacerItem *m_bottomSpaceItem;

public slots:
    void do_subMenu_itemClicked();

protected slots:
    void do_currentRowChanged(int row);

protected:
    void init_menu();
    void init_mainMenu();
    void init_utSettingMenu();
    void init_gateCurevesMenu();
    void init_displayMenu();
    void init_probePartMenu();
    void init_focallawMenu();
    void init_scanMenu();
    void init_measureMenu();
    void init_fileReportMenu();
    void init_preferenceMenu();
};
#endif // __MAIN_MENU_P_H__
