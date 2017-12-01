#ifndef __CONFIG_CONFIGURATION_H__
#define __CONFIG_CONFIGURATION_H__

#include <QString>
#include <QMap>
#include "msgpack.hpp"

namespace Config {

class BaseItemConfig;
class ConfigurationPrivate;

namespace Config_Group {

enum E_Group{
        Gate_Curves,
        UT,
        Focallaw,
        Probe_Part,
        Scan,
        Measurement
    };

    enum E_Gate_Curves {
        Gate,
        Alarm,
        Output,
        Analog,
        DAC,
        TCG,
    };

    enum E_Gate {
        Gate_Type,
        Gate_Switch,
        Gate_Start,
        Gate_Width,
        Gate_Height,
        Gate_Synchro,
        Gate_Measure,
        Gate_Mode,
        Gate_Color,
    };

    enum E_TCG{
        TCG_Index,
        TCG_Position,
        TCG_Gain,
        TCG_Amplitude,
    };

    enum E_UT{
        General,
        Pulser,
        Receiver,
        Advanced,
    };

    enum E_General {
        General_Gain,
        General_Start,
        General_Range,
        General_Velocity,
        General_WedgeDelay,
        General_UTUnit,
    };
}


enum E_MainConfig {
    Preference,
    Group,
    WaveData,
};

namespace Config_Preference {
    enum E_Preference {
        Bright,
        Opacity,
        Language,
        StartingPage,
        GateMode,
    };
}


typedef std::map<int, BaseItemConfig*>  UnpackerMap;

class Configuration
{
public:

    Configuration();
    ~Configuration();

    static Configuration *instance();

    bool load_config(const QString &configFilePath = s_defaultConfigFilePath);
    bool save_config(const QString &configFilePath = s_defaultConfigFilePath);

private:
    ConfigurationPrivate        *d;
    static Configuration        *s_configuration;
    static QString              s_defaultConfigFilePath;

    void deal_object(const msgpack::object &object);


    Q_DISABLE_COPY(Configuration)
};

}

#endif // __CONFIG_CONFIGURATION_H__
