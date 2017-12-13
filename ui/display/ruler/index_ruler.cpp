#include "index_ruler.h"

IndexRuler::IndexRuler(MarkPostion position, QWidget *parent) :
    Ruler(position, "(mm)", parent)
{
    set_scroll(true);
}
