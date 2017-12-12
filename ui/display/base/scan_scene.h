/**
 * @file scan_scene.h
 * @brief Scan场景
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-07-13
 */
#ifndef __SCAN_SCENE_H__
#define __SCAN_SCENE_H__

#include <QGraphicsScene>

class ScanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit ScanScene(QObject *parent = 0);
};


#endif // __SCAN_SCENE_H__
