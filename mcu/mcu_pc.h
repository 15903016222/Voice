#ifndef __MCU_PC_H__
#define __MCU_PC_H__

#include "mcu.h"

class McuPc : public Mcu
{
public:
    McuPc() : Mcu() {}
    void query_core_temp() {}
    void query_fpga_temp() {}
    void query_power_temp() {}
    void query_mcu_temp() {}
    void query_first_battery() {}
    void query_second_battery() {}
    void query_first_battery_status() {}
    void query_second_battery_status() {}
    void query_brightness() {}
    void query_probe() {}
    void notify_started() {}
    void set_poweroff() {}
    void set_brightness(char light) { Q_UNUSED(light); }
};

#endif // __MCU_PC_H__
