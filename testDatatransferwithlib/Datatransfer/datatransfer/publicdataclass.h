#ifndef PUBLICDATACLASS_H
#define PUBLICDATACLASS_H

#include <QObject>

#define CHANNELNUM_ANALOG 18 //模拟量通道数
#define CHANNELNUM_SWITCH 16 //开关量通道数

class PublicDataClass: public QObject
{
    Q_OBJECT

public:

    //数据类型
   enum DATATYPE{
       Type_byte = 1,
       Type_sbyte,
       Type_ushort,
       Type_short,
       Type_uint,
       Type_int,
       Type_ulong,
       Type_long,
       Type_float,
       Type_double,
       Type_bool,
       Type_char,
       Type_string,
       Type_bcd,
       Type_ibcd,
       Type_bs8,
       Type_bs16,
       Type_ipv4,
       Type_mac,
       Type_gbk,
       Type_utf8,
       Type_gb2312,
       Type_datetime,
       Type_binaryfile
   };


    //========== data ==========//
    typedef struct{
        QString value;//值
        int type;//类型
        int length;//长度
    }GENERAL_DATA;

    typedef struct{
        int dataNum;
        QList<GENERAL_DATA> dataList;
    }GENERAL_DATA_STUCT;

    GENERAL_DATA_STUCT generalParamCommunicate;
    GENERAL_DATA_STUCT generalParamDevInfo;
    GENERAL_DATA_STUCT generalParamChannelInfo[CHANNELNUM_ANALOG];
    GENERAL_DATA_STUCT generalWRParamTransient;
    GENERAL_DATA_STUCT generalWRParamSteady;
    GENERAL_DATA_STUCT generalWRParamSwitch;
    GENERAL_DATA_STUCT generalWRParamAnalog[CHANNELNUM_ANALOG];
    GENERAL_DATA_STUCT generalWRParamComponent;
    GENERAL_DATA_STUCT generalWRParamPulseIn;
    GENERAL_DATA_STUCT generalWRParamPulseOut;
    GENERAL_DATA_STUCT generalWRParamCalibration[CHANNELNUM_ANALOG];

    //===============================================
    //通讯参数
    typedef struct{
        QString        portName1;
        unsigned short boundRate1 ;
        char           parity1;
        QString        portName2;
        unsigned short boundRate2 ;
        char           parity2;

    }PARAM_COMMUNICATE;
    //PARAM_COMMUNICATE sParamCommunicate;

    //===============================================
    //系统配置参数
    //设备标识参数
    typedef struct{
        QString        companyName;
        QString        stationName;
        QString        deviceName;
        QString        factoryNum;

    }PARAM_DEVINFO;
    PARAM_DEVINFO sParamDevInfo;

    //采集通道参数
    typedef struct{
        unsigned short index;
        char property;
        char phase;
        char lineNum;
        float ratedValue;
        float ratio;
        QString name;//char[16]
        float range;
    }PARAM_CHANNELINFO;
    PARAM_CHANNELINFO sParamChannelInfo[CHANNELNUM_ANALOG];

    //最高采样率
    unsigned int mMaxSampleRate;

    //校时方式
    char mTimeCalibrationType;


    //===============================================
    //录波相关参数
    //暂态录波参数
    typedef struct{
        unsigned int sampleFrequencyA;
        unsigned int sampleTimeA;
        unsigned int sampleFrequencyB;
        unsigned int sampleTimeB;
        unsigned int sampleFrequencyC;
        unsigned int sampleTimeC;
        unsigned int sampleMaxTime;
    }WR_PARAM_TRANSIENT;
    WR_PARAM_TRANSIENT sWRParamTransient;

    //稳态录波参数
    typedef struct{
        unsigned int sampleFrequency;
        unsigned int sampleMaxTime;
    }WR_PARAM_STEADY;
    WR_PARAM_STEADY sWRParamSteady;

    //开关量触发
    typedef struct{
        char isSelect;
        char trigerType;
    }WR_TRIGER_SWITCH;

    typedef struct{
        WR_TRIGER_SWITCH switchTrigerInfo[CHANNELNUM_SWITCH];
        char switchLogic;
        char switchMode;
        unsigned short delay;
    }WR_PARAM_TRIGER_SWITCH;
    WR_PARAM_TRIGER_SWITCH sWRParamSwitch;

    //模拟量触发
    typedef struct{

    }WR_PARAM_TRIGER_ANALOG;
    WR_PARAM_TRIGER_ANALOG sWRParamAnalog[CHANNELNUM_ANALOG];

    //分组/序分量设置
    typedef struct{

    }WR_PARAM_COMPONENT;
    WR_PARAM_COMPONENT sWRParamComponent;

    //===============================================
    //电能检定相关参数
    //电能表检定启动/停止下发

    //电能检定输入脉冲参数下载/读取
    typedef  struct{
        unsigned int meterConstant;
        unsigned int checkLaps;
        char meterType;
        unsigned int pulseConstant;
    }PM_PARAM_PowerMeter_IN;
    PM_PARAM_PowerMeter_IN sWRParamPulseIn;
    //电能输出脉冲参数下载下载/读取
    typedef  struct{
        char mode;
        unsigned int pulseConstant;
    }PM_PARAM_PowerMeter_OUT;
    PM_PARAM_PowerMeter_OUT sWRParamPulseOut;

    //===============================================
    //校准相关参数
    typedef  struct{
        float amplitude;
        float phase;
    }CA_PARAM_Calibration;
    CA_PARAM_Calibration sWRParamCalibration[CHANNELNUM_ANALOG];

    //===============================================
    //波形实时数据传输


    //===============================================
    //设备录波文件召测

};
















#endif // PUBLICDATACLASS_H
