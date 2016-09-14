#ifndef __GPIO_H__
#define __GPIO_H__

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

    static Gpio* get_instance();
    static void destroyed();

    bool set(GpioPin pinNo, PinState state);

protected:
    explicit Gpio();
    virtual ~Gpio();

private:
    static Gpio *m_gpio;
    GpioPrivate *d;
};

inline Gpio* Gpio::get_instance()
{
    if (m_gpio == nullptr) {
        m_gpio = new Gpio();
    }
    return m_gpio;
}

inline void Gpio::destroyed()
{
    if (m_gpio) {
        delete m_gpio;
        m_gpio = nullptr;
    }
}

#endif
