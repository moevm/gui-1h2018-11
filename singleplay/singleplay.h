#ifndef SINGLEPLAY_H
#define SINGLEPLAY_H

#include <QWidget>
#include <QtSql>
#include <databasehandler.h>
#include <mainwindow.h>
#include "singleplay/Rounds/round.h"

class MainWindow;

namespace Ui {
    class singleplay;
}

class SinglePlay : public QWidget
{
    Q_OBJECT

public:
    explicit SinglePlay(MainWindow *parent = 0);
    ~SinglePlay();
    DataBaseHandler* getDataBaseHandler();


private slots:
    void changeRound(Round::rounds r);

private:

    void setRound(Round::rounds r);

    Round *currentRound;

    Ui::singleplay *ui;

    DataBaseHandler *db;
};

#endif // SINGLEPLAY_H
