﻿#ifndef PUBLICDATACLASS_H
#define PUBLICDATACLASS_H

#include <QObject>

#define CHANNELNUM_ANALOG 18 //模拟量通道数
#define CHANNELNUM_SWITCH 16 //开关量通道数
#define GROUPNUM_MAX 4 //最大总组数

#define g_C2Q(str) QString::fromLocal8Bit(str)

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

   int getLenfromType(int type)
   {
       int len = 0;
       switch(type)
       {
       case Type_byte:
       {
           len = 1;
       }break;
       case Type_sbyte:
       {
           len = 1;
       }break;
       case Type_ushort:
       {
           len = 2;
       }break;
       case Type_short:
       {
           len = 2;
       }break;
       case Type_uint:
       {
           len = 4;
       }break;
       case Type_int:
       {
           len = 4;
       }break;
       case Type_ulong:
       {
           len = 8;
       }break;
       case Type_long:
           {
              len = 8;
           }break;
       case Type_float:
           {
               len = 4;
           }break;
       case Type_double:
           {
               len = 8;
           }break;
       case Type_bool:
           {
               len = 1;
           }break;
       case Type_char:
           {
              //
           }break;
       case Type_string:
           {
               //
           }break;
       case Type_bcd:
           {
               //
           }break;
       case Type_ibcd:
           {
               //
           }break;
       case Type_bs8:
           {
               len = 1;
           }break;
       case Type_bs16:
           {
               len = 2;
           }break;
       case Type_ipv4:
           {
              len = 4;
           }break;
       case Type_mac:
           {
               len = 6;
           }break;
       case Type_gbk:
           {
               //
           }break;
       case Type_utf8:
           {
               //
           }break;
       case Type_gb2312:
           {
               //
           }break;
       case Type_datetime:
           {
               len = 7;
           }break;
       case Type_binaryfile:
           {
               //
           }break;
       }

       return len;
   }

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
    GENERAL_DATA_STUCT generalWRParamSwitch[CHANNELNUM_SWITCH+1];//公共信息+通道信息
    GENERAL_DATA_STUCT generalWRParamAnalog[CHANNELNUM_ANALOG+1];//公共信息+通道信息
    GENERAL_DATA_STUCT generalWRParamComponent[CHANNELNUM_ANALOG+1];//公共信息+通道信息
    //GENERAL_DATA_STUCT generalWRParamComponent;
    GENERAL_DATA_STUCT generalWRParamPulseIn;
    GENERAL_DATA_STUCT generalWRParamPulseOut;
    GENERAL_DATA_STUCT generalWRParamCalibration[CHANNELNUM_ANALOG];
    GENERAL_DATA_STUCT generalWRCommandCalibration[CHANNELNUM_ANALOG];

    GENERAL_DATA_STUCT generalWRComtradeData;

    GENERAL_DATA_STUCT generalEnergyValue;//电能量数据
    GENERAL_DATA_STUCT generalMeterValue;//标准表传输数据

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
        char comtradeVersion;
        char comtradeType;

    }PARAM_DEVINFO;
    //PARAM_DEVINFO sParamDevInfo;

    //采集通道参数
    typedef struct{
        unsigned short index;
        QString name;//char[16]
        char property;
        char phase;
        char lineNum;
        char groupNum;//组序号
        QString ratio;//10字节:*/*格式
        float ratedValue;//额定值
        float range;//量程
    }PARAM_CHANNELINFO;
    //PARAM_CHANNELINFO sParamChannelInfo[CHANNELNUM_ANALOG];

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
    //WR_PARAM_TRANSIENT sWRParamTransient;

    //稳态录波参数
    typedef struct{
        unsigned int sampleFrequency;
        unsigned int sampleMaxTime;
    }WR_PARAM_STEADY;
    //WR_PARAM_STEADY sWRParamSteady;

    //开关量触发
    typedef struct{
        char isSelect;//是否选择
        char isComtrade;//是否录波
        char trigerType;//触发极性（字节型，0-上升沿 1-下降沿）
        QString name;//开关量名称
    }WR_TRIGER_SWITCH;

    typedef struct{
        WR_TRIGER_SWITCH switchTrigerInfo[CHANNELNUM_SWITCH];
        char switchLogic;//开关通道触发逻辑关系（字节型，0-与 1-或）
        char switchMode;//触发模式（字节型，0-正常触发 1-单次触发 2-延时触发）
        unsigned short delay;//延时时间（无符号整形，单位-毫秒）
    }WR_PARAM_TRIGER_SWITCH;
    //WR_PARAM_TRIGER_SWITCH sWRParamSwitch;

    //模拟量触发
    typedef struct{
        char isSelect;//是否选择
        char isComtrade;//是否录波
        char isSelect_UP;//越上限是否选择
        float value_UP;//越上限定值
        char isSelect_Down;//越下限是否选择
        float value_Down;//越下限定值
        char isSelect_Mutation;//突变量是否选择
        char type_Mutation;//突变量极性（0-正常 1-上升沿 2-下降沿）
        float value_Mutation;//突变量定值
        char isSelect_Harmonic2;//2次谐波是否选择
        float value_Harmonic2;//2次谐波定值
        char isSelect_Harmonic3;//3次谐波是否选择
        float value_Harmonic3;//3次谐波定值
        char isSelect_Harmonic5;//5次谐波是否选择
        float value_Harmonic5;//5次谐波定值
        char isSelect_Harmonic7;//7次谐波是否选择
        float value_Harmonic7;//7次谐波定值
    }WR_TRIGER_ANALOG;

    typedef struct{
        WR_TRIGER_ANALOG analogTrigerInfo[CHANNELNUM_ANALOG];
        char switchMode;//触发模式（字节型，0-正常触发 1-单次触发 2-延时触发）
    }WR_PARAM_TRIGER_ANALOG;
    //WR_PARAM_TRIGER_ANALOG sWRParamAnalog[CHANNELNUM_ANALOG];

    //分组/序分量设置
    typedef struct{
        char groupSEQnum;//组序号（1/2/3/4）
        char isSelect_UP_P;//正序上限是否选择
        float value_UP_P;//越上限定值
        char isSelect_Down_P;//正序下限是否选择
        float value_Down_P;//越下限定值
        char isSelect_Mutation_P;//正序突变量是否选择
        float value_Mutation_P;//正序突变量定值
        char isSelect_UP_N;//负序上限是否选择
        float value_UP_N;//越上限定值
        char isSelect_Mutation_N;//负序突变量是否选择
        float value_Mutation_N;//负序突变量定值
        char isSelect_UP_Z;//零序上限是否选择
        float value_UP_Z;//越上限定值
        char isSelect_Mutation_Z;//零序突变量是否选择
        float value_Mutation_Z;//零序突变量定值
    }WR_COMPONENT;

    typedef struct{
        WR_COMPONENT componentInfo[GROUPNUM_MAX];
        char groupTotalnum;

    }WR_PARAM_COMPONENT;
    //WR_PARAM_COMPONENT sWRParamComponent;

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
    //PM_PARAM_PowerMeter_IN sWRParamPulseIn;
    //电能输出脉冲参数下载下载/读取
    typedef  struct{
        char mode;
        unsigned int pulseConstant;
    }PM_PARAM_PowerMeter_OUT;
    //PM_PARAM_PowerMeter_OUT sWRParamPulseOut;

    //===============================================
    //校准相关参数
    typedef  struct{
        float amplitude;
        float phase;
    }CA_PARAM_Calibration;
    //CA_PARAM_Calibration sWRParamCalibration[CHANNELNUM_ANALOG];

    //校准命令
    typedef  struct{
        float amplitude;
        float phase;
    }CA_COMMAND_Calibration;


    //===============================================
    //波形实时数据传输


    //===============================================
    //设备录波文件召测


    //===============================================
    //召测传输数据

    //电能量数据召测 是否与当前路数关联，按最大4路定义
    typedef  struct{
        float ernergy_DCType;//电磁式电能量示值
        float ernergy_DZType;//电子式电能量示值
        float meterERR_1;
        float meterERR_2;
        float meterERR_3;
        float meterERR_4;
        float meterERR_5;
        float meterERR_6;
        float meterERR_7;
        float meterERR_8;
    }CALL_ErnergyValue;

    //标准表实时测量数据召测  标准表实时采集的电压电流功率等值以及谐波采集值

    typedef  struct{//1路中电压相关参数
        float UA;
        float UB;
        float UC;
        float UAB;
        float UBC;
        float UCA;
        float _3U0;
        float _3U0_Cal;
        float RMS_UA; 	//有效值UA1
        float RMS_UB;	//有效值UB1
        float RMS_UC;	//有效值UC1
        float RMS_3U0;	//有效值U01
        float UA_Angle;
        float UB_Angle;
        float UC_Angle;
        float _3U0_Angle;
        float _3U0_Cal_Angle;
        float UAB_Angle;
        float UCB_Angle;
        float UAC_Angle;
    }UrelatedValue_oneroad;

    typedef  struct{//1路中电流相关参数
        float IA;
        float IB;
        float IC;
        float _3I0;
        float _3I0_Cal;
        float RMS_IA; 	//有效值IA1
        float RMS_IB;	//有效值IB1
        float RMS_IC;	//有效值IC1
        float RMS_3I0;	//有效值I01
        float IA_Angle;
        float IB_Angle;
        float IC_Angle;
        float _3I0_Angle;
        float _3I0_Cal_Angle;
    }IrelatedValue_oneroad;

    typedef  struct{//1路电压电流组合相关参数
        float PA;
        float PB;
        float PC;
        float QA;
        float QB;
        float QC;
        float PZ;
        float QZ;
        float COSA;
        float COSB;
        float COSC;
        float COS;
        float SINA;
        float SINB;
        float SINC;
        float SIN;
    }UIrelatedValue_oneroad;

    typedef  struct{//1路直流量相关参数
        float DC;//直流分量幅值
        float FREQ;//直流分量频率
    }DCrelatedValue_oneroad;

    //harmonic
    typedef  struct{//1个通道谐波相关参数
        float harmonicContent[32];
    }HrelatedValue_onechannel;

    //energy
    typedef  struct{//1路电能量相关参数
        float ENEERGY_P;
        float ENEERGY_Q;
    }ErelatedValue_oneroad;

    typedef  struct{







        float NUMBER;//当前脉冲圈数NUMBER

    }CALL_StandardMeter_analog;

    //状态信息召测
    typedef  struct{
        char inputState_1;//开入1状态
        char inputState_2;
        char inputState_3;
        char inputState_4;
        char inputState_5;
        char inputState_6;
        char inputState_7;
        char inputState_8;
        char inputState_9;
        char inputState_10;
        char inputState_11;
        char inputState_12;
        char inputState_13;
        char inputState_14;
        char inputState_15;
        char inputState_16;
        char waveState;   //录波状态
        char timeState;   //对时状态
        char devWarnning; //设备告警
    }CALL_StandardMeter_switch;
};
















#endif // PUBLICDATACLASS_H
