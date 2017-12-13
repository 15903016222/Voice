#ifndef __S_SCAN_SCENE_H__
#define __S_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <QReadWriteLock>

#include <device/group.h>
#include <display/palette_color.h>
#include <source/beams.h>

class SscanImage;
class SscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SscanScene(const DplDevice::GroupPointer &grp, const DplDisplay::PaletteColorPointer &palette);
    ~SscanScene();

    /**
     * @brief set_palette   设置调色板
     * @param palette       调色板
     */
    void set_palette(const DplDisplay::PaletteColorPointer &palette);

public slots:
    /**
     * @brief set_size  设置大小
     * @param size      大小
     */
    void set_size(const QSize &size);

    /**
     * @brief set_beams 设置显示Beam组数据
     * @param beams     Beam组
     */
    void set_beams(const DplSource::BeamsPointer &beams);

signals:
    void image_changed();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    SscanImage *m_image;
    QReadWriteLock m_rwLock;
    DplDisplay::PaletteColorPointer m_palette;
    DplSource::BeamsPointer m_beams;
    QPixmap m_pixmap;
    DplDevice::GroupPointer m_group;
};

inline void SscanScene::set_palette(const DplDisplay::PaletteColorPointer &palette)
{
    m_palette = palette;
}

#endif // __S_SCAN_SCENE_H__