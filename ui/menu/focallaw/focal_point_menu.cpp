#include "focal_point_menu.h"

#include <device/device.h>

#include <QEvent>

namespace DplFocalLawMenu {

FocalPointMenu::FocalPointMenu(QWidget *parent) :
    BaseMenu(parent),
    m_typeItem(new ComboMenuItem(this, tr("Type"))),
    m_offsetStartItem(new SpinMenuItem(this, tr("Offset Start"), "mm")),
    m_offsetEndItem(new SpinMenuItem(this, tr("Offset End"), "mm")),
    m_depthStartItem(new SpinMenuItem(this, tr("Offset Start"), "mm")),
    m_depthEndItem(new SpinMenuItem(this, tr("Offset End"), "mm"))
{
    m_layout0->addWidget(m_typeItem);
    m_layout1->addWidget(m_offsetStartItem);
    m_layout2->addWidget(m_offsetEndItem);
    m_layout3->addWidget(m_depthStartItem);
    m_layout4->addWidget(m_depthEndItem);

    m_offsetStartItem->set(0, 1000, 2);
    connect(m_offsetStartItem, SIGNAL(value_changed(double)),
            this, SLOT(do_offsetStartItem_changed(double)));

    m_offsetEndItem->set(1, 1000, 2);
    connect(m_offsetEndItem, SIGNAL(value_changed(double)),
            this, SLOT(do_offsetEndItem_changed(double)));

    m_depthStartItem->set(0, 1000, 2);
    connect(m_depthStartItem, SIGNAL(value_changed(double)),
            this, SLOT(do_depthStartItem_changed(double)));

    m_depthEndItem->set(1, 1000, 2);
    connect(m_depthEndItem, SIGNAL(value_changed(double)),
            this, SLOT(do_depthEndItem_changed(double)));

    connect(DplDevice::Device::instance(),
            SIGNAL(current_group_changed(DplDevice::GroupPointer)),
            this, SLOT(do_group_changed(DplDevice::GroupPointer)));
    do_group_changed(DplDevice::Device::instance()->current_group());
}

void FocalPointMenu::do_group_changed(const DplDevice::GroupPointer &group)
{
    if (m_focallawer) {
        disconnect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
                   SIGNAL(focus_changed(DplFocallaw::FocusPointer)),
                   this, SLOT(do_focus_changed(DplFocallaw::FocusPointer)));
    }

    m_focallawer = group->focallawer();
    do_focus_changed(m_focallawer->focus());

    connect(static_cast<DplFocallaw::Focallawer *>(m_focallawer.data()),
            SIGNAL(focus_changed(DplFocallaw::FocusPointer)),
            this, SLOT(do_focus_changed(DplFocallaw::FocusPointer)));
}

void FocalPointMenu::do_focus_changed(const DplFocallaw::FocusPointer &focus)
{
    if (m_focus) {
        if (m_focus->mode() == DplFocallaw::Focus::TRUE_DEPTH) {
            disconnect(static_cast<DplFocallaw::TrueDepthFocus *>(m_focus.data()),
                       SIGNAL(depth_changed(float)),
                       this, SLOT(update_offsetStartItem()));
        } else if (m_focus->mode() == DplFocallaw::Focus::HALF_PATH) {
            disconnect(static_cast<DplFocallaw::HalfPathFocus *>(m_focus.data()),
                       SIGNAL(radius_changed(float)),
                       this, SLOT(update_offsetStartItem()));
        } else if (m_focus->mode() == DplFocallaw::Focus::PROJECTION) {
            disconnect(static_cast<DplFocallaw::ProjectionFocus *>(m_focus.data()),
                       SIGNAL(offset_changed(float)),
                       this, SLOT(update_offsetStartItem()));
        } else if (m_focus->mode() == DplFocallaw::Focus::FOCAL_PLANE) {
            DplFocallaw::FocalPlaneFocus *focus = m_focus.staticCast<DplFocallaw::FocalPlaneFocus>().data();
            disconnect(focus, SIGNAL(begin_offset_changed(float)),
                       this, SLOT(update_offsetStartItem()));
            disconnect(focus, SIGNAL(end_offset_changed(float)),
                       this, SLOT(update_offsetEndItem()));
            disconnect(focus, SIGNAL(begin_depth_changed(float)),
                       this, SLOT(update_depthStartItem()));
            disconnect(focus, SIGNAL(end_depth_changed(float)),
                       this, SLOT(update_depthEndItem()));
        }
    }

    m_focus = focus;
    update_typeItem();
    update_offsetStartItem();
    update_offsetEndItem();
    update_depthStartItem();
    update_depthEndItem();

    if (m_focus->mode() == DplFocallaw::Focus::TRUE_DEPTH) {
        connect(static_cast<DplFocallaw::TrueDepthFocus *>(m_focus.data()),
                SIGNAL(depth_changed(float)),
                this, SLOT(update_offsetStartItem()));
    } else if (m_focus->mode() == DplFocallaw::Focus::HALF_PATH) {
        connect(static_cast<DplFocallaw::HalfPathFocus *>(m_focus.data()),
                SIGNAL(radius_changed(float)),
                this, SLOT(update_offsetStartItem()));
    } else if (m_focus->mode() == DplFocallaw::Focus::PROJECTION) {
        connect(static_cast<DplFocallaw::ProjectionFocus *>(m_focus.data()),
                SIGNAL(offset_changed(float)),
                this, SLOT(update_offsetStartItem()));
    } else if (m_focus->mode() == DplFocallaw::Focus::FOCAL_PLANE) {
        DplFocallaw::FocalPlaneFocus *focus = m_focus.staticCast<DplFocallaw::FocalPlaneFocus>().data();
        connect(focus, SIGNAL(begin_offset_changed(float)),
                this, SLOT(update_offsetStartItem()));
        connect(focus, SIGNAL(end_offset_changed(float)),
                this, SLOT(update_offsetEndItem()));
        connect(focus, SIGNAL(begin_depth_changed(float)),
                this, SLOT(update_depthStartItem()));
        connect(focus, SIGNAL(end_depth_changed(float)),
                this, SLOT(update_depthEndItem()));
    }
}

