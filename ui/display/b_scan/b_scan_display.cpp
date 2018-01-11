#include "b_scan_display.h"

#include <device/device.h>

#include "../base/scan_view.h"
#include "../base/scan_scene.h"
#include "../color_bar/color_bar.h"
#include "../ruler/ruler.h"
#include "../cursor/ut_ref_cursor_item.h"
#include "../cursor/ut_meas_cursor_item.h"

#include <QLabel>

BscanDisplay::BscanDisplay(const DplDevice::GroupPointer &grp, QWidget *parent) :
    ScanDisplay(parent),
    m_group(grp),
    m_bscanItem(new BscanItem(grp)),
    m_utRefCursorItem(new UtRefCursorItem(grp, Qt::Vertical)),
    m_utMeasCursorItem(new UtMeasCursorItem(grp, Qt::Vertical))
{
    m_scene->addItem(m_bscanItem);
    m_scene->addItem(m_utRefCursorItem);
    m_scene->addItem(m_utMeasCursorItem);

    m_colorBar->set_palette(DplDevice::Device::instance()->display()->palette());
    m_titleLabel->setText(QString("B-Scan|Grp") + QString::number(m_group->index() + 1));
}

BscanDisplay::~BscanDisplay()
{
}

void BscanDisplay::resize_event(const QSize &size)
{
    QSize s;
    if (m_view->orientation() == Qt::Vertical) {
        s.setHeight(size.width());
        s.setWidth(size.height());
    } else {
        s = size;
    }
    m_scene->setSceneRect(-s.width()/2, -s.height()/2,
                          s.width(), s.height());
    m_bscanItem->set_size(s);
    m_utRefCursorItem->set_size(s);
    m_utMeasCursorItem->set_size(s);
}

