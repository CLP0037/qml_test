#ifndef __INCLUDE_COMTRADE_FORMAT_H
#define __INCLUDE_COMTRADE_FORMAT_H

#if defined (__cplusplus)
extern "C" {
#endif /* defined (__cplusplus) */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <assert.h>
#include <sys/types.h>
#include <io.h>
#include <process.h>
#include <sys/stat.h>  
#include <fcntl.h>


/* Copyright,lizhi<ibox>
 *
 * 2012-10-10 V1.0 lizhi<QQ:252240557,msn:ddgooo@hotmail.com> created
*/



/**
 * 宏开关 定义为文件读写
 */
#define CMTR_IOFILE


/**
 * 宏定义文件的读写操作，可以根据需要改写该接口，如重定义为网口的recv\send、串口r\w等。
 * _my_read_cmtr_bufn/_my_read_cmtr_bufn - cmtr的读写操作
 * @pfd: 读写地址，可以为文件的fd、或者buffer地址等
 * @buf: 缓冲区地址
 * @count: 需要读写的字节数
 */
#if defined(CMTR_IOFILE)
typedef int _my_cmtr_ioptr;
#define	_my_cmtr_ioptr_null -1
#define _my_read_cmtr_bufn(pfd, buf, count)         \
    do{	\
    int k=0;\
    k = _read((pfd), (buf), (count));\
    if( k<= 0)	\
{\
    printf("pfd%d k%d\n",pfd,k);\
    (pfd) = -1;							\
}\
    else{\
}\
}while(0);
#define _my_write_cmtr_bufn(pfd, buf, count)		\
    do{											\
    if (_write((pfd), (buf), (count)) <= 0)	\
{										\
    (pfd) = -1;							\
}										\
}while(0);
#define _my_check_cmtr_ptr(pfd)						\
    (((pfd) != -1) && ((pfd) != 0))
#elif defined(CMTR_IOBUFFER)
typedef unsigned char* _my_cmtr_ioptr;
#define	_my_cmtr_ioptr_null NULL
#define _my_read_cmtr_bufn(pfd, buf, count)			\
    do{                                 		\
    memcpy((buf), (pfd), (count));  		\
    (pfd) += (count);               		\
}while(0);
#define _my_write_cmtr_bufn(pfd, buf, count)		\
    do{                                 		\
    memcpy((pfd), (buf), (count));  		\
    (pfd) += (count);               		\
} while(0);
#define _my_check_cmtr_ptr(pfd)             		\
    (((pfd) != -1) && ((pfd) != 0))
#endif

/**
 * _my_cmtr_openrb/_my_cmtr_openwb/_my_cmtr_openab/_my_cmtr_close
 * - 可以根据需要改写该接口，如重定义为网口的recv\send、串口r\w
 * @pfd:  文件地址、缓冲区地址、或者socket地址等
 * @str:  文件路径或者联机ip或者串口地址或者共享内存名称
 */

#define _my_cmtr_openrb(str)    (open((str), O_RDONLY, S_IWRITE | S_IREAD))
#define _my_cmtr_openwb(str)    (open((str), O_CREAT | O_RDWR, S_IWRITE | S_IREAD))
#define _my_cmtr_openab(str)    (open((str), O_CREAT | O_APPEND | O_RDWR, S_IWRITE | S_IREAD))
#define _my_cmtr_close(pfd)     (close(pfd))

/**
 * 关于comtrade文件配置文件的宏定义。
 * 在此采用预定义最大个数方法，避免动态内存管理的问题。
 * 相关字符串最大字符个数，一般不会超过16个；
 * 模拟量端口最大个数，一般不会超过64个；
 * 数字量量端口最大个数，一般不会超过64个；
 * 采样率最大个数，一般不会超过8个；
 *
 */
#define		CMTR_STRING_MAX_LENGTH		64
#define		CMTR_ANALOG_MAX_COUNT		64*2
#define		CMTR_DIGIT_MAX_COUNT		64*2
#define		CMTR_SMPRATE_MAX_COUNT		16
#define		TRUE			                1
#define		FALSE	                    0


/**
 * cmtr_cfg_analog - 配置文件模拟量信息
 * @index: 模拟量端口序号（只是编号，解析时不做序号用）；
 * @name: 模拟量端口名称；
 * @phase: 模拟量端口相标识,值如（A、B、C、N等）；
 * @element：标识（还未知，待补充），一般为空；
 * @unit: 模拟量端口数值的单位，该单位常用来区分该端口是电流还是电流，值如：kV、V、A、mA等；
 * @factor_a: 系数a，一般为整数，可以是浮点数；
 * @factor_b: 系数b，一般为整数，可以是浮点数；
 * @offset_time: 时间偏移,指第一个点的时间偏移量，一般为0；
 * @smp_min: 通道的最小采用值，一般为整数,国内有些变态的仪器会生成浮点数(在次不支持)；
 * @smp_max: 通道的最大采用值，一般为整数,国内有些变态的仪器会生成浮点数(在次不支持)；
 * 通道采样的实际值计算方法：实际值 = factor_a * smp_value + factor_b；所以根据该公式，可以计算
 * 通道的最小值为：factor_a * smp_min + factor_b，最大值为：factor_a * smp_max + factor_b。
 *
 * 注：本来smp_min、smp_max为两个字节的一个数据（即最大为65535），但不同厂家会生成很大的四字节数据，
 *    所以采用s32类型；factor_a、factor_b用double类型，用float可能会丢精度；为了提供解析程序的适
 *    应性，以适应国内各种变态的有标准不遵循的厂家的仪器生成的cmtr文件。
 *
 */
struct   cmtr_cfg_analog
{
    signed long index;
    unsigned char name[CMTR_STRING_MAX_LENGTH];
    unsigned char phase[CMTR_STRING_MAX_LENGTH];
    unsigned char element[CMTR_STRING_MAX_LENGTH];
    unsigned char unit[CMTR_STRING_MAX_LENGTH];
    double factor_a;
    double factor_b;
    signed long offset_time;
    signed long smp_min;
    signed long smp_max;
    double primary;
    double secondary;
    unsigned char ps;
};


/**
 * cmtr_cfg_digit - 配置文件数字量信息
 * @index: 数字量端口序号（只是编号，解析时不做序号用）；
 * @name: 数字量端口名称；
 * @state: 数字量起始状态值，一般为1或者0，很少情况下会为2；
 *
 */
struct cmtr_cfg_digit
{
    signed long index;
    unsigned char name[CMTR_STRING_MAX_LENGTH];
    unsigned char phase[CMTR_STRING_MAX_LENGTH];
    unsigned char element[CMTR_STRING_MAX_LENGTH];
    signed char state;
};

/**
 * cmtr_cfg_smprate_info - 配置文件采样点信息
 * @rate: 采样率，一般为整数，也有小数表示的；
 * @point: 该采样率下采样的点数，为整数；
 *
 */
struct cmtr_cfg_smprate
{
    float rate;
    signed long point;
};

/**
 * cmtr_cfg_info - 配置文件信息。
 * @station_name: 厂站名称；
 * @kymograph_id: 录波器编号；
 * @analog_count: 模拟量个数；
 * @digit_count: 数字量个数；
 * @analogs: 模拟量信息；
 * @digits: 数字量信息；
 * @frequency: 基本频率，一般为额定频率，指的是电网频率；
 * @smprate_count: 采样率个数；
 * @smprates: 采样率信息；
 * @begin_time: 录波开始时间；
 * @end_time: 录波结束时间；
 * @file_type: 数据文件类型，可以“ASCII”和“Binary”，ASCII类型为dat文件可以用记事本打开看详
 *             细的采样信息；binary格式的只能用特殊的工具查看，为二进制数据文件；
 *
 */

struct cmtr_cfg_info
{
    unsigned char station_name[CMTR_STRING_MAX_LENGTH];
    unsigned char kymograph_id[CMTR_STRING_MAX_LENGTH];
    unsigned char rev_year[CMTR_STRING_MAX_LENGTH];
    unsigned long analog_count;
    unsigned long digit_count;
    struct cmtr_cfg_analog analogs[CMTR_ANALOG_MAX_COUNT];
    struct cmtr_cfg_digit digits[CMTR_DIGIT_MAX_COUNT];
    float frequency;
    unsigned long smprate_count;
    struct cmtr_cfg_smprate smprates[CMTR_SMPRATE_MAX_COUNT];
    unsigned char begin_time[CMTR_STRING_MAX_LENGTH];
    unsigned char end_time[CMTR_STRING_MAX_LENGTH];
    unsigned char file_type[CMTR_STRING_MAX_LENGTH];
    float timemult;

    //channel checked to show
    unsigned char channelChecked_analog[CMTR_ANALOG_MAX_COUNT];
    unsigned char channelChecked_digit[CMTR_DIGIT_MAX_COUNT];
};

/**
 * cmtr_dat_smpdot - 数据文件中的采样点数据信息.
 * @index: 端口序号（只是编号，解析时不做序号用）；
 * @time: 采样点采样时间偏移量，单位微妙；
 * @analogs: 模拟量信息，一般为有符号整数，国内有些变态的仪器会生成浮点数(在此不支持)；
 * @digits: 数字量信息，为有符号整数；
 *
 */
struct cmtr_dat_smpdot
{
    signed long index;
    signed long time;
    signed long analogs[CMTR_ANALOG_MAX_COUNT];
    signed char digits[CMTR_DIGIT_MAX_COUNT];
};



/**
 * write_cmtr_cfg_info - 写cmtr配置文件.
 * @pfd:  输入输出参数，地址
 * @cfg：输入参数，cmtr(cfg文件)结构体
 * @counter:  输出参数，写入的字节计数器；
 * 返回当前pfd指针,写失败返回NULL
 *
 */
 __declspec(dllexport) _my_cmtr_ioptr write_cmtr_cfg_info(_my_cmtr_ioptr pfd, struct cmtr_cfg_info *cfg,int *counter);

/**
 * write_cmtr_dat_smpdot_ascii - 写cmtr采样点数据信息(ascii格式).
 * @pfd:  输入输出参数，地址
 * @analog_count: 输入参数，模拟量个数；
 * @digit_count: 输入参数，数字量个数；
 * @dot:  输入参数，采样点信息；
 * @counter:  输出参数，写入的字节计数器；
 * 返回当前pfd指针,写失败返回NULL
 *
 */
  __declspec(dllexport) _my_cmtr_ioptr write_cmtr_dat_smpdot_ascii(_my_cmtr_ioptr pfd,int analog_count, int digit_count,struct cmtr_dat_smpdot *dot,int* counter);

/**
 * write_cmtr_dat_smpdot_binary - 写cmtr采样点数据信息（binary格式）.
 * @pfd:  输入输出参数，地址
 * @big_endian_tag: 输入参数，标识文件中数据的字节顺序，为FALSE按照小端写（默认值），True按照大端写；
 * @analog_count: 输入参数，模拟量个数；
 * @digit_count: 输入参数，数字量个数；
 * @dot:  输入参数，采样点信息；
 * @counter:  输出参数，写入的字节计数器；
 * 返回当前pfd指针,写失败返回NULL
 *
 */
  __declspec(dllexport) _my_cmtr_ioptr write_cmtr_dat_smpdot_binary(_my_cmtr_ioptr pfd, unsigned char big_endian_tag,int analog_count, int digit_count,struct cmtr_dat_smpdot *dot,int* counter);

/**
 * read_cmtr_cfg_info - 读cmtr配置文件.
 * @pfd:  输入输出参数，地址
 * @cfg：输出参数，cmtr(cfg文件)结构体
 * @counter:  输出参数，读取的字节计数器；
 * 返回当前pfd指针,读失败返回NULL
 *
 */
  __declspec(dllexport) _my_cmtr_ioptr read_cmtr_cfg_info(_my_cmtr_ioptr pfd,struct cmtr_cfg_info *cfg,int* counter);

/**
 * read_cmtr_dat_smpdot_ascii - 读ascii格式cmtr采样点数据信息.
 * @pfd:  输入输出参数，地址
 * @read_buf: 输入参数，读缓冲,在外部申请内存，避免在内部频繁申请、释放内存；
 * @buf_size: 输入参数，读缓冲区的大小；
 * @analog_count: 输入参数，模拟量个数；
 * @digit_count: 输入参数，数字量个数；
 * @dot:  输出参数，采样点信息；
 * @counter:  输出参数，读取的字节计数器；
 * 返回当前pfd指针,读失败返回NULL
 *
 */
  __declspec(dllexport) _my_cmtr_ioptr read_cmtr_dat_smpdot_ascii(_my_cmtr_ioptr pfd,unsigned char *read_buf, int buf_size,int analog_count, int digit_count,struct cmtr_dat_smpdot *dot ,int* counter);

/**
 * read_cmtr_dat_smpdot_binary - 读bin格式cmtr采样点数据信息.
 * @pfd:  输入输出参数，地址
 * @big_endian_tag: 输入参数，标识文件中数据的字节顺序，为FALSE按照小端读（默认值），True按照大端读；
 * @analog_count: 输入参数，模拟量个数；
 * @digit_count: 输入参数，数字量个数；
 * @dot:  输出参数，采样点信息；
 * @counter:  输出参数，读取的字节计数器；
 * 返回当前pfd指针,读失败返回NULL
 *
 */
  __declspec(dllexport)   _my_cmtr_ioptr   read_cmtr_dat_smpdot_binary(_my_cmtr_ioptr pfd, unsigned char big_endian_tag,int analog_count, int digit_count,  struct cmtr_dat_smpdot *dot,int* counter);
__declspec(dllexport)   char*     read_cmtr_dat_smpdot_binary_fast(const char* ptr, unsigned char big_endian_tag,int analog_count, int digit_count,  struct cmtr_dat_smpdot *dot,int* counter);
/**
 * print_cmtr_cfg_info - 打印cmtr文件配置数.
 * @cfg:  输入参数，cmtr文件配置数据;
 *
 */
  __declspec(dllexport) void print_cmtr_cfg_info(struct cmtr_cfg_info *cfg);

/**
 * print_cmtr_dat_smpdot - 打印cmtr数据文件采样点.
 * @cfg:  输入参数，cmtr文件配置数据;
 * @analog_count: 输入参数，模拟量个数；
 * @digit_count: 输入参数，数字量个数；
 * @dot:  输入参数，采样点信息；
 *
 */
  __declspec(dllexport) void print_cmtr_dat_smpdot(int analog_count, int digit_count,struct cmtr_dat_smpdot *dot);

#if defined (__cplusplus)
}
#endif /* defined (__cplusplus) */

#endif /* __INCLUDE_COMTRADE_FORMAT_H */
