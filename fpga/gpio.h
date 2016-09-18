#ifndef __GPIO_H__
#define __GPIO_H__

#include <QMutex>
#include <QAtomicPointer>

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

    static Gpio& get_gpio();

    bool set(GpioPin pinNo, PinState state);
    ~Gpio();

protected:
    explicit Gpio();

private:
    static QMutex m_mutex;
    static QAtomicPointer<Gpio> m_gpio;
    GpioPrivate *d;
};

#endif
