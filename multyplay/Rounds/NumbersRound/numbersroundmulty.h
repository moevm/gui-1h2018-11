#ifndef NUMBERSROUNDMULTY_H
#define NUMBERSROUNDMULTY_H

#include <QWidget>
#include "round.h"
#include "multyplay/multyplay.h"
#include "GUIelements/charlabel.h"
#include "GUIelements/backspacelabel.h"
class MultyPlay;

namespace Ui {
class NumbersRoundMulty;
}

class NumbersRoundMulty : public Round
{
    Q_OBJECT

public:
    explicit NumbersRoundMulty(MultyPlay *parent = 0, QString setUP = "");
    ~NumbersRoundMulty();
    void setState(Round::roundState st) override;

public slots:

    void backspacePress();

    void sendAnswer();

protected:
    virtual void keyPressEvent(QKeyEvent *event);


private slots:
    void getFinalScore(QString score);
    void nextRound();

    void addNumber(QString q);

    void addArithmeticOperator(QString q);


private:
    void addArithmeticOperators();
    void addNumbers(QString setUP);

    Ui::NumbersRoundMulty *ui;
};

#endif // NUMBERSROUNDMULTY_H
