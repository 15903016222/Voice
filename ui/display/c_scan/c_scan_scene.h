#ifndef __C_SCAN_SCENE_H__
#define __C_SCAN_SCENE_H__

#include <QGraphicsScene>

class CscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit CscanScene(QObject *parent = 0);
};

#endif // __C_SCAN_SCENE_H__
