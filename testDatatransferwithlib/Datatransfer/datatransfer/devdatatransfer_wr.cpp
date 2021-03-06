﻿#include "devdatatransfer_wr.h"
#include <QGuiApplication>

#include "publicdataclass.h"
PublicDataClass pubData;
DevDataTransfer_wr::DevDataTransfer_wr(QObject *parent) : QObject(parent)
{
    XmlData.ParamList.clear();

    wrClient = new WRClientStuff();
    connect(wrClient, &WRClientStuff::msgRecv, this, &DevDataTransfer_wr::respondmsgRecv);
    //connect(wrClient, &WRClientStuff::msgSend, this, &DevDataTransfer_wr::respondmsgSend);
    connect(wrClient, &WRClientStuff::statusChanged, this, &DevDataTransfer_wr::respondStatus);
    // FIXME change this connection to the new syntax
    connect(wrClient->tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(gotError(QAbstractSocket::SocketError)));

    wrClient_realtime = new WRClientStuff();
    connect(wrClient_realtime, &WRClientStuff::msgRecv, this, &DevDataTransfer_wr::respondmsgRecv_realtime);


//    void clientNewConnect(QString ip , int port);
//    void clientDisconnected(QString ip , int port);
//    //void msgSend(QByteArray sendBuf);
//    void msgRecv(QByteArray recvBuf);
    wrServer = new WRServerStuff(this);
    connect(wrServer, &WRServerStuff::clientNewConnect,this, &DevDataTransfer_wr::respondclientNewConnect);
    connect(wrServer, &WRServerStuff::clientDisconnected,this, &DevDataTransfer_wr::respondclientDisconnected);
    connect(wrServer, &WRServerStuff::msgRecv,this, &DevDataTransfer_wr::respondmsgRecv_server);

    returnCacheData.clear();
    returnCacheData_realtime.clear();
}

void DevDataTransfer_wr::clientConnect(QString host,int port)
{
    wrClient->connect2host(10000,host,port);//
}

void DevDataTransfer_wr::clientDisConnect()
{
    wrClient->closeConnection();
}
//_realtime
void DevDataTransfer_wr::clientConnect_realtime(QString host,int port)
{
    wrClient_realtime->connect2host(10000,host,port);//
}

