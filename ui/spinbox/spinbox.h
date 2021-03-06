#ifndef SPINBOX_H
#define SPINBOX_H

#include "mcu.h"

#include <QSpinBox>

class SpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit SpinBox(QWidget *parent = 0);
    ~SpinBox();

private:
    Mcu *m_mcu;

private slots:
    void do_rotary_event(Mcu::RotaryType type);
    void key_sure(Mcu::KeyType key);
};

#endif // SPINBOX_H
