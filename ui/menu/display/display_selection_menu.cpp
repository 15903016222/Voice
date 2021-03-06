/**
 * @file selection_menu.cpp
 * @brief selection menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "display_selection_menu.h"
#include "combo_menu_item.h"
#include "spin_menu_item.h"

namespace DplDisplayMenu {

SelectionMenu::SelectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    QStringList groupList;
    QStringList displayList;
    QStringList cScanSourceList;

    groupList.append(tr("All"));
    groupList.append(tr("Current"));

    displayList.append(tr("A A-Scan"));
    displayList.append(tr("B B-Scan"));
    displayList.append(tr("C C-Scan"));
    displayList.append(tr("S S-Scan"));
    displayList.append(tr("A-B A-Scan B-Scan"));
    displayList.append(tr("A-S A-Scan S-Scan"));
    displayList.append(tr("A-B-C A-Scan B-Scan C-Scan"));
    displayList.append(tr("A-B-S A-Scan B-Scan S-Scan"));
    displayList.append(tr("A-S-[C] A-Scan S-Scan [C-Scan]"));
    displayList.append(tr("S-A-A-A S-Scan A-Scan A-Scan A-Scan"));
    displayList.append(tr("S-A-C-C S-Scan A-Scan C-Scan C-Scan"));

    cScanSourceList.append(tr("A%"));
    cScanSourceList.append(tr("B%"));
    cScanSourceList.append(tr("Thickness"));
    cScanSourceList.append(tr("I/"));

    m_groupItem = new ComboMenuItem();
    m_displayItem = new ComboMenuItem;
    m_cSourceitem = new ComboMenuItem;
    m_minThicknessItem = new SpinMenuItem;
    m_maxThicknessItem = new SpinMenuItem;
    m_dataCompressionItem = new ComboMenuItem;

    /* Group menu item */
    m_groupItem->set(tr("Group"), groupList);

    /* Display menu item */
    m_displayItem->set(tr("Display"), displayList);

    /* C-Scan Source menu item */
    m_cSourceitem->set(tr("C-Scan<br>Source"), cScanSourceList);

    /* Min.Thickness menu item */
    m_minThicknessItem->set(tr("Min.Thickness"), "mm", 0.05, 20000, 2);

    /* Max.Thickness menu item */
    m_maxThicknessItem->set(tr("Max.Thickness"), "mm", 0.06, 20000, 2);

    /* Data compression */
    m_dataCompressionItem->set(tr("Data<br>Compression"), s_onOff);
}

SelectionMenu::~SelectionMenu()
{
    delete m_groupItem;
    delete m_displayItem;
    delete m_cSourceitem;
    delete m_minThicknessItem;
    delete m_maxThicknessItem;
    delete m_dataCompressionItem;
}

void SelectionMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_groupItem);
    ui->menuItem1->layout()->addWidget(m_displayItem);
    ui->menuItem2->layout()->addWidget(m_cSourceitem);
    ui->menuItem3->layout()->addWidget(m_minThicknessItem);
    ui->menuItem4->layout()->addWidget(m_maxThicknessItem);
    ui->menuItem5->layout()->addWidget(m_dataCompressionItem);
    m_groupItem->show();
    m_displayItem->show();
    m_cSourceitem->show();
    m_minThicknessItem->show();
    m_maxThicknessItem->show();
    m_dataCompressionItem->show();
}

void SelectionMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_groupItem);
    ui->menuItem1->layout()->removeWidget(m_displayItem);
    ui->menuItem2->layout()->removeWidget(m_cSourceitem);
    ui->menuItem3->layout()->removeWidget(m_minThicknessItem);
    ui->menuItem4->layout()->removeWidget(m_maxThicknessItem);
    ui->menuItem5->layout()->removeWidget(m_dataCompressionItem);
    m_groupItem->hide();
    m_displayItem->hide();
    m_cSourceitem->hide();
    m_minThicknessItem->hide();
    m_maxThicknessItem->hide();
    m_dataCompressionItem->hide();
}

}
