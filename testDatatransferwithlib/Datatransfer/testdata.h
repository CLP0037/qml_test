#ifndef TESTDATA_H
#define TESTDATA_H

#include <QObject>

class TestData : public QObject
{
    Q_OBJECT
public:
    explicit TestData(QObject *parent = nullptr);

    //======= 模拟赋值，实际赋值在界面前后端交互时实现 =======//
    //刷新通讯测试
    void setParamCommunicate();

    void setParamDevInfo();

    void setParamChannelInfo();

signals:

public slots:
};

#endif // TESTDATA_H