void DevDataTransfer_wr::clientDisConnect_realtime()
{
    wrClient_realtime->closeConnection();
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

//======================================= 与中间键通讯交互 ==========================================//
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
    temp_column.length = filepath.length();//.trimmed()
    temp_row.Param.append(temp_column);
    XmlData.ParamList.clear();
    XmlData.ParamList.append(temp_row);

    priProtocal_server.EncodeParam(XmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,SQ);

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

    XmlData.ParamList.append(temp_row);

    priProtocal_server.EncodeParam(XmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,SQ);

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

//======================================= 与下位机通讯交互 ==========================================//
void DevDataTransfer_wr::encodefromXMLData(CustomProtocol::_XmlDataStruct tempXmlData,int type)
{
    char objecttype = 5;
    char acttype = 1;
    unsigned int masteradr = 0;
    unsigned int slaveadr = 0;
    char *pbuf=new char[1024];
    int len=0;
    bool isover;
    int SQ = 1;


    //priProtocal.EncodeParam(tempXmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,1);
    switch (type) {
        case 1:{
            priProtocal.EncodeParam(tempXmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,1);
        }break;
        case 2:{
            priProtocal_realtime.EncodeParam(tempXmlData,pbuf,len,isover,objecttype,acttype,masteradr,slaveadr,1);
        }break;

    }

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss:zzz dddd");
    QByteArray buf;
    buf.clear();
    QString temp_str;
    for(int i=0;i<len;i++)
    {
        temp_str += QString("%1").arg((unsigned char)(*(pbuf+i)),2,16,QLatin1Char('0'));
        temp_str += " ";
        buf.append((unsigned char)(*(pbuf+i)));
    }
    qDebug()<<"client send_"<<timeStr<<":" << temp_str<<"(len="<<len<<")"<<"type_"<<type;

    switch (type) {
        case 1:{

            wrClient->bufSend(buf);
        }break;
        case 2:{

            wrClient_realtime->bufSend(buf);
        }break;

    }

}

void DevDataTransfer_wr::decodeRecievedData(QByteArray qbaBuf,int type)
{
    char* pbuf = new char[1024*2];
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss:zzz dddd");

    QString temp_str;
    for(int i=0;i<qbaBuf.size();i++)
    {
        temp_str += QString("%1").arg(char(qbaBuf[i])&0xFF,2,16,QChar('0'));
        temp_str += " ";
        pbuf[i] = (unsigned char)(qbaBuf[i]);
    }
    //qDebug()<<"client recv_"<<timeStr<< ":" << temp_str<<"(len="<<qbaBuf.size()<<")";
    int seqnum = pbuf[17] + pbuf[18]*256;
    qDebug()<<"client recv_"<<timeStr<<";type_"<<type<<";seqnum_"<<seqnum;

    QList<CustomProtocol::_ReturnDataStruct> returndatalist;
    //priProtocal.DecodeFrame(qbaBuf.data(),qbaBuf.size(),returndatalist);//pbuf
    switch (type) {
        case 1:{
            priProtocal.DecodeFrame(qbaBuf.data(),qbaBuf.size(),returndatalist);
        }break;
        case 2:{
            priProtocal_realtime.DecodeFrame(qbaBuf.data(),qbaBuf.size(),returndatalist);
        }break;

    }

    qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"returndatalist count:"<<returndatalist.count();

    if(returndatalist.count() > 0)
    {
        qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"TypeID:"<<returndatalist[0].TypeID;
        //qDebug()<<"ObjectType:"<<returndatalist[0].ObjectType;
        //qDebug()<<"DataLength:"<<returndatalist[0].DataLength;
        //qDebug()<<"Revlen:"<<returndatalist[0].Revlen;

        if(returndatalist[0].TypeID == 1)//下载
        {
            //肯定回复，否定回复=======

            if(returndatalist[0].IsOver)//帧传输结束，无后续
            {
                qDebug()<<g_C2Q("参数下载完成");
            }
            else
            {
                qDebug()<<"returndatalist[0].IsOver = false"<<g_C2Q("分帧传输，未完待续");


            }
        }
        else if(returndatalist[0].TypeID == 100)//主动上传
        {
            switch((unsigned char)(pbuf[23]))
            {
                case 0x85://通道2=====实时采样数据信号主动上传后召测
                {
                    CustomProtocol::_XmlDataStruct tempXmlData;
                    CustomProtocol::_RowInforStruct temp_row;
                    CustomProtocol::_ColumnInforStruct temp_column;

                    temp_row.Param.clear();
                    temp_row.RowTypeID = 2;
                    //信息体地址：0x01000185
                    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                    temp_row.RowOffset = 0x0185;//行偏移量(低位)

                    tempXmlData.ParamList.clear();
                    tempXmlData.ParamList.append(temp_row);

                    if(type == 2)
                    {
                        returnCacheData_realtime.clear();
                        encodefromXMLData(tempXmlData,2);
                    }

                }break;
            }
        }
        else if(returndatalist[0].TypeID == 2 )//读取
        {
            QString temp_buf;

            if(type == 1)
            {
                if(seqnum==1)returnCacheData.clear();
                if(returnCacheData.isEmpty())//第一帧缓存，保留信息体地址，后续帧剔除信息体地址
                {
                    temp_buf="";
                    for(int i=0;i<returndatalist[0].DataLength;i++)
                    {
                        returnCacheData.append(returndatalist[0].DataField[i]);
                        temp_buf += QString("%1").arg((unsigned char)(returndatalist[0].DataField[i]),2,16,QLatin1Char('0'));
                        temp_buf += " ";
                    }
                    qDebug()<<"temp_buf(first frame):"<<temp_buf;
                }
                else
                {
                    temp_buf="";
                    for(int i=0;i<returndatalist[0].DataLength;i++)
                    {
                        returnCacheData.append(returndatalist[0].DataField[i]);
                        temp_buf += QString("%1").arg((unsigned char)(returndatalist[0].DataField[i]),2,16,QLatin1Char('0'));
                        temp_buf += " ";
                    }
                    //qDebug()<<"temp_buf:"<<temp_buf;
                }
                qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"returndatalist[0].DataLength:"<<returndatalist[0].DataLength<<";returnCacheData total size:"<<returnCacheData.size();
            }
            else if(type == 2)
            {
                if(seqnum==1)returnCacheData_realtime.clear();
                if(returnCacheData_realtime.isEmpty())//第一帧缓存，保留信息体地址，后续帧剔除信息体地址
                {
                    temp_buf="";
                    for(int i=0;i<returndatalist[0].DataLength;i++)
                    {
                        returnCacheData_realtime.append(returndatalist[0].DataField[i]);
                        temp_buf += QString("%1").arg((unsigned char)(returndatalist[0].DataField[i]),2,16,QLatin1Char('0'));
                        temp_buf += " ";
                    }
                    //qDebug()<<"temp_buf(first frame):"<<temp_buf;
                }
                else
                {
                    temp_buf="";
                    for(int i=0;i<returndatalist[0].DataLength;i++)
                    {
                        returnCacheData_realtime.append(returndatalist[0].DataField[i]);
                        temp_buf += QString("%1").arg((unsigned char)(returndatalist[0].DataField[i]),2,16,QLatin1Char('0'));
                        temp_buf += " ";
                    }
                    //qDebug()<<"temp_buf:"<<temp_buf;
                }
                qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"returndatalist[0].DataLength:"<<returndatalist[0].DataLength<<";returnCacheData_realtime total size:"<<returnCacheData_realtime.size();
            }
            //

            //帧传输是否结束=====传输结束，处理缓存数据
            if(returndatalist[0].IsOver)//帧传输结束，无后续
            {
                qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"returndatalist[0].IsOver = true";
                //帧传输结束，帧解析
                CustomProtocol::_XmlDataStruct rtnXmlData;
                CustomProtocol::_RowInforStruct temp_row;
                CustomProtocol::_ColumnInforStruct temp_column;

                //调用帧解析前帧结构传输
                switch((unsigned char)(pbuf[23]))//pbuf
                {
                    case 0x80://通讯配置
                    {//temp_row.RowName = g_C2Q("基本通讯参数");

//                        //信息体地址：0x01000080
//                        temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
//                        temp_row.RowOffset = 0x0080;//行偏移量(低位)
                        //信息体地址：
                        temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                        temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8);//行偏移量(低位)
                        qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;
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
                    {
                        switch((unsigned char)(pbuf[24]))//pbuf[24]
                        {
                            case 0x00://
                            {
//                                //信息体地址：0x01000080
//                                temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
//                                temp_row.RowOffset = 0x0081;//行偏移量(低位)
                                //信息体地址：
                                temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                                temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8);//行偏移量(低位)
                                qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;
                                temp_row.Param.clear();
                                for(int i=0;i<pubData.generalParamDevInfo.dataNum;i++)
                                {
                                    temp_column.value = "";
                                    temp_column.type = pubData.generalParamDevInfo.dataList[i].type;
                                    temp_column.length = pubData.generalParamDevInfo.dataList[i].length;
                                    temp_row.Param.append(temp_column);
                                }

                                rtnXmlData.ParamList.clear();
                                rtnXmlData.ParamList.append(temp_row);

                            }break;
                            case 0x01://采集通道
                            {


                                rtnXmlData.ParamList.clear();

                                for(int i=0;i<CHANNELNUM_ANALOG;i++)
                                {
                                    //信息体地址：0x01000181
                                    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                                    temp_row.RowOffset = 0x0181 + i;//行偏移量(低位)
//                                    //信息体地址：
//                                    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
//                                    qDebug()<< "qbaBuf[23]" << QString::number(uint(qbaBuf[23]), 16) << "qbaBuf[24]" << QString::number(uint(qbaBuf[24]), 16);
//                                    temp_row.RowOffset = uint(qbaBuf[23])+(uint(qbaBuf[24])*256) + uint(i);//行偏移量(低位)<<8
//                                    qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;

                                    temp_row.Param.clear();
                                    for(int j=0;j<pubData.generalParamChannelInfo[i].dataNum;j++)
                                    {

                                        temp_column.value = "";
                                        temp_column.type = pubData.generalParamChannelInfo[i].dataList[j].type;
                                        temp_column.length = pubData.generalParamChannelInfo[i].dataList[j].length;
                                        temp_row.Param.append(temp_column);

                                        //qDebug()<<"i="<<i<<";j="<<j<<";type = "<<temp_column.type<<";length = "<<temp_column.length;
                                    }
                                    rtnXmlData.ParamList.append(temp_row);
                                }


                            }break;
                            case 0x02://最高采样率数值
                            {
                                //信息体地址：
                                temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                                temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8) ;//行偏移量(低位)
                                qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;
                                temp_row.Param.clear();
                                rtnXmlData.ParamList.clear();
                                temp_column.value = "";
                                temp_column.type = pubData.Type_ushort;
                                temp_column.length = pubData.getLenfromType(temp_column.type);
                                temp_row.Param.append(temp_column);

                                rtnXmlData.ParamList.append(temp_row);

                            }break;
                            case 0x03://校时方式值
                            {
                                //信息体地址：
                                temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                                temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8) ;//行偏移量(低位)
                                qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;
                                temp_row.Param.clear();
                                rtnXmlData.ParamList.clear();
                                temp_column.value = "";
                                temp_column.type = pubData.Type_sbyte;
                                temp_column.length = pubData.getLenfromType(temp_column.type);;
                                temp_row.Param.append(temp_column);

                                rtnXmlData.ParamList.append(temp_row);
                            }break;
                        }
                    }break;
                    case 0x82://录波参数
                    {
                        //信息体地址：
                        temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                        temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8) ;//行偏移量(低位)
                        qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;

                        switch((unsigned char)(pbuf[24]))//pbuf[24]
                        {
                        case 0x00://暂态录波基本配置
                        {
                            temp_row.Param.clear();
                            rtnXmlData.ParamList.clear();
                            for(int i=0;i<pubData.generalWRParamTransient.dataNum;i++)
                            {

                                temp_column.value = "";
                                temp_column.type = pubData.generalWRParamTransient.dataList[i].type;
                                temp_column.length = pubData.generalWRParamTransient.dataList[i].length;
                                temp_row.Param.append(temp_column);
                            }

                            rtnXmlData.ParamList.append(temp_row);

                        }break;
                        case 0x01://稳态录波基本配置
                        {
                            temp_row.Param.clear();

                            rtnXmlData.ParamList.clear();
                            for(int i=0;i<pubData.generalWRParamSteady.dataNum;i++)
                            {

                                temp_column.value = "";
                                temp_column.type = pubData.generalWRParamSteady.dataList[i].type;
                                temp_column.length = pubData.generalWRParamSteady.dataList[i].length;
                                temp_row.Param.append(temp_column);
                            }

                            rtnXmlData.ParamList.append(temp_row);

                        }break;
                        case 0x02://开关量触发
                        {
                            rtnXmlData.ParamList.clear();
                            for(int i=0;i<CHANNELNUM_SWITCH+1;i++)
                            {
                                //信息体地址：
                                temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                                temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8) + i;//行偏移量(低位)
                                qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;

                                temp_row.Param.clear();
                                for(int j=0;j<pubData.generalWRParamSwitch[i].dataNum;j++)
                                {

                                    temp_column.value = "";
                                    temp_column.type = pubData.generalWRParamSwitch[i].dataList[j].type;
                                    temp_column.length = pubData.generalWRParamSwitch[i].dataList[j].length;
                                    temp_row.Param.append(temp_column);
                                }
                                rtnXmlData.ParamList.append(temp_row);
                            }

                        }break;
                        case 0x03://模拟量触发
                        {
                            rtnXmlData.ParamList.clear();
                            for(int i=0;i<CHANNELNUM_ANALOG+1;i++)
                            {
                                //信息体地址：
                                temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                                temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8) + i;//行偏移量(低位)
                                qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;

                                temp_row.Param.clear();
                                for(int j=0;j<pubData.generalWRParamAnalog[i].dataNum;j++)
                                {

                                    temp_column.value = "";
                                    temp_column.type = pubData.generalWRParamAnalog[i].dataList[j].type;
                                    temp_column.length = pubData.generalWRParamAnalog[i].dataList[j].length;
                                    temp_row.Param.append(temp_column);
                                }
                                rtnXmlData.ParamList.append(temp_row);
                            }

                        }break;
                        case 0x04://分组/序分量
                        {
                            rtnXmlData.ParamList.clear();

                            int nums = pubData.generalWRParamComponent[0].dataList[0].value.toInt()+1;
                            for(int i=0;i<nums;i++)
                            {
                                //信息体地址：
                                temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                                temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8) + i;//行偏移量(低位)
                                qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;

                                temp_row.Param.clear();
                                for(int j=0;j<pubData.generalWRParamComponent[i].dataNum;j++)
                                {

                                    temp_column.value = "";
                                    temp_column.type = pubData.generalWRParamComponent[i].dataList[j].type;
                                    temp_column.length = pubData.generalWRParamComponent[i].dataList[j].length;
                                    temp_row.Param.append(temp_column);
                                }
                                rtnXmlData.ParamList.append(temp_row);
                            }

                        }break;
                        case 0x05://手动录波启动/停止设置确认（是否有肯定确认和否定确认？？？）
                        {
                            //信息体地址：
                            temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                            temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8);//行偏移量(低位)
                            qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;

                            temp_row.Param.clear();

                            rtnXmlData.ParamList.append(temp_row);
                        }break;
                        }
                    }break;
                    case 0x83://电能量
                    {
                        //信息体地址：
                        temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                        temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8) ;//行偏移量(低位)
                        qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;


                        switch((unsigned char)(pbuf[24]))
                        {
                        case 0x00://电能表检定启动/停止设置确认
                        {
                            temp_row.Param.clear();
                            rtnXmlData.ParamList.clear();
                            rtnXmlData.ParamList.append(temp_row);
                        }break;
                        case 0x01://电能检定输入脉冲参数
                        {
                            temp_row.Param.clear();

                            rtnXmlData.ParamList.clear();
                            for(int i=0;i<pubData.generalWRParamPulseIn.dataNum;i++)
                            {

                                temp_column.value = "";
                                temp_column.type = pubData.generalWRParamPulseIn.dataList[i].type;
                                temp_column.length = pubData.generalWRParamPulseIn.dataList[i].length;
                                temp_row.Param.append(temp_column);
                            }

                            rtnXmlData.ParamList.append(temp_row);

                        }break;
                        case 0x02://电能输出脉冲参数
                        {
                            temp_row.Param.clear();

                            rtnXmlData.ParamList.clear();
                            for(int i=0;i<pubData.generalWRParamPulseOut.dataNum;i++)
                            {

                                temp_column.value = "";
                                temp_column.type = pubData.generalWRParamPulseOut.dataList[i].type;
                                temp_column.length = pubData.generalWRParamPulseOut.dataList[i].length;
                                temp_row.Param.append(temp_column);
                            }

                            rtnXmlData.ParamList.append(temp_row);

                        }break;

                        }
                    }break;
                    case 0x84://校准
                    {
                        switch((unsigned char)(pbuf[24]))
                        {
                        case 0x00://
                        {

                        }break;
                        case 0x01://
                        {

                        }break;

                        }
                    }break;
                    case 0x85://录波
                    {
                        //信息体地址：0x01000185
                        temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
                        temp_row.RowOffset = 0x0185;//行偏移量(低位)

                        switch((unsigned char)(pbuf[24]))
                        {
                            case 0x00://实时传输启动/停止设置确认
                            {
                                temp_row.Param.clear();
                                rtnXmlData.ParamList.clear();
                                rtnXmlData.ParamList.append(temp_row);
                            }break;
                            case 0x01://实时数据上传
                            {

                                if(type == 1)
                                {
                                    temp_row.Param.clear();
                                    rtnXmlData.ParamList.clear();
                                    rtnXmlData.ParamList.append(temp_row);
                                }
                                else if(type == 2)//默认实时数据通道解析
                                {
                                    //通道个数
                                    //数据点数N
                                    if(returnCacheData_realtime.size() < 14+4)
                                    {
                                        //通用信息无法正常提取，数据域内容异常
                                        qWarning()<<"returndatalist DataLength less than 14+4(wave record data)";
                                        return;
                                    }

                                    //缓存内容
                                    QString temp_str1;
                                    for(int i=0;i<14+4;i++)
                                    {
                                        temp_str1 += QString("%1").arg(char(returnCacheData_realtime[i])&0xFF,2,16,QChar('0'));
                                        temp_str1 += " ";

                                    }
                                    qDebug()<<"returndatalist:" << temp_str1<<"(total len="<<returnCacheData_realtime.size()<<")";


                                    int num_channel = returnCacheData_realtime[7+4]&0xff;
                                    int num_dataN = (returnCacheData_realtime[8+4]&0xff) + (returnCacheData_realtime[9+4]&0xff)*256;
                                    qWarning()<<g_C2Q("录波数据上传：通道个数_")<<num_channel<<g_C2Q(";数据点数N_")<<num_dataN;

                                    pubData.generalWRComtradeData.dataNum = 4 + num_channel*(2+num_dataN);
                                    pubData.generalWRComtradeData.dataList.clear();




        //                            //信息体地址：
        //                            temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
        //                            temp_row.RowOffset = (unsigned char)(pbuf[23])+(((unsigned char)(pbuf[24]))<<8);//行偏移量(低位)

                                    qDebug()<<"temp_row.RowInfoAddr:"<<temp_row.RowInfoAddr<<";temp_row.RowOffset"<<temp_row.RowOffset;
                                    temp_row.Param.clear();

                                    //4个公共信息
                                    for(int i=0;i<4;i++)
                                    {

                                        temp_column.value = "";
                                        switch (i) {
                                        case 0:{
                                            temp_column.type = pubData.Type_datetime;
                                        }break;
                                        case 1:{
                                            temp_column.type = pubData.Type_byte;
                                        }break;
                                        case 2:{
                                            temp_column.type = pubData.Type_ushort;
                                        }break;
                                        case 3:{
                                            temp_column.type = pubData.Type_float;
                                        }break;

                                        }

                                        temp_column.length = pubData.getLenfromType(temp_column.type);
                                        temp_row.Param.append(temp_column);
                                    }
                                    //通道数据信息
                                    for(int i=0;i<num_channel;i++)
                                    {
                                        //通道号
                                        temp_column.value = "";
                                        temp_column.type = pubData.Type_byte;
                                        temp_column.length = pubData.getLenfromType(temp_column.type);
                                        temp_row.Param.append(temp_column);
                                        //通道系数
                                        temp_column.value = "";
                                        temp_column.type = pubData.Type_float;
                                        temp_column.length = pubData.getLenfromType(temp_column.type);
                                        temp_row.Param.append(temp_column);
                                        //数据值1-N
                                        for(int j=0;j<num_dataN;j++)
                                        {
                                            temp_column.value = "";
                                            temp_column.type = pubData.Type_ushort;
                                            temp_column.length = pubData.getLenfromType(temp_column.type);
                                            temp_row.Param.append(temp_column);
                                        }

                                    }

                                    rtnXmlData.ParamList.clear();
                                    rtnXmlData.ParamList.append(temp_row);
                                }


                            }break;

                        }
                    }break;
                }

                qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"ParamList.count():"<<rtnXmlData.ParamList.count();
                switch (type) {
                    case 1:{
                        priProtocal.AnalysisRevData(rtnXmlData,1,returnCacheData.data(),returnCacheData.size());
                        qDebug()<<"ParamList.count():"<<rtnXmlData.ParamList.count()<<";returnCacheData.size():"<<returnCacheData.size();
                        returnCacheData.clear();//解析完成，清空缓存
                    }break;
                    case 2:{
//                        for(int i=0;i<returnCacheData_realtime.size();i++)
//                        {

//                        }
                        priProtocal_realtime.AnalysisRevData(rtnXmlData,1,returnCacheData_realtime.data(),returnCacheData_realtime.size());
                        qDebug()<<"ParamList.count():"<<rtnXmlData.ParamList.count()<<";returnCacheData_realtime.size():"<<returnCacheData_realtime.size();
                        returnCacheData_realtime.clear();//解析完成，清空缓存
                    }break;

                }

                //接收到的内容解析后，进行界面数据刷新
                //refreshData(rtnXmlData);
                if(rtnXmlData.ParamList.count() > 0)
                {
                    qDebug()<<"rtnXmlData.ParamList[0].Param[0].value"<<rtnXmlData.ParamList[0].Param[0].value;
                }
                qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"returndatalist[0].Txlen:"<<returndatalist[0].Txlen;
            }
            else
            {
                qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"returndatalist[0].IsOver = false"<<g_C2Q("分帧传输，未完待续");
            }

        }

        qDebug()<<(QDateTime::currentDateTime()).toString("yyyy-MM-dd hh:mm:ss:zzz")<<"returndatalist[0].Txlen:"<<returndatalist[0].Txlen;
        if(returndatalist[0].Txlen > 0)//有内容发送
        {
            QDateTime time1 = QDateTime::currentDateTime();//获取系统现在的时间
            QString timeStr1 = time1.toString("yyyy-MM-dd hh:mm:ss:zzz dddd");
            QByteArray buf;
            buf.clear();
            QString temp_str;
            for(int i=0;i<returndatalist[0].Txlen;i++)
            {
                temp_str += QString("%1").arg((unsigned char)(returndatalist[0].Tbuf[i]),2,16,QLatin1Char('0'));
                temp_str += " ";
                buf.append((unsigned char)(returndatalist[0].Tbuf[i]));
            }
            qDebug()<<"client send(sequence)_"<<timeStr1<<":" << temp_str<<"(len="<<returndatalist[0].Txlen<<")"<<"type_"<<type;

            //wrClient->bufSend(buf);
            switch (type) {
                case 1:{
                    wrClient->bufSend(buf);
                }break;
                case 2:{
                    wrClient_realtime->bufSend(buf);
                }break;

            }
        }
    }
}

