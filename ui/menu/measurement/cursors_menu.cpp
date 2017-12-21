#include "cursors_menu.h"
#include "../menu_item/vpa_menu_item.h"

#include <global.h>
#include <ui/tool/tool.h>
#include <source/scan.h>

namespace DplMeasurementMenu {

CursorsMenu::CursorsMenu(QWidget *parent) :
    BaseMenu(parent),
    m_selectionItem(new ComboMenuItem(this, tr("Selection"))),
    m_rItem(new SpinMenuItem(this, ("%(r)"), "%")),
    m_mItem(new SpinMenuItem(this, "%(m)", "%")),
    m_urItem(new SpinMenuItem(this, ("U(r)"), "mm")),
    m_umItem(new SpinMenuItem(this, "U(m)", "mm")),
    m_srItem(new SpinMenuItem(this, "S(r)", "s")),
    m_smItem(new SpinMenuItem(this, "S(m)", "s")),
    m_irItem(new SpinMenuItem(this, "I(r)", "mm")),
    m_imItem(new SpinMenuItem(this, "I(m)", "mm")),
    m_vpaItem(new VpaMenuItem(this))
{
    m_layout0->addWidget(m_selectionItem);
    /* Selection menu item */
    m_selectionItem->add_item(tr("A-Scan"));
    m_selectionItem->add_item(tr("B-Scan"));
    m_selectionItem->add_item(tr("C-Scan"));
    m_selectionItem->add_item(tr("S-Scan"));
    connect(m_selectionItem, SIGNAL(value_changed(int)),
            this, SLOT(do_selectionItem_changed(int)));

    /* %(r) menu item */
    m_rItem->set(0, 100, 1);
    connect(m_rItem, SIGNAL(value_changed(double)),
            this, SLOT(do_rItem_changed(double)));

    /* %(m) menu item */
    m_mItem->set(0, 100, 1);
    connect(m_mItem, SIGNAL(value_changed(double)),
            this, SLOT(do_mItem_changed(double)));

    /* U(r) menu item */
    connect(m_urItem, SIGNAL(value_changed(double)),
            this, SLOT(do_urItem_changed(double)));

    /* U(m) menu item */
    connect(m_umItem, SIGNAL(value_changed(double)),
            this, SLOT(do_umItem_changed(double)));

    DplSource::Scan *scan = DplSource::Scan::instance();
    DplSource::AxisPointer scanAxis = scan->scan_axis();
    DplSource::AxisPointer indexAxis = scan->index_axis();

    /* S(r) menu item */
    connect(m_srItem, SIGNAL(value_changed(double)),
            this, SLOT(do_srItem_changed(double)));
    connect(scan, SIGNAL(speed_changed(double)),
            this, SLOT(update_srItem()));
    connect(static_cast<DplSource::Axis *>(scanAxis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(update_srItem()));
    connect(static_cast<DplSource::Axis *>(scanAxis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_srItem()));
    connect(static_cast<DplSource::Axis *>(scanAxis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(update_srItem()));

    /* S(m) menu item */
    connect(m_smItem, SIGNAL(value_changed(double)),
            this, SLOT(do_smItem_changed(double)));
    connect(scan, SIGNAL(speed_changed(double)),
            this, SLOT(update_smItem()));
    connect(static_cast<DplSource::Axis *>(scanAxis.data()),
            SIGNAL(driving_changed(DplSource::Axis::Driving)),
            this, SLOT(update_smItem()));
    connect(static_cast<DplSource::Axis *>(scanAxis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_smItem()));
    connect(static_cast<DplSource::Axis *>(scanAxis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(update_smItem()));

    /* I(r) menu item */
    connect(m_irItem, SIGNAL(value_changed(double)),
            this, SLOT(do_irItem_changed(double)));
    connect(static_cast<DplSource::Axis *>(indexAxis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_irItem()));
    connect(static_cast<DplSource::Axis *>(indexAxis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(update_irItem()));

    /* I(m) menu item */
    connect(m_imItem, SIGNAL(value_changed(double)),
            this, SLOT(do_imItem_changed(double)));
    connect(static_cast<DplSource::Axis *>(indexAxis.data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_imItem()));
    connect(static_cast<DplSource::Axis *>(indexAxis.data()),
            SIGNAL(end_changed(float)),
            this, SLOT(update_imItem()));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this,
            SLOT(update(DplDevice::GroupPointer)));

    update(DplDevice::Device::instance()->current_group());

    DplMeasure::CursorPointer cursorPointer = m_group->cursor();
    DplMeasure::Cursor *cursor = static_cast<DplMeasure::Cursor*>(cursorPointer.data());

    if(NULL != cursor) {
        connect(cursor, SIGNAL(scan_measurement_changed(double)),
                this, SLOT(do_scan_measurement_changed(double)));

        connect(cursor, SIGNAL(scan_reference_changed(double)),
                this, SLOT(do_scan_reference_changed(double)));

        connect(cursor, SIGNAL(ultrasound_measurement_changed(double)),
                this, SLOT(do_ultrasound_measurement_changed(double)));

        connect(cursor, SIGNAL(ultrasound_reference_changed(double)),
                this, SLOT(do_ultrasound_reference_changed(double)));
    }
}

void CursorsMenu::show_scan()
{
    m_layout0->addWidget(m_selectionItem);
    m_selectionItem->show();
    switch (m_selectionItem->current_index()) {
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
    case 3:
        /* S-Scan */
        show_s_scan();
        break;
    default:
        break;
    }
}

void CursorsMenu::show_a_scan()
{
    m_layout1->addWidget(m_rItem);
    m_layout2->addWidget(m_mItem);
    m_layout3->addWidget(m_urItem);
    m_layout4->addWidget(m_umItem);
    m_rItem->show();
    m_mItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::hide_a_scan()
{
    m_layout1->removeWidget(m_rItem);
    m_layout2->removeWidget(m_mItem);
    m_layout3->removeWidget(m_urItem);
    m_layout4->removeWidget(m_umItem);
    m_rItem->hide();
    m_mItem->hide();
    m_urItem->hide();
    m_umItem->hide();
}

void CursorsMenu::show_b_scan()
{
    m_layout1->addWidget(m_srItem);
    m_layout2->addWidget(m_smItem);
    m_layout3->addWidget(m_urItem);
    m_layout4->addWidget(m_umItem);
    m_srItem->show();
    m_smItem->show();
    m_urItem->show();
    m_umItem->show();
}

void CursorsMenu::hide_b_scan()
{
    m_layout1->removeWidget(m_srItem);
    m_layout2->removeWidget(m_smItem);
    m_layout3->removeWidget(m_urItem);
    m_layout4->removeWidget(m_umItem);
    m_srItem->hide();
    m_smItem->hide();
    m_urItem->hide();
    m_umItem->hide();
}

void CursorsMenu::show_c_scan()
{
    m_layout1->addWidget(m_srItem);
    m_layout2->addWidget(m_smItem);
    m_layout3->addWidget(m_irItem);
    m_layout4->addWidget(m_imItem);
    m_srItem->show();
    m_smItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::hide_c_scan()
{
    m_layout1->removeWidget(m_srItem);
    m_layout2->removeWidget(m_smItem);
    m_layout3->removeWidget(m_irItem);
    m_layout4->removeWidget(m_imItem);
    m_srItem->hide();
    m_smItem->hide();
    m_irItem->hide();
    m_imItem->hide();
}

void CursorsMenu::show_s_scan()
{
    m_layout1->addWidget(m_vpaItem);
    m_layout2->addWidget(m_urItem);
    m_layout3->addWidget(m_umItem);
    m_layout4->addWidget(m_irItem);
    m_layout5->addWidget(m_imItem);
    m_vpaItem->show();
    m_urItem->show();
    m_umItem->show();
    m_irItem->show();
    m_imItem->show();
}

void CursorsMenu::hide_s_scan()
{
    m_layout1->removeWidget(m_vpaItem);
    m_layout2->removeWidget(m_urItem);
    m_layout3->removeWidget(m_umItem);
    m_layout4->removeWidget(m_irItem);
    m_layout5->removeWidget(m_imItem);
    m_vpaItem->hide();
    m_urItem->hide();
    m_umItem->hide();
    m_irItem->hide();
    m_imItem->hide();
}

void CursorsMenu::update_srItem()
{
    DplSource::Scan *scan = DplSource::Scan::instance();
    DplSource::AxisPointer scanAxis = scan->scan_axis();
    if (scanAxis->driving() == DplSource::Axis::TIMER) {
        m_srItem->set_unit("s");
        m_srItem->set(scanAxis->start() / scan->speed(),
                      scanAxis->end() / scan->speed(),
                      1, 0.1);
        m_srItem->set_value(m_cursor->scan_reference() / DplSource::Scan::instance()->speed());
    } else {
        m_srItem->set_unit("mm");
        m_srItem->set(scanAxis->start(),
                      scanAxis->end(), 1, 0.1);
        m_srItem->set_value(m_cursor->scan_reference());
    }
}

void CursorsMenu::update_smItem()
{
    DplSource::Scan *scan = DplSource::Scan::instance();
    DplSource::AxisPointer scanAxis = scan->scan_axis();
    if (scanAxis->driving() == DplSource::Axis::TIMER) {
        m_smItem->set_unit("s");
        m_smItem->set(scanAxis->start() / scan->speed(),
                      scanAxis->end() / scan->speed(),
                      1, 0.1);
        m_smItem->set_value(m_cursor->scan_reference() / DplSource::Scan::instance()->speed());
    } else {
        m_smItem->set_unit("mm");
        m_smItem->set(scanAxis->start(),
                      scanAxis->end(), 1, 0.1);
        m_smItem->set_value(m_cursor->scan_reference());
    }
}

void CursorsMenu::update_urItem()
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_urItem->set_unit(US_STR);
    } else {
        m_urItem->set_unit(MM_STR);
    }

    m_urItem->set(Tool::cnf_to_display(m_group, m_group->sample()->start()),
                  Tool::cnf_to_display(m_group, m_group->sample()->start() + m_group->sample()->range()),
                  1, 0.1);
    m_urItem->set_value(Tool::cnf_to_display(m_group, m_cursor->ultrasound_reference()));
}

void CursorsMenu::update_umItem()
{
    if (m_group->ut_unit() == DplDevice::Group::Time) {
        m_umItem->set_unit(US_STR);
    } else {
        m_umItem->set_unit(MM_STR);
    }

    m_umItem->set(Tool::cnf_to_display(m_group, m_group->sample()->start()),
                  Tool::cnf_to_display(m_group, m_group->sample()->start() + m_group->sample()->range()),
                  1, 0.1);
    m_umItem->set_value(Tool::cnf_to_display(m_group, m_cursor->ultrasound_measurement()));
}

void CursorsMenu::update_irItem()
{
    DplSource::AxisPointer indexAxis = DplSource::Scan::instance()->index_axis();
    m_irItem->set(indexAxis->start(),
                  indexAxis->end(),
                  1, 0.1);
    m_irItem->set_value(m_cursor->index_reference());
}

void CursorsMenu::update_imItem()
{
    DplSource::AxisPointer indexAxis = DplSource::Scan::instance()->index_axis();
    m_imItem->set(indexAxis->start(),
                  indexAxis->end(),
                  1, 0.1);
    m_imItem->set_value(m_cursor->index_measurement());
}

void CursorsMenu::update(const DplDevice::GroupPointer &grp)
{
    if (m_group) {
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
                   this, SLOT(update_urItem()));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(start_changed(float)),
                   this, SLOT(update_urItem()));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(range_changed(float)),
                   this, SLOT(update_urItem()));
        disconnect(static_cast<DplDevice::Group *>(m_group.data()),
                   SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
                   this, SLOT(update_umItem()));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(start_changed(float)),
                   this, SLOT(update_umItem()));
        disconnect(static_cast<DplUt::Sample *>(m_group->sample().data()),
                   SIGNAL(range_changed(float)),
                   this, SLOT(update_umItem()));

        DplMeasure::CursorPointer cursorPointer = grp->cursor();
        DplMeasure::Cursor *cursor = static_cast<DplMeasure::Cursor*>(cursorPointer.data());

        if(NULL != cursor) {
            disconnect(cursor, SIGNAL(scan_measurement_changed(double)),
                    this, SLOT(do_scan_measurement_changed(double)));

            disconnect(cursor, SIGNAL(scan_reference_changed(double)),
                    this, SLOT(do_scan_reference_changed(double)));

            disconnect(cursor, SIGNAL(ultrasound_measurement_changed(double)),
                    this, SLOT(do_ultrasound_measurement_changed(double)));

            disconnect(cursor, SIGNAL(ultrasound_reference_changed(double)),
                    this, SLOT(do_ultrasound_reference_changed(double)));
        }
    }

