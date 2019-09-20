#ifndef SYSINFOQML_H
#define SYSINFOQML_H

#include <QObject>
//#include "SysInfo.h"

class SysInfoQML : public QObject
{
    Q_OBJECT
public:
    explicit SysInfoQML(QObject *parent = nullptr);

signals:

public slots:
};

#endif // SYSINFOQML_H
