#include "amp_ruler.h"

AmpRuler::AmpRuler(MarkPostion position, QWidget *parent):
    Ruler(position, "%", parent)
{
    set_prec(0);
    set_range(0, 100);
}
