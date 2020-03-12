#ifndef CUSTOMPROTOCOL_GLOBAL_H
#define CUSTOMPROTOCOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CUSTOMPROTOCOL_LIBRARY)
#  define CUSTOMPROTOCOLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CUSTOMPROTOCOLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // CUSTOMPROTOCOL_GLOBAL_H
