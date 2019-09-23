#include "devdatatransfer_wr.h"
#include <QGuiApplication>

#include "publicdataclass.h"
PublicDataClass pubData;
DevDataTransfer_wr::DevDataTransfer_wr(QObject *parent) : QObject(parent)
{

    XmlData.ParamList.clear();



}

void DevDataTransfer_wr::test()
{
    qDebug()<<"test in datatransfer";
}


void DevDataTransfer_wr::wr_sendParamCommunicate(int            typeID,
                                             QString        portName1,
                                             unsigned short boundRate1,
                                             char           parity1,
                                             QString        portName2,
                                             unsigned short boundRate2,
                                             char           parity2)
{
    testdata.setParamCommunicate();

    qDebug()<<"pubData.generalParamCommunicate.dataNum:"<<pubData.generalParamCommunicate.dataNum;

    qDebug()<<"pubData.sParamCommunicate  portName:"<<pubData.sParamCommunicate.portName1
           <<" ;boundRate1:"<<QString::number(pubData.sParamCommunicate.boundRate1)
           <<" ;parity1:"<<QString::number(pubData.sParamCommunicate.parity1);



    char objecttype = 5;
    char acttype = 2;
    unsigned int masteradr = 0;
    unsigned int slaveadr = 0;
    char *pbuf=new char[1024];
    int len=0;
    bool isover;


/*  从xml中获取数据类型和数据长度
    QString path = qApp->applicationDirPath();
    path += "/xml/xml_ParamCommunicate.xml";

    QString openstr = priProtocal.AnalysisXml(path,&XmlData);
    if(openstr!="1")
    {
        qDebug()<<g_C2Q("打开XML文件失败：")<<path;
        return;
    }
    if(XmlData.ParamList.count()<2)
    {
        return;
    }
    //    //信息体地址：0x01000080
    //    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    //    temp_row.RowOffset = 0x0080;//行偏移量(低位)
    XmlData.ParamList[0].RowTypeID = typeID;
    XmlData.ParamList[0].IsShow = false;
    //XmlData.ParamList[0].RowInfoAddr = 0x0100;
    //XmlData.ParamList[0].RowOffset = 0x0080;
    XmlData.ParamList[0].Param[0].value = portName1;
    XmlData.ParamList[0].Param[1].value = QString::number(boundRate1);
    XmlData.ParamList[0].Param[2].value = QString::number(parity1);
    XmlData.ParamList[1].RowTypeID = typeID;
    XmlData.ParamList[1].IsShow = false;
    XmlData.ParamList[1].Param[0].value = portName2;
    XmlData.ParamList[1].Param[1].value = QString::number(boundRate2);
    XmlData.ParamList[1].Param[2].value = QString::number(parity2);
    */

    //直接赋值
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowName = g_C2Q("基本通讯参数");//XmlData.ParamList[0]
    temp_row.RowTypeID = typeID;//下设或读取
    temp_row.IsShow = false;       //是否展示
    //信息体地址：0x01000080
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0080;//行偏移量(低位)

    temp_row.Param.clear();
    for(int i=0;i<pubData.generalParamCommunicate.dataNum;i++)
    {
        qDebug()<<"pubData.generalParamCommunicate.dataList_"<<i<<":"
               <<pubData.generalParamCommunicate.dataList[i].value
              <<","<<pubData.generalParamCommunicate.dataList[i].type
             <<","<<pubData.generalParamCommunicate.dataList[i].length;

        temp_column.value = pubData.generalParamCommunicate.dataList[i].value;
        temp_column.type = pubData.generalParamCommunicate.dataList[i].type;
        temp_column.length = pubData.generalParamCommunicate.dataList[i].length;
        temp_row.Param.append(temp_column);
    }

//    temp_column.value = portName1;
//    temp_column.type = 12;//固定长度字符串
//    temp_column.length = 6;
//    temp_row.Param.append(temp_column);
//    temp_column.value = QString::number(boundRate1);
//    temp_column.type = 3;//短整型
//    temp_column.length = 2;
//    temp_row.Param.append(temp_column);
//    temp_column.value = QString::number(parity1);
//    temp_column.type = 1;//字节型
//    temp_column.length = 1;
//    temp_row.Param.append(temp_column);

//    temp_column.value = portName2;
//    temp_column.type = 12;//固定长度字符串
//    temp_column.length = 6;
//    temp_row.Param.append(temp_column);
//    temp_column.value = QString::number(boundRate2);
//    temp_column.type = 3;//短整型
//    temp_column.length = 2;
//    temp_row.Param.append(temp_column);
//    temp_column.value = QString::number(parity2);
//    temp_column.type = 1;//字节型
//    temp_column.length = 1;
//    temp_row.Param.append(temp_column);




    XmlData.ParamList.append(temp_row);

    priProtocal.EncodeParam(XmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,1);
//    for(int i=0;i<len;i++)
//    {
//        qDebug() << i<<len<< QString::number(*(pbuf+i),16);
//    }
    QString temp_str;
    for(int i=0;i<len;i++)
    {
        temp_str += QString("%1").arg((unsigned char)(*(pbuf+i)),2,16,QLatin1Char('0'));
        temp_str += " ";
    }
    qDebug() << temp_str<<"(len="<<len<<")";

}





