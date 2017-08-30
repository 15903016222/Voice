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
    m_scan(DplSource::Scan::instance())
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

    /* Index Menu Item */
    m_indexItem->add_item(tr("Encoder 1"));
    m_indexItem->add_item(tr("Encoder 2"));
    connect(m_indexItem, SIGNAL(value_changed(int)),
            this, SLOT(do_indexItem_changed(int)));

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

    m_scan->set_mode((DplSource::Scan::Mode)pos);

    if (pos == 0) {
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

    update_scanItem();
}

void InspectionMenu::do_scanItem_changed(int pos)
{
    DplSource::Driving *driving = NULL;
    if (m_scan->mode() == DplSource::Scan::ONELINE
            && pos == 0){
        driving = new DplSource::Driving();
    } else if (m_scan->mode() == DplSource::Scan::ONELINE) {
        driving = new DplSource::Encoder(pos);
    } else {
        if (pos == 0) {
            driving = new DplSource::Encoder(1);
            m_scan->index_axis()->driving().staticCast<DplSource::Encoder>()->set_index(2);
            m_indexItem->set_current_index(1);
        } else {
            driving = new DplSource::Encoder(2);
            m_scan->index_axis()->driving().staticCast<DplSource::Encoder>()->set_index(1);
            m_indexItem->set_current_index(0);
        }
    }
    m_scan->scan_axis()->set_driving(DplSource::DrivingPointer(driving));
}

void InspectionMenu::do_indexItem_changed(int pos)
{
    DplSource::Driving *driving = new DplSource::Encoder(pos+1);
    m_scan->index_axis()->set_driving(DplSource::DrivingPointer(driving));

    if (pos == 0) {
        m_scan->scan_axis()->driving().staticCast<DplSource::Encoder>()->set_index(2);
        m_scanItem->set_current_index(1);
    } else {
        m_scanItem->set_current_index(0);
        m_scan->scan_axis()->driving().staticCast<DplSource::Encoder>()->set_index(1);
    }
}

void InspectionMenu::update_scanItem()
{
    DplSource::DrivingPointer driving = m_scan->scan_axis()->driving();
    QStringList scanStringList;
    int pos = 0;

    /* 更新选择内容 */
    if (m_scan->mode() == DplSource::Scan::ONELINE) {
        scanStringList.append(tr("Time"));
    }
    scanStringList.append(tr("Encoder 1"));
    scanStringList.append(tr("Encoder 2"));
    m_scanItem->set(scanStringList);

    if (m_scan->mode() != DplSource::Scan::ONELINE
            && driving->type() == DplSource::Driving::TIMER) {
        DplSource::Encoder *enc = new DplSource::Encoder;
        if (m_scan->index_axis()->driving()->type() == DplSource::Driving::ENCODER) {
            DplSource::EncoderPointer indexEnc = m_scan->index_axis()->driving().staticCast<DplSource::Encoder>();
            if (indexEnc->index() == 1) {
                enc->set_index(2);
            }
        }
        driving = DplSource::DrivingPointer(enc);
        m_scan->scan_axis()->set_driving(driving);
    }

    if (driving->type() != DplSource::Driving::TIMER) {
        DplSource::EncoderPointer enc = driving.staticCast<DplSource::Encoder>();
        if (m_scan->mode() == DplSource::Scan::ONELINE) {
            pos = enc->index();
        } else {
            pos = enc->index() - 1;
        }
    }

    m_scanItem->set_current_index(pos);
}

void InspectionMenu::update_indexItem()
{
    if (m_scan->mode() == DplSource::Scan::ONELINE) {
        return;
    }

    DplSource::EncoderPointer indexEnc = m_scan->index_axis()->driving().staticCast<DplSource::Encoder>();
    m_indexItem->set_current_index(indexEnc->index());
}


}
