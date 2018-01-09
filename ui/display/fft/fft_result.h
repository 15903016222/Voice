#ifndef __FFT_RESULT_H__
#define __FFT_RESULT_H__

#include <QObject>
#include "fft_calculator.h"

class FFTResult : public QObject
{
    Q_OBJECT
public:
    explicit FFTResult(QObject *parent = 0);

    static FFTResult *instance();
    void set_result(const FFTCalculator::S_FFT_result &result);
    const FFTCalculator::S_FFT_result &result();
    inline void set_enable(bool flag) { m_enable = flag; }
    inline bool enable() { return m_enable; }

private:
    FFTCalculator::S_FFT_result m_result;
    bool m_enable;

};

#endif // __FFT_RESULT_H__
