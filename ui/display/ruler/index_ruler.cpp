#include "index_ruler.h"

IndexRuler::IndexRuler(const DplDevice::GroupPointer &group, MarkPostion position, QWidget *parent) :
    Ruler(position, "(mm)", parent),
    m_group(group)
{
    set_background_color(PaleGreenColor);
    set_scroll(true);
}

void IndexRuler::update()
{
    Ruler::update();
}

void IndexRuler::resizeEvent(QResizeEvent *e)
{
    Ruler::resizeEvent(e);
}
