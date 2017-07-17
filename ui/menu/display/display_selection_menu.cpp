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
#include "display_select_dialog.h"

namespace DplDisplayMenu {

SelectionMenu::SelectionMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    QStringList cScanSourceList;

    m_display = DplDisplay::Display::get_instance();

//    displayList.append(tr("A A-Scan"));
//    displayList.append(tr("B B-Scan"));
//    displayList.append(tr("C C-Scan"));
//    displayList.append(tr("S S-Scan"));
//    displayList.append(tr("A-B A-Scan B-Scan"));
//    displayList.append(tr("A-S A-Scan S-Scan"));
//    displayList.append(tr("A-B-C A-Scan B-Scan C-Scan"));
//    displayList.append(tr("A-B-S A-Scan B-Scan S-Scan"));
//    displayList.append(tr("A-S-[C] A-Scan S-Scan [C-Scan]"));
//    displayList.append(tr("S-A-A-A S-Scan A-Scan A-Scan A-Scan"));
//    displayList.append(tr("S-A-C-C S-Scan A-Scan C-Scan C-Scan"));

    cScanSourceList.append(tr("A%"));
    cScanSourceList.append(tr("B%"));
    cScanSourceList.append(tr("Thickness"));
    cScanSourceList.append(tr("I/"));

    /* Display menu item */
    m_displayItem.set(tr("Display"), "A");
    connect(&m_displayItem, SIGNAL(clicked()),
            this, SLOT(do_displayItem_clicked()));

    /* C-Scan Source menu item */
    m_cSourceItem.set(tr("C-Scan<br>Source"), cScanSourceList);

    /* Min.Thickness menu item */
    m_minThicknessItem.set(tr("Min.Thickness"), "mm", 0.05, 20000, 2);

    /* Max.Thickness menu item */
    m_maxThicknessItem.set(tr("Max.Thickness"), "mm", 0.06, 20000, 2);

    /* Data compression */
    m_dataCompressionItem.set(tr("Data<br>Compression"), s_onOff);
}

SelectionMenu::~SelectionMenu()
{
}

void SelectionMenu::show()
{
    ui->layout0->addWidget(&m_displayItem);
    ui->layout1->addWidget(&m_cSourceItem);
    ui->layout2->addWidget(&m_minThicknessItem);
    ui->layout3->addWidget(&m_maxThicknessItem);
    ui->layout4->addWidget(&m_dataCompressionItem);
    m_displayItem.show();
    m_cSourceItem.show();
    m_minThicknessItem.show();
    m_maxThicknessItem.show();
    m_dataCompressionItem.show();
}

void SelectionMenu::hide()
{
    ui->layout0->removeWidget(&m_displayItem);
    ui->layout1->removeWidget(&m_cSourceItem);
    ui->layout2->removeWidget(&m_minThicknessItem);
    ui->layout3->removeWidget(&m_maxThicknessItem);
    ui->layout4->removeWidget(&m_dataCompressionItem);
    m_displayItem.hide();
    m_cSourceItem.hide();
    m_minThicknessItem.hide();
    m_maxThicknessItem.hide();
    m_dataCompressionItem.hide();
}

void SelectionMenu::do_displayItem_clicked()
{
    DisplaySelectDialog dialog;
    dialog.exec();
}

}
