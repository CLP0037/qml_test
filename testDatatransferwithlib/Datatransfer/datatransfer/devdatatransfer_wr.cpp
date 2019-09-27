#include "devdatatransfer_wr.h"
#include <QGuiApplication>

#include "publicdataclass.h"
PublicDataClass pubData;
DevDataTransfer_wr::DevDataTransfer_wr(QObject *parent) : QObject(parent)
{
    XmlData.ParamList.clear();
    //XmlData_ParamCommunicate.ParamList.clear();

    wrClient = new WRClientStuff("localhost", 4001);
    connect(wrClient, &WRClientStuff::msgRecv, this, &DevDataTransfer_wr::respondmsgRecv);
    //connect(wrClient, &WRClientStuff::msgSend, this, &DevDataTransfer_wr::respondmsgSend);
    connect(wrClient, &WRClientStuff::statusChanged, this, &DevDataTransfer_wr::respondStatus);
    // FIXME change this connection to the new syntax
    connect(wrClient->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(gotError(QAbstractSocket::SocketError)));

//    void clientNewConnect(QString ip , int port);
//    void clientDisconnected(QString ip , int port);
//    //void msgSend(QByteArray sendBuf);
//    void msgRecv(QByteArray recvBuf);
    wrServer = new WRServerStuff(this);
    connect(wrServer, &WRServerStuff::clientNewConnect,this, &DevDataTransfer_wr::respondclientNewConnect);
    connect(wrServer, &WRServerStuff::clientDisconnected,this, &DevDataTransfer_wr::respondclientDisconnected);
    connect(wrServer, &WRServerStuff::msgRecv,this, &DevDataTransfer_wr::respondmsgRecv_server);
}

void DevDataTransfer_wr::clientConnect()
{
    wrClient->connect2host(10000);
}

void DevDataTransfer_wr::clientDisConnect()
{
    wrClient->closeConnection();
}

void DevDataTransfer_wr::test()
{
    qDebug()<<"test in datatransfer";
}

void DevDataTransfer_wr::startServer(int port)
{
    int rtn = wrServer->startListen(port);
    if(rtn < 0)
    {
        qDebug()<<g_C2Q("启动监听失败");
    }
    qDebug()<<g_C2Q("启动监听");
}

void DevDataTransfer_wr::stopServer()
{
    wrServer->stopListen();
}

void DevDataTransfer_wr::serverSendbuf_filepath(int index,QString filepath)//测试===录波完成路径回复
{
    char objecttype = 6;
    char acttype = 1;
    char typeID = 1;
    unsigned int masteradr = 0;
    unsigned int slaveadr = 0;
    char *pbuf=new char[1024];
    int len=0;
    bool isover = true;
    char SQ = 1;

    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;
    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x00010000
    temp_row.RowInfoAddr = 0x0001;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0000;//行偏移量(低位)

    temp_row.Param.clear();
    temp_column.value = filepath;
    temp_column.type = 0x0D;//string
    temp_column.length = filepath.trimmed().length();
    temp_row.Param.append(temp_column);
    XmlData.ParamList.clear();
    XmlData.ParamList.append(temp_row);

    priProtocal.EncodeParam(XmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,SQ);

    QByteArray buf;
    buf.clear();
    QString temp_str;
    for(int i=0;i<len;i++)
    {
        temp_str += QString("%1").arg((unsigned char)(*(pbuf+i)),2,16,QLatin1Char('0'));
        temp_str += " ";
        buf.append((unsigned char)(*(pbuf+i)));
    }
    qDebug()<<"server send:" << temp_str<<"(len="<<len<<")";

    wrServer->sendbufToClient(index,buf);
}

