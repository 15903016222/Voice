#ifndef __FOCALLAW_H__
#define __FOCALLAW_H__

#include <QObject>
#include <QSharedPointer>

namespace DplFocallaw {

class Focallaw;
typedef QSharedPointer<Focallaw> FocallawPointer;

class Focallaw : public QObject
{
    Q_OBJECT
public:
    explicit Focallaw(QObject *parent = 0) : QObject(parent) {;}

    int beam_qty() const { return 1;}

signals:
    void beam_qty_changed(int qty);
};

} // namespace Dpl

#endif /* end of include guard */
