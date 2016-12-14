#include "base_menu.h"

QList<double> BaseMenu::s_steps1;
QList<double> BaseMenu::s_steps2;

BaseMenu::BaseMenu(QObject *parent)
    :QObject(parent)
{
    if (s_steps1.isEmpty()) {
        s_steps1.append(0.1);
        s_steps1.append(0.5);
        s_steps1.append(1.0);
        s_steps1.append(2.0);
        s_steps1.append(5.0);
    }

    if (s_steps2.isEmpty()) {
        s_steps2.append(0.01);
        s_steps2.append(0.1);
        s_steps2.append(1.00);
        s_steps2.append(10.0);
        s_steps2.append(100.0);
    }
}
