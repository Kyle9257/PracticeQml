QT += quick core widgets

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

opencv_dir = $$PWD/thirdpart/opencv454
json_dir = $$PWD/thidrdpart/nlohmann

INCLUDEPATH += $$opencv_dir/include

CONFIG(debug, release|debug){

    TARGET = Paracticed
    DESTDIR = $$PWD/bin/debug
    LIBS += -L$$opencv_dir/lib        -lopencv_world454d
}

CONFIG(release, release|debug){

    TARGET = Paractice
    DESTDIR = $$PWD/bin/release
    LIBS += -L$$opencv_dir/lib        -lopencv_world454
}

SOURCES += \
        DeviceHandler.cpp \
        ImageHandle.cpp \
        Interactor.cpp \
        SystemControlCore.cpp \
        main.cpp

RESOURCES += qml.qrc

include(DeviceMonitor/DeviceMonitor.pri)
include(ImageGetter/ImageGetter.pri)


INCLUDEPATH += $$PWD/DeviceMonitor

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    DeviceHandler.h \
    ImageHandle.h \
    Interactor.h \
    SystemControlCore.h
