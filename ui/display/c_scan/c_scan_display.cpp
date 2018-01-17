#include "c_scan_display.h"
#include "c_scan_item.h"

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../color_bar/color_bar.h"
#include "../cursor/scan_ref_cursor_item.h"
#include "../cursor/scan_meas_cursor_item.h"

#include <device/device.h>

#include <QLabel>

CscanDisplay::CscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    ScanDisplay(parent),
    m_group(grp),
    m_cscanItem(new CscanItem(grp)),
    m_scanRefCursorItem(new ScanRefCursorItem(grp->cursor(), Qt::Horizontal)),
    m_scanMeasCursorItem(new ScanMeasCursorItem(grp->cursor(), Qt::Horizontal))
{
    m_colorBar->set_palette(DplDevice::Device::instance()->display()->palette());
    m_titleLabel->setText(QString("C-Scan|Grp%1").arg(m_group->index()+1));

    m_scene->addItem(m_cscanItem);
    m_scene->addItem(m_scanRefCursorItem);
    m_scene->addItem(m_scanMeasCursorItem);
}

CscanDisplay::~CscanDisplay()
{
}

void CscanDisplay::resize_event(const QSize &size)
{
    QSize s;
    if (m_view->orientation() == Qt::Vertical) {
        s.setHeight(size.width());
        s.setWidth(size.height());
    } else {
        s = size;
    }
    m_scene->setSceneRect(0, 0, s.width(), s.height());
    m_cscanItem->set_size(s);
    m_scanRefCursorItem->set_size(s);
    m_scanMeasCursorItem->set_size(s);
}

