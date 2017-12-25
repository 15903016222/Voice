#include "fft_result.h"

FFTResult *FFTResult::s_instance = NULL;

FFTResult::FFTResult(QObject *parent) : QObject(parent)
{
    memset(&m_result, 0, sizeof(FFTCalculator::S_FFT_result));
}

FFTResult *FFTResult::instance()
{
    if(NULL == s_instance) {
        s_instance = new FFTResult;
    }
    return s_instance;
}

void FFTResult::set_result(const FFTCalculator::S_FFT_result &result)
{
    m_result = result;
}

const FFTCalculator::S_FFT_result &FFTResult::result()
{
    return m_result;
}
