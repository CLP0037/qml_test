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

    tempData.value = QString::number(sParamDevInfo.comtradeVersion);
    tempData.type = pubData.Type_byte;
    tempData.length = 1;
    pubData.generalParamDevInfo.dataList.append(tempData);

    tempData.value = QString::number(sParamDevInfo.comtradeType);
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

        tempData.value = QString::number(sParamChannelInfo[i].property);
        tempData.type = pubData.Type_byte;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = QString::number(sParamChannelInfo[i].phase);
        tempData.type = pubData.Type_sbyte;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = QString::number(sParamChannelInfo[i].lineNum);
        tempData.type = pubData.Type_sbyte;
        tempData.length = pubData.getLenfromType(tempData.type);
        pubData.generalParamChannelInfo[i].dataList.append(tempData);

        tempData.value = QString::number(sParamChannelInfo[i].groupNum);
        tempData.type = pubData.Type_sbyte;
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

//暂态录波基本配置
void TestData::setWRParamTransient()
{
    PublicDataClass::WR_PARAM_TRANSIENT sWRParamTransient;
    sWRParamTransient.sampleFrequencyA = 40;
    sWRParamTransient.sampleTimeA = 200;
    sWRParamTransient.sampleFrequencyB = 40;
    sWRParamTransient.sampleTimeB = 200;
    sWRParamTransient.sampleFrequencyC = 40;
    sWRParamTransient.sampleTimeC = 200;
    sWRParamTransient.sampleMaxTime = 1000;

    pubData.generalWRParamTransient.dataNum = 7;
    pubData.generalWRParamTransient.dataList.clear();

    PublicDataClass::GENERAL_DATA tempData;
    //值
    //类型
    //长度(字符串型数据自行设置长度)

    for(int i=0;i<pubData.generalWRParamTransient.dataNum;i++)
    {
        tempData.type = pubData.Type_ushort;
        tempData.length = pubData.getLenfromType(tempData.type);

        switch (i) {
            case 0:{
                tempData.value = QString::number(sWRParamTransient.sampleFrequencyA);
            }break;
            case 1:{
                tempData.value = QString::number(sWRParamTransient.sampleTimeA);
            }break;
            case 2:{
                tempData.value = QString::number(sWRParamTransient.sampleFrequencyB);
            }break;
            case 3:{
                tempData.value = QString::number(sWRParamTransient.sampleTimeB);
            }break;
            case 4:{
                tempData.value = QString::number(sWRParamTransient.sampleFrequencyC);
            }break;
            case 5:{
                tempData.value = QString::number(sWRParamTransient.sampleTimeC);
            }break;
            case 6:{
                tempData.value = QString::number(sWRParamTransient.sampleMaxTime);
            }break;
        }


        pubData.generalWRParamTransient.dataList.append(tempData);
    }

}

//稳态录波基本配置
void TestData::setWRParamSteady()
{
    PublicDataClass::WR_PARAM_STEADY sWRParamSteady;

    sWRParamSteady.sampleFrequency = 40;
    sWRParamSteady.sampleMaxTime = 1000;

    pubData.generalWRParamSteady.dataNum = 2;
    pubData.generalWRParamSteady.dataList.clear();

    PublicDataClass::GENERAL_DATA tempData;
    //值
    //类型
    //长度(字符串型数据自行设置长度)

    for(int i=0;i<pubData.generalWRParamSteady.dataNum;i++)
    {
        tempData.type = pubData.Type_ushort;
        tempData.length = pubData.getLenfromType(tempData.type);

        switch (i) {
            case 0:{
                tempData.value = QString::number(sWRParamSteady.sampleFrequency);
            }break;
            case 1:{
                tempData.value = QString::number(sWRParamSteady.sampleMaxTime);
            }break;

        }


        pubData.generalWRParamSteady.dataList.append(tempData);
    }

}

