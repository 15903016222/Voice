#include "format_menu.h"
#include "combo_menu_item.h"

namespace DplFileReportMenu {

FormatMenu::FormatMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    /* Probe/Wedge Info Menu Item */
    m_probeWedgeItem = new ComboMenuItem;
    m_probeWedgeItem->set(tr("Probe/Wedge Info"), s_onOff);

    /* Inspection Info menu item */
    m_inspectionInfoItem = new ComboMenuItem;
    m_inspectionInfoItem->set(tr("Inspection Info"), s_onOff);

    /* Scan Info menu item */
    m_scanInfoItem = new ComboMenuItem;
    m_scanInfoItem->set(tr("Scan Info"), s_onOff);

    /* Encoder Info Menu Item */
    m_encoderInfoItem = new ComboMenuItem;
    m_encoderInfoItem->set(tr("Encoder Info"), s_onOff);

    /* DAC/TCG Info Number item */
    m_dacTcgInfoItem = new ComboMenuItem;
    m_dacTcgInfoItem->set(tr("DAC/TCG Info"), s_onOff);

    /* Flaw Record Table menu item */
    m_flawRecordTableItem = new ComboMenuItem;
    m_flawRecordTableItem->set(tr("Flaw Record Table"), s_onOff);
}

FormatMenu::~FormatMenu()
{
    delete m_probeWedgeItem;
    delete m_inspectionInfoItem;
    delete m_scanInfoItem;
    delete m_encoderInfoItem;
    delete m_dacTcgInfoItem;
    delete m_flawRecordTableItem;
}

void FormatMenu::show()
{
    ui->menuItem0->layout()->addWidget(m_probeWedgeItem);
    ui->menuItem1->layout()->addWidget(m_inspectionInfoItem);
    ui->menuItem2->layout()->addWidget(m_scanInfoItem);
    ui->menuItem3->layout()->addWidget(m_encoderInfoItem);
    ui->menuItem4->layout()->addWidget(m_dacTcgInfoItem);
    ui->menuItem5->layout()->addWidget(m_flawRecordTableItem);
    m_probeWedgeItem->show();
    m_inspectionInfoItem->show();
    m_scanInfoItem->show();
    m_encoderInfoItem->show();
    m_dacTcgInfoItem->show();
    m_flawRecordTableItem->show();
}

void FormatMenu::hide()
{
    ui->menuItem0->layout()->removeWidget(m_probeWedgeItem);
    ui->menuItem1->layout()->removeWidget(m_inspectionInfoItem);
    ui->menuItem2->layout()->removeWidget(m_scanInfoItem);
    ui->menuItem3->layout()->removeWidget(m_encoderInfoItem);
    ui->menuItem4->layout()->removeWidget(m_dacTcgInfoItem);
    ui->menuItem5->layout()->removeWidget(m_flawRecordTableItem);
    m_probeWedgeItem->hide();
    m_inspectionInfoItem->hide();
    m_scanInfoItem->hide();
    m_encoderInfoItem->hide();
    m_dacTcgInfoItem->hide();
    m_flawRecordTableItem->hide();
}

}
