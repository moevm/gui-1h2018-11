#ifndef ANAGRAMSROUNDMULTY_H
#define ANAGRAMSROUNDMULTY_H

#include <QWidget>
#include "round.h"
#include "multyplay/multyplay.h"
#include "GUIelements/charlabel.h"
#include "GUIelements/backspacelabel.h"
class MultyPlay;

namespace Ui {
class AnagramsRoundMulty;
}

class AnagramsRoundMulty : public Round
{
    Q_OBJECT

public:
    explicit AnagramsRoundMulty(MultyPlay *parent = 0, QString setUP = "");
    ~AnagramsRoundMulty();

    void setState(Round::roundState st) override;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
private slots:
    void addCharToPreAnswer(QString str);

    void sendAnswer();

    void getFinalScore(QString score);
    void nextRound();
    void backspacePress();
private:
    QString anagram;

    void setUpWords(QVector<QString> *anagram);
    Ui::AnagramsRoundMulty *ui;
};

#endif // ANAGRAMSROUNDMULTY_H