//开关量触发配置
void TestData::setWRParamSwitch()
{
    PublicDataClass::WR_PARAM_TRIGER_SWITCH sWRParamSwitch;
    sWRParamSwitch.switchLogic = 0;
    sWRParamSwitch.switchMode = 0;
    sWRParamSwitch.delay = 100;
    for(int i=0;i<CHANNELNUM_SWITCH;i++)
    {
        sWRParamSwitch.switchTrigerInfo[i].isSelect = 1;
        sWRParamSwitch.switchTrigerInfo[i].isComtrade = 1;
        sWRParamSwitch.switchTrigerInfo[i].trigerType = 0;
        sWRParamSwitch.switchTrigerInfo[i].name = g_C2Q("开关量名称");
    }

    PublicDataClass::GENERAL_DATA tempData;

    pubData.generalWRParamSwitch[0].dataNum = 3;
    for(int i=0;i<pubData.generalWRParamSwitch[0].dataNum;i++)
    {
        tempData.type = pubData.Type_sbyte;
        tempData.length = pubData.getLenfromType(tempData.type);

        switch (i) {
            case 0:{
                tempData.value = QString::number(sWRParamSwitch.switchLogic);
            }break;
            case 1:{
                tempData.value = QString::number(sWRParamSwitch.switchMode);
            }break;
            case 2:{
                tempData.value = QString::number(sWRParamSwitch.delay);
            }break;
        }
        pubData.generalWRParamSwitch[0].dataList.append(tempData);
    }

    for(int i=0;i<CHANNELNUM_SWITCH;i++)
    {
        pubData.generalWRParamSwitch[i+1].dataNum = 4;
        for(int j=0;j<4;j++)
        {
            tempData.type = pubData.Type_sbyte;
            tempData.length = pubData.getLenfromType(tempData.type);

            switch (j) {
                case 0:{
                    tempData.value = QString::number(sWRParamSwitch.switchTrigerInfo[i].isSelect);
                }break;
                case 1:{
                    tempData.value = QString::number(sWRParamSwitch.switchTrigerInfo[i].isComtrade);
                }break;
                case 2:{
                    tempData.value = QString::number(sWRParamSwitch.switchTrigerInfo[i].trigerType);
                }break;
                case 3:{
                    tempData.value = sWRParamSwitch.switchTrigerInfo[i].name;
                    tempData.type = pubData.Type_char;
                    tempData.length = 64;
                }break;
            }
            pubData.generalWRParamSwitch[i+1].dataList.append(tempData);
        }
    }


}

void TestData::setWRParamAnalog()
{
    PublicDataClass::WR_PARAM_TRIGER_ANALOG sWRParamAnalog;
    sWRParamAnalog.switchMode = 0;
    //analogTrigerInfo[CHANNELNUM_ANALOG]
    for(int i=0;i<CHANNELNUM_ANALOG;i++)
    {
        sWRParamAnalog.analogTrigerInfo[i].isSelect = 1;
        sWRParamAnalog.analogTrigerInfo[i].isComtrade = 1;
        sWRParamAnalog.analogTrigerInfo[i].isSelect_UP = 1;
        sWRParamAnalog.analogTrigerInfo[i].value_UP = 1000;
        sWRParamAnalog.analogTrigerInfo[i].isSelect_Down = 1;
        sWRParamAnalog.analogTrigerInfo[i].value_Down = 100;
        sWRParamAnalog.analogTrigerInfo[i].isSelect_Mutation = 1;
        sWRParamAnalog.analogTrigerInfo[i].type_Mutation = 0;
        sWRParamAnalog.analogTrigerInfo[i].value_Mutation = 200;
        sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic2 = 1;
        sWRParamAnalog.analogTrigerInfo[i].value_Harmonic3 = 123;
        sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic3 = 1;
        sWRParamAnalog.analogTrigerInfo[i].value_Harmonic5 = 123;
        sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic5 = 1;
        sWRParamAnalog.analogTrigerInfo[i].value_Harmonic2 = 123;
        sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic7 = 1;
        sWRParamAnalog.analogTrigerInfo[i].value_Harmonic7 = 123;
    }

    PublicDataClass::GENERAL_DATA tempData;

    pubData.generalWRParamAnalog[0].dataNum = 1;
    tempData.type = pubData.Type_sbyte;
    tempData.length = pubData.getLenfromType(tempData.type);
    tempData.value = sWRParamAnalog.switchMode;
    pubData.generalWRParamAnalog[0].dataList.append(tempData);


    for(int i=0;i<CHANNELNUM_ANALOG;i++)
    {
        pubData.generalWRParamAnalog[i+1].dataNum = 17;
        for(int j=0;j<17;j++)
        {
            tempData.type = pubData.Type_sbyte;

            switch (j) {
                case 0:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect);
                }break;
                case 1:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isComtrade);
                }break;
                case 2:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect_UP);
                }break;
                case 3:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].value_UP);
                    tempData.type = pubData.Type_float;
                }break;
                case 4:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect_Down);
                }break;
                case 5:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].value_Down);
                    tempData.type = pubData.Type_float;
                }break;
                case 6:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect_Mutation);
                }break;
                case 7:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].type_Mutation);
                }break;
                case 8:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].value_Mutation);
                    tempData.type = pubData.Type_float;
                }break;
                case 9:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic2);
                }break;
                case 10:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].value_Harmonic2);
                    tempData.type = pubData.Type_float;
                }break;
                case 11:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic3);
                }break;
                case 12:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].value_Harmonic3);
                    tempData.type = pubData.Type_float;
                }break;
                case 13:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic5);
                }break;
                case 14:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].value_Harmonic5);
                    tempData.type = pubData.Type_float;
                }break;
                case 15:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].isSelect_Harmonic7);
                }break;
                case 16:{
                    tempData.value = QString::number(sWRParamAnalog.analogTrigerInfo[i].value_Harmonic7);
                    tempData.type = pubData.Type_float;
                }break;
            }
            tempData.length = pubData.getLenfromType(tempData.type);
            pubData.generalWRParamAnalog[i+1].dataList.append(tempData);
        }

    }


}

