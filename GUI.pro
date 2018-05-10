#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T17:21:22
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    mainwindow.h \
    singleplay/singleplay.h \
    startmenu.h \    
    databasehandler.h \    
    singleplay/Rounds/LattersRound/lattersround.h \
    singleplay/Rounds/LattersRound/chargenerator.h \
    singleplay/Rounds/NumbersRound/numbersround.h \
    singleplay/Rounds/AnagramsRound/anagramsround.h \
    singleplay/Rounds/NumbersRound/numbergenerator.h \
    GUIelements/backspacelabel.h \
    GUIelements/charlabel.h \
    round.h \
    multyplay/multyplay.h \
    multyplay/authform.h \    
    multyplay/connection.h \
    multyplay/lostconnection.h \
    multyplay/Rounds/LattersRound/lattersroundmulty.h \
    multyplay/Rounds/NumbersRound/numbersroundmulty.h \
    multyplay/Rounds/AnagramsRound/anagramsroundmulty.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    singleplay/singleplay.cpp \
    startmenu.cpp \
    databasehandler.cpp \    
    singleplay/Rounds/LattersRound/lattersround.cpp \    
    singleplay/Rounds/LattersRound/chargenerator.cpp \    
    singleplay/Rounds/NumbersRound/numbersround.cpp \
    singleplay/Rounds/AnagramsRound/anagramsround.cpp \
    singleplay/Rounds/NumbersRound/numbergenerator.cpp \
    GUIelements/backspacelabel.cpp \
    GUIelements/charlabel.cpp \
    round.cpp \    
    multyplay/multyplay.cpp \
    multyplay/authform.cpp \    
    multyplay/connection.cpp \
    multyplay/lostconnection.cpp \
    multyplay/Rounds/LattersRound/lattersroundmulty.cpp \
    multyplay/Rounds/NumbersRound/numbersroundmulty.cpp \
    multyplay/Rounds/AnagramsRound/anagramsroundmulty.cpp

FORMS += \
    mainwindow.ui \
    singleplay/singleplay.ui \    
    singleplay/Rounds/LattersRound/lattersround.ui \
    singleplay/Rounds/NumbersRound/numbersround.ui \
    singleplay/Rounds/AnagramsRound/anagramround.ui \    
    multyplay/multyplay.ui \
    multyplay/authform.ui \
    multyplay/lostconnection.ui \
    multyplay/Rounds/LattersRound/lattersroundmulty.ui \
    multyplay/Rounds/NumbersRound/numbersroundmulty.ui \
    multyplay/Rounds/AnagramsRound/anagramsroundmulty.ui




win32 {
    CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
    CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

    copy_to_build.path = $$DESTDIR
    copy_to_build.files = copy_to_build_dir/*

    INSTALLS += \
        copy_to_build
}

linux {
    CONFIG(release, debug|release): DESTDIR = $$OUT_PWD/release
    CONFIG(debug, debug|release): DESTDIR = $$OUT_PWD/debug

    copy_to_build.path = $$DESTDIR
    copy_to_build.files = copy_to_build_dir/*

    INSTALLS += \
        copy_to_build
}

android {
    deployment.path = /assets
    deployment.files += /assets/words.db
    INSTALLS += deployment
}


