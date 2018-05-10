#ifndef NUMBERGENERATOR_H
#define NUMBERGENERATOR_H

#include <QString>
#include <QVector>

class NumberGenerator
{
public:

    NumberGenerator(const int &lowNumbers, const int &bigNumbers);

    QString getExpression();

    QVector<QString> getNumbers();

    QVector<QString> makeExpression(QString str);

    QString getRequiredNumber();

    QString getUserAnswer(QString str);
private:

    static const constexpr int BIG_NUMBERS[] = {25, 50, 75, 100};
    static const constexpr int LOW_NUMBERS[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    static const constexpr char OPERATORS[] = {'+', '-', '*', '/'};

    QVector<QString> *expression;
    QVector<QString> *numbers;

    void generateExpression(const int &lowNumbers, const int &bigNumbers);

    QVector<QString> fillUpNumbers(const int &lowNumbers, const int &bigNumbers);
    void shakeExpression(QVector<QString> *expr);
    void addOperators(QVector<QString> *expr);
    void insertOperator(QVector<QString> *expr, char oper, int pos);

    int getAnswer(QVector<QString> *expr);

    bool isOperator(QString str);
};

#endif // NUMBERGENERATOR_H
