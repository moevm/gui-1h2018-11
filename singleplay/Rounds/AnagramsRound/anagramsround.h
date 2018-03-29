#ifndef ANAGRAMROUND_H
#define ANAGRAMROUND_H

#include <QWidget>
#include "singleplay/Rounds/round.h"
#include "singleplay/Rounds/LattersRound/charlabel.h"
#include "singleplay/singleplay.h"
#include "singleplay/Rounds/LattersRound/backspacelabel.h"
namespace Ui {
class AnagramRound;
}

class AnagramsRound : public Round
{
    Q_OBJECT

public:
    explicit AnagramsRound(SinglePlay *parent = 0);
    ~AnagramsRound();

    void setState(Round::roundState st) override;

protected:
    virtual void keyPressEvent(QKeyEvent *event);
private slots:
    void addCharToPreAnswer(QString str);

    void showFinalScore();
    void nextRound();
    void backspacePress();
private:
    DataBaseHandler *db;
    Ui::AnagramRound *ui;
    QString anagram;

    void setUpWords(QVector<QString> *anagram);
};

#endif // ANAGRAMROUND_H
