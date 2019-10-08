#include "testdata.h"

#include "./datatransfer/publicdataclass.h"
//#include "./datatransfer/devdatatransfer_wr.h"

extern PublicDataClass pubData;

TestData::TestData(QObject *parent) : QObject(parent)
{

}

void TestData::setParamCommunicate()
{
    PublicDataClass::PARAM_COMMUNICATE sParamCommunicate;
    sParamCommunicate.portName1 = "COM0";//pubData.
    sParamCommunicate.boundRate1 = 2400;
    sParamCommunicate.parity1 = 0;

    sParamCommunicate.portName2 = "COM4";
    sParamCommunicate.boundRate2 = 4800;
    sParamCommunicate.parity2 = 2;



    pubData.generalParamCommunicate.dataNum = 6;
    pubData.generalParamCommunicate.dataList.clear();

    PublicDataClass::GENERAL_DATA tempData;
    //值
    //类型
    //长度
    tempData.value = sParamCommunicate.portName1;
    tempData.type = pubData.Type_char;
    tempData.length = 6;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(sParamCommunicate.boundRate1);
    tempData.type = pubData.Type_ushort;
    tempData.length = 2;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(sParamCommunicate.parity1);
    tempData.type = pubData.Type_byte;
    tempData.length = 1;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = sParamCommunicate.portName2;
    tempData.type = pubData.Type_char;
    tempData.length = 6;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(sParamCommunicate.boundRate2);
    tempData.type = pubData.Type_ushort;
    tempData.length = 2;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(sParamCommunicate.parity2);
    tempData.type = pubData.Type_byte;
    tempData.length = 1;
    pubData.generalParamCommunicate.dataList.append(tempData);
}

void TestData::setParamDevInfo()
{
    PublicDataClass::PARAM_DEVINFO sParamDevInfo;
    sParamDevInfo.companyName = g_C2Q("公司名称");//"CSG"
    sParamDevInfo.stationName = g_C2Q("场站名称");
    sParamDevInfo.deviceName = g_C2Q("装置名称");
    sParamDevInfo.factoryNum = g_C2Q("出厂编号");
    sParamDevInfo.comtradeVersion = 1;//0-1991;1-1999
    sParamDevInfo.stationName = 1;//0-ASCII;1-BINARY

    pubData.generalParamDevInfo.dataNum = 6;
    pubData.generalParamDevInfo.dataList.clear();

    PublicDataClass::GENERAL_DATA tempData;
    //值
    //类型
    //长度
    tempData.value = sParamDevInfo.companyName;
    tempData.type = pubData.Type_char;
    tempData.length = 64;
    pubData.generalParamDevInfo.dataList.append(tempData);

    tempData.value = sParamDevInfo.stationName;
    tempData.type = pubData.Type_char;
    tempData.length = 64;
    pubData.generalParamDevInfo.dataList.append(tempData);

    tempData.value = sParamDevInfo.deviceName;
    tempData.type = pubData.Type_char;
    tempData.length = 64;
    pubData.generalParamDevInfo.dataList.append(tempData);

    tempData.value = sParamDevInfo.factoryNum;
    tempData.type = pubData.Type_char;
    tempData.length = 64;
    pubData.generalParamDevInfo.dataList.append(tempData);

    tempData.value = sParamDevInfo.comtradeVersion;
    tempData.type = pubData.Type_byte;
    tempData.length = 1;
    pubData.generalParamDevInfo.dataList.append(tempData);

    tempData.value = sParamDevInfo.comtradeType;
    tempData.type = pubData.Type_byte;
    tempData.length = 1;
    pubData.generalParamDevInfo.dataList.append(tempData);

}

void TestData::setParamChannelInfo()
{
    PublicDataClass::PARAM_CHANNELINFO sParamChannelInfo[CHANNELNUM_ANALOG];

    for(int i=0;i<CHANNELNUM_ANALOG;i++)
    {
        sParamChannelInfo[i].index = i+1;
        sParamChannelInfo[i].name = g_C2Q("通道名称");
        sParamChannelInfo[i].property = 1;//通道属性（1-U/2-I/3-DC）
        sParamChannelInfo[i].phase = 1;//相别（1-A/2-B/3-C/4-0/5-null）
        sParamChannelInfo[i].lineNum = 1;
        sParamChannelInfo[i].groupNum = 1;
        sParamChannelInfo[i].ratio = "600/5";
        sParamChannelInfo[i].ratedValue = 200.0f;
        sParamChannelInfo[i].range = 200.0f;
    }

    for(int i=0;i<CHANNELNUM_ANALOG;i++)
    {
        //generalParamChannelInfo
        pubData.generalParamChannelInfo[i].dataNum = 9;
        pubData.generalParamChannelInfo[i].dataList.clear();

        PublicDataClass::GENERAL_DATA tempData;
        //值
        //类型
        //长度
        tempData.value = QString::number(sParamChannelInfo[i].index);
        tempData.type = pubData.Type_ushort;
        tempData.length = pubData.getLenfromType(tempData.type);//
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = sParamChannelInfo[i].name;
        tempData.type = pubData.Type_char;
        tempData.length = 64;
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = sParamChannelInfo[i].property;
        tempData.type = pubData.Type_byte;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = sParamChannelInfo[i].phase;
        tempData.type = pubData.Type_byte;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = sParamChannelInfo[i].lineNum;
        tempData.type = pubData.Type_byte;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = sParamChannelInfo[i].groupNum;
        tempData.type = pubData.Type_byte;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = sParamChannelInfo[i].ratio;
        tempData.type = pubData.Type_char;
        tempData.length = 10;
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = QString::number(sParamChannelInfo[i].ratedValue);
        tempData.type = pubData.Type_float;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = QString::number(sParamChannelInfo[i].range);
        tempData.type = pubData.Type_float;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

    }

}
