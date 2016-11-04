/**
 * @file fpga_spi.cpp
 * @brief FpgaSpi
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-04
 */
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
        open("/dev/spidev4.0");
        set_mode(Spi::MODE3);
        set_bits_per_word(32);
        set_speed(2000*1000);
#else
#error "Not Specify spi device"
#endif

}
