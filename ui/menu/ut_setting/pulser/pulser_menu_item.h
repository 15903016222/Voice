#ifndef __PULSER_MENU_ITEM_H__
#define __PULSER_MENU_ITEM_H__

#include "../../menu_item/spin_menu_item.h"

#include <device/group.h>

class PulserMenuItem : public SpinMenuItem
{
    Q_OBJECT
public:
    explicit PulserMenuItem(QWidget *parent);

protected slots:
    void do_group_changed(const DplDevice::GroupPointer &group);
    void do_probe_changed(const DplFocallaw::ProbePointer &probe);

    void update_value(uint val);

    void do_value_changed(double val);

protected:
    void language_changed();

private:
    DplFocallaw::FocallawerPointer m_focallawer;
    DplFocallaw::PaProbePointer m_probe;
};

#endif // __PULSER_MENU_ITEM_H__
