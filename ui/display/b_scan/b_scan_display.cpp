#include "b_scan_display.h"

#include <device/device.h>

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../color_bar/color_bar.h"
#include "../ruler/ruler.h"

#include <QLabel>

BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    ScanDisplay(parent),
    m_bscanItem(new BscanItem(grp)),
    m_group(grp)
{
    m_scene->addItem(m_bscanItem);

    m_colorBar->set_palette(DplDevice::Device::instance()->display()->palette());
    m_titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));
}

BscanDisplay::~BscanDisplay()
{
}

void BscanDisplay::resize_event(const QSize &size)
{
    Q_UNUSED(size);
}

