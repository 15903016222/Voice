#ifndef __CONFIG_CONFIGURATION_H__
#define __CONFIG_CONFIGURATION_H__

#include <QString>
#include <QMap>
#include "msgpack.hpp"

namespace Config {

class BaseItemConfig;
class ConfigurationPrivate;

namespace Config_Group {

    enum E_Group {
        General,
        Gate,
        UT,
        Focallawer,
        DACS,
        TCGS,
        Cursor,
        Scan,
        GroupItemNum
    };

    enum E_Gate {
        Gate_Type,
        Gate_Switch,
        Gate_Start,
        Gate_Width,
        Gate_Height,
        Gate_Synchro,
        Gate_Measure,
        Gate_Color,
        Gate_ItemNum
    };

    enum E_UT {
        UT_Sample,
        UT_Transceiver,
        UT_ItemNum
    };

    enum E_Transceiver {
        Transceiver_Mode,
        Transceiver_PW,
        Transceiver_Filter,
        Transceiver_Rectifier,
        Transceiver_VideoFilter,
        Transceiver_Averaging
    };

    enum E_Sample {
        Sample_Precision,
        Sample_Gain,
        Sample_Start,
        Sample_Range,
        Sample_PointQty,
        Sample_AutoSet,
        Sample_ItemNum
    };

    enum E_Focallawer {
        Probe,
        Wedge,
        Specimen,
        FocusCnf,
        Focallawer_ItemNum
    };

    enum E_Probe {
        Probe_PA,
        Probe_FileName,
        Probe_ItemNum
    };

   enum E_Wedge {
        Wedge_FileName,
        Wedge_Serial,
        Wedge_Model,
        Wedge_Angle,
        Wedge_RootAngle,
        Wedge_Velocity,
        Wedge_PrimaryOffset,
        Wedge_SecondaryOffset,
        Wedge_FirstElementHeight,
        Wedge_Length,
        Wedge_Width,
        Wedge_Height,
        Wedge_Orientation,
        Wedge_delay,
        Wedge_ItemNum
    };

   enum E_Specimen{
       Specimen_Type,
       Specimen_WaveType,
       Specimen_Velocity,
       Specimen_ItemNum
    };

   enum E_FocusCnf {
        FocusCnf_Mode,
        FocusCnf_ItemNum
    };

   enum E_TCGS {
       TCGS_Enable,
       TCGS_CurrentTcgIndex,
       TCGS_CurrentPointIndex,
       TCGS_TcgList,
       TCGS_ItemNum
   };

   enum E_Point {
       Point_Index,
       Point_Position,
       Point_Gain,
       Point_ItemNum
   };

   enum E_Cursor {
       Cursor_AmplitudeReference,
       Cursor_AmplitudeMeasurement,
       Cursor_UltrasoundReference,
       Cursor_UltrasoundMeasurement,
       Cursor_ScanReference,
       Cursor_ScanMeasurement,
       Cursor_IndexReference,
       Cursor_IndexMeasurement,
       Cursor_Visible,
       Cursor_ItemNum
   };

   enum E_Scan {
       Scan_StartX,
       Scan_StopX,
       Scan_StartY,
       Scan_StopY,
       Scan_Width,
       Scan_Height,
       Scan_ItemNum
   };

    enum E_General {
        General_Mode,
        General_UTUnit,
        General_CurrentAngle,
        General_CurrentBeamIndex

    };
}


enum E_MainConfig {
    Preference,
    Group,
    WaveData
};

namespace Config_Preference {
    enum E_Preference {
        Bright,
        Opacity,
        Language,
        StartingPage,
        GateMode
    };
}


typedef std::map<int, BaseItemConfig*>  UnpackerMap;

class Configuration
{
public:

    Configuration();
    ~Configuration();

    /**
     * @brief instance  获取配置信息实例
     * @return          返回配置信息类实例指针
     */
    static Configuration *instance();

    /**
     * @brief load_config       加载配置文件
     * @param configFilePath    配置文件路径
     * @return  true：加载成功；false：加载失败
     */
    bool load_config(const QString &configFilePath);

    /**
     * @brief save_config       保存配置文件
     * @param configFilePath    待保存的配置文件路径
     * @return  true：保存成功；false：保存失败
     */
    bool save_config(const QString &configFilePath);

private:
    ConfigurationPrivate        *d;
    static Configuration        *s_configuration;

    void deal_object(const msgpack::object &object);

    Q_DISABLE_COPY(Configuration)
};

}

#endif // __CONFIG_CONFIGURATION_H__
