#include "properties_menu.h"
#include "combo_menu_item.h"

namespace DplDisplayMenu {

PropertiesMenu::PropertiesMenu(Ui::BaseMenu *ui, QObject *parent) :
    BaseMenu(ui, parent)
{
    QStringList scanList;
    QStringList colorList;
    QStringList envelopeList;
    QStringList cScanModeList;

    scanList.append(tr("A-Scan"));
    scanList.append(tr("B-Scan"));
    scanList.append(tr("C-Scan"));

    colorList.append(tr("Blue"));
    colorList.append(tr("Green"));
    colorList.append(tr("Red"));
    colorList.append(tr("Yellow"));
    colorList.append(tr("Black"));
    colorList.append(tr("White"));

    envelopeList.append(tr("None"));
    envelopeList.append(tr("Infinite"));

    cScanModeList.append(tr("Sectorial"));
    cScanModeList.append(tr("Linear"));

    m_scanItem.set(tr("Scan"), scanList);
    connect(&m_scanItem, SIGNAL(value_changed(int)), this, SLOT(do_mode_changed(int)));

    /* A-Scan */
    m_colorItem.set(tr("Color"), colorList);
    m_envelopItem.set(tr("Envelope"), envelopeList);
    m_peakHoldingItem.set(tr("Peak Holding"), s_onOff);
    m_referenceholdingItem.set(tr("Reference Holding"), s_onOff);

    /* B-Scan */
    m_compressionItem.set(tr("Compression"), s_onOff);

    /* C-Scan */
    m_ratioItem.set(tr("Ratio 1:1"), s_onOff);

    m_cScanModeItem.set(tr("C-Scan Mode"), cScanModeList);
}

PropertiesMenu::~PropertiesMenu()
{
}

void PropertiesMenu::show()
{
    switch (m_scanItem.current_index()) {
    case 0:
        /* A-Scan */
        show_a_scan();
        break;
    case 1:
        /* B-Scan */
        show_b_scan();
        break;
    case 2:
        /* C-Scan */
        show_c_scan();
        break;
    default:
        break;
    }
}

void PropertiesMenu::hide()
{
    /* A-Scan */
    ui->menuItem0->layout()->removeWidget(&m_scanItem);
    ui->menuItem1->layout()->removeWidget(&m_colorItem);
    ui->menuItem2->layout()->removeWidget(&m_envelopItem);
    ui->menuItem3->layout()->removeWidget(&m_peakHoldingItem);
    ui->menuItem4->layout()->removeWidget(&m_referenceholdingItem);
    m_scanItem.hide();
    m_colorItem.hide();
    m_envelopItem.hide();
    m_peakHoldingItem.hide();
    m_referenceholdingItem.hide();

    /* B-Scan */
    ui->menuItem1->layout()->removeWidget(&m_compressionItem);
    m_compressionItem.hide();

    /* C-Scan */
    ui->menuItem1->layout()->removeWidget(&m_ratioItem);
    ui->menuItem2->layout()->removeWidget(&m_cScanModeItem);
    m_ratioItem.hide();
    m_cScanModeItem.hide();
}

void PropertiesMenu::show_a_scan()
{
    ui->menuItem0->layout()->addWidget(&m_scanItem);
    ui->menuItem1->layout()->addWidget(&m_colorItem);
    ui->menuItem2->layout()->addWidget(&m_envelopItem);
    ui->menuItem3->layout()->addWidget(&m_peakHoldingItem);
    ui->menuItem4->layout()->addWidget(&m_referenceholdingItem);
    m_scanItem.show();
    m_colorItem.show();
    m_envelopItem.show();
    m_peakHoldingItem.show();
    m_referenceholdingItem.show();
}

void PropertiesMenu::show_b_scan()
{
    ui->menuItem0->layout()->addWidget(&m_scanItem);
    ui->menuItem1->layout()->addWidget(&m_compressionItem);
    m_scanItem.show();
    m_compressionItem.show();
}

void PropertiesMenu::show_c_scan()
{
    ui->menuItem0->layout()->addWidget(&m_scanItem);
    ui->menuItem1->layout()->addWidget(&m_ratioItem);
    ui->menuItem2->layout()->addWidget(&m_cScanModeItem);
    m_scanItem.show();
    m_ratioItem.show();
    m_cScanModeItem.show();
}

void PropertiesMenu::do_mode_changed(int i)
{
    Q_UNUSED(i);
    hide();
    show();
}

}
