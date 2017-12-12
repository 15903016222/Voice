/**
 * @file a_scan_hdisplay.cpp
 * @brief A扫横向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */

#include "global.h"
#include "a_scan_hdisplay.h"
#include "a_scan_scene.h"
#include "tcg_item.h"
#include "wave_item.h"

#include "../ruler/ruler.h"

AscanHDisplay::AscanHDisplay(const DplDevice::GroupPointer &group,
                             QWidget *parent) :
    AscanDisplay(group, parent)
{
    /* ruler setting */
    connect(static_cast<DplDevice::Group *>(m_group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this,
            SLOT(update_bottom_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(start_changed(float)),
            this,
            SLOT(update_bottom_ruler()));
    connect(static_cast<DplUt::Sample *>(m_group->sample().data()),
            SIGNAL(range_changed(float)),
            this,
            SLOT(update_bottom_ruler()));

    m_bottomRuler->set_scroll(true);
    update_bottom_ruler();

    m_leftRuler->set_prec(0);
    m_leftRuler->set_range(100, 0);
    m_leftRuler->set_unit("(%)");
    m_leftRuler->set_background_color(QColor("#ffff7f"));
}

AscanHDisplay::~AscanHDisplay()
{

}

void AscanHDisplay::do_size_changed(const QSize &size)
{
    m_scene->setSceneRect(-size.width()/2, -size.height()/2,
                               size.width(), size.height());
    m_waveItem->set_size(size);
    m_tcgItem->set_size(size);

    AscanDisplay::do_size_changed(size);
}

void AscanHDisplay::update_bottom_ruler()
{
    double start = m_group->sample()->start();
    double end = (start + m_group->sample()->range());

    start = Dpl::ns_to_us(start);
    end = Dpl::ns_to_us(end);

    DplDevice::Group::UtUnit unit = m_group->ut_unit();

    if (DplDevice::Group::Time == unit) {
        m_bottomRuler->set_unit("(us)");
        m_bottomRuler->set_background_color(QColor("#F9CCE2"));
    } else {
        m_bottomRuler->set_unit("(mm)");
        start *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        start /= 2;
        end *= m_group->focallawer()->specimen()->velocity() * Dpl::m_to_mm(1.0) / Dpl::s_to_us(1);
        end /= 2;
        m_bottomRuler->set_background_color(QColor("#f29cb1"));
        if (DplDevice::Group::TruePath == unit) {
            start *= qCos(m_group->current_angle());
            end   *= qCos(m_group->current_angle());
            m_bottomRuler->set_background_color(QColor("#ff00ff"));
        }
    }

    m_bottomRuler->set_range(start, end);
}
