#ifndef FFTCALCULATOR_H
#define FFTCALCULATOR_H

class FFTCalculator
{

public:
    struct S_FFT_result {
        double min6dbFrequency;
        double max6dbFrequency;
        double min20dbFrequency;
        double max20dbFrequency;
        double bandWidth6dbPercent;
        double bandWidth20dbPercent;
        double bandWidth6db;
        double bandWidth20db;
        double centerFrequency6db;
        double centerFrequency20db;
        double peakFrequency;
        const unsigned char *data;
    };

    struct S_Complex
    {
        double real;
        double img;
    };

    struct S_Data
    {
        unsigned char *data;
        int            len;
    };


    FFTCalculator();
    ~FFTCalculator();

    bool execute(int len, unsigned char *data, int targetDataLen);
    const S_FFT_result &get_result() const;

    static const int s_NUM = 1024;

private:
    S_FFT_result    m_fftResult;
    S_Complex       m_wn[s_NUM];
    S_Complex       m_data[s_NUM];
    int             m_dataLen;
    unsigned char   m_returnData[s_NUM];

    void init_data(unsigned char *data);
    void complex_data();
    void rearrange_data();
    void calculate_result(int targetDataLen);

    void fft_mul(const S_Complex &a, const S_Complex &b, S_Complex &c);
    void fft_sub(const S_Complex &a, const S_Complex &b, S_Complex &c);
    void fft_add(const S_Complex &a, const S_Complex &b, S_Complex &c);

};

#endif // FFTCALCULATOR_H
