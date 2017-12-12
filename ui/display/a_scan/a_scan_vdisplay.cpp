/**
 * @file a_scan_vdisplay.cpp
 * @brief A扫纵向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-19
 */
#include "global.h"
#include "a_scan_vdisplay.h"

#include "../ruler/ruler.h"

#include <qmath.h>

AscanVDisplay::AscanVDisplay(const DplDevice::GroupPointer &group,
                             QWidget *parent) :
    AscanDisplay(group, Qt::Vertical, parent)
{  
    /* ruler setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_left_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_left_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_left_ruler()));

    update_left_ruler();

    m_bottomRuler->set_prec(0);
    m_bottomRuler->set_range(100, 0);
    m_bottomRuler->set_unit("(%)");
    m_bottomRuler->set_background_color(QColor("#ffff7f"));
}

AscanVDisplay::~AscanVDisplay()
{
}

void AscanVDisplay::update_left_ruler()
{
    double start = m_group->sample()->start();
    double end = (start + m_group->sample()->range());

    start = Dpl::ns_to_us(start);
    end = Dpl::ns_to_us(end);

    DplDevice::Group::UtUnit unit = m_group->ut_unit();

    if (DplDevice::Group::Time == unit) {
        m_leftRuler->set_unit("(us)");
        m_leftRuler->set_background_color(QColor("#F9CCE2"));
    } else{
        m_leftRuler->set_unit("(mm)");
        start *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        start /= 2;
        end   *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        end /= 2;
        m_leftRuler->set_background_color(QColor("#f29cb1"));
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            m_leftRuler->set_background_color(QColor("#ff00ff"));
        }
    }
    m_leftRuler->set_range(start, end);

    m_leftRuler->update();
}
