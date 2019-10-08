#ifndef MODEL_COMTRADEHISTORY_H
#define MODEL_COMTRADEHISTORY_H

#include <QObject>

#include <QSqlQueryModel>
#include "sqldb.h"

class Model_comtradehistory : public QSqlQueryModel
{
    Q_OBJECT
public:
    enum Roles {
        seqnum = Qt::UserRole +1,
        fname,
        ftime,
        ftype,
        fcause,
        fsize_cfg,
        fsize_dat,
        fpath,
        fexistflag
    };



    Model_comtradehistory();

    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;


    protected:
    QHash<int, QByteArray> roleNames() const;

public slots:
    void updateModel();//const QString &date
    QVariantMap get(int idx);


};

#endif // MODEL_COMTRADEHISTORY_H
