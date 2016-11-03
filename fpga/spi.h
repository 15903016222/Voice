#ifndef __SPI_H__
#define __SPI_H__

#include <QTypeInfo>

class Spi
{
public:
    enum SpiMode {
        CPHA        = 0x01,     /* 采样的时钟相位 */
        CPOL        = 0x02,     /* 时钟信号起始相位,高或低电平 */
//        CS_HIGH     = 0x04,     /* 置位时，片选的有效信号为高电平 */
//        LSB_FIRST   = 0x08,     /* 发送时低比特在前 */
//        THREE_WIRE  = 0x10,     /* 输入输出信号使用同一根信号线 */
//        LOOP        = 0x20,     /* 回环模式 */
//        NO_CS       = 0x40,
//        READY       = 0x80,
//        TX_DUAL     = 0x100,
//        TX_DUAD     = 0x200,
//        RX_DUAL     = 0x400,
//        RX_DUAD     = 0x800,
        MODE0       = 0x00,
        MODE1       = MODE0|CPHA,
        MODE2       = CPOL|MODE0,
        MODE3       = CPOL|CPHA
    };

    Spi();
    ~Spi();

    bool open(const char *name);
    void close();
    bool is_open() const;

    Spi::SpiMode mode() const { return m_mode; }
    bool set_mode(SpiMode mode);

    quint8 bits_per_word() const { return m_bits; }
    bool set_bits_per_word(quint8 bits);

    quint32 speed() const { return m_speed; }
    bool set_speed(quint32 speed);

    bool is_lsb_first() const { return m_lsbFirst; }
    bool set_lsb_first(bool flag);

    bool write(char *data, quint32 len);

private:
    int m_fd;
    SpiMode m_mode;
    quint8 m_bits;
    quint32 m_speed;
    bool m_lsbFirst;
};

#endif // __SPI_H__
