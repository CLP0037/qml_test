#ifndef SYSINFO_H
#define SYSINFO_H

#include "meminfo.h"
#include "cpuinfo.h"

class SysInfo
{
public:
    CpuInfo m_cpuInfo;
    MemInfo m_memInfo;

public:
    SysInfo();

    virtual void update() = 0;
};

#endif // SYSINFO_H