    m_group = grp;
    m_cursor = m_group->cursor();

    do_selectionItem_changed(0);

    m_rItem->set_value(m_cursor->amplitude_reference());
    m_mItem->set_value(m_cursor->amplitude_measurement());
    update_urItem();
    update_umItem();
    update_srItem();
    update_smItem();
    update_irItem();
    update_imItem();

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_urItem()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_urItem()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_urItem()));
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_umItem()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_umItem()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_umItem()));

    DplMeasure::CursorPointer cursorPointer = m_group->cursor();
    DplMeasure::Cursor *cursor = static_cast<DplMeasure::Cursor*>(cursorPointer.data());

    if(NULL != cursor) {
        connect(cursor, SIGNAL(scan_measurement_changed(double)),
                this, SLOT(do_scan_measurement_changed(double)));

        connect(cursor, SIGNAL(scan_reference_changed(double)),
                this, SLOT(do_scan_reference_changed(double)));

        connect(cursor, SIGNAL(ultrasound_measurement_changed(double)),
                this, SLOT(do_ultrasound_measurement_changed(double)));

        connect(cursor, SIGNAL(ultrasound_reference_changed(double)),
                this, SLOT(do_ultrasound_reference_changed(double)));
    }
}

void CursorsMenu::do_selectionItem_changed(int index)
{
    hide_a_scan();
    hide_b_scan();
    hide_c_scan();
    hide_s_scan();

    if ( 0 == index ) {
        /* A-Scan */
        show_a_scan();
    } else if ( 1 == index ) {
        /* B-Scan */
        show_b_scan();
    } else if ( 2 == index ) {
        /* C-Scan */
        show_c_scan();
    } else if ( 3 == index ) {
        /* S-Scan */
        show_s_scan();
    }

}

