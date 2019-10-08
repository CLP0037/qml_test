#ifndef SQLDB_H
#define SQLDB_H

#include <QObject>

#include <QSql>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QFile>
#include <QDate>
#include <QDebug>

#define DATABASE_HOSTNAME   "wrDataBase"
#define DATABASE_NAME       "db_wave_recorder.db"

//历史录波文件信息表
#define TABLE_COMTRADEHISTORY   "history_comtradefile_info"
#define TABLE_CHF_COLUMN01      "seqnum"
#define TABLE_CHF_COLUMN02      "fname"
#define TABLE_CHF_COLUMN03      "ftime"
#define TABLE_CHF_COLUMN04      "ftype"
#define TABLE_CHF_COLUMN05      "fcause"
#define TABLE_CHF_COLUMN06      "fsize_cfg"
#define TABLE_CHF_COLUMN07      "fsize_dat"
#define TABLE_CHF_COLUMN08      "fpath"
#define TABLE_CHF_COLUMN09      "fexistflag"

//通道信息（通道系统基本信息+通道录波基本信息）
#define TABLE_CHANNELINFO  "channelinfo_sys_analog"
#define TABLE_CHINFO01_PUB_01 "id"
#define TABLE_CHINFO02_PUB_02 "channel_name"
#define TABLE_CHINFO03_SYS_01 "sys_cproperty"
#define TABLE_CHINFO04_SYS_02 "sys_cphase"
#define TABLE_CHINFO05_SYS_03 "sys_clinenum"
#define TABLE_CHINFO06_SYS_04 "sys_cratedvalue"
#define TABLE_CHINFO07_SYS_05 "sys_cratio"
#define TABLE_CHINFO08_SYS_06 "sys_crange"
#define TABLE_CHINFO09_ANA_01 "analog_uperlimitvalue"
#define TABLE_CHINFO10_ANA_02 "analog_lowerlimitvalue"
#define TABLE_CHINFO11_ANA_03 "analog_mutationvalue"
#define TABLE_CHINFO12_ANA_04 "analog_mutationpolarity"
#define TABLE_CHINFO13_ANA_05 "analog_harmonicvalue_2"
#define TABLE_CHINFO14_ANA_06 "analog_harmonicvalue_3"
#define TABLE_CHINFO15_ANA_07 "analog_harmonicvalue_5"
#define TABLE_CHINFO16_ANA_08 "analog_harmonicvalue_7"
#define TABLE_CHINFO09_ANA_01f "analog_uperlimitflag"
#define TABLE_CHINFO10_ANA_02f "analog_lowerlimitflag"
#define TABLE_CHINFO11_ANA_03f "analog_mutationflag"
//#define TABLE_CHINFO12_ANA_04 "analog_mutationpolarity"
#define TABLE_CHINFO13_ANA_05f "analog_harmonicflag_2"
#define TABLE_CHINFO14_ANA_06f "analog_harmonicflag_3"
#define TABLE_CHINFO15_ANA_07f "analog_harmonicflag_5"
#define TABLE_CHINFO16_ANA_08f "analog_harmonicflag_7"


class SqlDB : public QObject
{
    Q_OBJECT
public:
    explicit SqlDB(QObject *parent = nullptr);
    ~SqlDB();

    bool connectToDataBase(QString path);

private:
    bool openDataBase(QString path);


private:
    QSqlDatabase    db;

signals:

public slots:
};

#endif // SQLDB_H