void DevDataTransfer_wr::serverSendbuf_meter(int index)
{
    char objecttype = 6;
    char acttype = 1;
    char typeID = 1;
    unsigned int masteradr = 0;
    unsigned int slaveadr = 0;
    char *pbuf=new char[1024];
    int len=0;
    bool isover;
    char SQ = 1;

    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;
    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x00010001
    temp_row.RowInfoAddr = 0x0001;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0001;//行偏移量(低位)

    //传值


    priProtocal.EncodeParam(XmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,SQ);

    QByteArray buf;
    buf.clear();
    QString temp_str;
    for(int i=0;i<len;i++)
    {
        temp_str += QString("%1").arg((unsigned char)(*(pbuf+i)),2,16,QLatin1Char('0'));
        temp_str += " ";
        buf.append((unsigned char)(*(pbuf+i)));
    }
    qDebug()<<"server send:" << temp_str<<"(len="<<len<<")";

    wrServer->sendbufToClient(index,buf);
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

//    qDebug()<<"pubData.sParamCommunicate  portName:"<<pubData.sParamCommunicate.portName1
//           <<" ;boundRate1:"<<QString::number(pubData.sParamCommunicate.boundRate1)
//           <<" ;parity1:"<<QString::number(pubData.sParamCommunicate.parity1);



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
//        qDebug()<<"pubData.generalParamCommunicate.dataList_"<<i<<":"
//               <<pubData.generalParamCommunicate.dataList[i].value
//              <<","<<pubData.generalParamCommunicate.dataList[i].type
//             <<","<<pubData.generalParamCommunicate.dataList[i].length;

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



    XmlData.ParamList.clear();
    XmlData.ParamList.append(temp_row);

    priProtocal.EncodeParam(XmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,1);
//    for(int i=0;i<len;i++)
//    {
//        qDebug() << i<<len<< QString::number(*(pbuf+i),16);
//    }

    QByteArray buf;
    buf.clear();
    QString temp_str;
    for(int i=0;i<len;i++)
    {
        temp_str += QString("%1").arg((unsigned char)(*(pbuf+i)),2,16,QLatin1Char('0'));
        temp_str += " ";
        buf.append((unsigned char)(*(pbuf+i)));
    }
    qDebug()<<"client send:" << temp_str<<"(len="<<len<<")";


    wrClient->bufSend(buf);
}



void DevDataTransfer_wr::respondStatus(bool newStatus)
{
    if(newStatus)
    {
        qDebug()<<"client connection established";
    }
    else
    {
        qDebug()<<"client connection closed";
    }
}

