#ifndef RANDOMCHAR_H
#define RANDOMCHAR_H
#include <QString>
#include <QVector>

class CharGenerator
{
public:
	CharGenerator();

    enum charType{Consonant,Vovel};
    static const unsigned int LATTERS_COUNT = 9;
    static const unsigned int MAX_VOWEL_COUNT = 5;
    static const unsigned int MAX_CONSONANT_COUNT = 6;

	QString generateNextChar(bool);
	QVector<QString> getPossibleCombination();

	unsigned int getCurrentCharsCount();

	QString getVowelByNumber(unsigned int);
	QString getConsonantByNumber(unsigned int);

	bool isVowelCanBeAdd(QString &ch);
	bool isConsonantCanBeAdd(QString &ch);
    bool isGenerated();

	void reGenerateChars();

private:

	void generateChars();

	unsigned int currentVowelCount, currentConsonantCount;
	QString resVowel;
	QString resConsonant;
};

#endif // RANDOMCHAR_H
