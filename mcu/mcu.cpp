
#include "mcu.h"

#ifdef PHASCAN_II
#include "mcu_imx.h"
#else
#include "mcu_omap.h"
#endif

Mcu* Mcu::m_mcu = NULL;

Mcu::Mcu()
    :QObject()
{
#ifdef PHASCAN_II
    d_ptr = new McuImx();
#else /*PHASCAN*/
    d_ptr = new McuOmap();
#endif

    if ( ! connect(d_ptr, SIGNAL(event(Mcu::Cmd,QByteArray&)), this, SIGNAL(event(Mcu::Cmd,QByteArray&))) ) {
        qDebug("failed");
    }
}

Mcu::~Mcu()
{
    delete d_ptr;
}

void Mcu::query_core_temp()
{
    d_ptr->query(CORE_TEMPERATURE);
}

void Mcu::query_fpga_temp()
{
    d_ptr->query(FPGA_TEMPERATURE);
}

void Mcu::query_power_temp()
{
    d_ptr->query(POWER_TEMPERATURE);
}

void Mcu::query_mcu_temp()
{
    d_ptr->query(MCU_TEMPERATUREE);
}

void Mcu::query_first_battery()
{
    d_ptr->query(BATTERY1_QUANTITY);
}

void Mcu::query_second_battery()
{
    d_ptr->query(BATTERY2_QUANTITY);
}

void Mcu::query_first_battery_status()
{
    d_ptr->query(BATTERY1_STATUS);
}

void Mcu::query_second_battery_status()
{
    d_ptr->query(BATTERY2_STATUS);
}

void Mcu::query_brightness()
{
    d_ptr->query(BRIGHTNESS);
}

void Mcu::query_pa_probe_model()
{
    d_ptr->query(PA_PROBE_MODEL);
}

void Mcu::query_pa_probe_series()
{
    d_ptr->query(PA_PROBE_SERIES);
}

void Mcu::query_pa_probe_type()
{
    d_ptr->query(PA_PROBE_TYPE);
}

void Mcu::query_pa_probe_freq()
{
    d_ptr->query(PA_PROBE_FREQ);
}

void Mcu::query_pa_probe_elements()
{
    d_ptr->query(PA_PROBE_ELEMENTS_QTY);
}

void Mcu::query_pa_probe_elements_distance()
{
    d_ptr->query(PA_PROBE_ELEMENTS_DISTANCE);
}

void Mcu::query_pa_probe_ference_point()
{
    d_ptr->query(PA_PROBE_FERENCE_POINT);
}

void Mcu::notify_started()
{
    d_ptr->set(NOTIFY_STARTED, 0);
}

void Mcu::set_poweroff()
{
    d_ptr->set(POWEROFF, 0);
}

void Mcu::set_brightness(uchar light)
{
    d_ptr->set(BRIGHTNESS, (char)light);
}

