#include "ut_menu_item.h"

#include <global.h>

#include "../../../tool/tool.h"

UtMenuItem::UtMenuItem(QWidget *parent, const QString &title) :
    CursorMenuItem(parent, title)
{
    set_decimals(2);
    set_step(0.01);
}

void UtMenuItem::update_unit(DplDevice::Group::UtUnit type)
{
    if (type == DplDevice::Group::Time) {
        set_unit(US_STR);
    } else {
        set_unit(MM_STR);
    }
    update_range();
}

void UtMenuItem::update_range()
{
    set_range(Tool::cnf_to_display(group(), group()->sample()->start()),
              Tool::cnf_to_display(group(), group()->sample()->start()
                                   + group()->sample()->range()));
    update_value();
}

void UtMenuItem::disconnect_group(const DplDevice::GroupPointer &group)
{
    disconnect(static_cast<DplDevice::Group *>(group.data()),
               SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
               this, SLOT(update_unit(DplDevice::Group::UtUnit)));
    disconnect(static_cast<DplUt::Sample *>(group->sample().data()),
               SIGNAL(start_changed(float)),
               this, SLOT(update_range()));
    disconnect(static_cast<DplUt::Sample *>(group->sample().data()),
               SIGNAL(range_changed(float)),
               this, SLOT(update_range()));
    CursorMenuItem::disconnect_group(group);
}

void UtMenuItem::connect_group(const DplDevice::GroupPointer &group)
{
    update_unit(group->ut_unit());

    connect(static_cast<DplDevice::Group *>(group.data()),
            SIGNAL(ut_unit_changed(DplDevice::Group::UtUnit)),
            this, SLOT(update_unit(DplDevice::Group::UtUnit)));
    connect(static_cast<DplUt::Sample *>(group->sample().data()),
            SIGNAL(start_changed(float)),
            this, SLOT(update_range()));
    connect(static_cast<DplUt::Sample *>(group->sample().data()),
            SIGNAL(range_changed(float)),
            this, SLOT(update_range()));

    CursorMenuItem::connect_group(group);
}
