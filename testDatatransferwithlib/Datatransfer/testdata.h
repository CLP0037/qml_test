#ifndef TESTDATA_H
#define TESTDATA_H

#include <QObject>

class TestData : public QObject
{
    Q_OBJECT
public:
    explicit TestData(QObject *parent = nullptr);

    //======= 模拟赋值，实际赋值在界面前后端交互时实现 =======//
    //通讯参数
    void setParamCommunicate();
    //设备标识信息
    void setParamDevInfo();
    //采集通道
    void setParamChannelInfo();
    //最高频率(单位kHz)

    //校时方式

    //暂态录波基本配置
    void setWRParamTransient();
    //稳态录波基本配置
    void setWRParamSteady();
    //开关量触发配置
    void setWRParamSwitch();
    //分组/序分量配置
    void setWRParamComponent();
    //
    //
    //
    //电能检定输入脉冲参数
    void setWRParamPulseIn();
    //电能输出脉冲参数
    void setWRParamPulseOut();


signals:

public slots:
};

#endif // TESTDATA_H
