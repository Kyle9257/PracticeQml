
QT -= gui

TEMPLATE = lib
DEFINES += CUSCONFIG_LIBRARY

CONFIG += c++17
json_dir = $$PWD/../thirdpart/nlohmann

INCLUDEPATH += $$json_dir

CONFIG(debug,debug|release){
    DESTDIR = $$PWD/../thirdpart/CusConfig/lib
    TARGET = CusConfigd

}
CONFIG(release,debug|release){
    DESTDIR = $$PWD/../thirdpart/CusConfig/lib
    TARGET = CusConfig

}

# 自动复制 DLL 到 bin
win32 {
    BIN_DIR = $$PWD/../thirdpart/CusConfig/bin
    HEAD_DIR = $$PWD/../thirdpart/CusConfig/include

    #到运行目录
    DEBUG_RUN =     $$PWD/../PracticeQml/bin/debug
    RELEASE_RUN =   $$PWD/../PracticeQml/bin/release

    # 创建 bin 目录
   # QMAKE_POST_LINK += $$QMAKE_MKDIR $$shell_path($$BIN_DIR) $$escape_expand(\\n\\t)

    # 复制文件
    QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$DESTDIR/$${TARGET}.dll) $$shell_path($$BIN_DIR) $$escape_expand(\\n\\t)

    QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$PWD/*.h) $$shell_path($$HEAD_DIR) $$escape_expand(\\n\\t)

    # Debug 额外复制 PDB
    CONFIG(debug, debug|release) {
        #QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$DESTDIR/$${TARGET}.pdb) $$shell_path($$BIN_DIR) $$escape_expand(\\n\\t)
        QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$DESTDIR/$${TARGET}.dll) $$shell_path($$DEBUG_RUN) $$escape_expand(\\n\\t)

    }else{
    QMAKE_POST_LINK += $$QMAKE_COPY $$shell_path($$DESTDIR/$${TARGET}.dll) $$shell_path($$RELEASE_RUN) $$escape_expand(\\n\\t)

    }
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CusConfig.cpp

HEADERS += \
    CusConfig_global.h \
    CusConfig.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