void DevDataTransfer_wr::refreshData(CustomProtocol::_XmlDataStruct rtnXmlData)
{
    if(rtnXmlData.ParamList.count() > 0)
    {
        qDebug()<<"rtnXmlData.ParamList.count():"<<rtnXmlData.ParamList.count();
        for(int i=0;i<rtnXmlData.ParamList.count();i++)
        {
            qDebug()<<"RowInfoAddr:"<<rtnXmlData.ParamList[i].RowInfoAddr
                   <<";RowOffset:"<<rtnXmlData.ParamList[i].RowOffset;
            for(int j=0;j<rtnXmlData.ParamList[i].Param.count();j++)
            {
                if(j == 0)
                    qDebug()<<"rtnXmlData.ParamList[i].Param[j].value"<<rtnXmlData.ParamList[i].Param[j].value//.toUtf8()
                       <<"(i="<<i<<",j="<<j<<")";
            }
        }

       int rowTypeID =  rtnXmlData.ParamList[0].RowTypeID;
       //读取返回或主动上传进行刷新参数
       int rowOffset_base =  rtnXmlData.ParamList[0].RowOffset;
       int rowOffset_H = (rowOffset_base & 0xff)>>8;
       int rowOffset_L = (rowOffset_base & 0xff);
       if(rowTypeID != 2)//设置返回不需要刷新参数
       {
           if(rowTypeID == 100 && rowOffset_L==0x87)
           {
               //仅电能校验后电能量相关数据主动上传需要刷新
               //其他刷新数据均进行召测
           }
           else
               return;
       }

/*

       switch (rowOffset_L) {
           case 0x80://通讯配置
           {
               switch (rowOffset_H) {
                   case 0:{//通讯参数

                   if(rtnXmlData.ParamList[0].Param.count() != 6)
                   {
                       qDebug()<<g_C2Q("参数个数不匹配，理论值：6，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count();
                       return;
                   }
                   pubData.generalParamCommunicate.dataNum = rtnXmlData.ParamList[0].Param.count();
                   pubData.generalParamCommunicate.dataList.clear();

                   for(int i=0;i<rtnXmlData.ParamList[0].Param.count();i++)
                   {
                       PublicDataClass::GENERAL_DATA tempData;
                       //值
                       //类型
                       //长度
                       tempData.value = rtnXmlData.ParamList[0].Param[i].value;
                       tempData.type = rtnXmlData.ParamList[0].Param[i].type;
                       tempData.length = rtnXmlData.ParamList[0].Param[i].length;
                       pubData.generalParamCommunicate.dataList.append(tempData);
                   }

                   }break;

               }
           }break;
           case 0x81://系统配置
           {
               switch (rowOffset_H) {
                   case 0:{//设备标识
                       if(rtnXmlData.ParamList[0].Param.count() != 6)
                       {
                           qDebug()<<g_C2Q("参数个数不匹配，理论值：6，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count();
                           return;
                       }
                       pubData.generalParamDevInfo.dataNum = rtnXmlData.ParamList[0].Param.count();
                       pubData.generalParamDevInfo.dataList.clear();

                       for(int i=0;i<rtnXmlData.ParamList[0].Param.count();i++)
                       {
                           PublicDataClass::GENERAL_DATA tempData;
                           //值
                           //类型
                           //长度
                           tempData.value = rtnXmlData.ParamList[0].Param[i].value;
                           tempData.type = rtnXmlData.ParamList[0].Param[i].type;
                           tempData.length = rtnXmlData.ParamList[0].Param[i].length;
                           pubData.generalParamDevInfo.dataList.append(tempData);
                       }
                   }break;
                   case 1:{//采集通道
                       if(rtnXmlData.ParamList.count() != CHANNELNUM_ANALOG)
                       {
                           qDebug()<<g_C2Q("参数行数不匹配，理论值：CHANNELNUM_ANALOG=18，读取返回参数个数：")<<rtnXmlData.ParamList.count();
                           return;
                       }

                       for(int i=0;i<rtnXmlData.ParamList.count();i++)
                       {
                           if(rtnXmlData.ParamList[i].Param.count() != 9)
                           {
                               qDebug()<<g_C2Q("参数个数不匹配，理论值：9，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count()<<g_C2Q("(当前行_")<<i<<")";
                               return;
                           }
                           pubData.generalParamChannelInfo[i].dataNum = 9;
                           pubData.generalParamChannelInfo[i].dataList.clear();
                           for(int j=0;j<rtnXmlData.ParamList[i].Param.count();j++)
                           {
                               PublicDataClass::GENERAL_DATA tempData;
                               //值
                               //类型
                               //长度
                               tempData.value = rtnXmlData.ParamList[i].Param[j].value;
                               tempData.type = rtnXmlData.ParamList[i].Param[j].type;
                               tempData.length = rtnXmlData.ParamList[i].Param[j].length;
                               pubData.generalParamChannelInfo[i].dataList.append(tempData);
                           }
                       }


                   }break;
                   case 2://最高频率
                   case 3://校时方式
                   case 4://时间同步
                    {
                       if(rtnXmlData.ParamList[0].Param.count() != 1)
                       {
                           qDebug()<<g_C2Q("参数个数不匹配，理论值：1，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count();
                           return;
                       }

                       PublicDataClass::GENERAL_DATA tempData;
                       //值
                       //类型
                       //长度
                       tempData.value = rtnXmlData.ParamList[0].Param[0].value;
                       tempData.type = rtnXmlData.ParamList[0].Param[0].type;
                       tempData.length = rtnXmlData.ParamList[0].Param[0].length;

                       //====================

                   }break;
//                   case 3:{//校时方式

//                   }break;
//                   case 4:{//时间同步

//                   }break;

               }
           }break;
           case 0x82://录波参数
           {
               switch (rowOffset_H) {
                   case 0:{//暂态录波基本配置
                       if(rtnXmlData.ParamList[0].Param.count() != 7)
                       {
                           qDebug()<<g_C2Q("参数个数不匹配，理论值：7，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count();
                           return;
                       }
                       pubData.generalWRParamTransient.dataNum = 7;
                       pubData.generalWRParamTransient.dataList.clear();
                       for(int i=0;i<rtnXmlData.ParamList[0].Param.count();i++)
                       {
                           PublicDataClass::GENERAL_DATA tempData;
                           //值
                           //类型
                           //长度
                           tempData.value = rtnXmlData.ParamList[0].Param[i].value;
                           tempData.type = rtnXmlData.ParamList[0].Param[i].type;
                           tempData.length = rtnXmlData.ParamList[0].Param[i].length;
                           pubData.generalWRParamTransient.dataList.append(tempData);
                       }

                   }break;
                   case 1:{//稳态录波基本配置
                       if(rtnXmlData.ParamList[0].Param.count() != 2)
                       {
                           qDebug()<<g_C2Q("参数个数不匹配，理论值：2，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count();
                           return;
                       }
                       pubData.generalWRParamSteady.dataNum = 2;
                       pubData.generalWRParamSteady.dataList.clear();
                       for(int i=0;i<rtnXmlData.ParamList[0].Param.count();i++)
                       {
                           PublicDataClass::GENERAL_DATA tempData;
                           //值
                           //类型
                           //长度
                           tempData.value = rtnXmlData.ParamList[0].Param[i].value;
                           tempData.type = rtnXmlData.ParamList[0].Param[i].type;
                           tempData.length = rtnXmlData.ParamList[0].Param[i].length;
                           pubData.generalWRParamSteady.dataList.append(tempData);
                       }

                   }break;
                   case 2:{//开关量触发
                       if(rtnXmlData.ParamList.count() != (CHANNELNUM_SWITCH+1))
                       {
                           qDebug()<<g_C2Q("参数行数不匹配，理论值：(CHANNELNUM_SWITCH+1)=17，读取返回参数个数：")<<rtnXmlData.ParamList.count();
                           return;
                       }

                       for(int i=0;i<rtnXmlData.ParamList.count();i++)
                       {
                           if(i==0)
                           {
                               if(rtnXmlData.ParamList[i].Param.count() != 3)
                               {
                                   qDebug()<<g_C2Q("参数个数不匹配，理论值：3，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count()<<g_C2Q("(当前行_")<<i<<")";
                                   return;
                               }
                               pubData.generalWRParamSwitch[i].dataNum = 3;
                           }
                           else
                           {
                               if(rtnXmlData.ParamList[i].Param.count() != 4)
                               {
                                   qDebug()<<g_C2Q("参数个数不匹配，理论值：4，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count()<<g_C2Q("(当前行_")<<i<<")";
                                   return;
                               }
                               pubData.generalWRParamSwitch[i].dataNum = 4;
                           }

                           pubData.generalWRParamSwitch[i].dataList.clear();
                           for(int j=0;j<rtnXmlData.ParamList[i].Param.count();j++)
                           {
                               PublicDataClass::GENERAL_DATA tempData;
                               //值
                               //类型
                               //长度
                               tempData.value = rtnXmlData.ParamList[i].Param[j].value;
                               tempData.type = rtnXmlData.ParamList[i].Param[j].type;
                               tempData.length = rtnXmlData.ParamList[i].Param[j].length;
                               pubData.generalWRParamSwitch[i].dataList.append(tempData);
                           }
                       }

                   }break;
                   case 3:{//模拟量触发
                       if(rtnXmlData.ParamList.count() != (CHANNELNUM_ANALOG+1))
                       {
                           qDebug()<<g_C2Q("参数行数不匹配，理论值：(CHANNELNUM_ANALOG+1)=19，读取返回参数个数：")<<rtnXmlData.ParamList.count();
                           return;
                       }

                       for(int i=0;i<rtnXmlData.ParamList.count();i++)
                       {
                           if(i==0)
                           {
                               if(rtnXmlData.ParamList[i].Param.count() != 1)
                               {
                                   qDebug()<<g_C2Q("参数个数不匹配，理论值：1，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count()<<g_C2Q("(当前行_")<<i<<")";
                                   return;
                               }
                               pubData.generalWRParamAnalog[i].dataNum = 1;
                           }
                           else
                           {
                               if(rtnXmlData.ParamList[i].Param.count() != 17)
                               {
                                   qDebug()<<g_C2Q("参数个数不匹配，理论值：17，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count()<<g_C2Q("(当前行_")<<i<<")";
                                   return;
                               }
                               pubData.generalWRParamAnalog[i].dataNum = 17;
                           }

                           pubData.generalWRParamAnalog[i].dataList.clear();
                           for(int j=0;j<rtnXmlData.ParamList[i].Param.count();j++)
                           {
                               PublicDataClass::GENERAL_DATA tempData;
                               //值
                               //类型
                               //长度
                               tempData.value = rtnXmlData.ParamList[i].Param[j].value;
                               tempData.type = rtnXmlData.ParamList[i].Param[j].type;
                               tempData.length = rtnXmlData.ParamList[i].Param[j].length;
                               pubData.generalWRParamAnalog[i].dataList.append(tempData);
                           }
                       }
                   }break;
                   case 4:{//分组/序分量
                        if(rtnXmlData.ParamList.count() < 2 || rtnXmlData.ParamList.count() > 6)
                        {
                            qDebug()<<g_C2Q("参数行数不匹配，理论值：(1-4)+1，读取返回参数个数：")<<rtnXmlData.ParamList.count();
                            return;
                        }
                        int groupNum = rtnXmlData.ParamList[0].Param[0].value.toInt();
                        if(rtnXmlData.ParamList.count() != (groupNum+1))
                        {
                            qDebug()<<g_C2Q("参数行数不匹配，理论值(组数+1)：")<<(groupNum+1)
                                    <<g_C2Q(",读取返回参数行数：")<<rtnXmlData.ParamList.count();
                            return;
                        }

                        for(int i=0;i<rtnXmlData.ParamList.count();i++)
                        {
                            if(i==0)
                            {
                                if(rtnXmlData.ParamList[i].Param.count() != 1)
                                {
                                    qDebug()<<g_C2Q("参数个数不匹配，理论值：1，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count()<<g_C2Q("(当前行_")<<i<<")";
                                    return;
                                }
                                pubData.generalWRParamComponent[i].dataNum = 1;
                            }
                            else
                            {
                                if(rtnXmlData.ParamList[i].Param.count() != 15)
                                {
                                    qDebug()<<g_C2Q("参数个数不匹配，理论值：15，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count()<<g_C2Q("(当前行_")<<i<<")";
                                    return;
                                }
                                pubData.generalWRParamComponent[i].dataNum = 15;
                            }

                            pubData.generalWRParamComponent[i].dataList.clear();
                            for(int j=0;j<rtnXmlData.ParamList[i].Param.count();j++)
                            {
                                PublicDataClass::GENERAL_DATA tempData;
                                //值
                                //类型
                                //长度
                                tempData.value = rtnXmlData.ParamList[i].Param[j].value;
                                tempData.type = rtnXmlData.ParamList[i].Param[j].type;
                                tempData.length = rtnXmlData.ParamList[i].Param[j].length;
                                pubData.generalWRParamComponent[i].dataList.append(tempData);
                            }
                        }

                   }break;
                   //0x01000582 手动录波启动/停止
               }
           }break;
           case 0x83://电能量
           {
               switch (rowOffset_H) {
                   case 0:{//电能表检相关配置参数

                   }break;
                   case 1:{//电能检定输入脉冲参数
                       if(rtnXmlData.ParamList[0].Param.count() != 6)
                       {
                           qDebug()<<g_C2Q("参数个数不匹配，理论值：6，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count();
                           return;
                       }
                       pubData.generalWRParamPulseIn.dataNum = rtnXmlData.ParamList[0].Param.count();
                       pubData.generalWRParamPulseIn.dataList.clear();

                       for(int i=0;i<rtnXmlData.ParamList[0].Param.count();i++)
                       {
                           PublicDataClass::GENERAL_DATA tempData;
                           //值
                           //类型
                           //长度
                           tempData.value = rtnXmlData.ParamList[0].Param[i].value;
                           tempData.type = rtnXmlData.ParamList[0].Param[i].type;
                           tempData.length = rtnXmlData.ParamList[0].Param[i].length;
                           pubData.generalWRParamPulseIn.dataList.append(tempData);
                       }
                   }break;
                   case 2:{//电能输出脉冲参数
                       if(rtnXmlData.ParamList[0].Param.count() != 6)
                       {
                           qDebug()<<g_C2Q("参数个数不匹配，理论值：6，读取返回参数个数：")<<rtnXmlData.ParamList[0].Param.count();
                           return;
                       }
                       pubData.generalWRParamPulseOut.dataNum = rtnXmlData.ParamList[0].Param.count();
                       pubData.generalWRParamPulseOut.dataList.clear();

                       for(int i=0;i<rtnXmlData.ParamList[0].Param.count();i++)
                       {
                           PublicDataClass::GENERAL_DATA tempData;
                           //值
                           //类型
                           //长度
                           tempData.value = rtnXmlData.ParamList[0].Param[i].value;
                           tempData.type = rtnXmlData.ParamList[0].Param[i].type;
                           tempData.length = rtnXmlData.ParamList[0].Param[i].length;
                           pubData.generalWRParamPulseOut.dataList.append(tempData);
                       }
                   }break;
                   case 3:{

                   }break;
                   case 4:{

                   }break;
                   case 5:{

                   }break;
               }
           }break;
           case 0x84://校准
           {
               switch (rowOffset_H) {
                   case 0:{//校准参数

                   }break;
                   case 1:{//校准命令

                   }break;
                   case 2:{

                   }break;

               }
           }break;
           case 0x85://录波
           {
               switch (rowOffset_H) {
                   //实时传输启动/停止设置：0x01000085
                   case 1:{//实时数据  generalWRComtradeData

                    qDebug()<<"generalWRComtradeData rtnXmlData struct count:"<<rtnXmlData.ParamList[0].Param.count();
                       pubData.generalWRComtradeData.dataNum = rtnXmlData.ParamList[0].Param.count();
                       pubData.generalWRComtradeData.dataList.clear();

                       for(int i=0;i<rtnXmlData.ParamList[0].Param.count();i++)
                       {
                           PublicDataClass::GENERAL_DATA tempData;
                           //值
                           //类型
                           //长度
                           tempData.value = rtnXmlData.ParamList[0].Param[i].value;
                           tempData.type = rtnXmlData.ParamList[0].Param[i].type;
                           tempData.length = rtnXmlData.ParamList[0].Param[i].length;
                           pubData.generalWRComtradeData.dataList.append(tempData);
                       }

                   }break;
                   case 2:{

                   }break;

               }
           }break;
           case 0x86://录波文件召测
           {
               switch (rowOffset_H) {
                   //录波完成主动上传(故障录波序号)：0x01000086
                   case 1:{//波形数据召测

                   }break;
                   case 2:{

                   }break;

               }
           }break;
       }
*/
    }


}

