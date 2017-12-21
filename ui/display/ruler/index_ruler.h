#ifndef __INDEX_RULER_H__
#define __INDEX_RULER_H__

#include "ruler.h"

#include <device/group.h>

class IndexRuler : public Ruler
{
    Q_OBJECT
public:
    IndexRuler(const DplDevice::GroupPointer &group, MarkPostion position, QWidget *parent);

public slots:
    void update();

protected:
    void resizeEvent(QResizeEvent *e);

private:
    DplDevice::GroupPointer m_group;
};

#endif // __INDEX_RULER_H__
