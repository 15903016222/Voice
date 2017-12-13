#include "scan_ruler.h"

ScanRuler::ScanRuler(MarkPostion pos, QWidget *parent):
    Ruler(pos, "(mm)", parent)
{
    set_scroll(true);
}
