#include <QDebug>

#include "../fpga_spi.h"

static void test_spi(int argc, char **argv);
static void test_fpga_spi(int argc, char **argv);

int main(int argc, char *argv[])
{
    test_fpga_spi(argc, argv);
}

void test_fpga_spi(int argc, char **argv)
{
    char msg[800];
    ::memset(msg, 0xbb, sizeof(msg));

    int num = 800;

    if (argc < 2) {
        qWarning()<<"test_spi [device] [data num]";
        exit(-1);
    }

    if (argv[2] != NULL) {
        num = atoi(argv[2]);
        qDebug()<<"num="<<num;
    }
    FpgaSpi *spi = FpgaSpi::get_spi();
    qDebug("Mode[%d] Bits[%d] Speed[%dkHz] LSB_First[%d]",
           spi->mode(), spi->bits_per_word(), spi->speed()/1000, spi->is_lsb_first());

    spi->write((char *)&msg, num);
}

void test_spi(int argc, char **argv)
{
//    char msg[] = {0xaa, 0xbb, 0xcc, 0xdd, 'a', 'b', 'c', 'd', 1, 2, 3, 4};
//    quint32 msg = 0xaabbccdd;
    char msg[800];
    ::memset(msg, 0xbb, sizeof(msg));

    int num = 800;

    if (argc < 2) {
        qDebug()<<"test_spi [device] [data_num]";
        exit(1);
    }

    if (argv[2] != NULL) {
        num = atoi(argv[2]);
        qDebug()<<"num = "<<num;
    }

    Spi *m_spi = new Spi();

    if ( ! m_spi->open(argv[1]) ) {
        qDebug()<<"open"<<argv[1]<<"failed";
        exit(1);
    }

    if ( ! m_spi->set_mode(Spi::MODE3) ) {
        qDebug()<<"set mode failed";
        exit(1);
    }

    if ( ! m_spi->set_bits_per_word(32)) {
        qDebug()<<"set bits per word failed";
        exit(1);
    }

    if ( ! m_spi->set_speed(500*1000)) {
        qDebug()<<"set max speed failed";
        exit(1);
    }

//    if ( ! m_spi->set_lsb_first(false) ) {
//        qDebug()<<"set lsb first failed";
//        return -1;
//    }

    qDebug("Mode[%d] Bits[%d] Speed[%dkHz] LSB_First[%d]",
           m_spi->mode(), m_spi->bits_per_word(), m_spi->speed()/1000, m_spi->is_lsb_first());

    m_spi->write((char *)&msg, num);
}
