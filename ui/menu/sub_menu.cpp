#include "sub_menu.h"
#include "ui_sub_menu.h"

#include <QKeyEvent>
#include <QDebug>

SubMenu::SubMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubMenu)
{
    ui->setupUi(this);
    menuConfig = new MenuConfig;

//    ui->subMenu_1->installEventFilter(this);
    current.insert("UT Settings", "General");
    qDebug() << current;

    set_third_menu_and_connect("UT Settings", "General");

}

SubMenu::~SubMenu()
{
    delete ui;
}

void SubMenu::set_third_menu(QString str1, QString str2)
{
    QString str1_c = current.keys().at(0);
    QString str2_c = current.values().at(0);

    if(str1 != str1_c || str2 != str2_c) {
        disconnect_previous_signals(str1_c, str2_c);
        get_second_menu_string(str1, str2);
        set_third_menu_and_connect(str1, str2);
    }

}

void SubMenu::set_third_menu_and_connect(QString str1, QString str2)
{
    QStringList thirdMenuList = menuConfig->get_third_menu_list(menuConfig->menuMap, str1, str2);

    for(int i = 0; i < 6; i ++) {
        MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
        widget->clean();

        if(i < thirdMenuList.count()) {
            QString str = thirdMenuList.at(i);
            QVariantMap map = menuConfig->get_third_menu_map(menuConfig->menuMap, str1, str2, str);

            widget->set_title(str);
            if(menuConfig->get_style(map) == 1) {
                widget->set_type(MenuItem::Spin);
                widget->set_unit(menuConfig->get_spinBox_unit(map));
                widget->set_steps(menuConfig->get_spinBox_step_list(map));
                widget->set_decimals(menuConfig->get_spinBox_decimal(map));
                QList<double> rangeList = menuConfig->get_spinBox_range_list(map);
                widget->set_range(rangeList.at(0), rangeList.at(1));

//                connect(widget, SIGNAL(spin_event(double)), , SLOT());
            } else if(menuConfig->get_style(map) == 2) {
                widget->set_type(MenuItem::Combo);
                widget->set_combo_items(menuConfig->get_comboBox_option_list(map));

//                connect(widget, SIGNAL(combo_event(double)), , SLOT());
            } else {
                widget->set_type(MenuItem::Combo);
            }
        } else {
            widget->set_type(MenuItem::Combo);
        }
    }
}

bool SubMenu::eventFilter(QObject *object, QEvent *event)
{
//    if(event->type() == QEvent::KeyPress) {
//        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

//        switch (keyEvent->key()) {
//        case Qt::Key_Alt:
//            if(this->isHidden()) {
//                this->show();
//            } else {
//               this->hide();
//            }

//            return true;
//            break;
//        default:
//            break;
//        }
//    }
//    return QWidget::eventFilter(object, event);
}

void SubMenu::disconnect_previous_signals(QString str1, QString str2)
{
    if(!current.isEmpty()) {
        QStringList list = menuConfig->get_third_menu_list(menuConfig->menuMap, str1, str2);
        for(int i = 0; i < list.count(); i ++) {
//            MenuItem *widget = findChild<MenuItem*>("subMenu_" + QString::number(i + 1));
            QString str3 = list.at(i);
            QVariantMap map = menuConfig->get_third_menu_map(menuConfig->menuMap, str1, str2, str3);

            if(menuConfig->get_style(map) == 1) {
                qDebug() << "disconnect";
//                disconnect(widget, SIGNAL(spin_event(double)), , SLOT());
            } else if(menuConfig->get_style(map) == 2) {
//                disconnect(widget, SIGNAL(combo_event(int)), , SLOT());
                qDebug() << "disconnect";
            }
        }
    }
}

void SubMenu::get_second_menu_string(QString str1, QString str2)
{
    qDebug() << "str1" << str1 << "str2" << str2;
    if(!previous.isEmpty()) {
        previous.clear();
    }
    previous.insert(current.keys().at(0), current.values().at(0));
    current.clear();
    current.insert(str1, str2);
}
