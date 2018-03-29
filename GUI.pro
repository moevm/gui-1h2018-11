#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T17:21:22
#
#-------------------------------------------------

QT       += core gui sql

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
    singleplay/Rounds/round.h \
    singleplay/Rounds/LattersRound/lattersround.h \
    singleplay/Rounds/LattersRound/backspacelabel.h \
    singleplay/Rounds/LattersRound/chargenerator.h \
    singleplay/Rounds/LattersRound/charlabel.h \
    singleplay/Rounds/NumbersRound/numbersround.h \
    singleplay/Rounds/AnagramsRound/anagramsround.h \
    singleplay/Rounds/NumbersRound/numbergenerator.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    singleplay/singleplay.cpp \
    startmenu.cpp \
    databasehandler.cpp \
    singleplay/Rounds/round.cpp \
    singleplay/Rounds/LattersRound/lattersround.cpp \
    singleplay/Rounds/LattersRound/backspacelabel.cpp \
    singleplay/Rounds/LattersRound/chargenerator.cpp \
    singleplay/Rounds/LattersRound/charlabel.cpp \
    singleplay/Rounds/NumbersRound/numbersround.cpp \
    singleplay/Rounds/AnagramsRound/anagramsround.cpp \
    singleplay/Rounds/NumbersRound/numbergenerator.cpp

FORMS += \
    mainwindow.ui \
    singleplay/singleplay.ui \    
    singleplay/Rounds/LattersRound/lattersround.ui \
    singleplay/Rounds/NumbersRound/numbersround.ui \
    singleplay/Rounds/AnagramsRound/anagramround.ui

DISTFILES +=


