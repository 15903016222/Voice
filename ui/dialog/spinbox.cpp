#include "spinbox.h"

#include <QEvent>
#include <QKeyEvent>
#include <QApplication>

SpinBox::SpinBox(QWidget *parent) :
    QSpinBox(parent)
{
    m_mcu = Mcu::get_mcu();
    connect(m_mcu, SIGNAL(rotary_event(Mcu::RotaryType)), this, SLOT(do_rotary_event(Mcu::RotaryType)));
    connect(m_mcu, SIGNAL(key_event(Mcu::KeyType)), this, SLOT(key_sure(Mcu::KeyType)));
}

void SpinBox::do_rotary_event(Mcu::RotaryType type)
{
    if(hasFocus()) {
        if (type == Mcu::ROTARY_UP) {
            this->stepUp();
        } else {
            this->stepDown();
        }
    }
}

void SpinBox::key_sure(Mcu::KeyType key)
{
    if(hasFocus()){
        if(key == Mcu::KEY_SURE) {
            QKeyEvent *event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier);
            QApplication::sendEvent(this, event);
        }
    }
}

SpinBox::~SpinBox()
{
}
