#ifndef ANAGRAMSROUNDMULTY_H
#define ANAGRAMSROUNDMULTY_H

#include <QWidget>

namespace Ui {
class AnagramsRoundMulty;
}

class AnagramsRoundMulty : public QWidget
{
    Q_OBJECT

public:
    explicit AnagramsRoundMulty(QWidget *parent = 0);
    ~AnagramsRoundMulty();

private:
    Ui::AnagramsRoundMulty *ui;
};

#endif // ANAGRAMSROUNDMULTY_H
