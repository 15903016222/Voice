/**
 * @file fpga_spi.h
 * @brief FpgaSpi 
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
#ifndef __FPGA_SPI_H__
#define __FPGA_SPI_H__

#include "spi.h"

#include <QMutex>

class FpgaSpi : public Spi
{
public:
    static FpgaSpi *get_spi(void);

    bool send(char *data, quint32 len) { QMutexLocker l(&s_mutex); return s_spi->write(data, len); }

protected:
    FpgaSpi();

private:
    static FpgaSpi *s_spi;
    static QMutex s_mutex;
};

#endif // __FPGA_SPI_H__
