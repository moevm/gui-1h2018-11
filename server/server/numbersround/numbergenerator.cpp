#include "numbergenerator.h"

#include "numbergenerator.h"
#include <random>
#include <ctime>
constexpr const  int NumberGenerator::LOW_NUMBERS[];
constexpr const  int NumberGenerator::BIG_NUMBERS[] ;
constexpr const char NumberGenerator::OPERATORS[];

NumberGenerator::NumberGenerator(const int &lowNumbers, const int &bigNumbers)
{
    numbers = new QVector<QString>();
    generateExpression(lowNumbers, bigNumbers);
}

QString NumberGenerator::getExpression()
{
    QString res;
    for (QString str : *expression) {
        res.append(str);
    }
    return res;
}

QVector<QString> NumberGenerator::getNumbers()
{
    return *numbers;
}

void NumberGenerator::generateExpression(const int &lowNumbers,
        const int &bigNumbers)
{
    srand(time(0));
    expression = new QVector<QString>(fillUpNumbers(lowNumbers, bigNumbers));

    shakeExpression(expression);
    addOperators(expression);
}

void NumberGenerator::shakeExpression(QVector<QString> *expr)
{

    for (int i = 0, size = expr->length(); i < size; ++i)
        std::swap(*(expr->begin() + i), *(expr->begin() + std::rand() % size));
}

QVector<QString> NumberGenerator::fillUpNumbers(const int &lowNumbers,
        const int &bigNumbers)
{
    QVector<QString> tmp;
    for (unsigned int i = 0; i < lowNumbers; ++i) {
        tmp.push_back(QString::number(LOW_NUMBERS[rand() % 10]));
        numbers->push_back(QString::number(LOW_NUMBERS[rand() % 10]));
    }
    for (unsigned int i = 0; i < bigNumbers; ++i) {
        tmp.push_back(QString::number(BIG_NUMBERS[rand() % 4]));
        numbers->push_back(QString::number(BIG_NUMBERS[rand() % 4]));
    }

    return tmp;
}

void NumberGenerator::addOperators(QVector<QString> *expr)
{
    for (int i = 0; i < 5; ++i) {
        insertOperator(expr, OPERATORS[rand() % 4], i);
    }

}

void NumberGenerator::insertOperator(QVector<QString> *expr, char oper, int pos)
{
    switch (oper) {
    case '/':
        if (expr->at(pos * 2).toInt() % expr->at(pos * 2 + 1).toInt()) {
            insertOperator(expr, OPERATORS[rand() % 4], pos);
        } else {
            expr->insert(1 + pos * 2, QString(oper));
        }
        break;
    default:
        expr->insert(1 + pos * 2, QString(oper));
        break;
    }
}


int NumberGenerator::getAnswer(QVector<QString> *expr)
{
    if (expr->isEmpty())
        return -2;
    QVector<QString> *tmp = new QVector<QString>;
    for (int i = 0; i < expr->length(); ++i) {
        tmp->push_back(expr->at(i));
    }

    for (int i = 1; i < tmp->length(); i += 2) {
        if (tmp->at(i) == "*") {
            *(tmp->begin() + i) = QString::number((tmp->begin() + i + 1)->toInt() * (tmp->begin() + i - 1)->toInt());
            tmp->remove(i - 1);
            tmp->remove(i);
            i -= 2;
        } else if (tmp->at(i) == "/") {
            if (tmp->at(i - 1).toInt() % expr->at(i + 1).toInt())
                return -1;
            *(tmp->begin() + i) = QString::number((tmp->begin() + i - 1)->toInt() / (tmp->begin() + i + 1)->toInt());
            tmp->remove(i - 1);
            tmp->remove(i);
            i -= 2;
        }
    }
    for (int i = 1; i < tmp->length(); i += 2) {
        if (tmp->at(i) == "+") {
            *(tmp->begin() + i) = QString::number((tmp->begin() + i + 1)->toInt() + (tmp->begin() + i - 1)->toInt());
            tmp->remove(i - 1);
            tmp->remove(i);
            i -= 2;
        } else if (tmp->at(i) == "-") {
            *(tmp->begin() + i) = QString::number((tmp->begin() + i - 1)->toInt() - (tmp->begin() + i + 1)->toInt());
            tmp->remove(i - 1);
            tmp->remove(i);
            i -= 2;
        }
    }

    return tmp->begin()->toInt();
}

bool NumberGenerator::isOperator(QString str)
{
    for (int i = 0; i < 4; ++i) {
        if (str == (QString(OPERATORS[i])))
            return true;
    }
    return false;
}

QString NumberGenerator::getUserAnswer(QString str)
{
    int userAnswerValue = getAnswer(new QVector<QString>(makeExpression(str)));
    if (userAnswerValue == -1) {
        return QString("Дроби в ходе вычисления");
    } else if (userAnswerValue == -2) {
        return QString("Вы не дали ответ");
    }
    return QString::number(userAnswerValue);
}

QVector<QString> NumberGenerator::makeExpression(QString str)
{
    if (str.isEmpty())
        return QVector<QString>();
    QVector<QString> vec;
    QString s;
    for (QString c : str) {
        if (c[0].isNumber()) {
            s.push_back(c);
        } else {
            vec.push_back(s);
            s.clear();
            vec.push_back(c);
        }

    }
    vec.push_back(s);
    return vec;
}

QString NumberGenerator::getRequiredNumber()
{
    return QString::number(getAnswer(expression));
}