void DevDataTransfer_wr::wr_sendParamCommunicate(int            typeID)/*,
                                             QString        portName1,
                                             unsigned short boundRate1,
                                             char           parity1,
                                             QString        portName2,
                                             unsigned short boundRate2,
                                             char           parity2)*/
{
    testdata.setParamCommunicate();
    returnCacheData.clear();//新的命令下发，接收缓存清空
    qDebug()<<"pubData.generalParamCommunicate.dataNum:"<<pubData.generalParamCommunicate.dataNum;


    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowName = g_C2Q("基本通讯参数");//XmlData.ParamList[0]
    temp_row.RowTypeID = typeID;//下设或读取
    temp_row.IsShow = false;       //是否展示
    //信息体地址：0x01000080
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0080;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
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
    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendParamDevInfo(int            typeID)

{
    testdata.setParamDevInfo();
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000080
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0081;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        for(int i=0;i<pubData.generalParamDevInfo.dataNum;i++)
        {
    //        qDebug()<<"pubData.generalParamDevInfo.dataList_"<<i<<":"
    //               <<pubData.generalParamDevInfo.dataList[i].value
    //              <<","<<pubData.generalParamDevInfo.dataList[i].type
    //             <<","<<pubData.generalParamDevInfo.dataList[i].length;

            temp_column.value = pubData.generalParamDevInfo.dataList[i].value;
            temp_column.type = pubData.generalParamDevInfo.dataList[i].type;
            temp_column.length = pubData.generalParamDevInfo.dataList[i].length;
            temp_row.Param.append(temp_column);
        }
    }



    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);

}

