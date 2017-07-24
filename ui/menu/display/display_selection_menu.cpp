/**
 * @file selection_menu.cpp
 * @brief selection menu
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-12-16
 */
#include "display_selection_menu.h"
#include "display_select_dialog.h"
#include "ui_base_menu.h"

namespace DplDisplayMenu {

SelectionMenu::SelectionMenu(QWidget *parent) :
    BaseMenu(parent),
    m_displayItem(new LabelMenuItem(this, tr("Display"), "A")),
    m_cSourceItem(new ComboMenuItem(this, tr("C Scan<br>Source"))),
    m_minThicknessItem(new SpinMenuItem(this, tr("Min.Thickness"), "mm")),
    m_maxThicknessItem(new SpinMenuItem(this, tr("Max.Thickness"), "mm")),
    m_dataCompressionItem(new ComboMenuItem(this, tr("Data<br>Compression")))
{
    ui->layout0->addWidget(m_displayItem);
    ui->layout1->addWidget(m_cSourceItem);
    ui->layout2->addWidget(m_minThicknessItem);
    ui->layout3->addWidget(m_maxThicknessItem);
    ui->layout4->addWidget(m_dataCompressionItem);

    QStringList cScanSourceList;

    cScanSourceList.append(tr("A%"));
    cScanSourceList.append(tr("B%"));
    cScanSourceList.append(tr("Thickness"));
    cScanSourceList.append(tr("I/"));

    /* Display menu item */
    connect(m_displayItem, SIGNAL(clicked()),
            this, SLOT(do_displayItem_clicked()));

    /* C-Scan Source menu item */
    m_cSourceItem->set(cScanSourceList);

    /* Min.Thickness menu item */
    m_minThicknessItem->set(0.05, 20000, 2);

    /* Max.Thickness menu item */
    m_maxThicknessItem->set(0.06, 20000, 2);

    /* Data compression */
    m_dataCompressionItem->set(s_onOff);
}

SelectionMenu::~SelectionMenu()
{
}

void SelectionMenu::do_displayItem_clicked()
{
    DisplaySelectDialog dialog;
    dialog.exec();
}

}
