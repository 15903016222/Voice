#ifndef __LINE_H__
#define __LINE_H__

#include <QWidget>

class Line : public QWidget
{
    Q_OBJECT
public:
    explicit Line(Qt::Orientation orientation = Qt::Vertical, QWidget *parent = 0);
    virtual ~Line();

    void set_orientation(Qt::Orientation orientation);

protected:
    void paintEvent(QPaintEvent *e);
};

#endif // __LINE_H__