void FocalPointMenu::update_typeItem()
{
    disconnect(m_typeItem, SIGNAL(value_changed(int)),
               this, SLOT(do_typeItem_changed(int)));

    m_typeItem->clear();
    m_typeItem->add_item(tr("Half Path"));
    m_typeItem->add_item(tr("True Depth"));
    m_typeItem->add_item(tr("Projection"));
    m_typeItem->add_item(tr("Focal Plane"));
    m_typeItem->add_item(tr("DDF"));
    m_typeItem->set_current_index(m_focus->mode());

    connect(m_typeItem, SIGNAL(value_changed(int)),
            this, SLOT(do_typeItem_changed(int)));
}

void FocalPointMenu::update_offsetStartItem()
{
    if (m_focus->mode() == DplFocallaw::Focus::TRUE_DEPTH) {
        m_offsetStartItem->set_title(tr("Depth"));
        m_offsetStartItem->set_value(m_focus.staticCast<DplFocallaw::TrueDepthFocus>()->depth());
    } else if (m_focus->mode() == DplFocallaw::Focus::HALF_PATH) {
        m_offsetStartItem->set_title(tr("Radius"));
        m_offsetStartItem->set_value(m_focus.staticCast<DplFocallaw::HalfPathFocus>()->radius());
    } else if (m_focus->mode() == DplFocallaw::Focus::PROJECTION) {
        m_offsetStartItem->set_title(tr("Offset"));
        m_offsetStartItem->set_value(m_focus.staticCast<DplFocallaw::ProjectionFocus>()->offset());
    } else if (m_focus->mode() == DplFocallaw::Focus::FOCAL_PLANE) {
        m_offsetStartItem->set_title(tr("Offset Start"));
        m_offsetStartItem->set_value(m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->begin_offset());
    }
}

void FocalPointMenu::update_offsetEndItem()
{
    if (m_focus->mode() != DplFocallaw::Focus::FOCAL_PLANE) {
        m_offsetEndItem->hide();
        return;
    }
    m_offsetEndItem->show();
    m_offsetEndItem->set_value(m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->end_offset());
}

void FocalPointMenu::update_depthStartItem()
{
    if (m_focus->mode() != DplFocallaw::Focus::FOCAL_PLANE) {
        m_depthStartItem->hide();
        return;
    }

    m_depthStartItem->show();
    m_depthStartItem->set_value(m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->begin_depth());
}

void FocalPointMenu::update_depthEndItem()
{
    if (m_focus->mode() != DplFocallaw::Focus::FOCAL_PLANE) {
        m_depthEndItem->hide();
        return;
    }

    m_depthEndItem->show();
    m_depthEndItem->set_value(m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->end_depth());
}

void FocalPointMenu::do_typeItem_changed(int i)
{
    if (i == m_focus->mode()) {
        return;
    }
    if (DplFocallaw::Focus::TRUE_DEPTH == i) {
        m_focallawer->set_focus(DplFocallaw::FocusPointer(new DplFocallaw::TrueDepthFocus));
    } else if (DplFocallaw::Focus::HALF_PATH == i) {
        m_focallawer->set_focus(DplFocallaw::FocusPointer(new DplFocallaw::HalfPathFocus));
    } else if (DplFocallaw::Focus::PROJECTION == i) {
        m_focallawer->set_focus(DplFocallaw::FocusPointer(new DplFocallaw::ProjectionFocus));
    } else if (DplFocallaw::Focus::FOCAL_PLANE == i) {
        m_focallawer->set_focus(DplFocallaw::FocusPointer(new DplFocallaw::FocalPlaneFocus));
    }
}

void FocalPointMenu::do_offsetStartItem_changed(double val)
{
    if (m_focus->mode() == DplFocallaw::Focus::TRUE_DEPTH) {
        m_focus.staticCast<DplFocallaw::TrueDepthFocus>()->set_depth(val);
    } else if (m_focus->mode() == DplFocallaw::Focus::HALF_PATH) {
        m_focus.staticCast<DplFocallaw::HalfPathFocus>()->set_radius(val);
    } else if (m_focus->mode() == DplFocallaw::Focus::PROJECTION) {
        m_focus.staticCast<DplFocallaw::ProjectionFocus>()->set_offset(val);
    } else if (m_focus->mode() == DplFocallaw::Focus::FOCAL_PLANE) {
        m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->set_begin_offset(val);
    }
}

void FocalPointMenu::do_offsetEndItem_changed(double val)
{
    m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->set_end_offset(val);
}

void FocalPointMenu::do_depthStartItem_changed(double val)
{
    m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->set_begin_depth(val);
}

void FocalPointMenu::do_depthEndItem_changed(double val)
{
    m_focus.staticCast<DplFocallaw::FocalPlaneFocus>()->set_end_depth(val);
}

void FocalPointMenu::changeEvent(QEvent *e)
{
    if (e->type() == QEvent::LanguageChange) {
        update_typeItem();
        update_offsetStartItem();
        update_offsetEndItem();
        update_depthStartItem();
        update_depthEndItem();
        return;
    }
    BaseMenu::changeEvent(e);
}

}
