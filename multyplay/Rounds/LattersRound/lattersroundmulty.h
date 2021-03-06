#ifndef LATTERSROUNDMULTY_H
#define LATTERSROUNDMULTY_H

#include <QWidget>
#include "round.h"
#include "multyplay/multyplay.h"
#include "GUIelements/charlabel.h"
#include "GUIelements/backspacelabel.h"
class MultyPlay;

namespace Ui {
class LattersRoundMulty;
}

class LattersRoundMulty : public Round
{
    Q_OBJECT

public:
    explicit LattersRoundMulty(MultyPlay *parent = 0, QString setUP = "");
    ~LattersRoundMulty();

public slots:

    void addCharToPreAnswer(QString str);

    void nextRound();

    void initSignalsAndSlots();

    void setState(Round::roundState st);

    void addCharLabel(QString str);

    void fillCharWidget(QString chars);

    void getFinalScore(QString answer);

    void sendAnswer();

    void skipRound();

protected:
    virtual void keyPressEvent(QKeyEvent *event);

public slots:
    void backspacePress();


private slots:

    void answerSended();

private:

    void addBackspaceLabel();

    Ui::LattersRoundMulty *ui;
};

#endif // LATTERSROUNDMULTY_H
