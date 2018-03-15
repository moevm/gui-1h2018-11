#include "randomchar.h"
#include <random>
#include <ctime>

static int verVowel[] = {259, 459, 648, 822, 884, 931, 976, 991, 999, 1000};
static int verConsonant[] = {115, 223, 318, 400, 478, 554, 614, 669, 720, 769, 798, 828, 857, 885, 913, 934, 951, 967, 980, 988, 994, 999, 1000};
static QString vowel = "ОEАИУЯЫЮЭЁ";
static QString consonant = "НТСРВЛКМДПГЬЗБЧЙХЖШЦЩФЪ";
static const int vowelCount = 5;
static const int consonantCount = 6;


randomchar::randomchar():v(0),c(0)
{
    int random = 0;
    srand(time(0));
    for(size_t k =0;k<vowelCount;++k){
        random = rand()%1001;
        for(size_t i=0;i<10;++i)
        {
            if(random < verVowel[i]){
                int count = 0;

                for(auto a : resVowel)
                {
                    if(a == vowel[i])
                        count++;
                }
                if(count>3){
                    k--;
                    break;
                }
                resVowel.append(vowel[i]);
                break;
            }
        }
    }
    srand(time(0));
    for(size_t k =0;k<consonantCount;++k){
        random = rand()%1001;
        for(size_t i=0;i<23;++i)
        {
            if(random < verConsonant[i]){
                int count = 0;

                for(auto a : verConsonant)
                {
                    if(a == consonant[i])
                        count++;
                }
                if(count>3){
                    k--;
                    break;
                }
                resConsonant.append(consonant[i]);
                break;
            }
        }
    }
}

QString randomchar::getNextVowel()
{    
    if(v == vowelCount)
        return "NONE";
    return QString(resVowel[v++]);
}

QString randomchar::getNextConsonant()
{    
    if(c == consonantCount)
        return "NONE";
    return QString(resConsonant[c++]);
}
