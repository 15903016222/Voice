#ifndef __GPIO_H__
#define __GPIO_H__

#include <QMutex>

struct GpioPrivate;

class Gpio
{
public:

    enum GpioPin {
#ifdef PHASCAN_II
#else  /* Phascan */
        PIN_43  = 0x6002,
        PIN_61  = 0x6000
#endif
    };

    enum PinState {
        LOW,
        HIGHT
    };

    static Gpio* get_gpio();
    static void destroy();

    bool set(GpioPin pinNo, PinState state);

protected:
    explicit Gpio();
    ~Gpio();

private:
    static QMutex m_mutex;
    static Gpio *m_gpio;
    GpioPrivate *d;
};

#endif
