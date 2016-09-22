#ifndef __PROBE_H__
#define __PROBE_H__

#include <QString>

class Probe
{
public:
    enum ProbeType {
        UNKNOWN     = 0,
        CUSTOM      = 1,
        ANGLE_BEAM  = 3,
        CONTACT     = 5,
        IMMERSION   = 6
    };

    Probe(): m_type(UNKNOWN) {}

    ProbeType type() const { return m_type; }
    void set_type(ProbeType type) { m_type = type; }

    const QString& model() const { return m_model; }
    void set_model(const QString& model) { m_model = model; }

    const QString& serial() const { return m_serial; }
    void set_serial(const QString& serial) { m_serial = serial; }

    int elements_quantity() const { return m_elemQty; }
    void set_elements_quantity(int qty) { m_elemQty = qty; }

    int pitch() const { return m_pitch; }
    void set_pitch(int pitch) { m_pitch = pitch; }

    int freq() const { return m_freq; }
    void set_freq(int freq) { m_freq = freq; }

    int reference_point() const { return m_point; }
    void set_reference_point(int point)  { m_point = point; }

private:
    ProbeType m_type;
    QString m_model;
    QString m_serial;
    int m_elemQty;
    int m_pitch;           /* unit is 0.001mm */
    int m_freq;
    int m_point;
};

#endif // __PROBE_H__
