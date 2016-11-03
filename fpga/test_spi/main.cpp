#include <QCoreApplication>
#include <QDebug>

#include <unistd.h>

#include "../spi.h"

int main(int argc, char *argv[])
{
//    char msg[] = {0xaa, 0xbb, 0xcc, 0xdd, 'a', 'b', 'c', 'd', 1, 2, 3, 4};
    quint32 msg = 0xaabbccdd;

    QCoreApplication a(argc, argv);

    if (argc < 2) {
        qDebug()<<"test_spi [device]";
        return -1;
    }

    Spi *m_spi = new Spi();

    if ( ! m_spi->open(argv[1]) ) {
        qDebug()<<"open"<<argv[1]<<"failed";
        return -1;
    }

    if ( ! m_spi->set_mode(Spi::MODE3) ) {
        qDebug()<<"set mode failed";
        return -1;
    }

    if ( ! m_spi->set_bits_per_word(32)) {
        qDebug()<<"set bits per word failed";
        return -1;
    }

    if ( ! m_spi->set_speed(500*1000)) {
        qDebug()<<"set max speed failed";
        return -1;
    }

//    if ( ! m_spi->set_lsb_first(false) ) {
//        qDebug()<<"set lsb first failed";
//        return -1;
//    }

    qDebug("Mode[%d] Bits[%d] Speed[%dkHz] LSB_First[%d]",
           m_spi->mode(), m_spi->bits_per_word(), m_spi->speed()/1000, m_spi->is_lsb_first());

    m_spi->write((char *)&msg, sizeof(msg));

    return 0;
}
