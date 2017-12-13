#ifndef __SCAN_RULER_H__
#define __SCAN_RULER_H__

#include "ruler.h"

class ScanRuler : public Ruler
{
    Q_OBJECT
public:
    ScanRuler(MarkPostion pos, QWidget *parent);
};

#endif // __SCAN_RULER_H__
