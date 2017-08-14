#ifndef __PAINT_THREAD_H__
#define __PAINT_THREAD_H__

#include <QThread>

class PaintThread : public QThread
{
public:
    PaintThread(QObject *parent = 0);

signals:

protected:
    void run();
};

#endif // PAINT_THREAD_H
