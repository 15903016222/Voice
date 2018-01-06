#include "format_menu.h"


namespace DplFileReportMenu {

FormatMenu::FormatMenu(QWidget *parent) :
    BaseMenu(parent),
    m_probeWedgeItem(new ComboMenuItem(this, tr("Probe/Wedge"))),
    m_inspectionInfoItem(new ComboMenuItem(this, tr("Inspection"))),
    m_scanInfoItem(new ComboMenuItem(this, tr("Scan"))),
    m_encoderInfoItem(new ComboMenuItem(this, tr("Encoder"))),
    m_dacTcgInfoItem(new ComboMenuItem(this, tr("DAC/TCG"))),
    m_flawRecordTableItem(new ComboMenuItem(this, tr("Flaw Record\nTable")))
{
    m_layout0->addWidget(m_probeWedgeItem);
    m_layout1->addWidget(m_inspectionInfoItem);
    m_layout2->addWidget(m_scanInfoItem);
    m_layout3->addWidget(m_encoderInfoItem);
    m_layout4->addWidget(m_dacTcgInfoItem);
    m_layout5->addWidget(m_flawRecordTableItem);

    /* Probe/Wedge Info Menu Item */
    m_probeWedgeItem->set(s_onOff);

    /* Inspection Info menu item */
    m_inspectionInfoItem->set(s_onOff);

    /* Scan Info menu item */
    m_scanInfoItem->set(s_onOff);

    /* Encoder Info Menu Item */
    m_encoderInfoItem->set(s_onOff);

    /* DAC/TCG Info Number item */
    m_dacTcgInfoItem->set(s_onOff);

    /* Flaw Record Table menu item */
    m_flawRecordTableItem->set(s_onOff);
}

FormatMenu::~FormatMenu()
{
}

void FormatMenu::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange) {
        m_probeWedgeItem->set_title(tr("Probe/Wedge"));
        m_inspectionInfoItem->set_title(tr("Inspection"));
        m_scanInfoItem->set_title(tr("Scan"));
        m_encoderInfoItem->set_title(tr("Encoder"));
        m_dacTcgInfoItem->set_title(tr("DAC/TCG"));
        m_flawRecordTableItem->set_title(tr("Flaw Record\nTable"));
        s_onOff.clear();
        s_onOff << tr("On") << tr("Off");
        m_probeWedgeItem->retranslate_items(s_onOff);
        m_inspectionInfoItem->retranslate_items(s_onOff);
        m_scanInfoItem->retranslate_items(s_onOff);
        m_encoderInfoItem->retranslate_items(s_onOff);
        m_dacTcgInfoItem->retranslate_items(s_onOff);
        m_flawRecordTableItem->retranslate_items(s_onOff);
        return;
    }

    BaseMenu::changeEvent(event);
}

}
