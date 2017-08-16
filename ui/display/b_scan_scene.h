#ifndef __B_SCAN_SCENE_H__
#define __B_SCAN_SCENE_H__

#include <QGraphicsScene>
#include <QVector>

#include <display/palette_color.h>
#include <source/beams.h>

class BscanScene : public QGraphicsScene
{
    Q_OBJECT

public:


    enum E_BscanDirection{
        HORIZONTAL,
        VERTICAL
    };

    struct WaveIndex {
        QByteArray  wave;
        int         index;
    };


    explicit BscanScene(const DplDisplay::PaletteColorPointer &palette, QObject *parent = 0);
    void show_wave(DplSource::BeamPointer beamPointer);
    void reset();
    bool set_pix_per_beam(double ratio);
    inline void set_direction(E_BscanDirection direction) { m_direction = direction; }
    inline E_BscanDirection direction() { return m_direction; }

signals:
    void one_beam_show_successed();

public slots:
    void set_size(const QSize &size);


protected:
    void drawBackground(QPainter *painter, const QRectF &rect);
    virtual void draw_beams();

    QImage                          *m_image;
    DplDisplay::PaletteColorPointer m_palette;
    DplSource::BeamPointer          m_beamPointer;
    QSize                           m_size;
    int                             m_currentIndex;
    double                          m_pixPerBeamRatio;
    static const int COMPRESS_TYPE = 0;
    E_BscanDirection                m_direction;
    QVector<WaveIndex>            m_waveVect;


private:
    /**
     * @brief draw_horizontal_beam  B扫的水平显示
     * @param ratio                 每个像素代表多少beam中的多少个点数据
     * @param pixCount              每条beam占多少像素
     * @param maxIndex              最大的beam数，超出后滚动显示
     * @param align                 对齐数据（例子：width为20， ratio为3， 则align为 width % ratio = 2）
     */
    void draw_horizontal_beam(float ratio, int pixCount, int maxIndex, int align);

    /**
     * @brief draw_vertical_beam    B扫的垂直显示
     * @param ratio                 每个像素代表多少beam中的多少个点数据
     * @param pixCount              每条beam占多少像素
     * @param maxIndex              最大的beam数，超出后滚动显示
     * @param align                 对齐数据（例子：width为20， pixCount为3， 则align为 width % pixCount = 2）
     */
    void draw_vertical_beam(float ratio, int pixCount, int maxIndex, int align);

    /**
     * @brief reset_show 当显示大小改变，重新画B扫
     */
    void reset_show();

    void reset_draw_horizontal_beam(float ratio, int pixCount, int maxIndex, int align);
    void reset_draw_vertical_beam(float ratio, int pixCount, int maxIndex, int align);

};

#endif // __B_SCAN_SCENE_H__
