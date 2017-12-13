#ifndef __INDEX_RULER_H__
#define __INDEX_RULER_H__

#include "ruler.h"

class IndexRuler : public Ruler
{
    Q_OBJECT
public:
    IndexRuler(MarkPostion position, QWidget *parent);
};

#endif // __INDEX_RULER_H__