//setParamChannelInfo()
void DevDataTransfer_wr::wr_sendParamChannelInfo(int            typeID)
{
    testdata.setParamChannelInfo();
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000080
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0181;//行偏移量(低位)

    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        for(int i=0;i<CHANNELNUM_ANALOG;i++)
        {
            temp_row.Param.clear();
            for(int j=0;j<pubData.generalParamChannelInfo[i].dataNum;j++)
            {
                qDebug()<<"pubData.generalParamChannelInfo[i].dataList_"<<j<<":"
                       <<pubData.generalParamChannelInfo[i].dataList[j].value
                      <<","<<pubData.generalParamChannelInfo[i].dataList[j].type
                     <<","<<pubData.generalParamChannelInfo[i].dataList[j].length;

                temp_column.value = pubData.generalParamChannelInfo[i].dataList[j].value;
                temp_column.type = pubData.generalParamChannelInfo[i].dataList[j].type;
                temp_column.length = pubData.generalParamChannelInfo[i].dataList[j].length;
                temp_row.Param.append(temp_column);
            }

            tempXmlData.ParamList.append(temp_row);
        }
    }
    else  //数据内容为空，数据结构需要赋值
    {
        tempXmlData.ParamList.append(temp_row);
    }

    qDebug()<<"XmlData.ParamList.count():"<<tempXmlData.ParamList.count();

    encodefromXMLData(tempXmlData,1);

}


