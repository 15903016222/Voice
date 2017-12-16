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

    void drawBackground(const QImage &image);

signals:
    void update_requested();

protected slots:
    void update();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    QPixmap m_pixmap;
};

inline void ScanScene::drawBackground(const QImage &image)
{
    m_pixmap = QPixmap::fromImage(image);
    emit update_requested();
}


#endif // __SCAN_SCENE_H__