//分组/序分量配置
void TestData::setWRParamComponent()
{//generalWRParamComponent
    PublicDataClass::WR_PARAM_COMPONENT sWRParamComponent;

    sWRParamComponent.groupTotalnum = 2;

    for(int i=0;i<sWRParamComponent.groupTotalnum;i++)
    {
        sWRParamComponent.componentInfo[i].groupSEQnum = 1+1;
        sWRParamComponent.componentInfo[i].isSelect_UP_P = 1;//正序上限是否选择
        sWRParamComponent.componentInfo[i].value_UP_P = 1;//越上限定值
        sWRParamComponent.componentInfo[i].isSelect_Down_P = 1;//正序下限是否选择
        sWRParamComponent.componentInfo[i].value_Down_P = 1;//越下限定值
        sWRParamComponent.componentInfo[i].isSelect_Mutation_P = 1;//正序突变量是否选择
        sWRParamComponent.componentInfo[i].value_Mutation_P = 1;//正序突变量定值
        sWRParamComponent.componentInfo[i].isSelect_UP_N = 1;//负序上限是否选择
        sWRParamComponent.componentInfo[i].value_UP_N = 1;//越上限定值
        sWRParamComponent.componentInfo[i].isSelect_Mutation_N = 1;//负序突变量是否选择
        sWRParamComponent.componentInfo[i].value_Mutation_N = 1;//负序突变量定值
        sWRParamComponent.componentInfo[i].isSelect_UP_Z = 1;//零序上限是否选择
        sWRParamComponent.componentInfo[i].value_UP_Z = 1;//越上限定值
        sWRParamComponent.componentInfo[i].isSelect_Mutation_Z = 1;//零序突变量是否选择
        sWRParamComponent.componentInfo[i].value_Mutation_Z = 1;//零序突变量定值
    }

    PublicDataClass::GENERAL_DATA tempData;

    pubData.generalWRParamComponent[0].dataNum = 1;
    tempData.type = pubData.Type_sbyte;
    tempData.length = pubData.getLenfromType(tempData.type);
    tempData.value = sWRParamComponent.groupTotalnum;
    pubData.generalWRParamComponent[0].dataList.append(tempData);


    for(int i=0;i<sWRParamComponent.groupTotalnum;i++)
    {
        pubData.generalWRParamComponent[i+1].dataNum = 15;
        for(int j=0;j<15;j++)
        {
            tempData.type = pubData.Type_sbyte;

            switch (j) {
                case 0:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].groupSEQnum);
                }break;
                case 1:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].isSelect_UP_P);
                }break;
                case 2:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].value_UP_P);
                    tempData.type = pubData.Type_float;
                }break;
                case 3:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].isSelect_Down_P);

                }break;
                case 4:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].value_Down_P);
                    tempData.type = pubData.Type_float;
                }break;
                case 5:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].isSelect_Mutation_P);

                }break;
                case 6:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].value_Mutation_P);
                    tempData.type = pubData.Type_float;
                }break;
                case 7:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].isSelect_UP_N);
                }break;
                case 8:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].value_UP_N);
                    tempData.type = pubData.Type_float;
                }break;
                case 9:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].isSelect_Mutation_N);
                }break;
                case 10:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].value_Mutation_N);
                    tempData.type = pubData.Type_float;
                }break;
                case 11:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].isSelect_UP_Z);
                }break;
                case 12:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].value_UP_Z);
                    tempData.type = pubData.Type_float;
                }break;
                case 13:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].isSelect_Mutation_Z);
                }break;
                case 14:{
                    tempData.value = QString::number(sWRParamComponent.componentInfo[i].value_Mutation_Z);
                    tempData.type = pubData.Type_float;
                }break;

            }
            tempData.length = pubData.getLenfromType(tempData.type);
            pubData.generalWRParamComponent[i+1].dataList.append(tempData);
        }

    }
}

