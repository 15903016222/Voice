#ifndef PHASCANIIDATE_H
#define PHASCANIIDATE_H


#include <QTimer>
#include "sourcedata.h"
#include "dmaoperate.h"

class PhascanIDate : public SourceData
{
    Q_OBJECT
public:
    PhascanIDate();
    ~PhascanIDate();
public:

    void adjust_scan_or_index_address(int dimension,int  scan,int index,int dataSize);
    void start_timer(){m_timer->start(get_delay_time());}
public slots:
    void timeoutFun();

private:
    static QMutex m_mutex;
    DmaOperate *m_dma_operate;
    QTimer *m_timer;
};

#endif // PHASCANIIDATE_H
