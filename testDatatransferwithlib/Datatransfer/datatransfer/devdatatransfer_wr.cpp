#include "devdatatransfer_wr.h"

DevDataTransfer_wr::DevDataTransfer_wr(QObject *parent) : QObject(parent)
{

    //XmlData.ParamList.clear();
}

void DevDataTransfer_wr::test()
{
    qDebug()<<"test in datatransfer";
}


/*
void DevDataTransfer_wr::wr_sendParamCommunicate(int            typeID,
                                             QString        portName1,
                                             unsigned short boundRate1,
                                             char           parity1,
                                             QString        portName2,
                                             unsigned short boundRate2,
                                             char           parity2)
{

    char objecttype = 5;
    char acttype = 2;
    unsigned int masteradr = 0;
    unsigned int slaveadr = 0;
    char *pbuf=new char[1024];
    int len=0;
    bool isover;

    XmlData.ParamList[0].RowName = g_C2Q("基本通讯参数");
    XmlData.ParamList[0].RowTypeID = typeID;//下设或读取
    XmlData.ParamList[0].IsShow = false;       //是否展示
    //信息体地址：0x01000080
    XmlData.ParamList[0].RowInfoAddr = 0x0100;//参数信息体地址(高位)
    XmlData.ParamList[0].RowOffset = 0x0080;//行偏移量(低位)

//    QString ColumnName;//列名
//    QString desc;//描述
//    QString value;//值
//    int type;//类型
//    int length;//长度
    QList<QVariant> tempList;
    tempList.clear();
    tempList.append(portName1);
    tempList.append(boundRate1);
    tempList.append(parity1);
    tempList.append(portName2);
    tempList.append(boundRate2);
    tempList.append(parity2);

    for(int i=0;i<tempList.count();i++)
    {
        XmlData.ParamList[0].Param[i].value = tempList[i].toString();
        XmlData.ParamList[0].Param[i].type = tempList[i].type();//需进行QVariant数据类型枚举与私有规约定义的数据类型转换
        //==========
        //XmlData.ParamList[0].Param[i].type =
        //XmlData.ParamList[0].Param[i].length =
    }

    priProtocal.EncodeParam(XmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,1);
    for(int i=0;i<len;i++)
    {
        qDebug() << i<<len<< QString::number(*(pbuf+i),16);
    }



}
*/




