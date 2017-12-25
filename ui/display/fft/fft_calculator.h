#ifndef FFTCALCULATOR_H
#define FFTCALCULATOR_H

class FFTCalculator
{

public:
    struct S_FFT_result {
        double MhzRatio;
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

    /**
     * @brief execute       执行FFT计算
     * @param len           数据长度
     * @param data          需要FFT的数据
     * @param targetDataLen 目标数据长度
     * @param dataMHz       数据采样频率
     * @return
     */
    bool execute(int len, unsigned char *data, int targetDataLen, double dataMHz);

    /**
     * @brief get_result    获取FFT转换后结果
     * @return              结果
     */
    const S_FFT_result &get_result() const;

    static const int s_NUM = 1024;

private:
    S_FFT_result    m_fftResult;
    S_Complex       m_wn[s_NUM];
    S_Complex       m_data[s_NUM];
    int             m_dataLen;
    unsigned char   m_returnData[s_NUM];
    double          m_MHzRatio;

    /**
     * @brief init_data 初始化待处理数据，不足1024，后面补齐数据
     * @param data      待处理数据
     */
    void init_data(unsigned char *data);

    /**
     * @brief complex_data  进行FFT数据计算
     */
    void complex_data();

    /**
     * @brief rearrange_data 重组待计算的数据
     */
    void rearrange_data();

    /**
     * @brief calculate_result  计算FFT后数据结果
     * @param targetDataLen     要显示的数据长度
     */
    void calculate_result(int targetDataLen);

    /**
     * @brief fft_mul   数据相乘
     * @param a
     * @param b
     * @param c
     */
    void fft_mul(const S_Complex &a, const S_Complex &b, S_Complex &c);

    /**
     * @brief fft_sub   数据相减
     * @param a
     * @param b
     * @param c
     */
    void fft_sub(const S_Complex &a, const S_Complex &b, S_Complex &c);

    /**
     * @brief fft_add   数据相加
     * @param a
     * @param b
     * @param c
     */
    void fft_add(const S_Complex &a, const S_Complex &b, S_Complex &c);

};

#endif // FFTCALCULATOR_H
