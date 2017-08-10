#ifndef __S_SCAN_SCENE_H__
#define __S_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <display/palette_color.h>
#include <source/beams.h>

class SscanImage;
class SscanScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit SscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent = 0);

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
     * @brief show_wave 显示Beam组
     * @param beams     Beam组
     */
    void show_beams(const DplSource::BeamsPointer &beams);

protected:
    void drawBackground(QPainter *painter, const QRectF &rect);

private:
    SscanImage *m_image;
    DplDisplay::PaletteColorPointer m_palette;
    DplSource::BeamsPointer m_beams;
    QThread *m_thread;
};

inline void SscanScene::set_palette(const DplDisplay::PaletteColorPointer &palette)
{
    m_palette = palette;
}

#endif // __S_SCAN_SCENE_H__
