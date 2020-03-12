#include "SysInfoQML.h"
#pragma comment(lib,"user32.lib")
#pragma comment(lib, "advapi32.lib")

#ifdef Q_OS_WIN
    #include "WindowsInfo.h"
#elif defined(Q_OS_ANDROID)
    #include "AndroidInfo.h"
#endif

SysInfoQML::SysInfoQML(QObject *parent) : QObject(parent)
{
#ifdef Q_OS_WIN
    this->m_sysInfo = new WindowsInfo();
#elif defined(Q_OS_ANDROID)
    this->m_sysInfo = new AndroidInfo();
#endif

}

double SysInfoQML::cpuTotal() const
{
    return this->m_sysInfo->m_cpuInfo.getTotal();
}

double SysInfoQML::cpuUsage() const
{
    return this->m_sysInfo->m_cpuInfo.getUsage();
}

double SysInfoQML::memTotal() const
{
    return this->m_sysInfo->m_memInfo.getTotal();
}

double SysInfoQML::memUsage() const
{
    return this->m_sysInfo->m_memInfo.getUsage();
}

void SysInfoQML::update()
{
    this->m_sysInfo->update();
}

bool SysInfoQML::shutDown()
{
    HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
            return false;

       //获取关机特权的LUID
       LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
       tkp.PrivilegeCount = 1;
     tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

       //获取这个进程的关机特权
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
       if (GetLastError() != ERROR_SUCCESS) return false;//


       //强制关闭计算机
       if ( !ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0))
             return false;

       return true;
}

bool SysInfoQML::reBoot()
{
    HANDLE hToken;
   TOKEN_PRIVILEGES tkp;

   //获取进程标志
   if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
            return false;

       //获取关机特权的LUID
       LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME,    &tkp.Privileges[0].Luid);
       tkp.PrivilegeCount = 1;
     tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

       //获取这个进程的关机特权
       AdjustTokenPrivileges(hToken, false, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
       if (GetLastError() != ERROR_SUCCESS) return false;//


       //强制关闭计算机
       if ( !ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0))
             return false;

       return true;
}
