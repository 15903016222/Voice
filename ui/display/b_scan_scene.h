#ifndef __B_SCAN_SCENE_H__
#define __B_SCAN_SCENE_H__

#include <QGraphicsScene>

class BscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit BscanScene(QObject *parent = 0);
};

#endif // BSCANSCENE_H
