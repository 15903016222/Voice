#include "b_scan_vdisplay.h"

#include "../scan_view.h"

#include <source/source.h>
#include <source/scan.h>

BscanVDisplay::BscanVDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, Qt::Vertical, parent)
{
    init_ruler();
}


void BscanVDisplay::init_ruler()
{
    update_scan_type_ruler(m_bscanView->size());

    update_sound_path_ruler();

}
