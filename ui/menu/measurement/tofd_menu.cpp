#include "tofd_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"

namespace DplMeasurementMenu {

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Spin,
    MenuItem::Label,
    MenuItem::Label,
    MenuItem::Spin,
    MenuItem::Spin
};

TofdMenu::TofdMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
{
    /* Select menu item */
    QStringList selectList;
    selectList.append(tr("TOFD Settings"));
    selectList.append(tr("TOFD Analysis"));
    m_menuItem[0]->set(tr("Select"), selectList);
    connect(m_menuItem[0], SIGNAL(value_changed(int)), this, SLOT(do_select_changed(int)));

    /* Wedge Sep. menu item */
    m_menuItem[1]->set(tr("Wedge Sep."), "mm", 0, 10000, 1);
    /* Layer Depth menu item */
    m_menuItem[2]->set(tr("Layer Depth"), "");
    /* TOFD Calculator menu item */
    m_menuItem[3]->set(tr("TOFD Calculator"), "");
    /* Start menu item */
    m_menuItem[4]->set(tr("Start"), "mm", 0, 16000, 2);
    /* Range menu item */
    m_menuItem[5]->set(tr("Range"), "mm", 0, 16000, 2);


    /* Straightening menu item */
    m_straighteningItem = new ComboMenuItem();
    m_straighteningItem->set(tr("Straightening"), s_onOff);
    /* Remove Lateral menu item */
    m_removeLateralItem = new ComboMenuItem();
    m_removeLateralItem->set(tr("Remove Lateral"), s_onOff);
    /* Ref.Position menu item */
    m_refPositionItem = new SpinMenuItem();
    m_refPositionItem->set(tr("Ref.Position"), "mm", 0, 2000, 2);
    /* Depth Calibration menu item */
    m_depthCalibrationItem = new ComboMenuItem();
    m_depthCalibrationItem->set(tr("Depth Calibration"), s_onOff);
}

TofdMenu::~TofdMenu()
{
    delete m_straighteningItem;
    delete m_removeLateralItem;
    delete m_refPositionItem;
    delete m_depthCalibrationItem;
}

void TofdMenu::show()
{
    if (m_menuItem[0]->get_current_index() == 0) {
        BaseMenu::show();
    } else {
        show_analysis();
    }
}

void TofdMenu::hide()
{
    if (m_menuItem[0]->get_current_index() == 0) {
        BaseMenu::hide();
    } else {
        hide_analysis();
    }
}

void TofdMenu::show_analysis()
{
    ui->menuItem0->layout()->addWidget(m_menuItem[0]);
    ui->menuItem1->layout()->addWidget(m_straighteningItem);
    ui->menuItem2->layout()->addWidget(m_removeLateralItem);
    ui->menuItem3->layout()->addWidget(m_refPositionItem);
    ui->menuItem4->layout()->addWidget(m_depthCalibrationItem);
    m_menuItem[0]->show();
    m_straighteningItem->show();
    m_removeLateralItem->show();
    m_refPositionItem->show();
    m_depthCalibrationItem->show();
}

void TofdMenu::hide_analysis()
{
    ui->menuItem0->layout()->removeWidget(m_menuItem[0]);
    ui->menuItem1->layout()->removeWidget(m_straighteningItem);
    ui->menuItem2->layout()->removeWidget(m_removeLateralItem);
    ui->menuItem3->layout()->removeWidget(m_refPositionItem);
    ui->menuItem4->layout()->removeWidget(m_depthCalibrationItem);
    m_menuItem[0]->hide();
    m_straighteningItem->hide();
    m_removeLateralItem->hide();
    m_refPositionItem->hide();
    m_depthCalibrationItem->hide();
}

void TofdMenu::do_select_changed(int index)
{
    if (0 == index) {
        hide_analysis();
        BaseMenu::show();
    } else {
        BaseMenu::hide();
        show_analysis();
    }
}

}
