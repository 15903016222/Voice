#include "c_scan_display.h"
#include "c_scan_item.h"

#include "../base_image_item.h"
#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../color_bar/color_bar.h"

#include <device/device.h>

#include <QLabel>

CscanDisplay::CscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    ScanDisplay(parent),
    m_group(grp),
    m_cscanItem(new CscanItem(grp))
{
    m_colorBar->set_palette(DplDevice::Device::instance()->display()->palette());
    m_titleLabel->setText(QString("C-Scan|Grp%1").arg(m_group->index()+1));

    m_scene->addItem(m_cscanItem);
}


CscanDisplay::~CscanDisplay()
{
}

void CscanDisplay::resize_event(const QSize &size)
{
    Q_UNUSED(size);
}

