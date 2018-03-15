#ifndef NUMBERLOGIC_H
#define NUMBERLOGIC_H

#include <QVector>
class numberlogic
{
public:
    numberlogic(int small, int big);
    QString userInput(QVector<QString> formula);

    QVector<int> *getSet() const;

private:
    QString results(QVector<QString> formula);
    void generation();

    int res;
    QVector<QString> *mathFormula;
    QVector<int> *set;
};

#endif // NUMBERLOGIC_H
