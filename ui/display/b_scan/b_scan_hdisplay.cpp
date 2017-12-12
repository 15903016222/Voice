#include "b_scan_hdisplay.h"

#include "../scan_view.h"

#include <source/scan.h>

BscanHDisplay::BscanHDisplay(const DplDevice::GroupPointer &grp, QWidget *parent)
    : BscanDisplay(grp, Qt::Horizontal, parent)
{
    init_ruler();
}


void BscanHDisplay::init_ruler()
{
    update_scan_type_ruler(m_bscanView->size());
    update_sound_path_ruler();

}
