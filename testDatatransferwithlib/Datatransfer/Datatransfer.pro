QT += qml quick widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
    datatransfer/devdatatransfer_wr.cpp \
    testdata.cpp \
    client/wrclientstuff.cpp \
    server/wrserverstuff.cpp \
    udpclient/udpclient.cpp \
    udpserver/udpserver.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    datatransfer/devdatatransfer_wr.h \
    datatransfer/publicdataclass.h \
    testdata.h \
    client/wrclientstuff.h \
    server/wrserverstuff.h \
    udpclient/udpclient.h \
    udpserver/udpserver.h

INCLUDEPATH += ./include

#message($$QT_VERSION)
equals(QT_VERSION, 5.12.2){#message($$QT_VERSION)
    message("version 5.12.2")
    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/5.12/release/ -lCustomProtocol
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/5.12/debug/ -lCustomProtocol
    else:unix: LIBS += -L$$PWD/lib/ -lCustomProtocol
}

equals(QT_VERSION, 5.9.7){#message($$QT_VERSION)
    message("version 5.9.7")
    win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/5.9.7/release/ -lCustomProtocol
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/5.9.7/debug/ -lCustomProtocol
    else:unix: LIBS += -L$$PWD/lib/ -lCustomProtocol
}

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/release/ -lCustomProtocol
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/debug/ -lCustomProtocol
#else:unix: LIBS += -L$$PWD/lib/ -lCustomProtocol
