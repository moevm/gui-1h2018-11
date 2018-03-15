#include "numberlogic.h"
#include <QTextStream>
#include <ctime>


numberlogic::numberlogic(int small, int big)
{
    this->set = new QVector<int>;
    srand(time(0));

    QVector<int> *s = new QVector<int>;
    for (int i = 0; i < small;) {
        int num = 1 + rand() % 20;
        int k = 0;
        bool repeat = false;
        while ((k < i) and (!repeat)) {
            if (s->at(k) == num) {
                repeat = true;
            }
            k++;
        }
        if (!repeat) {
            i++;
            s->push_back(num);
        }
    }

    for  (int i = 0; i < small; i++) {
        if (s->at(i) <=10) {
            set->push_back(s->at(i));
        } else {
            set->push_back((s->at(i)) - 10);
        }
    }

    QVector<int> *b = new QVector<int>;
    for (int i = 0; i < big;) {
        int num = 1 + rand() % 4;
        int k = 0;
        bool repeat = false;
        while ((k < i) and (!repeat)) {
            if (b->at(k) == num) {
                repeat = true;
            }
            k++;
        }
        if (!repeat) {
            i++;
            b->push_back(num);
        }
    }

    for  (int i = 0; i < big; i++) {
        set->push_back(25 * (b->at(i)));
    }

//    QTextStream cout(stdout);
//    for (int  i = 0; i < 9; i++) {
//        cout << set->at(i) << endl;
//    }

    s->~QVector();
    b->~QVector();

    generation();
//    for (int i = 0; i < mathFormula->size(); i++) {
//            cout << mathFormula->at(i);
//    }
//    cout << "=" << res;
//    cout << endl;
}

QString numberlogic::userInput(QVector<QString> formula)
{
    return results(formula);
}

void numberlogic::generation()
{
    //QTextStream cout(stdout);
    srand(time(0));
    int n = 6 + rand() % 4; //количество используемых чисел
    //cout << "n=" << n << endl;

    QVector<int> *num = new QVector<int>();
    for (int i = 0; i < n;) {
        int number = rand() % 9;
        int k = 0;
        bool repeat = false;
        while ((k < i) and (!repeat)) {
            if (num->at(k) == number) {
                repeat = true;
            }
            k++;
        }
        if (!repeat) {
            i++;
            num->push_back(number);
        }
    }

    QVector<QString> *sign = new QVector<QString>();
    sign->append("+");
    sign->append("-");
    sign->append("-");
    sign->append("+");
    sign->append("*");
    sign->append("-");
    sign->append("/");
    sign->append("*");
    sign->append("+");
    sign->append("+");
    QVector<QString> *formula = new QVector<QString>();

    formula->append(QString::number(set->at(num->at(0))));
    for (int i = 1; i < n; i++) {
        formula->append(sign->at(rand()%10));
        formula->append(QString::number(set->at(num->at(i))));
    }

    QString res1 = results(*formula);

    int k = 2 * (rand()%(n-1)); // (
    int l = 2 * (rand()%(n-1)); // )
    if (k > l) {
        int t = k;
        k = l;
        l = t;
    }
    formula->insert(formula->begin() + l + 1, ")");
    formula->insert(formula->begin() + k, "(");

//    for (int i = 0; i < formula->size(); i++) {
//        cout << formula->at(i);
//    }
//    cout << endl;

    QString res = results(*formula);
    if (res == "Error") {
        generation();
    } else {
        if (res.toInt() < 100 or res.toInt() > 999 ) {
            generation();
        } else {
            if (res1 != res) {
                this->mathFormula = formula;
                this->res = res.toInt();
            } else {
                formula->erase(formula->begin() + k);
                formula->erase(formula->begin() + l + 1);
                this->mathFormula = formula;
                this->res = res.toInt();
            }
        }
    }

    num->~QVector();
    sign->~QVector();
}

QVector<int> *numberlogic::getSet() const
{
    return set;
}


QString numberlogic::results(QVector<QString> formula)
{
    int begin = -1;
    int end = 0;
    for (int i = 0; i < formula.size() - 1; i++) {
        if (formula.at(i) == "("){
            begin = i;
        }
    }

    if (begin > -1) {
        // в выражении есть скобки
        end = 0;
        for (int i = formula.size() - 1; i > begin; i--) {
            if (formula.at(i) == ")" and end==0){
                end = i;
            }
        }
        QString res = results(formula.mid(begin + 1, end - begin - 1));
        formula.erase(formula.begin() + begin, formula.begin() + end + 1);
        formula.insert(formula.begin() + begin, res);
    }

    int count = 0;
    for (int i = 0; i < formula.size(); i++) {
        if ((formula.at(i) == "*") or (formula.at(i) == "/")) {
            count ++;
        }
    }
    bool integer = true;
    while (integer and count > 0) {
        count--;
        int symbol = -1;
        int k = 0;
        while (symbol == -1) {
            if ((formula.at(k) == "*") or (formula.at(k) == "/")) {
                symbol = k;
            }
            k++;
        }

        int res = formula.at(symbol - 1).toInt();

        if (formula.at(symbol) == "*"){
            res *= formula.at(symbol + 1).toInt();
        } else {
            int d = formula.at(symbol + 1).toInt();
            if (res % d != 0) {
                integer = false;
            } else {
                res = res / d;
            }
        }
        if (integer){
            formula.erase(formula.begin() + symbol - 1, formula.begin() + symbol + 2);
            formula.insert(formula.begin() + symbol - 1, QString::number(res));
        }
    }

    if (integer) {
        int res = formula.at(0).toInt();
        for (int i = 1; i < formula.size(); i = i+2) {
            if (formula.at(i) == "+") {
                res += formula.at(i + 1).toInt();
            } else {
                res -= formula.at(i + 1).toInt();
            }
        }
        return QString::number(res);

    } else {
        return "Error";
    }
}

