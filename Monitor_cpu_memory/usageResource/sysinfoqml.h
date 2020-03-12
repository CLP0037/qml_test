﻿#ifndef SYSINFOQML_H
#define SYSINFOQML_H

#include <QObject>
#include "SysInfo.h"

#include <windows.h>
#include <iostream>
#include "WinUser.h"
#include "processthreadsapi.h"
using namespace std;

class SysInfoQML : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double cpuTotal READ cpuTotal)
    Q_PROPERTY(double cpuUsage READ cpuUsage)
    Q_PROPERTY(double memTotal READ memTotal)
    Q_PROPERTY(double memUsage READ memUsage)
public:
    SysInfoQML(QObject *parent = 0);

    double cpuTotal() const;
    double cpuUsage() const;

    double memTotal() const;
    double memUsage() const;

    //关机
    Q_INVOKABLE bool shutDown();
    //重启
    Q_INVOKABLE bool reBoot();

public slots:
    void update();

private:
    SysInfo* m_sysInfo;
};

#endif // SYSINFOQML_H
