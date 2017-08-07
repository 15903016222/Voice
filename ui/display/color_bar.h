#ifndef __COLOR_BAR_H__
#define __COLOR_BAR_H__

#include <QWidget>
#include <display/palette_color.h>

class ColorBar : public QWidget
{
    Q_OBJECT
public:
    explicit ColorBar(QWidget *parent = 0);

    /**
     * @brief set_palette   设置要显示调色板
     * @param palette       调色板
     */
    void set_palette(const DplDisplay::PaletteColorPointer &palette);

protected:
    void paintEvent(QPaintEvent *e);

private:
    DplDisplay::PaletteColorPointer m_palette;
};

inline void ColorBar::set_palette(const DplDisplay::PaletteColorPointer &palette)
{
    m_palette = palette;
    update();
}

#endif // __COLOR_BAR_H__
