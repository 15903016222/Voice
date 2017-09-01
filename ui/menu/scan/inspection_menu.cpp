#include "inspection_menu.h"
#include "ui_base_menu.h"

namespace DplScanMenu {

InspectionMenu::InspectionMenu(QWidget *parent) :
    BaseMenu(parent),
    m_typeItem(new ComboMenuItem(this, tr("Type"))),
    m_scanItem(new ComboMenuItem(this, tr("Scan"))),
    m_indexItem(new ComboMenuItem(this, tr("Index"))),
    m_maxScanSpeedItem(new SpinMenuItem(this, tr("Scan Speed"), tr("m/s"))),
    m_maxScanSpeedRPMItem(new SpinMenuItem(this, tr("Scan Speed(rpm)"), tr("m/s"))),
    m_scan(DplSource::Scan::instance()),
    m_scanAxis(m_scan->scan_axis()),
    m_indexAxis(m_scan->index_axis()),
    m_encX(m_scan->encoder_x()),
    m_encY(m_scan->encoder_y())
{
    ui->layout0->addWidget(m_typeItem);
    ui->layout1->addWidget(m_scanItem);

    /* Type menu item */
    m_typeItem->add_item(tr("One Line"));
    m_typeItem->add_item(tr("Raster Scan"));
    m_typeItem->add_item(tr("Helicoidal Scan"));
    connect(m_typeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_typeItem_changed(int)));

    /* Scan Menu Item */
    connect(m_scanItem, SIGNAL(value_changed(int)),
            this, SLOT(do_scanItem_changed(int)));
    connect(static_cast<DplSource::Axis *>(m_scanAxis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this,
            SLOT(do_scanAxis_driving_changed(DplSource::Axis::Driving)));

    /* Index Menu Item */
    m_indexItem->add_item(tr("Encoder 1"));
    m_indexItem->add_item(tr("Encoder 2"));
    connect(m_indexItem, SIGNAL(value_changed(int)),
            this, SLOT(do_indexItem_changed(int)));
    connect(static_cast<DplSource::Axis *>(m_indexAxis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this,
            SLOT(do_indexAxis_driving_changed(DplSource::Axis::Driving)));

    /* Max Scan Speed menu item */
    m_maxScanSpeedItem->set(0, 1000, 2);
    connect(m_maxScanSpeedItem, SIGNAL(value_changed(double)),
            m_scan, SLOT(set_speed(double)));

    /* Max Scan Speed(rpm) Menu Item */
    m_maxScanSpeedRPMItem->set(0, 1000, 0);

    do_typeItem_changed(m_scan->mode());
}

void InspectionMenu::do_typeItem_changed(int pos)
{
    m_indexItem->hide();
    m_maxScanSpeedItem->hide();
    m_maxScanSpeedRPMItem->hide();

    QStringList scanStringList;

    if (pos == 0) {
        scanStringList.append(tr("Time"));
        ui->layout2->addWidget(m_maxScanSpeedItem);
        m_maxScanSpeedItem->show();
    } else {
        ui->layout2->addWidget(m_indexItem);
        ui->layout3->addWidget(m_maxScanSpeedItem);
        m_indexItem->show();
        m_maxScanSpeedItem->show();

        if (pos == 2) {
            ui->layout4->addWidget(m_maxScanSpeedRPMItem);
            m_maxScanSpeedRPMItem->show();
        }
    }

    scanStringList.append(tr("Encoder 1"));
    scanStringList.append(tr("Encoder 2"));
    m_scanItem->set(scanStringList);

    m_scan->set_mode((DplSource::Scan::Mode)pos);
}

void InspectionMenu::do_scanItem_changed(int pos)
{
    if (m_scan->mode() == DplSource::Scan::ONELINE) {
        m_scanAxis->set_driving(static_cast<DplSource::Axis::Driving>(pos));
    } else {
        m_scanAxis->set_driving(static_cast<DplSource::Axis::Driving>(pos+1));
    }
}

void InspectionMenu::do_indexItem_changed(int pos)
{
    m_indexAxis->set_driving(static_cast<DplSource::Axis::Driving>(pos+1));
}

void InspectionMenu::do_scanAxis_driving_changed(DplSource::Axis::Driving driving)
{
    if (m_scan->mode() == DplSource::Scan::ONELINE) {
        m_scanItem->set_current_index(driving);
    } else {
        m_scanItem->set_current_index(driving - 1);
    }
}

void InspectionMenu::do_indexAxis_driving_changed(DplSource::Axis::Driving driving)
{
    if (driving == DplSource::Axis::NONE
            || driving == DplSource::Axis::TIMER) {
        return;
    }
    m_indexItem->set_current_index(driving - 1);
}

}
