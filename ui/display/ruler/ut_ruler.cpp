#include "ut_ruler.h"

#include <global.h>

UtRuler::UtRuler(const DplDevice::GroupPointer &group,
                 MarkPostion position, QWidget *parent) :
    Ruler(position, "(mm)", parent),
    m_group(group)
{
    set_scroll(true);

    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this,
            SLOT(update()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this,
            SLOT(update()));

    update();
}

void UtRuler::update()
{
    double start = m_group->sample()->start();
    double end = (start + m_group->sample()->range());

    start = Dpl::ns_to_us(start);
    end = Dpl::ns_to_us(end);

    DplDevice::Group::UtUnit unit = m_group->ut_unit();

    if (DplDevice::Group::Time == unit) {
        set_unit("(us)");
        set_background_color(PalePinkColor);
    } else {
        set_unit("(mm)");
        start *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        start /= 2;
        end *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        end /= 2;
        set_background_color(PinkColor);
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            set_background_color(PurpleColor);
        }
    }

    set_range(start, end);

    Ruler::update();
}
