#include "fft_calculator.h"

#include <string.h>
#include <math.h>
#include <QDebug>

#define PI 3.1415926535897931

static const double g_defaultReal = 128.0;
static const double g_defaultImg  = 0.0;
static const double g_totalMhz    = 100.0;

FFTCalculator::FFTCalculator():
    m_dataLen(0.0),
    m_MHzRatio(0.0)

{
    memset(&m_fftResult, 0, sizeof(S_FFT_result));
   /* 初始化变换核*/
    memset(&m_wn ,0 ,sizeof(S_Complex) * s_NUM);
    memset(&m_data ,0 ,sizeof(S_Complex) * s_NUM);
    memset(&m_returnData ,100 , sizeof(unsigned char) * s_NUM);

    for(int i = 0; i < s_NUM; ++i) {
       m_wn[i].real = cos(2 * PI / s_NUM * i);
       m_wn[i].img  = -1 * sin(2 * PI / s_NUM * i);
    }
}

FFTCalculator::~FFTCalculator()
{

}

bool FFTCalculator::execute(int len, unsigned char *data, int targetDataLen, double dataMHz)
{
    memset(m_returnData, 0 , sizeof(unsigned char) * s_NUM);

    if(NULL == data) {
        return false;
    }

    m_dataLen = len;
    m_MHzRatio = dataMHz / (double)s_NUM;

    init_data(data);

    rearrange_data();

    complex_data();

    calculate_result(targetDataLen);

    return true;
}

const FFTCalculator::S_FFT_result &FFTCalculator::get_result() const
{
    return m_fftResult;
}

void FFTCalculator::init_data(unsigned char *data)
{
    for(int i = 0; i < FFTCalculator::s_NUM; ++i) {
        if(i < m_dataLen) {
            m_data[i].real = data[i];
            m_data[i].img  = g_defaultImg;
        } else {
            m_data[i].real = g_defaultReal;
            m_data[i].img  = g_defaultImg;
        }
    }
}

void FFTCalculator::complex_data()
{
    int i,j,k,l;
    S_Complex up,down,product;
    double log2n = log2(s_NUM);

    for(i = 0; i < log2n; ++i) {
        /* 一级蝶形运算 */
        l = 1 << i;
        for(j = 0 ;j < s_NUM ;j += 2 * l) {
            /* 一组蝶形运算 */
            for(k = 0 ;k < l ;k++) {
                /* 一个蝶形运算 */
                fft_mul(m_data[j + k + l] ,m_wn[s_NUM * k / 2 / l], product);
                fft_add(m_data[j + k] ,product , up);
                fft_sub(m_data[j + k] ,product , down);
                m_data[j + k] = up;
                m_data[j + k + l] = down;
            }
        }
    }
}

void FFTCalculator::rearrange_data()
{
    S_Complex temp;
    unsigned short j = 0;
    unsigned short k = 0;

    double log2n = log2(s_NUM);
    double t = log2n;

    for(int i = 0; i < s_NUM; ++i) {
        k = i;
        j = 0;
        t = log2n;

        while((t--) > 0) {
            j <<= 1;
            j |= (k & 1);
            k >>= 1;
        }

        if(j > i) {
            temp        = m_data[i];
            m_data[i] 	= m_data[j];
            m_data[j] 	= temp;
        }
    }
}

void FFTCalculator::calculate_result(int targetDataLen)
{
    double  max = 0;
    int     peakPoint = 0;
    double  temp;
    m_returnData[0] = 0; /* 丢掉直流部分 */

    for(int i = 1; i < targetDataLen; ++i) {
        if((m_data[i].img < 0.0001)
            && (m_data[i].img > -0.0001) ) {
            temp = m_data[i].real;
        } else {
            temp = sqrt(pow(m_data[i].real, 2) + pow(m_data[i].img, 2));
        }

        if(temp > 0) {
            temp = 16 * log2(temp);
            if(temp > max) {
                max = temp;
                peakPoint = i;
            }

            if(temp > 255) {
                m_returnData[i] = 255;
            } else {
                m_returnData[i] = temp;
            }
        } else {
            m_returnData[i] = 0;
        }
    }

    /* 计算衰减 */
    temp = 16 * log2(10) / 20;
    double db6PeakPoint = m_returnData[peakPoint] - 6 * temp;
    double db20PeakPoint = m_returnData[peakPoint] - 20 * temp;
    unsigned char data_db6 =  db6PeakPoint > 0 ? db6PeakPoint : 0;
    unsigned char data_db20 = db20PeakPoint> 0 ? db20PeakPoint : 0;

    /* 对应的位置，初始值，也是没找到的默认值 */
    int db6minPoint  = 1;
    int db6maxPoint  = m_dataLen;
    int db20minPoint = 1;
    int db20maxPoint = m_dataLen;


    for(int i = peakPoint; 0 < i; --i) {
        if(data_db6 > m_returnData[i]) {
            db6minPoint = i;
            break;
        }
    }

    for(int i = db6minPoint; i > 0; --i) {
        if(data_db20 > m_returnData[i]) {
            db20minPoint = i;
            break;
        }
    }

    for(int i = peakPoint; i < targetDataLen; ++i) {
        if(data_db6 > m_returnData[i]) {
            db6maxPoint = i;
            break;
        }
    }

    for(int i = db6maxPoint; i < targetDataLen; ++i) {
        if(data_db20 > m_returnData[i]) {
            db20maxPoint = i;
            break;
        }
    }

    m_fftResult.peakFrequency           = m_MHzRatio * peakPoint;
    m_fftResult.centerFrequency6db      = m_MHzRatio * (db6minPoint + db6maxPoint) / 2.0;
    m_fftResult.centerFrequency20db     = m_MHzRatio * (db20minPoint + db20maxPoint) / 2.0;
    m_fftResult.min6dbFrequency         = m_MHzRatio * db6minPoint;
    m_fftResult.min20dbFrequency        = m_MHzRatio * db20minPoint;
    m_fftResult.max6dbFrequency         = m_MHzRatio * db6maxPoint;
    m_fftResult.max20dbFrequency        = m_MHzRatio * db20maxPoint;
    m_fftResult.bandWidth6db            = m_MHzRatio * (db6maxPoint - db6minPoint);
    m_fftResult.bandWidth20db           = m_MHzRatio * (db20maxPoint - db20minPoint);
    m_fftResult.bandWidth6dbPercent     = (db6maxPoint > db6minPoint) ? peakPoint * 100.0 / (db6maxPoint - db6minPoint) : 0;
    m_fftResult.bandWidth20dbPercent    = (db20maxPoint > db20minPoint) ? peakPoint * 100.0 / (db20maxPoint - db20minPoint) : 0;
    m_fftResult.data                    = m_returnData;
    m_fftResult.MhzRatio                = m_MHzRatio;

}

void FFTCalculator::fft_mul(const FFTCalculator::S_Complex &a, const FFTCalculator::S_Complex &b, FFTCalculator::S_Complex &c)
{
    c.real  = a.real * b.real - a.img * b.img;
    c.img   = a.real * b.img + a.img * b.real;
}

void FFTCalculator::fft_sub(const FFTCalculator::S_Complex &a,const FFTCalculator::S_Complex &b, FFTCalculator::S_Complex &c)
{
    c.real  = a.real - b.real;
    c.img   = a.img - b.img;
}

inline void FFTCalculator::fft_add(const FFTCalculator::S_Complex &a, const FFTCalculator::S_Complex &b, FFTCalculator::S_Complex &c)
{
    c.real  = a.real + b.real;
    c.img   = a.img + b.img;
}
