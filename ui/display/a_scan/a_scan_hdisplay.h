/**
 * @file a_scan_hdisplay.h
 * @brief A扫横向布局
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @date 2017-06-28
 */
#ifndef __A_SCAN_HDISPLAY_H__
#define __A_SCAN_HDISPLAY_H__

#include "a_scan_display.h"

class UtRuler;
class AmpRuler;

class AscanHDisplay : public AscanDisplay
{
    Q_OBJECT
public:
    explicit AscanHDisplay(const DplDevice::GroupPointer &group,
                           QWidget *parent = 0);

protected slots:
    void resize_event(const QSize &size);

private:
    AmpRuler *m_ampRuler;
    UtRuler *m_utRuler;
};

#endif // __A_SCAN_DISPLAY_H__
