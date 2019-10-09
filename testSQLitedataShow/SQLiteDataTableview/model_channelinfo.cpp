#include "model_channelinfo.h"

Model_ChannelInfo::Model_ChannelInfo(QObject *parent) : QSqlQueryModel(parent)
{
    this->updateModel();
    qDebug()<<"Model_ChannelInfo()";
}

QVariant Model_ChannelInfo::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}





QHash<int, QByteArray> Model_ChannelInfo::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[id] = "id";
    roles[channel_name] = "channel_name";
    roles[sys_cproperty] = "sys_cproperty";
    roles[sys_cphase] = "sys_cphase";
    roles[sys_clinenum] = "sys_clinenum";
    roles[sys_cratedvalue] = "sys_cratedvalue";
    roles[sys_cratio] = "sys_cratio";
    roles[sys_crange] = "sys_crange";
    roles[analog_uperlimitflag]="analog_uperlimitflag";
    roles[analog_uperlimitvalue] = "analog_uperlimitvalue";
    roles[analog_lowerlimitflag]="analog_lowerlimitflag";
    roles[analog_lowerlimitvalue] = "analog_lowerlimitvalue";
    roles[analog_mutationflag]="analog_mutationflag";
    roles[analog_mutationvalue] = "analog_mutationvalue";
    roles[analog_mutationpolarity] = "analog_mutationpolarity";
    roles[analog_harmonicflag_2]="analog_harmonicflag_2";
    roles[analog_harmonicvalue_2] = "analog_harmonicvalue_2";
    roles[analog_harmonicflag_3]="analog_harmonicflag_3";
    roles[analog_harmonicvalue_3] = "analog_harmonicvalue_3";
    roles[analog_harmonicflag_5]="analog_harmonicflag_5";
    roles[analog_harmonicvalue_5] = "analog_harmonicvalue_5";
    roles[analog_harmonicflag_7]="analog_harmonicflag_7";
    roles[analog_harmonicvalue_7] = "analog_harmonicvalue_7";

    return roles;
}

void Model_ChannelInfo::updateModel()
{
    this->setQuery("SELECT "
                   TABLE_CHINFO01_PUB_01 ", "
                   TABLE_CHINFO02_PUB_02 ", "
                   TABLE_CHINFO03_SYS_01 ", "
                   TABLE_CHINFO04_SYS_02 ", "
                   TABLE_CHINFO05_SYS_03 ", "
                   TABLE_CHINFO06_SYS_04 ", "
                   TABLE_CHINFO07_SYS_05 ", "
                   TABLE_CHINFO08_SYS_06 ", "
                   TABLE_CHINFO09_ANA_01f ", "
                   TABLE_CHINFO09_ANA_01 ", "
                   TABLE_CHINFO10_ANA_02f ", "
                   TABLE_CHINFO10_ANA_02 ", "
                   TABLE_CHINFO11_ANA_03f ", "
                   TABLE_CHINFO11_ANA_03 ", "
                   TABLE_CHINFO12_ANA_04 ", "
                   TABLE_CHINFO13_ANA_05f ", "
                   TABLE_CHINFO13_ANA_05 ", "
                   TABLE_CHINFO14_ANA_06f ", "
                   TABLE_CHINFO14_ANA_06 ", "
                   TABLE_CHINFO15_ANA_07f ", "
                   TABLE_CHINFO15_ANA_07 ", "
                   TABLE_CHINFO16_ANA_08f ", "
                   TABLE_CHINFO16_ANA_08
                   " FROM " TABLE_CHANNELINFO
                   " ORDER BY " TABLE_CHINFO01_PUB_01);
}

