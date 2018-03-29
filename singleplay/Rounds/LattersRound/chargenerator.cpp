#include "chargenerator.h"
#include <random>
#include <ctime>

static unsigned int verVowel[] = { 259, 459, 648, 822, 884, 931, 976, 991, 999, 1000 };
static unsigned int verConsonant[] = { 115, 223, 318, 400, 478, 554, 614, 669, 720, 769, 798, 828, 857, 885, 913, 934, 951, 967, 980, 988, 994, 999, 1000 };
static QString vowel = "ОEАИУЯЫЮЭЁ";
static QString consonant = "НТСРВЛКМДПГЬЗБЧЙХЖШЦЩФЪ";



CharGenerator::CharGenerator() :currentVowelCount(0), currentConsonantCount(0)
{
	generateChars();
}

QString CharGenerator::generateNextChar(bool vowel)
{
	if (vowel) {
		return QString(resVowel[currentVowelCount++]);
	}
	else {
		return QString(resConsonant[currentConsonantCount++]);
	}
	return QString();
}

QVector<QString> CharGenerator::getPossibleCombination()
{
	QVector<QString> possibleCombinatin(3);

	for (unsigned int i = 0; i < 3; ++i) {        
        possibleCombinatin[i] = (resVowel.left(4+i)+ resConsonant.left(7-i)).left(9);
	}

	return possibleCombinatin;
}

unsigned int CharGenerator::getCurrentCharsCount()
{
	return currentConsonantCount + currentVowelCount;
}

QString CharGenerator::getVowelByNumber(unsigned int random)
{
	for (unsigned int i = 0; i < 10; ++i)
	{
		if (random < verVowel[i]) {
			return QString(vowel[i]);
		}
	}
}

QString CharGenerator::getConsonantByNumber(unsigned int random)
{
	for (unsigned int i = 0; i < 23; ++i)
	{
		if (random < verConsonant[i]) {
			return QString(consonant[i]);
		}
	}
}

bool CharGenerator::isVowelCanBeAdd(QString &ch)
{
	int count = 0;
	for (auto a : resVowel)
	{
		if (a == ch[0])
			count++;
	}
	if (count > 1) {
		return false;
	}
	return true;
}

bool CharGenerator::isConsonantCanBeAdd(QString &ch)
{
	int count = 0;
	for (auto a : resConsonant)
	{
		if (a == ch[0])
			count++;
	}
	if (count > 1) {
		return false;
	}
    return true;
}

bool CharGenerator::isGenerated()
{
    return (currentVowelCount == MAX_VOWEL_COUNT) ||
           (currentConsonantCount == MAX_CONSONANT_COUNT) ||
            (currentConsonantCount+currentVowelCount == LATTERS_COUNT);
}

//TODO add bufering
void CharGenerator::reGenerateChars()
{
	resVowel.clear();
	resConsonant.clear();
	currentConsonantCount = 0;
	currentVowelCount = 0;
	generateChars();
}

void CharGenerator::generateChars()
{	
	srand(time(0));
    for (unsigned int k = 0; k < MAX_VOWEL_COUNT + MAX_CONSONANT_COUNT; ++k) {
		unsigned int random = rand() % 1001;
        if (k > MAX_VOWEL_COUNT) {
			QString ch = getVowelByNumber(random);
			while (!isVowelCanBeAdd(ch)) {
				random = rand() % 1001;
				ch = getVowelByNumber(random);
			}
			resVowel.append(ch);
		}
		else
		{
			QString ch = getConsonantByNumber(random);
			while (!isConsonantCanBeAdd(ch)) {
				random = rand() % 1001;
				ch = getConsonantByNumber(random);
			}
			resConsonant.append(ch);
		}
	}
}


