#ifndef MODEL_CHANNELINFO_H
#define MODEL_CHANNELINFO_H

#include <QObject>
#include <QSqlQueryModel>

#include "sqldb.h"

class Model_ChannelInfo : public QSqlQueryModel
{
    Q_OBJECT
public:


    enum Roles {
        id = Qt::UserRole +1,
        channel_name,
        sys_cproperty,
        sys_cphase,
        sys_clinenum,
        sys_cratedvalue,
        sys_cratio,
        sys_crange,
        analog_uperlimitflag,
        analog_uperlimitvalue,
        analog_lowerlimitflag,
        analog_lowerlimitvalue,
        analog_mutationflag,
        analog_mutationvalue,
        analog_mutationpolarity,
        analog_harmonicflag_2,
        analog_harmonicvalue_2,
        analog_harmonicflag_3,
        analog_harmonicvalue_3,
        analog_harmonicflag_5,
        analog_harmonicvalue_5,
        analog_harmonicflag_7,
        analog_harmonicvalue_7
    };

    explicit Model_ChannelInfo(QObject *parent = nullptr);

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    protected:
    QHash<int, QByteArray> roleNames() const;

public slots:
    //读取数据库刷新界面显示
    void updateModel();//const QString &date

    void updateModel_SYS();
    void updateModel_ANA();

    //写入数据库
    bool refreshModel_SYS(const QString &index,//行号
                          const QString &channel_name,
                          const QString &sys_cproperty,
                          const QString &sys_cphase,
                          const QString &sys_clinenum,
                          const QString &sys_cratedvalue,
                          const QString &sys_cratio,
                          const QString &sys_crange);
    bool refreshModel_ANA(const QString &index,
                          const QString &uperlimitflag,
                          const QString &uperlimitvalue,
                          const QString &lowerlimitflag,
                          const QString &lowerlimitvalue,
                          const QString &mutationflag,
                          const QString &mutationvalue,
                          const QString &mutationpolarity,
                          const QString &harmonicflag_2,
                          const QString &harmonicvalue_2,
                          const QString &harmonicflag_3,
                          const QString &harmonicvalue_3,
                          const QString &harmonicflag_5,
                          const QString &harmonicvalue_5,
                          const QString &harmonicflag_7,
                          const QString &harmonicvalue_7);

    QVariantMap get(int idx);
};

#endif // MODEL_CHANNELINFO_H
