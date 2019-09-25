#ifndef DEVDATATRANSFER_WR_H
#define DEVDATATRANSFER_WR_H

#include <QObject>
#include <QDebug>




#include "./include/privateprotocal/customprotocol.h"
#include "./client/wrclientstuff.h"



#include "../testdata.h"

#define g_C2Q(str) QString::fromLocal8Bit(str)

class DevDataTransfer_wr : public QObject
{
    Q_OBJECT

public:
    explicit DevDataTransfer_wr(QObject *parent = nullptr);

    Q_INVOKABLE void clientConnect();
    Q_INVOKABLE void clientDisConnect();
    Q_INVOKABLE void test();

//    Q_INVOKABLE int wr_connect(QString hostname, int tcpPort);

//    Q_INVOKABLE void wr_devdisconnect(QString hostname, int tcpPort);


    //Q_INVOKABLE
    /**
     * @brief wr_sendParamCommunicate 通讯参数
     * @param typeID     功能码： 下载-1；读取-2
     * @param portName1  串口2串口号、波特率、校验
     * @param boundRate1
     * @param parity1
     * @param portName2  串口2串口号、波特率、校验
     * @param boundRate2
     * @param parity2
     */
    Q_INVOKABLE void wr_sendParamCommunicate(int            typeID,
                                             QString        portName1,
                                             unsigned short boundRate1,
                                             char           parity1,
                                             QString        portName2,
                                             unsigned short boundRate2,
                                             char           parity2);


//    /**
//     * @brief wr_sendParamDevInfo 设备标识参数
//     * @param typeID 功能码： 下载-1；读取-2
//     * @param companyName 公司名称
//     * @param stationName 场站名称
//     * @param deviceName 装置名称
//     * @param factoryNum 出厂编号
//     */
//    Q_INVOKABLE void wr_sendParamDevInfo(int            typeID,
//                             QString        companyName,
//                            QString        stationName,
//                            QString        deviceName,
//                            QString        factoryNum);

//    /**
//     * @brief wr_sendParamChannelInfo  采集通道参数
//     * @param typeID 功能码： 下载-1；读取-2
//     */
//    Q_INVOKABLE void wr_sendParamChannelInfo(int            typeID);

//    /**
//     * @brief wr_sendMaxSampleRate  最高采样率
//     * @param typeID 功能码： 下载-1；读取-2
//     * @param value 最高采样率
//     */
//    Q_INVOKABLE void wr_sendMaxSampleRate(int            typeID,
//                             unsigned int value);

//    /**
//     * @brief wr_send    校时方式
//     * @param typeID 功能码： 下载-1；读取-2
//     * @param value 校时方式  0-GPS,1-SNTP,2-B码
//     */
//    Q_INVOKABLE void wr_sendTimeCalibrationType(int            typeID,
//                  char         value  );




//    /**
//     * @brief wr_sendWRParamTransient
//     * @param typeID
//     * @param sampleFrequencyA
//     * @param sampleTimeA
//     * @param sampleFrequencyB
//     * @param sampleTimeB
//     * @param sampleFrequencyC
//     * @param sampleTimeC
//     * @param sampleMaxTime
//     */
//    Q_INVOKABLE void wr_sendWRParamTransient(int            typeID,
//                                 unsigned int sampleFrequencyA,
//                                 unsigned int sampleTimeA,
//                                 unsigned int sampleFrequencyB,
//                                 unsigned int sampleTimeB,
//                                 unsigned int sampleFrequencyC,
//                                 unsigned int sampleTimeC,
//                                 unsigned int sampleMaxTime);

//    /**
//     * @brief wr_sendWRParamSteady
//     * @param typeID
//     * @param sampleFrequency
//     * @param sampleMaxTime
//     */
//    Q_INVOKABLE void wr_sendWRParamSteady(int            typeID,
//                              unsigned int sampleFrequency,
//                              unsigned int sampleMaxTime);

//    /**
//     * @brief wr_sendWRParamSwitch
//     * @param typeID
//     */
//    Q_INVOKABLE void wr_sendWRParamSwitch(int            typeID//,
//                              );

//    /**
//     * @brief wr_sendWRParamAnalog
//     * @param typeID
//     */
//    Q_INVOKABLE void wr_sendWRParamAnalog(int            typeID//,
//                              );

//    /**
//     * @brief wr_sendWRParamComponent
//     * @param typeID
//     */
//    Q_INVOKABLE void wr_sendWRParamComponent(int            typeID//,
//                                 );

//    /**
//     * @brief wr_sendWROperate  手动启动/停止录波
//     * @param value 启动/停止录波（字节型 1-启动录波 0-停止录波）
//     */
//    Q_INVOKABLE void wr_sendWROperate(char value);

//    /**
//     * @brief wr_sendWRPowerMeterOperate 电能表检定启动/停止下发
//     * @param value 启动/停止检定（字节型 1-启动检定 0-停止检定）
//     */
//    Q_INVOKABLE void wr_sendPowerMeterOperate(char value);

//    /**
//     * @brief wr_sendPowerMeterParamPulseIn  电能检定输入脉冲参数下载/读取
//     * @param typeID
//     * @param meterConstant 输入脉冲表常数(无符号整型)、
//     * @param checkLaps 校验圈数(无符号整型)、
//     * @param meterType 表类型(字节型0-PT4 1-QT4 2-P32 3-Q32 4-Q90 5-Q60 6-Q33)、
//     * @param pulseConstant 脉冲常数(无符号整型)
//     */
//    Q_INVOKABLE void wr_sendPowerMeterParamPulseIn(int            typeID,
//            unsigned int meterConstant,
//            unsigned int checkLaps,
//            char meterType,
//            unsigned int pulseConstant);

//    /**
//     * @brief wr_sendPowerMeterParamPulseOut  电能输出脉冲参数下载下载/读取
//     * @param typeID
//     * @param mode 模式（字节型，1-自动 0-非自动）
//     * @param pulseConstant 脉冲常数（无符号整型，模式为0时设置生效）
//     */
//    Q_INVOKABLE void wr_sendPowerMeterParamPulseOut(int            typeID,
//            char mode,
//            unsigned int pulseConstant);

//    void wr_sendCalibrationParam();
//    void wr_sendCalibrationOperate();

signals:


public slots:
    void respondStatus(bool newStatus);
    void respondmsgRecv(QByteArray qbaBuf);
    void respondmsgSend(QByteArray qbaBuf);
    void gotError(QAbstractSocket::SocketError err);

public:

    CustomProtocol priProtocal;
    CustomProtocol::_XmlDataStruct XmlData;
    QList<CustomProtocol::_ReturnDataStruct> ReturnDataList;

    //CustomProtocol::_XmlDataStruct XmlData_ParamCommunicate;





    //PublicDataClass pubData;
    TestData testdata;
    WRClientStuff *wrClient;

private:





};

#endif // DEVDATATRANSFER_WR_H
