/**
 * @file scan_view.h
 * @brief scan视图
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __SCAN_VIEW_H__
#define __SCAN_VIEW_H__

#include <QGraphicsView>

class ScanView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ScanView(QWidget *parent = 0);
    ~ScanView();

    void set_orientation(Qt::Orientation orientation);

    Qt::Orientation orientation();

signals:
    void size_changed(const QSize &size);

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Qt::Orientation m_orientation;
};

inline Qt::Orientation ScanView::orientation()
{
    return m_orientation;
}

#endif // __SCAN_VIEW_H__
