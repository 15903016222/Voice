/**
 * @file a_scan_scene.h
 * @brief A扫场景，显示A扫
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 
 * @date 2017-07-13
 */
#ifndef __A_SCAN_SCENE_H__
#define __A_SCAN_SCENE_H__

#include <QGraphicsScene>

class AscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit AscanScene(QObject *parent = 0);
};


#endif // __A_SCAN_SCENE_H__
