#pragma once

#include "singleplay/Rounds/round.h"
#include "singleplay/Rounds/LattersRound/chargenerator.h"
#include "singleplay/Rounds/LattersRound/charlabel.h"
#include "singleplay/singleplay.h"

namespace Ui {
    class LattersRound;
}

class LattersRound : public Round
{
    Q_OBJECT

public:
    LattersRound(SinglePlay *parent);
    ~LattersRound();

    public slots:

    void createConsonant();
    void createVowel();
    void addCharToPreAnswer(QString str);

    void startLattersRound();

    void getFinalScore();

    void nextRound();


protected:
    virtual void keyPressEvent(QKeyEvent *event);

    public slots:
    void backspacePress();


private:


    void initCharGenerator();
    void initSignalsAndSlots();

    void setState(Round::roundState st);

    void addCharLabel(QString str);

    void fillCharWidget(CharGenerator::charType ct);

    QString getSystemAnswer();
    QString systemAnswer;

    CharGenerator charGenerator;

    DataBaseHandler *db;

    Ui::LattersRound *ui;

    void addBackspaceLabel();
};
