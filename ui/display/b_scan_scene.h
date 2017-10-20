#ifndef __B_SCAN_SCENE_H__
#define __B_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <QVector>
#include <QSharedPointer>
#include <QReadWriteLock>

#include <display/palette_color.h>
#include <source/beams.h>
#include <source/axis.h>


class BscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BscanScene(QObject *parent = 0);
};

#endif // BSCANSCENE_H
