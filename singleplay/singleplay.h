#ifndef SINGLEPLAY_H
#define SINGLEPLAY_H

#include <QWidget>
#include "randomchar.h"
#include "charlabel.h"
#include <QtSql>
#include "numberlogic.h"
#include "backspacelabel.h"
namespace Ui {
class singleplay;
}

class singleplay : public QWidget
{
    Q_OBJECT

signals:

    gameStarted();
    gameEnded();

public slots:

    void createConsonant();
    void createVowel();
    void addCharToPreAnswer(QString str);
    void checkAnswerSlot();

    void endGame();
    void startNumberRound();
    void startLatterRound();
    void nextRound();

    void changeBigNumbersCount(int n);
    void changeSmallNumbersCount(int n);

    void backspacePress();

public:
    explicit singleplay(QWidget *parent = 0);
    ~singleplay();

protected:
    virtual void keyPressEvent(QKeyEvent *event);


private:

    QString searchSystemAnswer(QString str);
    QString wordValue(QString str);
    bool checkWord(QString);

    backspaceLabel *b;

    randomchar *rand;

    numberlogic *num;

    QString chars;

    Ui::singleplay *ui;

    QSqlDatabase db_word;

    QString preAnswer,systemAnswer;

    QVector<charlabel*> vecLabel;
};

#endif // SINGLEPLAY_H
