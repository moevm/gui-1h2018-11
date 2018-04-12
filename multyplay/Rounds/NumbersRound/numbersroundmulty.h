#ifndef NUMBERSROUNDMULTY_H
#define NUMBERSROUNDMULTY_H

#include <QWidget>

namespace Ui {
class NumbersRoundMulty;
}

class NumbersRoundMulty : public QWidget
{
    Q_OBJECT

public:
    explicit NumbersRoundMulty(QWidget *parent = 0);
    ~NumbersRoundMulty();

private:
    Ui::NumbersRoundMulty *ui;
};

#endif // NUMBERSROUNDMULTY_H
