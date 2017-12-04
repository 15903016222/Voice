#include "properties_menu.h"


#include <QColorDialog>
#include <device/device.h>

namespace DplDisplayMenu {

PropertiesMenu::PropertiesMenu(QWidget *parent) :
    BaseMenu(parent),
    m_display(DplDevice::Device::instance()->display()),
    m_scanItem(new ComboMenuItem(this, tr("Scan"))),
    m_colorItem(new LabelMenuItem(this, tr("Color"))),
    m_envelopItem(new ComboMenuItem(this, tr("Envelope"))),
    m_peakHoldingItem(new ComboMenuItem(this, tr("Peak Holding"))),
    m_referenceholdingItem(new ComboMenuItem(this, tr("Reference\nHolding"))),
    m_compressionItem(new ComboMenuItem(this, tr("Compression"))),
    m_ratioItem(new ComboMenuItem(this, tr("Ratio"))),
    m_cScanModeItem(new ComboMenuItem(this, tr("C-Scan\nMode")))
{
    m_layout0->addWidget(m_scanItem);

    /* A-Scan */
    m_layout1->addWidget(m_colorItem);
    m_layout2->addWidget(m_envelopItem);
    m_layout3->addWidget(m_peakHoldingItem);
    m_layout4->addWidget(m_referenceholdingItem);

    /* B-Scan */
    m_layout1->addWidget(m_compressionItem);

    /* C-Scan */
    m_layout1->addWidget(m_ratioItem);
    m_layout2->addWidget(m_cScanModeItem);

    m_scanItem->add_item(tr("A-Scan"));
    m_scanItem->add_item(tr("B-Scan"));
    m_scanItem->add_item(tr("C-Scan"));
    connect(m_scanItem, SIGNAL(value_changed(int)), this, SLOT(do_scanItem_changed(int)));

    /* A-Scan */
//    m_colorItem->add_item(tr("Blue"));
//    m_colorItem->add_item(tr("Green"));
//    m_colorItem->add_item(tr("Red"));
//    m_colorItem->add_item(tr("Yellow"));
//    m_colorItem->add_item(tr("Black"));
//    m_colorItem->add_item(tr("White"));
    connect(m_colorItem, SIGNAL(clicked()),
            this, SLOT(do_colorItem_clicked()));
    m_colorItem->set_text(QString("<p style=\"color:%1\">%1</p>")
                          .arg(m_display->ascan()->color().name()));

    m_envelopItem->add_item(tr("None"));
    m_envelopItem->add_item(tr("Infinite"));

    m_peakHoldingItem->set(s_onOff);
    m_referenceholdingItem->set(s_onOff);

    /* B-Scan */
    m_compressionItem->set(s_onOff);

    /* C-Scan */
    m_ratioItem->set(s_onOff);

    m_cScanModeItem->add_item(tr("Sectorial"));
    m_cScanModeItem->add_item(tr("Linear"));

    do_scanItem_changed(0);
}

PropertiesMenu::~PropertiesMenu()
{
}

void PropertiesMenu::hide_scan()
{
    /* A-Scan */
    m_colorItem->hide();
    m_envelopItem->hide();
    m_peakHoldingItem->hide();
    m_referenceholdingItem->hide();

    /* B-Scan */
    m_compressionItem->hide();

    /* C-Scan */
    m_ratioItem->hide();
    m_cScanModeItem->hide();
}

void PropertiesMenu::show_a_scan()
{
    m_scanItem->show();
    m_colorItem->show();
    m_envelopItem->show();
    m_peakHoldingItem->show();
    m_referenceholdingItem->show();
}

void PropertiesMenu::show_b_scan()
{
    m_scanItem->show();
    m_compressionItem->show();
}

void PropertiesMenu::show_c_scan()
{
    m_scanItem->show();
    m_ratioItem->show();
    m_cScanModeItem->show();
}

void PropertiesMenu::do_scanItem_changed(int i)
{
    hide_scan();
    switch(i) {
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

void PropertiesMenu::do_colorItem_clicked()
{
    QColorDialog dlg;
    dlg.setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
    if ( dlg.exec() == QDialog::Accepted ) {
        m_display->ascan()->set_color(dlg.currentColor());
        m_colorItem->set_text(QString("<p style=\"color:%1\">%1</p>")
                              .arg(dlg.currentColor().name()));
    }

}

}
