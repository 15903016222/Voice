#ifndef __FFT_H_DISPLAY_H__
#define __FFT_H_DISPLAY_H__

#include <ui/display/fft_display.h>

class FFTHDisplay : public FFTDisplay
{
public:
    FFTHDisplay(const DplDevice::GroupPointer &group,
                QWidget *parent = 0);

private:
    void update_bottom_ruler();
};

#endif // __FFT_H_DISPLAY_H__
