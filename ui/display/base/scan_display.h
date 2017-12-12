#ifndef __SCAN_DISPLAY_H__
#define __SCAN_DISPLAY_H__

#include <QWidget>
#include <QLayout>

class ColorBar;
class Ruler;
class QLabel;
class ScanView;
class ScanScene;
class QGraphicsItem;

class ScanDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit ScanDisplay(QWidget *parent = 0);

protected slots:
    virtual void resize_event(const QSize &size) = 0;

protected:
    QLabel *m_titleLabel;
    Ruler *m_leftRuler;
    Ruler *m_bottomRuler;
    Ruler *m_colorRuler;
    ColorBar *m_colorBar;
    ScanView *m_view;
    ScanScene *m_scene;
};

#endif // __SCAN_DISPLAY_H__