void DevDataTransfer_wr::respondmsgRecv(QByteArray qbaBuf)
{
    char* pbuf = new char[1024];

    QString temp_str;
    for(int i=0;i<qbaBuf.size();i++)
    {
        temp_str += QString("%1").arg((unsigned char)(qbaBuf[i]),2,16,QLatin1Char('0'));
        temp_str += " ";
        pbuf[i] = (unsigned char)(qbaBuf[i]);
    }
    qDebug()<<"client recv:"  << temp_str<<"(len="<<qbaBuf.size()<<")";

    QList<CustomProtocol::_ReturnDataStruct> returndatalist;
    priProtocal.DecodeFrame(pbuf,qbaBuf.size(),returndatalist);
    qDebug()<<"returndatalist count:"<<returndatalist.count();
    qDebug()<<"TypeID:"<<returndatalist[0].TypeID;
    qDebug()<<"ObjectType:"<<returndatalist[0].ObjectType;
    qDebug()<<"DataLength:"<<returndatalist[0].DataLength;
    qDebug()<<"Revlen:"<<returndatalist[0].Revlen;

    CustomProtocol::_XmlDataStruct rtnXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;
    switch((unsigned char)(pbuf[23]))
    {
        case 0x80://通讯配置
        {

            temp_row.RowName = g_C2Q("基本通讯参数");
            //信息体地址：0x01000080
            temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
            temp_row.RowOffset = 0x0080;//行偏移量(低位)

            temp_row.Param.clear();
            for(int i=0;i<pubData.generalParamCommunicate.dataNum;i++)
            {
                //temp_column.value = pubData.generalParamCommunicate.dataList[i].value;
                temp_column.value = "";
                temp_column.type = pubData.generalParamCommunicate.dataList[i].type;
                temp_column.length = pubData.generalParamCommunicate.dataList[i].length;
                temp_row.Param.append(temp_column);
            }

            rtnXmlData.ParamList.clear();
            rtnXmlData.ParamList.append(temp_row);
        }break;
        case 0x81://系统配置
            switch(pbuf[24])
            {
                case 0x00://
                {

                }break;
                case 0x01://
                {

                }break;
                case 0x02://
                {

                }break;
                case 0x03://
                {

                }break;
            }
        break;
        case 0x82://录波参数
            switch(pbuf[24])
            {
            case 0x00://
            {

            }break;
            case 0x01://
            {

            }break;
            case 0x02://
            {

            }break;
            case 0x03://
            {

            }break;
            case 0x04://
            {

            }break;
            case 0x05://
            {

            }break;
            }
        break;
        case 0x83://电能量
            switch(pbuf[24])
            {
            case 0x00://
            {

            }break;
            case 0x01://
            {

            }break;
            case 0x02://
            {

            }break;

            }
        break;
        case 0x84://校准
            switch(pbuf[24])
            {
            case 0x00://
            {

            }break;
            case 0x01://
            {

            }break;

            }
        break;
        case 0x85://录波
            switch(pbuf[24])
            {
            case 0x00://
            {

            }break;
            case 0x01://
            {

            }break;

            }
        break;
    }
    priProtocal.AnalysisRevData(rtnXmlData,1,returndatalist[0].DataField,returndatalist[0].DataLength);
    qDebug()<<"ParamList.count():"<<rtnXmlData.ParamList.count();
    if(XmlData.ParamList.count() > 0)
    {
        qDebug()<<"RowInfoAddr:"<<rtnXmlData.ParamList[0].RowInfoAddr;
        qDebug()<<"RowOffset:"<<rtnXmlData.ParamList[0].RowOffset;

        for(int i=0;i<rtnXmlData.ParamList.count();i++)
        {
            for(int j=0;j<rtnXmlData.ParamList[i].Param.count();j++)
            {
                //XmlData.ParamList[i].Param[j].value = "";
                qDebug()<<"rtnXmlData.ParamList[i].Param[j].value"<<rtnXmlData.ParamList[i].Param[j].value
                       <<"(i="<<i<<",j="<<j<<")";
            }
        }
    }









//    //CustomProtocol::_XmlDataStruct rtnXmlData;
//    for(int i=0;i<XmlData.ParamList.count();i++)
//    {
//        for(int j=0;j<XmlData.ParamList[i].Param.count();j++)
//        {
//            qDebug()<<"XmlData.ParamList[i].Param[j].value"<<XmlData.ParamList[i].Param[j].value
//                   <<"(i="<<i<<",j="<<j<<")";
//            XmlData.ParamList[i].Param[j].value = "";
//        }
//    }
//    //SQ=1 连续
//    priProtocal.AnalysisRevData(XmlData,1,returndatalist[0].DataField,returndatalist[0].DataLength);
//    qDebug()<<"ParamList.count():"<<XmlData.ParamList.count();
//    if(XmlData.ParamList.count() > 0)
//    {
//        qDebug()<<"RowInfoAddr:"<<XmlData.ParamList[0].RowInfoAddr;
//        qDebug()<<"RowOffset:"<<XmlData.ParamList[0].RowOffset;

//        for(int i=0;i<XmlData.ParamList.count();i++)
//        {
//            for(int j=0;j<XmlData.ParamList[i].Param.count();j++)
//            {
//                //XmlData.ParamList[i].Param[j].value = "";
//                qDebug()<<"XmlData.ParamList[i].Param[j].value"<<XmlData.ParamList[i].Param[j].value
//                       <<"(i="<<i<<",j="<<j<<")";
//            }
//        }
//    }


}

void DevDataTransfer_wr::respondmsgSend(QByteArray qbaBuf)
{

}

void DevDataTransfer_wr::gotError(QAbstractSocket::SocketError err)
{
    qDebug()<<"SocketError num:"<<err;
}

