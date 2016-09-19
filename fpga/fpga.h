#ifndef __FPGA_H__
#define __FPGA_H__

#include <QObject>
#include <QMutex>
#include <QAtomicPointer>

class Fpga : public QObject
{
    Q_OBJECT
public:
    static Fpga* get_fpga(void);
    virtual bool reset() = 0;

protected:
    Fpga() {}
//    Fpga(const Fpga& fpga){Q_UNUSED(fpga);}
//    Fpga & operator=(const Fpga &fpga) {Q_UNUSED(fpga);}
    virtual ~Fpga() {}

private:
    static QMutex m_mutex;
    static Fpga *m_fpga;
};

#endif // __FPGA_H__