void Model_ChannelInfo::updateModel_SYS()
{
    this->setQuery("SELECT "
                   TABLE_CHINFO01_PUB_01 ", "
                   TABLE_CHINFO02_PUB_02 ", "
                   TABLE_CHINFO03_SYS_01 ", "
                   TABLE_CHINFO04_SYS_02 ", "
                   TABLE_CHINFO05_SYS_03 ", "
                   TABLE_CHINFO06_SYS_04 ", "
                   TABLE_CHINFO07_SYS_05 ", "
                   TABLE_CHINFO08_SYS_06
                   " FROM " TABLE_CHANNELINFO
                   " ORDER BY " TABLE_CHINFO01_PUB_01);
}

void Model_ChannelInfo::updateModel_ANA()
{
    this->setQuery("SELECT "
                   TABLE_CHINFO01_PUB_01 ", "
                   TABLE_CHINFO02_PUB_02 ", "
//                   TABLE_CHINFO09_ANA_01 ", "
//                   TABLE_CHINFO10_ANA_02 ", "
//                   TABLE_CHINFO11_ANA_03 ", "
//                   TABLE_CHINFO12_ANA_04 ", "
//                   TABLE_CHINFO13_ANA_05 ", "
//                   TABLE_CHINFO14_ANA_06 ", "
//                   TABLE_CHINFO15_ANA_07 ", "
//                   TABLE_CHINFO16_ANA_08
                   TABLE_CHINFO09_ANA_01f ", "
                   TABLE_CHINFO09_ANA_01 ", "
                   TABLE_CHINFO10_ANA_02f ", "
                   TABLE_CHINFO10_ANA_02 ", "
                   TABLE_CHINFO11_ANA_03f ", "
                   TABLE_CHINFO11_ANA_03 ", "
                   TABLE_CHINFO12_ANA_04 ", "
                   TABLE_CHINFO13_ANA_05f ", "
                   TABLE_CHINFO13_ANA_05 ", "
                   TABLE_CHINFO14_ANA_06f ", "
                   TABLE_CHINFO14_ANA_06 ", "
                   TABLE_CHINFO15_ANA_07f ", "
                   TABLE_CHINFO15_ANA_07 ", "
                   TABLE_CHINFO16_ANA_08f ", "
                   TABLE_CHINFO16_ANA_08
                   " FROM " TABLE_CHANNELINFO
                   " ORDER BY " TABLE_CHINFO01_PUB_01);
}

bool Model_ChannelInfo::refreshModel_SYS(const QString &index,//行号
                                         const QString &channel_name,
                                         const QString &sys_cproperty,
                                         const QString &sys_cphase,
                                         const QString &sys_clinenum,
                                         const QString &sys_cratedvalue,
                                         const QString &sys_cratio,
                                         const QString &sys_crange)
{
    QVariantList data;
    data.append(channel_name);
    data.append(sys_cproperty);
    data.append(sys_cphase);
    data.append(sys_clinenum);
    data.append(sys_cratedvalue);
    data.append(sys_cratio);
    data.append(sys_crange);

    QSqlQuery query;
    //INSERT INTO 新增一行
    //UPDATE 修改已存在的行
    query.prepare("UPDATE " TABLE_CHANNELINFO " SET "
                  TABLE_CHINFO02_PUB_02 " = :channel_name, "
                  TABLE_CHINFO03_SYS_01 " = :sys_cproperty, "
                  TABLE_CHINFO04_SYS_02 " = :sys_cphase, "
                  TABLE_CHINFO05_SYS_03 " = :sys_clinenum, "
                  TABLE_CHINFO06_SYS_04 " = :sys_cratedvalue, "
                  TABLE_CHINFO07_SYS_05 " = :sys_cratio, "
                  TABLE_CHINFO08_SYS_06 "  =  :sys_crange WHERE id = :id;");

    query.bindValue(":id", index);
    query.bindValue(":channel_name",        data[0].toString());
    query.bindValue(":sys_cproperty",       data[1].toString());
    query.bindValue(":sys_cphase",          data[2].toString());
    query.bindValue(":sys_clinenum",        data[3].toString());
    query.bindValue(":sys_cratedvalue",     data[4].toString());
    query.bindValue(":sys_cratio",          data[5].toString());
    query.bindValue(":sys_crange",          data[6].toString());

    //
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_CHANNELINFO;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }
}

