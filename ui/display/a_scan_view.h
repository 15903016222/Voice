/**
 * @file a_scan_view.h
 * @brief A扫视图
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_VIEW_H__
#define __A_SCAN_VIEW_H__

#include <QGraphicsView>

class AscanView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit AscanView(QWidget *parent = 0);
    ~AscanView();

protected:
    virtual void resizeEvent(QResizeEvent *event);
};


#endif // __A_SCAN_VIEW_H__
