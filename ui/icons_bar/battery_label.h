#ifndef __BATTERY_LABEL_H__
#define __BATTERY_LABEL_H__

#include <QLabel>
#include "mcu/mcu.h"

class BatteryLabel : public QLabel
{
    Q_OBJECT
public:
    explicit BatteryLabel(QWidget *parent = 0);

public slots:
    void set_status(Mcu::BatteryStatus status);
    void set_quantity(int value);

protected:
    void paintEvent(QPaintEvent *e);

private:
    Mcu::BatteryStatus m_status;
    int m_quantity;
};

#endif
