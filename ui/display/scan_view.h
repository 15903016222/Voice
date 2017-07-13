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
};

#endif // __SCAN_VIEW_H__
