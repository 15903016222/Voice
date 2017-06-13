#ifndef __MODE_RADIO_BUTTON_H__
#define __MODE_RADIO_BUTTON_H__

#include <QRadioButton>

class ModeRadioButton : public QRadioButton
{
public:
    ModeRadioButton(int mode, QWidget *parent = 0);

    int get_mode() const { return m_mode; }

private:
    int m_mode;
};

#endif // __MODE_RADIO_BUTTON_H__