void DevDataTransfer_wr::wr_sendMaxSampleRate(int typeID, unsigned int value)
{
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000281
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0281;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        temp_column.value = QString::number(value);
        temp_column.type = pubData.Type_ushort;
        temp_column.length = 2;
        temp_row.Param.append(temp_column);

    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendTimeCalibrationType(int typeID,char  value  )
{
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000381
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0381;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        temp_column.value = QString::number(value);
        temp_column.type = pubData.Type_ushort;
        temp_column.length = 2;
        temp_row.Param.append(temp_column);

    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

//时间入参格式："yy:MM:dd:hh:mm:ss:zzz:dddd"
void DevDataTransfer_wr::wr_sendTimeOperate(int typeID,QString time)
{
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000481
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0481;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        temp_column.value = time;
        temp_column.type = pubData.Type_datetime;
        temp_column.length = 7;
        temp_row.Param.append(temp_column);
    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendWRParamTransient(int typeID)
{
    testdata.setWRParamTransient();
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000082
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0082;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        for(int i=0;i<pubData.generalWRParamTransient.dataNum;i++)
        {

            temp_column.value = pubData.generalWRParamTransient.dataList[i].value;
            temp_column.type = pubData.generalWRParamTransient.dataList[i].type;
            temp_column.length = pubData.generalWRParamTransient.dataList[i].length;
            temp_row.Param.append(temp_column);
        }
    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);

}

void DevDataTransfer_wr::wr_sendWRParamSteady(int            typeID)
{
    testdata.setWRParamSteady();
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000182
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0182;//行偏移量(低位)

    temp_row.Param.clear();

    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        for(int i=0;i<pubData.generalWRParamSteady.dataNum;i++)
        {

            temp_column.value = pubData.generalWRParamSteady.dataList[i].value;
            temp_column.type = pubData.generalWRParamSteady.dataList[i].type;
            temp_column.length = pubData.generalWRParamSteady.dataList[i].length;
            temp_row.Param.append(temp_column);
        }
    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendWRParamSwitch(int            typeID)
{
    testdata.setWRParamSwitch();
    returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000282
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0282;//行偏移量(低位)



    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值generalWRParamSwitch[]
        for(int i=0;i<CHANNELNUM_SWITCH+1;i++)
        {
            temp_row.Param.clear();
            for(int j=0;j<pubData.generalWRParamSwitch[i].dataNum;j++)
            {

                temp_column.value = pubData.generalWRParamSwitch[i].dataList[j].value;
                temp_column.type = pubData.generalWRParamSwitch[i].dataList[j].type;
                temp_column.length = pubData.generalWRParamSwitch[i].dataList[j].length;
                temp_row.Param.append(temp_column);
            }
            tempXmlData.ParamList.append(temp_row);
        }

    }
    else
    {
        tempXmlData.ParamList.append(temp_row);
    }



    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendWRParamAnalog(int            typeID)
{
    testdata.setWRParamAnalog();
   returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000382
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0382;//行偏移量(低位)

    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        for(int i=0;i<CHANNELNUM_ANALOG+1;i++)
        {
            temp_row.Param.clear();
            for(int j=0;j<pubData.generalWRParamAnalog[i].dataNum;j++)
            {

                temp_column.value = pubData.generalWRParamAnalog[i].dataList[j].value;
                temp_column.type = pubData.generalWRParamAnalog[i].dataList[j].type;
                temp_column.length = pubData.generalWRParamAnalog[i].dataList[j].length;
                temp_row.Param.append(temp_column);
            }
            tempXmlData.ParamList.append(temp_row);
        }

    }
    else
    {
        tempXmlData.ParamList.append(temp_row);
    }



    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendWRParamComponent(int            typeID)
{
    testdata.setWRParamComponent();
   returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000482
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0482;//行偏移量(低位)

    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        int nums = pubData.generalWRParamComponent[0].dataList[0].value.toInt()+1;
        for(int i=0;i<nums;i++)
        {
            temp_row.Param.clear();
            for(int j=0;j<pubData.generalWRParamComponent[i].dataNum;j++)
            {

                temp_column.value = pubData.generalWRParamComponent[i].dataList[j].value;
                temp_column.type = pubData.generalWRParamComponent[i].dataList[j].type;
                temp_column.length = pubData.generalWRParamComponent[i].dataList[j].length;
                temp_row.Param.append(temp_column);
            }
            tempXmlData.ParamList.append(temp_row);
        }

    }
    else
    {
        tempXmlData.ParamList.append(temp_row);
    }



    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendWROperate(char value)
{
   returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;


    temp_row.RowTypeID = 1;//下设

    //信息体地址：0x01000582
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0582;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    //参数赋值
    temp_column.value = QString::number(value);
    temp_column.type = pubData.Type_sbyte;
    temp_column.length = pubData.getLenfromType(pubData.Type_sbyte);
    temp_row.Param.append(temp_column);

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendPowerMeterOperate(char value)
{
   returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;


    temp_row.RowTypeID = 1;//下设

    //信息体地址：0x01000083
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0083;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    //参数赋值
    temp_column.value = QString::number(value);
    temp_column.type = pubData.Type_sbyte;
    temp_column.length = pubData.getLenfromType(pubData.Type_sbyte);
    temp_row.Param.append(temp_column);

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendPowerMeterParamPulseIn(int            typeID)
{
    testdata.setWRParamPulseIn();
   returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000183
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0183;//行偏移量(低位)

    temp_row.Param.clear();

    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        for(int i=0;i<pubData.generalWRParamPulseIn.dataNum;i++)
        {

            temp_column.value = pubData.generalWRParamPulseIn.dataList[i].value;
            temp_column.type = pubData.generalWRParamPulseIn.dataList[i].type;
            temp_column.length = pubData.generalWRParamPulseIn.dataList[i].length;
            temp_row.Param.append(temp_column);
        }
    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendPowerMeterParamPulseOut(int            typeID)
{
    testdata.setWRParamPulseOut();
   returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    temp_row.RowTypeID = typeID;//下设或读取

    //信息体地址：0x01000283
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0283;//行偏移量(低位)

    temp_row.Param.clear();

    tempXmlData.ParamList.clear();
    if(typeID == 1)//下载参数
    {//参数赋值
        for(int i=0;i<pubData.generalWRParamPulseOut.dataNum;i++)
        {

            temp_column.value = pubData.generalWRParamPulseOut.dataList[i].value;
            temp_column.type = pubData.generalWRParamPulseOut.dataList[i].type;
            temp_column.length = pubData.generalWRParamPulseOut.dataList[i].length;
            temp_row.Param.append(temp_column);
        }
    }

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendCalibrationParam(int typeID,int currentIndex)
{

}

void DevDataTransfer_wr::wr_sendCalibrationOperate(int typeID,int currentIndex)
{

}

void DevDataTransfer_wr::wr_sendRealDataTransfer(char value)
{
   returnCacheData.clear();//新的命令下发，接收缓存清空

    //直接赋值
    CustomProtocol::_XmlDataStruct tempXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;


    temp_row.RowTypeID = 1;//下设

    //信息体地址：0x01000085
    temp_row.RowInfoAddr = 0x0100;//参数信息体地址(高位)
    temp_row.RowOffset = 0x0085;//行偏移量(低位)

    temp_row.Param.clear();
    tempXmlData.ParamList.clear();
    //参数赋值
    temp_column.value = QString::number(value);
    temp_column.type = pubData.Type_sbyte;
    temp_column.length = pubData.getLenfromType(pubData.Type_sbyte);
    temp_row.Param.append(temp_column);

    tempXmlData.ParamList.append(temp_row);

    encodefromXMLData(tempXmlData,1);
}

void DevDataTransfer_wr::wr_sendMeterRealDataCall()
{

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
    decodeRecievedData(qbaBuf,1);


}

QString DevDataTransfer_wr::unicodeToCn(QString Str)
{
    QString filename = Str;
    do {
        int idx = filename.indexOf("\\u");
        QString strHex = filename.mid(idx, 6);
        strHex = strHex.replace("\\u", QString());
        int nHex = strHex.toInt(0, 16);
        filename.replace(idx, 6, QChar(nHex));
    } while (filename.indexOf("\\u") != -1);
    return filename;
}



void DevDataTransfer_wr::respondmsgSend(QByteArray qbaBuf)
{

}

void DevDataTransfer_wr::gotError(QAbstractSocket::SocketError err)
{
    qDebug()<<"SocketError num:"<<err;
}

void DevDataTransfer_wr::respondmsgRecv_realtime(QByteArray qbaBuf)
{
    decodeRecievedData(qbaBuf,2);
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
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timeStr = time.toString("yyyy-MM-dd hh:mm:ss:zzz dddd");

    char* pbuf = new char[1024*2];

    QString temp_str;
    for(int i=0;i<qbaBuf.size();i++)
    {
        temp_str += QString("%1").arg((unsigned char)(qbaBuf[i]),2,16,QLatin1Char('0'));
        temp_str += " ";
        pbuf[i] = (unsigned char)(qbaBuf[i]);
    }
    //qDebug()<<"server recv_"<<timeStr<< ":" << temp_str<<"(len="<<qbaBuf.size()<<",from"<<ip<<":"<<port<<")";
    qDebug()<<"server recv_"<<timeStr;

    //解析
    QList<CustomProtocol::_ReturnDataStruct> returndatalist;//针对多帧通讯
    CustomProtocol::_XmlDataStruct rtnXmlData;
    CustomProtocol::_RowInforStruct temp_row;
    CustomProtocol::_ColumnInforStruct temp_column;

    priProtocal_server.DecodeFrame(pbuf,qbaBuf.size(),returndatalist);
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

