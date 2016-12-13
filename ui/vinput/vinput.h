/**
 * @file vinput.h
 * @brief Virtual Key Input
 * @author Jake Yang <yanghuanjie@cndoppler.cn>
 * @version 0.1
 * @date 2016-11-20
 */
#ifndef __VINPUT_H__
#define __VINPUT_H__

/* Qt */
#include <QObject>
#include <QMutex>


class VInputPrivate;
class VInput
{
public:
    enum Key {
        Key_Esc         = 1,
        Key_1,
        Key_2,
        Key_3,
        Key_4,
        Key_5,
        Key_6,
        Key_7,
        Key_8,
        Key_9,
        Key_0,
        Key_Minus,
        Key_Backspace,
        Key_Enter       = 28,
        Key_Dot,
        Key_Up          = 103,
        Key_Left        = 105,
        Key_Right       = 106,
        Key_Down        = 108,
        Key_Delete      = 111,
    };

    static VInput *get_vinput();
    void send(Key key, bool press, bool sync = true);
    void send_press(Key key) { send(key, true); }
    void send_release(Key key) { send(key, false); }
    void send(Key key) { send_press(key); send_release(key); }

protected:
    explicit VInput();
    ~VInput();

private:
    static VInput *s_vinput;
    static QMutex m_mutex;
    VInputPrivate *d;
};

#endif // __VINPUT_H__
