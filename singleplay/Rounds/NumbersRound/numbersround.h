#ifndef NUMBERSROUND_H
#define NUMBERSROUND_H

#include <QWidget>
#include "round.h"
#include "singleplay/singleplay.h"
#include "singleplay/Rounds/NumbersRound/numbergenerator.h"
#include "GUIelements/charlabel.h"
#include "GUIelements/backspacelabel.h"

namespace Ui {
class NumbersRound;
}

class NumbersRound : public Round
{
    Q_OBJECT

public:
    explicit NumbersRound(SinglePlay *parent = 0);
    ~NumbersRound();

    void setState(Round::roundState st) override;

public slots:

    void controlValuesOfNumbers();
    void backspacePress();


protected:
    virtual void keyPressEvent(QKeyEvent *event);


private slots:
    void startNumbersRound();
    void showFinalScore();
    void nextRound();

    void addNumber(QString q);

    void addArithmeticOperator(QString q);


private:
    Ui::NumbersRound *ui;

    NumberGenerator *num_gen;

    static const unsigned int NUMBERS_COUNT = 6;

    void initBigAndLowCounters();
    void addArithmeticOperators();
    void addNumbers();
};

#endif // NUMBERSROUND_H
