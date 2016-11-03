#include "fpga_spi.h"

FpgaSpi *FpgaSpi::s_spi = NULL;
QMutex FpgaSpi::s_mutex;

FpgaSpi *FpgaSpi::get_spi(void)
{
    QMutexLocker l(&s_mutex);
    if (s_spi == NULL) {
        s_spi = new FpgaSpi();
    }
    return s_spi;
}

FpgaSpi::FpgaSpi()
{

#ifdef PHASCAN
        s_spi->open("/dev/spidev1.0");
        s_spi->set_mode(Spi::MODE0);
        Gpio *gpio = Gpio::get_gpio();
        gpio->set(Gpio::PIN_61, Gpio::LOW);
        gpio->set(Gpio::PIN_61, Gpio::HIGHT);
        gpio->set(Gpio::PIN_43, Gpio::LOW);
        gpio->set(Gpio::PIN_43, Gpio::HIGHT);
#elif PHASCAN_II
        s_spi->open("/dev/spidev4.0");
        s_spi->set_mode(Spi::MODE3);
        s_spi->set_bits_per_word(32);
        s_spi->set_speed(500*1000);
#else
#error "Not Specify spi device"
#endif

}
