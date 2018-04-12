#ifndef MULTYPLAY_H
#define MULTYPLAY_H

#include <QWidget>
#include <mainwindow.h>
#include "round.h"
#include "multyplay/authform.h"
#include "multyplay/connection.h"
#include "multyplay/lostconnection.h"
#include "multyplay/Rounds/LattersRound/lattersroundmulty.h"
#include "multyplay/Rounds/AnagramsRound/anagramsroundmulty.h"
#include "multyplay/Rounds/NumbersRound/numbersroundmulty.h"

namespace Ui {
class MultyPlay;
}

class MultyPlay : public QWidget
{
    Q_OBJECT

public:
    explicit MultyPlay(MainWindow *parent = 0);
    ~MultyPlay();

    void setConnection(Connection *newConnection);    
    Connection* getConnection();

private slots:
    void changeRound(Round::rounds r);

    void connctionRefuse(QString str);
    void connectionSuccess();
    void gameStart();

    void showAuthForm();

private:    

    Connection *currentConnection;

    QWidget *centralWidget;

    Ui::MultyPlay *ui;
};

#endif // MULTYPLAY_H
