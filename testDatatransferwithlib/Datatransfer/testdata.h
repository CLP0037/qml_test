#ifndef TESTDATA_H
#define TESTDATA_H

#include <QObject>

class TestData : public QObject
{
    Q_OBJECT
public:
    explicit TestData(QObject *parent = nullptr);

    //刷新通讯测试
    void setParamCommunicate();

signals:

public slots:
};

#endif // TESTDATA_H
