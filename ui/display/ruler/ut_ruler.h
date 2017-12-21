#ifndef __UT_RULER_H__
#define __UT_RULER_H__

#include "ruler.h"
#include <device/group.h>

class UtRuler : public Ruler
{
    Q_OBJECT
public:
    UtRuler(const DplDevice::GroupPointer &group, MarkPostion position=TOP, QWidget *parent=0);

protected slots:
    void update();

private:
    DplDevice::GroupPointer m_group;
};

#endif // __UT_RULER_H__
