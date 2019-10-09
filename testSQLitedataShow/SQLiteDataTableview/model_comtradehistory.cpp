#include "model_comtradehistory.h"

Model_comtradehistory::Model_comtradehistory()
{
    this->updateModel();
    qDebug()<<"Model_comtradehistory()";
}

QVariant Model_comtradehistory::data(const QModelIndex & index, int role) const {

    int columnId = role - Qt::UserRole - 1;
    QModelIndex modelIndex = this->index(index.row(), columnId);
    return QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
}

QHash<int, QByteArray> Model_comtradehistory::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[seqnum] = "seqnum";
    roles[fname] = "fname";
    roles[ftime] = "ftime";
    roles[ftype] = "ftype";
    roles[fcause] = "fcause";
    roles[fsize_cfg] = "fsize_cfg";
    roles[fsize_dat] = "fsize_dat";
    roles[fpath] = "fpath";
    roles[fexistflag] = "fexistflag";
    return roles;
}

void Model_comtradehistory::updateModel()//const QString &date
{
    this->setQuery("SELECT "
                   TABLE_CHF_COLUMN01 ", "
                   TABLE_CHF_COLUMN02 ", "
                   TABLE_CHF_COLUMN03 ", "
                   TABLE_CHF_COLUMN04 ", "
                   TABLE_CHF_COLUMN05 ", "
                   TABLE_CHF_COLUMN06 ", "
                   TABLE_CHF_COLUMN07 ", "
                   TABLE_CHF_COLUMN08 ", "
                   TABLE_CHF_COLUMN09
                   " FROM " TABLE_COMTRADEHISTORY
                   " ORDER BY " TABLE_CHF_COLUMN01
                   " DESC limit 0,10");//desc 倒序  取前~条
}

QVariantMap Model_comtradehistory::get(int idx)
{
    QVariantMap map;
    foreach(int k, roleNames().keys()) {
        map[roleNames().value(k)] = data(index(idx, 0), k);
    }
    return map;
}