//
//
//
//电能检定输入脉冲参数
void TestData::setWRParamPulseIn()
{
    PublicDataClass::PM_PARAM_PowerMeter_IN sWRParamPulseIn;

    sWRParamPulseIn.meterConstant = 100;
    sWRParamPulseIn.checkLaps = 100;
    sWRParamPulseIn.meterType = 0;
    sWRParamPulseIn.pulseConstant = 100;

    pubData.generalWRParamPulseIn.dataNum = 4;
    pubData.generalWRParamPulseIn.dataList.clear();

    PublicDataClass::GENERAL_DATA tempData;
    //值
    //类型
    //长度(字符串型数据自行设置长度)

    for(int i=0;i<pubData.generalWRParamPulseIn.dataNum;i++)
    {
        tempData.type = pubData.Type_ushort;

        switch (i) {
            case 0:{
                tempData.value = QString::number(sWRParamPulseIn.meterConstant);
            }break;
            case 1:{
                tempData.value = QString::number(sWRParamPulseIn.checkLaps);
            }break;
            case 2:{
                tempData.value = QString::number(sWRParamPulseIn.meterType);
                tempData.type = pubData.Type_sbyte;
            }break;
            case 3:{
                tempData.value = QString::number(sWRParamPulseIn.pulseConstant);
            }break;
        }
        tempData.length = pubData.getLenfromType(tempData.type);

        pubData.generalWRParamPulseIn.dataList.append(tempData);
    }
}

//电能输出脉冲参数
void TestData::setWRParamPulseOut()
{
    PublicDataClass::PM_PARAM_PowerMeter_OUT sWRParamPulseOut;

    sWRParamPulseOut.mode = 1;
    sWRParamPulseOut.pulseConstant = 1000;

    pubData.generalWRParamPulseOut.dataNum = 2;
    pubData.generalWRParamPulseOut.dataList.clear();

    PublicDataClass::GENERAL_DATA tempData;
    //值
    //类型
    //长度(字符串型数据自行设置长度)

    for(int i=0;i<pubData.generalWRParamPulseOut.dataNum;i++)
    {

        switch (i) {
            case 0:{
                tempData.value = QString::number(sWRParamPulseOut.mode);
                tempData.type = pubData.Type_sbyte;
            }break;
            case 1:{
                tempData.value = QString::number(sWRParamPulseOut.pulseConstant);
                tempData.type = pubData.Type_ushort;
            }break;

        }
        tempData.length = pubData.getLenfromType(tempData.type);

        pubData.generalWRParamPulseOut.dataList.append(tempData);
    }
}
