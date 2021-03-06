QT += quick
QT += gui
QT       += core
QT += widgets
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
    form.cpp \
    form01.cpp \
    comtrde/mainwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    form.ui \
    form01.ui \
    comtrde/mainwindow.ui

HEADERS += \
    form.h \
    form01.h \
    comtrde/mainwindow.h \
    FFTW3_msvc_2017_64/api/api.h \
    FFTW3_msvc_2017_64/api/f77funcs.h \
    FFTW3_msvc_2017_64/api/fftw3.h \
    FFTW3_msvc_2017_64/api/guru.h \
    FFTW3_msvc_2017_64/api/guru64.h \
    FFTW3_msvc_2017_64/api/mktensor-iodims.h \
    FFTW3_msvc_2017_64/api/plan-guru-dft.h \
    FFTW3_msvc_2017_64/api/plan-guru-dft-c2r.h \
    FFTW3_msvc_2017_64/api/plan-guru-dft-r2c.h \
    FFTW3_msvc_2017_64/api/plan-guru-r2r.h \
    FFTW3_msvc_2017_64/api/plan-guru-split-dft.h \
    FFTW3_msvc_2017_64/api/plan-guru-split-dft-c2r.h \
    FFTW3_msvc_2017_64/api/plan-guru-split-dft-r2c.h \
    FFTW3_msvc_2017_64/api/x77.h

LIBS += -L$$PWD/lib -lcomtradeview
LIBS += -L$$PWD/lib -lcomtrade_format
LIBS += -L$$PWD/FFTW3_msvc_2017_64 -llibfftw3-3


