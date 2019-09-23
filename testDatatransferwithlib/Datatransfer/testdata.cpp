#include "testdata.h"

#include "./datatransfer/publicdataclass.h"
//#include "./datatransfer/devdatatransfer_wr.h"

extern PublicDataClass pubData;

TestData::TestData(QObject *parent) : QObject(parent)
{

}

void TestData::setParamCommunicate()
{
    pubData.sParamCommunicate.portName1 = "COM0";
    pubData.sParamCommunicate.boundRate1 = 2400;
    pubData.sParamCommunicate.parity1 = 0;

    pubData.sParamCommunicate.portName2 = "COM4";
    pubData.sParamCommunicate.boundRate2 = 4800;
    pubData.sParamCommunicate.parity2 = 2;



    pubData.generalParamCommunicate.dataNum = 6;
    pubData.generalParamCommunicate.dataList.clear();

    PublicDataClass::GENERAL_DATA tempData;
    //值
    //类型
    //长度
    tempData.value = pubData.sParamCommunicate.portName1;
    tempData.type = pubData.Type_char;
    tempData.length = 6;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(pubData.sParamCommunicate.boundRate1);
    tempData.type = pubData.Type_ushort;
    tempData.length = 2;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(pubData.sParamCommunicate.parity1);
    tempData.type = pubData.Type_byte;
    tempData.length = 1;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = pubData.sParamCommunicate.portName2;
    tempData.type = pubData.Type_char;
    tempData.length = 6;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(pubData.sParamCommunicate.boundRate2);
    tempData.type = pubData.Type_ushort;
    tempData.length = 2;
    pubData.generalParamCommunicate.dataList.append(tempData);

    tempData.value = QString::number(pubData.sParamCommunicate.parity2);
    tempData.type = pubData.Type_byte;
    tempData.length = 1;
    pubData.generalParamCommunicate.dataList.append(tempData);
}
