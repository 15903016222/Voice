#ifndef __RECEIVER_MENU_H__
#define __RECEIVER_MENU_H__

#include "base_menu.h"

class ReceiverMenu : public BaseMenu
{
    Q_OBJECT
public:
    explicit ReceiverMenu(Ui::SubMenu *ui, QObject *parent = 0);
    void show();
    void hide();

signals:

public slots:

private:
    LabelMenuItem *m_receiverItem;


    QStringList m_filters;
    QStringList m_rectifiers;
    QStringList m_averagings;

    void receiver_item();
    void filter_item();
    void rectifier_item();
    void video_filter_item();
    void averagin_item();
};

#endif // __RECEIVER_MENU_H__
