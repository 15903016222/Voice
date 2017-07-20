#include "tool.h"


double Tool::cnf_to_display(const DplDevice::GroupPointer &group, double val)
{
    if (group->ut_unit() == DplDevice::Group::Time) {
        val = Dpl::ns_to_us(val);
    } else {
        val = Dpl::ns_to_s(val) * group->sample()->velocity() / 2;
        val = Dpl::m_to_mm(val);
        if (group->ut_unit() == DplDevice::Group::TruePath) {
            val *= qCos(group->current_angle());
        }
    }
    return val;
}

double Tool::display_to_cnf(const DplDevice::GroupPointer &group, double val)
{
    if (group->ut_unit() == DplDevice::Group::Time) {
        val = Dpl::us_to_ns(val);
    } else {
        val = Dpl::mm_to_m(val);
        val = val * 2 / group->sample()->velocity();
        val = Dpl::s_to_ns(val);
        if (group->ut_unit() == DplDevice::Group::TruePath) {
            val /= qCos(group->current_angle());
        }
    }
    return val;
}

