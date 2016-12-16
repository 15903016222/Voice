#include "properties_menu.h"
#include "combo_menu_item.h"

static const MenuItem::Type s_types[MAX_ITEMS] = {
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo,
    MenuItem::Combo
};

PropertiesMenu::PropertiesMenu(Ui::SubMenu *ui, QObject *parent) :
    BaseMenu(ui, s_types, parent)
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

    m_menuItem[0]->set(tr("Scan"), scanList);
    connect(m_menuItem[0], SIGNAL(value_changed(int)), this, SLOT(do_mode_changed(int)));

    /* A-Scan */
    m_menuItem[1]->set(tr("Color"), colorList);
    m_menuItem[2]->set(tr("Envelope"), envelopeList);
    m_menuItem[3]->set(tr("Peak Holding"), s_onOff);
    m_menuItem[4]->set(tr("Reference Holding"), s_onOff);

    /* B-Scan */
    m_compressionItem = new ComboMenuItem();
    m_compressionItem->set(tr("Compression"), s_onOff);

    /* C-Scan */
    m_ratioItem = new ComboMenuItem();
    m_ratioItem->set(tr("Ratio 1:1"), s_onOff);

    m_cScanModeItem = new ComboMenuItem();
    m_cScanModeItem->set(tr("C-Scan Mode"), cScanModeList);
}

void PropertiesMenu::show()
{
    switch (m_menuItem[0]->get_current_index()) {
    case 0:
        /* A-Scan */
        BaseMenu::show();
        break;
    case 1:
        /* B-Scan */
        ui->menuItem1->layout()->addWidget(m_menuItem[0]);
        ui->menuItem2->layout()->addWidget(m_compressionItem);
        ui->menuItem3->layout()->addWidget(m_menuItem[5]);
        ui->menuItem4->layout()->addWidget(m_menuItem[5]);
        ui->menuItem5->layout()->addWidget(m_menuItem[5]);
        m_menuItem[0]->show();
        m_compressionItem->show();
        m_menuItem[5]->show();
        break;
    case 2:
        /* C-Scan */
        ui->menuItem1->layout()->addWidget(m_menuItem[0]);
        ui->menuItem2->layout()->addWidget(m_ratioItem);
        ui->menuItem3->layout()->addWidget(m_cScanModeItem);
        ui->menuItem4->layout()->addWidget(m_menuItem[5]);
        ui->menuItem4->layout()->addWidget(m_menuItem[5]);
        m_menuItem[0]->show();
        m_ratioItem->show();
        m_cScanModeItem->show();
        m_menuItem[5]->show();
        break;
    default:
        break;
    }
}

void PropertiesMenu::hide()
{
    /* A-Scan */
    BaseMenu::hide();

    ui->menuItem2->layout()->removeWidget(m_compressionItem);

    m_compressionItem->hide();

    ui->menuItem2->layout()->removeWidget(m_ratioItem);
    ui->menuItem3->layout()->removeWidget(m_cScanModeItem);


    m_ratioItem->hide();
    m_cScanModeItem->hide();
}

void PropertiesMenu::do_mode_changed(int i)
{
    Q_UNUSED(i);
    hide();
    show();
}
