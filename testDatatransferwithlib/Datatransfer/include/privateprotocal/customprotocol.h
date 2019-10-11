#ifndef CUSTOMPROTOCOL_H
#define CUSTOMPROTOCOL_H
#include <QString>
#include <QList>
#include "customprotocol_global.h"
#include <QMap>
#include <QTextCodec>
#include <QVariant>

#define g_C2Q(str) QString::fromLocal8Bit(str)

#define CODEMAXLEN 512*4//宏定义数据域最大长度
class Q_DECL_EXPORT CustomProtocol
{
public:
    CustomProtocol();

//    const int iLenOfConfCode=27;//帧固定部分长度
    int iLenOfConfCode;

    struct _UpFileDataStruct
    {
        int Offset;//每块偏移地址
        QByteArray UpFileData;//升级文件中自定义块的数据，主要用于指示器@
    };

    struct _SectionStruct//升级文件解析存储
    {
        int Num;//段序号
        char Code[CODEMAXLEN+30];//段代码
        int CodeLen;//段长度
        int CodeDataLen;//数据长度，不包含类型和长度
        ushort checksum;//段校验和
        int ParamCount;//段内参数个数
    };

    struct _UpDateValueStruct//升级文件配置信息config
    {
        QString StartInfo;//起始信息
        QStringList DevInfo;//设备信息
        QStringList MCUInfo;//MCU类型
        QStringList RFInfo;//RF类型
        QStringList GPRSInfo;//GPRS类型
        QStringList MemoryInfo;//存储类型
        QString SoftwareInfo;//软件版本
        QString HardwareInfo;//硬件版本
        QString SpareInfo;//保留
        QString UpSupportInfo;//可升级版本
    };

    struct _ColumnInforStruct //每列对应的数据信息
    {
        QString ColumnName;//列名
        QString desc;//描述
        QString value;//值
        int type;//类型
        int length;//长度
    };

    struct _RowInforStruct//行信息结构体
    {
        QString RowName;     //名称
        int RowTypeID;     //功能码
        bool IsShow;       //是否展示
        int RowInfoAddr;//参数信息体地址
        int RowOffset;//行偏移量
        QList<_ColumnInforStruct> Param;
    };

    struct _XmlDataStruct  //xml文件对应的数据结构体
    {
        QList<_RowInforStruct> ParamList;//参数List
    };

    struct _DataInforStruct //解帧返回的每个参数结构体
    {
        int InforAdr;
        QString value;//值
        int type;//类型
        int length;//长度
    };

    struct _ReturnDataStruct   //解帧返回数据结构
    {
        int TypeID;            //功能码
        char ObjectType;       //设备类型1：故指 2：DTU  3：TTU
        uint MasterAdr;         //主设备地址
        uint SlaveAdr;         //从设备地址
        char ActType;         //设备操作类型 1-对主2-对从
        char IsDataContinuous;//数据域是否连续0:离散，1:连续，2：片段连续
        char DataField[CODEMAXLEN+50];//数据是否更新
        int DataLength;//数据域长度
        bool IsOver;//是否有后续
        bool IsFileGenerated;//是否有文件生成
        QString FilePath;//若有文件生成，文件路径
        int Txlen;//需要发送数据的长度
        char Tbuf[CODEMAXLEN+50];//需要发送的数据
        int Revlen;//收到的报文长度
        char RevBuf[CODEMAXLEN+50];//收到的报文
    };

    /**
         * @brief 解析xml文件
         * @param[in] filepath xml文件路径
         * @param[in] xmldata xml返回数据结构
         * QString 返回的提示信息
         */
    QString AnalysisXml(QString filepath,_XmlDataStruct* xmldata);

    /**
     * @brief EncodeParam 参数组帧
     * @param xmldata 参数存储的结构体
     * @param pbuf 返回的字节数组
     * @param len 返回字节数组长度
     * @param isover 是否最后一帧
     * @param objecttype 设备类型1,故指，2Dtu,3.TTU，4.超级终端
     * @param acttype 操作类型 1.主设备，2.从设备
     * @param masteradr 主设备地址
     * @param slaveadr 从设备地址
     */
    void EncodeParam(_XmlDataStruct xmldata,char *pbuf, int &len,bool &isover,char objecttype,char acttype,uint masteradr,uint slaveadr,int SQ);


    /**
     * @brief AnalysisUgradeFile 升级文件解析，升级一般先调用这个函数，再调用SectionUgradeFile函数
     * @param upfilepath  升级文件路径 *bin或*.txt格式
     * @param objecttype 设备类型1,故指，2Dtu,3.TTU，4.超级终端
     * @param acttype  操作类型 1.主设备，2.从设备
     * @param sysfilepath  升级相关信息配置文件，解析故指汇集单元升级文件头，其他类型用不到
     */
    void AnalysisUgradeFile(QString upfilepath,char objecttype,char acttype,QString sysfilepath="");

    /**
     * @brief SectionUgradeFile 升级组帧
     * @param pbuf 返回的字节数组
     * @param len len返回字节数组长度
     * @param isover 是否最后一帧
     * @param objecttype 设备类型1,故指，2Dtu,3.TTU，4.超级终端
     * @param acttype 操作类型 1.主设备，2.从设备
     * @param masteradr 主设备地址
     * @param slaveadr 从设备地址
     * @param typeID 功能码
     */
    void SectionUgradeFile(char *pbuf,int &len ,bool &isover,char objecttype,char acttype,uint masteradr,uint slaveadr,int typeID);