void DevDataTransfer_wr::respondclientNewConnect(QString ip , int port)
{
    qDebug()<<"respondclientNewConnect"<<ip<<":"<<port;
}
void DevDataTransfer_wr::respondclientDisconnected(QString ip , int port)
{
    qDebug()<<"respondclientDisconnected"<<ip<<":"<<port;
}
//void respondmsgSend_server(QByteArray sendBuf);
void DevDataTransfer_wr::respondmsgRecv_server(QString ip , int port,QByteArray qbaBuf)
{
    char* pbuf = new char[1024];

    QString temp_str;
    for(int i=0;i<qbaBuf.size();i++)
    {
        temp_str += QString("%1").arg((unsigned char)(qbaBuf[i]),2,16,QLatin1Char('0'));
        temp_str += " ";
        pbuf[i] = (unsigned char)(qbaBuf[i]);
    }
    qDebug()<<"client recv:"  << temp_str<<"(len="<<qbaBuf.size()<<",from"<<ip<<":"<<port<<")";


    //解析
    QList<CustomProtocol::_ReturnDataStruct> returndatalist;//针对通讯连帧
    CustomProtocol::_XmlDataStruct rtnXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    priProtocal.DecodeFrame(pbuf,qbaBuf.size(),returndatalist);
    qDebug()<<"returndatalist count:"<<returndatalist.count();


    if(returndatalist.count() > 0)
    {
        qDebug()<<"TypeID:"<<returndatalist[0].TypeID;
        qDebug()<<"ObjectType:"<<returndatalist[0].ObjectType;
        qDebug()<<"DataLength:"<<returndatalist[0].DataLength;
        qDebug()<<"Revlen:"<<returndatalist[0].Revlen;
        qDebug()<<"Revlen:"<<returndatalist[0].ActType;

        switch(returndatalist[0].ActType)//设备操作类型：1-录波仪；2-标准表
        {
            case 1:
            {
                //若后期需要多个功能，进行拆解
                //接收到录波设置
//                Float 追忆时间
//                Float 总录波时间
//                Int 采样率
//                String 录波文件名称
//                Int 触发方式（暂无）
//                Bool 开入逻辑，0或1与
//                Bool x 16(开入选择)

                temp_column.value = "";
                temp_column.type = pubData.Type_float;
                temp_column.length = 4;
                temp_row.Param.append(temp_column);

                temp_column.value = "";
                temp_column.type = pubData.Type_float;
                temp_column.length = 4;
                temp_row.Param.append(temp_column);

                temp_column.value = "";
                temp_column.type = pubData.Type_int;
                temp_column.length = 4;
                temp_row.Param.append(temp_column);

                temp_column.value = "";
                temp_column.type = pubData.Type_string;
                temp_column.length = 64;
                temp_row.Param.append(temp_column);

                temp_column.value = "";
                temp_column.type = pubData.Type_int;
                temp_column.length = 4;
                temp_row.Param.append(temp_column);

                temp_column.value = "";
                temp_column.type = pubData.Type_bool;
                temp_column.length = 1;
                temp_row.Param.append(temp_column);

                temp_column.value = "";
                temp_column.type = pubData.Type_bool;
                temp_column.length = 1;
                temp_row.Param.append(temp_column);

                rtnXmlData.ParamList.clear();
                rtnXmlData.ParamList.append(temp_row);


            }break;
            case 2:
            {

            }break;
        }


        priProtocal.AnalysisRevData(rtnXmlData,1,returndatalist[0].DataField,returndatalist[0].DataLength);
        qDebug()<<"ParamList.count():"<<rtnXmlData.ParamList.count();
        if(XmlData.ParamList.count() > 0)
        {
            qDebug()<<"RowInfoAddr:"<<rtnXmlData.ParamList[0].RowInfoAddr;
            qDebug()<<"RowOffset:"<<rtnXmlData.ParamList[0].RowOffset;

            for(int i=0;i<rtnXmlData.ParamList.count();i++)
            {
                for(int j=0;j<rtnXmlData.ParamList[i].Param.count();j++)
                {
                    //XmlData.ParamList[i].Param[j].value = "";
                    qDebug()<<"rtnXmlData.ParamList[i].Param[j].value"<<rtnXmlData.ParamList[i].Param[j].value
                           <<"(i="<<i<<",j="<<j<<")";
                }
            }
        }



    }








}

