#ifndef SPI_H
#define SPI_H

#include <QIODevice>
#include <QFile>
class Spi : public QFile
{
    Q_OBJECT
public:
    enum SpiMode {
        /* CPHA|CPOL */
        MODE0 = (0|0),
        MODE1 = (0|1),
        MODE2 = (2|0),
        MODE3 = (2|1)
    };

    Spi():QFile() {}
//    bool open()
    bool set_mode(SpiMode mode);
    SpiMode mode();

private:
};

#endif // SPI_H