bool Model_ChannelInfo::refreshModel_ANA(const QString &index,//行号
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
                                         const QString &harmonicvalue_7)
{
    QVariantList data;
    data.append(uperlimitflag);
    data.append(uperlimitvalue);
    data.append(lowerlimitflag);
    data.append(lowerlimitvalue);
    data.append(mutationflag);
    data.append(mutationvalue);
    data.append(mutationpolarity);
    data.append(harmonicflag_2);
    data.append(harmonicvalue_2);
    data.append(harmonicflag_3);
    data.append(harmonicvalue_3);
    data.append(harmonicflag_5);
    data.append(harmonicvalue_5);
    data.append(harmonicflag_7);
    data.append(harmonicvalue_7);

    QSqlQuery query;
    //INSERT INTO 新增一行
    //UPDATE 修改已存在的行
    query.prepare("UPDATE " TABLE_CHANNELINFO " SET "
                  TABLE_CHINFO09_ANA_01f " = :analog_uperlimitflag, "
                  TABLE_CHINFO09_ANA_01 " = :analog_uperlimitvalue, "
                  TABLE_CHINFO10_ANA_02f " = :analog_lowerlimitflag, "
                  TABLE_CHINFO10_ANA_02 " = :analog_lowerlimitvalue, "
                  TABLE_CHINFO11_ANA_03f " = :analog_mutationflag, "
                  TABLE_CHINFO11_ANA_03 " = :analog_mutationvalue, "
                  TABLE_CHINFO12_ANA_04 " = :analog_mutationpolarity, "
                  TABLE_CHINFO13_ANA_05f " = :analog_harmonicflag_2, "
                  TABLE_CHINFO13_ANA_05 " = :analog_harmonicvalue_2, "
                  TABLE_CHINFO14_ANA_06f " = :analog_harmonicflag_3, "
                  TABLE_CHINFO14_ANA_06 " = :analog_harmonicvalue_3, "
                  TABLE_CHINFO15_ANA_07f " = :analog_harmonicflag_5, "
                  TABLE_CHINFO15_ANA_07 " = :analog_harmonicvalue_5, "
                  TABLE_CHINFO16_ANA_08f " = :analog_harmonicflag_7, "
                  TABLE_CHINFO16_ANA_08 "  =  :analog_harmonicvalue_7 WHERE id = :id;");

    query.bindValue(":id", index);
    query.bindValue(":analog_uperlimitflag",        data[0].toString());
    query.bindValue(":analog_uperlimitvalue",       data[1].toString());
    query.bindValue(":analog_lowerlimitflag",       data[2].toString());
    query.bindValue(":analog_lowerlimitvalue",      data[3].toString());
    query.bindValue(":analog_mutationflag",         data[4].toString());
    query.bindValue(":analog_mutationvalue",        data[5].toString());
    query.bindValue(":analog_mutationpolarity",     data[6].toString());
    query.bindValue(":analog_harmonicflag_2",       data[7].toString());
    query.bindValue(":analog_harmonicvalue_2",      data[8].toString());
    query.bindValue(":analog_harmonicflag_3",       data[9].toString());
    query.bindValue(":analog_harmonicvalue_3",      data[10].toString());
    query.bindValue(":analog_harmonicflag_5",       data[11].toString());
    query.bindValue(":analog_harmonicvalue_5",      data[12].toString());
    query.bindValue(":analog_harmonicflag_7",       data[13].toString());
    query.bindValue(":analog_harmonicvalue_7",      data[14].toString());
    //
    if(!query.exec()){
        qDebug() << "error insert into " << TABLE_CHANNELINFO;
        qDebug() << query.lastError().text();
        return false;
    } else {
        return true;
    }

}




QVariantMap Model_ChannelInfo::get(int idx)
{
    QVariantMap map;
    foreach(int k, roleNames().keys()) {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }
    return map;
}