void CursorsMenu::do_rItem_changed(double val)
{
    m_cursor->set_amplitude_reference(val);
}

void CursorsMenu::do_mItem_changed(double val)
{
    m_cursor->set_amplitude_measurement(val);
}

void CursorsMenu::do_srItem_changed(double val)
{
    DplMeasure::Cursor *cursor = static_cast<DplMeasure::Cursor*>(m_cursor.data());
    disconnect(cursor, SIGNAL(scan_reference_changed(double)),
            this, SLOT(do_scan_reference_changed(double)));
    m_cursor->set_scan_reference(val);
    connect(cursor, SIGNAL(scan_reference_changed(double)),
            this, SLOT(do_scan_reference_changed(double)));
}

void CursorsMenu::do_smItem_changed(double val)
{
    DplMeasure::Cursor *cursor = static_cast<DplMeasure::Cursor*>(m_cursor.data());
    disconnect(cursor, SIGNAL(scan_measurement_changed(double)),
            this, SLOT(do_scan_measurement_changed(double)));
    m_cursor->set_scan_measurement(val);
    connect(cursor, SIGNAL(scan_measurement_changed(double)),
            this, SLOT(do_scan_measurement_changed(double)));
}

void CursorsMenu::do_urItem_changed(double val)
{
    DplMeasure::Cursor *cursor = static_cast<DplMeasure::Cursor*>(m_cursor.data());
    disconnect(cursor, SIGNAL(ultrasound_reference_changed(double)),
            this, SLOT(do_ultrasound_reference_changed(double)));
    m_cursor->set_ultrasound_reference(Tool::display_to_cnf(m_group, val));
    connect(cursor, SIGNAL(ultrasound_reference_changed(double)),
            this, SLOT(do_ultrasound_reference_changed(double)));
}

