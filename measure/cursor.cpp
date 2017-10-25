/**
 * @file cursor.cpp
 * @brief 测量光标
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-10-20
 */
#include "cursor.h"

namespace DplMeasure {

class CursorPrivate
{
public:
    CursorPrivate() :
        m_r(0.0),
        m_m(0.0),
        m_ur(0.0),
        m_um(0.0),
        m_sr(0.0),
        m_sm(0.0),
        m_ir(0.0),
        m_im(0.0),
        m_visible(false)
    {}

    /* attributions */
    double m_r;      // Amplitude value at the Reference-cursor position
    double m_m;      // Amplitude value at the Measurement-cursor position
    double m_ur;     // Position of the Reference cursor on the ultrasound axis
    double m_um;     // Position of the Measurement cursor on the ultrasound axis
    double m_sr;     // Position of the Reference cursor on the scan axis
    double m_sm;     // Position of the Measurement cursor on the scan axis
    double m_ir;     // Position of the Reference cursor on the index axis
    double m_im;     // Position of the Measurement cursor on the index axis
    bool m_visible;
};

Cursor::Cursor(QObject *parent) : QObject(parent),
    d(new CursorPrivate)
{

}

Cursor::~Cursor()
{
    delete d;
}

double Cursor::amplitude_reference() const
{
    return d->m_r;
}

void Cursor::set_amplitude_reference(double val)
{
    if ( !qFuzzyCompare(val, d->m_r) ) {
        d->m_r = val;
        emit amplitude_reference_changed(val);
    }
}

double Cursor::amplitude_measurement() const
{
    return d->m_m;
}

void Cursor::set_amplitude_measurement(double val)
{
    if ( !qFuzzyCompare(val, d->m_m) ) {
        d->m_m = val;
        emit amplitude_measurement_changed(val);
    }
}

double Cursor::ultrasound_reference() const
{
    return d->m_ur;
}

void Cursor::set_ultrasound_reference(double val)
{
    if ( !qFuzzyCompare(val, d->m_ur) ) {
        d->m_ur = val;
        emit ultrasound_reference_changed(val);
    }
}

double Cursor::ultrasound_measurement() const
{
    return d->m_um;
}

void Cursor::set_ultrasound_measurement(double val)
{
    if ( !qFuzzyCompare(val, d->m_um )) {
        d->m_um = val;
        emit ultrasound_measurement_changed(val);
    }
}

double Cursor::scan_reference() const
{
    return d->m_sr;
}

void Cursor::set_scan_reference(double val)
{
    if ( !qFuzzyCompare(val, d->m_sr) ) {
        d->m_sr = val;
        emit scan_reference_changed(val);
    }
}

double Cursor::scan_measurement() const
{
    return d->m_sm;
}

void Cursor::set_scan_measurement(double val)
{
    if ( !qFuzzyCompare(val, d->m_sm) ) {
        d->m_sm = val;
        emit scan_measurement_changed(val);
    }
}

double Cursor::index_reference() const
{
    return d->m_ir;
}

void Cursor::set_index_reference(double val)
{
    if ( !qFuzzyCompare(val, d->m_ir)) {
        d->m_ir = val;
        emit index_reference_changed(val);
    }
}

double Cursor::index_measurement() const
{
    return d->m_im;
}

void Cursor::set_index_measurement(double val)
{
    if ( !qFuzzyCompare(val, d->m_im) ) {
        d->m_im = val;
        emit index_measurement_changed(val);
    }
}

bool Cursor::is_visible() const
{
    return d->m_visible;
}

void Cursor::set_visible(bool flag)
{
    if (flag != d->m_visible) {
        d->m_visible = flag;
        emit visible_changed(flag);
    }
}

}