    /**
     * @brief DecodeFrame 解帧
     * @param pbuf 输入字节数组
     * @param buflen 输入字节数组长度
     * @param pDataList 返回的解析数据结构体列表
     */
    void DecodeFrame(char *pbuf,uint buflen ,QList<_ReturnDataStruct>&pDataList);

    /**
     * @brief EncodeUgradeCheck 升级文件下载完后的校验帧
     * @param pbuf 返回的报文字节数组
     * @param len len返回字节数组长度
     * @param isover 是否最后一帧
     * @param objecttype 设备类型1,故指，2Dtu,3.TTU，4.超级终端
     * @param acttype 操作类型 1.主设备，2.从设备
     * @param masteradr 主设备地址
     * @param slaveadr 从设备地址
     * @param typeID 功能码
     * @param version 升级文件版本号
     */
    void EncodeUgradeCheck(char *pbuf,int &len ,bool &isover,char objecttype,char acttype,int masteradr,int slaveadr,int typeID,QString version);

    /**
     * @brief EncodeUgradeUp 升级命令，
     * @param pbuf 返回的报文字节数组
     * @param len len返回字节数组长度
     * @param isover 是否最后一帧
     * @param objecttype 设备类型1,故指，2Dtu,3.TTU，4.超级终端
     * @param acttype 操作类型 1.主设备，2.从设备
     * @param masteradr 主设备地址
     * @param slaveadr 从设备地址
     * @param typeID 功能码
     * @param version 升级文件版本号
     */
    void EncodeUgradeUp(char *pbuf,int &len ,bool &isover,char objecttype,char acttype,int masteradr,int slaveadr,int typeID,QString version);

    /**
     * @brief AnalysisRevData 读参数回复，解析数据域内容
     * @param xmldata 当前页参数的xmldata结构
     * @param SQ 参数是否连续0：离散，1：连续
     * @param data 数据域内容
     * @param datalen 数据域长度
     */
    void AnalysisRevData(_XmlDataStruct &xmldata,int SQ,char * data, int datalen);
    /**
     * @brief AnalysisMsg 解析报文
     * @param data 报文
     * @param msg 返回解析内容
     * dir 传输方向0：收，1发,其他：不要方向和时间
     */
    void AnalysisMsg(unsigned char *data, int len, QByteArray &msg,int dir);
    void AnalysisMsg(char *data, int len, QByteArray &msg,int dir);
    /**
     * @brief AnalysisMsg 字符数组转QByteArray
     * @param data 字符数组
     * @return 返回处理结果
     */
    QByteArray ChartoMsg(unsigned char *data, int len);

    /**
     * @brief HandleDataField 组帧处理xmldata内容，转为char *
     * @param xmldata 转换的xmldata源
     * @param section 转换的报文内容存储到_SectionStruct结构体
     * @param rownum 当前的行号，即xmldata中的paramlist序号
     * @param SQ 是否离散
     */
    void HandleDataField(_XmlDataStruct xmldata,_SectionStruct &section,int &rownum,int SQ);
    /**
     * @brief CountParamLen 计算参数长度
     * @param type 参数类型
     * @param length 参数长度
     * @param value 参数内容
     * @return
     */
    int CountParamLen(int type,int length,QString value);

    void HandleParam(char * tmepcode,int templen,int type,int length,QString value);
private:






    ushort CheckSum(char * data,int len);
    ushort CheckSum(unsigned char * data,int len);

    void AnalysisSysFile(QString sysfilepath);

    void AnalysisHdUpdateFile(QString upfilepath);

    void AnalysisGzUpdateFile(QString upfilepath);

    void AnalysisDTUUpdateFile(QString upfilepath);


    void Encode(char *pbuf, int &len,char *pdata,int &datalen,bool &isover,char objecttype,char acttype,uint masteradr,uint slaveadr,int typeID,int SQ);

    bool CorrectValue(QString value,uint min,uint max);

    QVariant DayOfWeek(QVariant weekday);

    int DataTypeConvert(QString type);

    //参数组帧相关变量
    //分帧的后续帧帧号可根据回复帧号或自己记录的上次帧号
    int SegNum;//帧序号，从1开始，记录分帧时的帧号
    bool HaveFlag;//后续帧标志，
    QByteArray FileData;//存储回复分帧时的数据
    int FileDataLen;//长度
    int mPreviousType;//上个参数的类型

    //升级数据处理
    bool mIsGz;//故指升级组帧标志位
    QList<_SectionStruct> SectionList;//升级文件生成的段序列
    ushort CheckSumCheck;//总升级文件校验和
    ushort SegCount;//总段数
    uint AllByteCount;//总字节数
    //升级文件配置信息实例化
    _UpDateValueStruct UpDateValue;
    //升级文件头数据域
    char* UpHeaderInfo;//存储汇集单元升级文件头的设备信息18字节
    //升级文件处理
    QList<_UpFileDataStruct> UpFileDataList;//升级文件中自定义段每段的数据集合

    //解帧相关变量
    char mpBuf[1024*2];
    uint miBufLen;

//    //gbk解码
//    QTextCodec *codec = QTextCodec::codecForName("GB18030");


};

#endif // CUSTOMPROTOCOL_H
