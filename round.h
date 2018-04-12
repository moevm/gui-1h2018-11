#pragma once

#include <QWidget>

class Round : public QWidget
{
    Q_OBJECT


public:
    enum roundState { preparation, play, end };

    enum rounds {latters, numbers, anagrams};

    virtual void setState(roundState st) = 0;

    Round(QWidget *parent);
    ~Round();
signals :
    void endRound(Round::rounds r);
};
