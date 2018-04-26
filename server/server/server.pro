QT -= gui
QT += network core sql
CONFIG += c++11 console
CONFIG -= app_bundle

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
    server.cpp \
    client.cpp \
    databasehandler.cpp \
    lattersround/chargenerator.cpp

HEADERS += \
    server.h \
    client.h \
    databasehandler.h \
    lattersround/chargenerator.h

win32 {
    CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
    CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

    copy_to_build.path = $$DESTDIR
    copy_to_build.files = copy_to_build_dir/*

    INSTALLS += \
        copy_to_build
}

android {
    deployment.files += words.db
    deployment.path = /assets/db
    INSTALLS += deployment
}

