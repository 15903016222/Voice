#include "fft_result.h"

FFTResult::FFTResult(QObject *parent) : QObject(parent),
    m_enable(false)
{
    memset(&m_result, 0, sizeof(FFTCalculator::S_FFT_result));
}

FFTResult *FFTResult::instance()
{
    static FFTResult *instance = new FFTResult;
    return instance;
}

void FFTResult::set_result(const FFTCalculator::S_FFT_result &result)
{
    m_result = result;
}

const FFTCalculator::S_FFT_result &FFTResult::result()
{
    return m_result;
}
