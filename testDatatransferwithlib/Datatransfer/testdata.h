#ifndef TESTDATA_H
#define TESTDATA_H

#include <QObject>

class TestData : public QObject
{
    Q_OBJECT
public:
    explicit TestData(QObject *parent = nullptr);

    void setParamCommunicate();

signals:

public slots:
};

#endif // TESTDATA_H
