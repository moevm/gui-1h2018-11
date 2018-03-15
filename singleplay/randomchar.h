#ifndef RANDOMCHAR_H
#define RANDOMCHAR_H
#include <QString>

class randomchar
{
public:
    randomchar();
    QString getNextVowel();
    QString getNextConsonant();
private:
    int v,c;
    QString resVowel;
    QString resConsonant;
};

#endif // RANDOMCHAR_H