void CursorsMenu::do_umItem_changed(double val)
{
    DplMeasure::Cursor *cursor = static_cast<DplMeasure::Cursor*>(m_cursor.data());
    disconnect(cursor, SIGNAL(ultrasound_measurement_changed(double)),
            this, SLOT(do_ultrasound_measurement_changed(double)));
    m_cursor->set_ultrasound_measurement(Tool::display_to_cnf(m_group, val));
    connect(cursor, SIGNAL(ultrasound_measurement_changed(double)),
            this, SLOT(do_ultrasound_measurement_changed(double)));
}

void CursorsMenu::do_irItem_changed(double val)
{
    m_cursor->set_index_reference(val);
}

void CursorsMenu::do_imItem_changed(double val)
{
    m_cursor->set_index_measurement(val);
}

void CursorsMenu::do_angleItem_changed(double val)
{
    m_group->set_current_beam(val);
}

void CursorsMenu::do_ultrasound_reference_changed(double value)
{
    /* U(r) menu item */
    disconnect(m_urItem, SIGNAL(value_changed(double)),
            this, SLOT(do_urItem_changed(double)));

    m_urItem->set_value(Tool::cnf_to_display(m_group, value));

    connect(m_urItem, SIGNAL(value_changed(double)),
            this, SLOT(do_urItem_changed(double)));

}

void CursorsMenu::do_ultrasound_measurement_changed(double value)
{
    /* U(m) menu item */
    disconnect(m_umItem, SIGNAL(value_changed(double)),
            this, SLOT(do_umItem_changed(double)));

    m_umItem->set_value(Tool::cnf_to_display(m_group, value));

    connect(m_umItem, SIGNAL(value_changed(double)),
            this, SLOT(do_umItem_changed(double)));
}

void CursorsMenu::do_scan_reference_changed(double value)
{
    /* S(r) menu item */
    disconnect(m_srItem, SIGNAL(value_changed(double)),
            this, SLOT(do_srItem_changed(double)));

    m_srItem->set_value(Tool::cnf_to_display(m_group, value));

    connect(m_srItem, SIGNAL(value_changed(double)),
            this, SLOT(do_srItem_changed(double)));
}

void CursorsMenu::do_scan_measurement_changed(double value)
{
    /* S(m) menu item */
    disconnect(m_smItem, SIGNAL(value_changed(double)),
            this, SLOT(do_smItem_changed(double)));

    m_smItem->set_value(Tool::cnf_to_display(m_group, value));

    connect(m_smItem, SIGNAL(value_changed(double)),
            this, SLOT(do_smItem_changed(double)));
}

}
