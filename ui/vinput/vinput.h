#ifndef __VINPUT_H__
#define __VINPUT_H__

/* Qt */
#include <QObject>
#include <QMutex>


class VInputPrivate;
class VInput
{
public:
    enum KeyType {
        Press,
        Release
    };

    enum Key {
        Key_1           = 2,
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
        Key_Equal,
        Key_Backspace,
        Key_Tab,
        Key_Q,
        Key_W,
        Key_E,
        Key_R,
        Key_T,
        Key_Y,
        Key_U,
        Key_I,
        Key_O,
        Key_P,
        Key_Enter       = 28,
        Key_A           = 30,
        Key_S,
        Key_D,
        Key_F,
        Key_G,
        Key_H,
        Key_J,
        Key_K,
        Key_L,
        Key_LeftShift   = 42,
        Key_Z           = 44,
        Key_X,
        Key_C,
        Key_V,
        Key_B,
        Key_N,
        Key_M,
        Key_Comma,
        Key_Dot,
        Key_RightShift  = 54,
        Key_Capslock    = 58,
        Key_Up          = 103,
        Key_Left        = 105,
        Key_Right       = 106,
        Key_Down        = 108,
        Key_Delete      = 111
    };

    static VInput *get_vinput();
    void send(KeyType type, Key key);
    void send_press(Key key) { send(Press, key); }
    void send_release(Key key) { send(Release, key); }
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
