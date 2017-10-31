#include "mode_radio_button.h"

#define W_SIZE (100) //(177)
#define H_SIZE (54)  //(96)

ModeRadioButton::ModeRadioButton(int mode, QWidget *parent) :
    QRadioButton(parent),
    m_mode(mode)
{
    setIcon(QIcon(QString(":/resource/display_mode/%1.png").arg(mode)));
    setIconSize(QSize(W_SIZE, H_SIZE));
    setFocusPolicy(Qt::NoFocus);
}
