#ifndef __SCAN_DISPLAY_H__
#define __SCAN_DISPLAY_H__

#include <QWidget>

class ColorBar;
class Ruler;
class QLabel;
class QLayout;
class ScanDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ScanDisplay(QWidget *parent = 0);

signals:

public slots:

protected:
    QLabel *m_titleLabel;
    ColorBar *m_colorBar;
    Ruler *m_leftRuler;
    Ruler *m_rightRuler;
    Ruler *m_bottomRuler;
    QLayout *m_scanLayout;
};

#endif // __SCAN_DISPLAY_H__
