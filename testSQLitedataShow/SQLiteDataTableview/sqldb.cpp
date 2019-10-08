#include "sqldb.h"

SqlDB::SqlDB(QObject *parent) : QObject(parent)
{

}

SqlDB::~SqlDB(){ }

bool SqlDB::connectToDataBase(QString path) {

    if(!path.contains(".db"))
    {
        path += "/";
        path += DATABASE_NAME;
    }

    if(!QFile(path).exists()){
        //文件不存在
        qDebug()<<"DB file not exist:" + path;
        return false;

    } else {
        return this->openDataBase(path);
    }
}

bool SqlDB::openDataBase(QString path) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(path);
    if(db.open()){
        return true;
    } else {
        qDebug()<<"DB file open failed:" + path;
        return false;
    }
}


