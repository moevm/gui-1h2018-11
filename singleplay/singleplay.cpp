#include "singleplay.h"
#include "ui_singleplay.h"
#include <QtSql>
#include <map>
#include <singleplay/Rounds/LattersRound/lattersround.h>
#include <singleplay/Rounds/AnagramsRound/anagramsround.h>
#include <singleplay/Rounds/NumbersRound/numbersround.h>

SinglePlay::SinglePlay(MainWindow *parent) :
    QWidget(parent),
    ui(new Ui::singleplay)
{
    ui->setupUi(this);

    db = new DataBaseHandler();

    setRound(Round::latters);

    connect(ui->exit_2,SIGNAL(clicked(bool)),
            parent,SLOT(startMenu()));
}

SinglePlay::~SinglePlay()
{
    delete ui;
    delete db;
}


DataBaseHandler * SinglePlay::getDataBaseHandler()
{
    return db;
}

void SinglePlay::changeRound(Round::rounds r)
{
    delete currentRound;
    switch (r)
    {
    case Round::latters:
        setRound(Round::numbers);
        break;
    case Round::numbers:
        setRound(Round::anagrams);
        break;
    case Round::anagrams:
        setRound(Round::latters);
        break;
    default:
        break;
    }
}

void SinglePlay::setRound(Round::rounds r)
{
    switch (r)
    {
    case Round::latters:
        currentRound = new LattersRound(this);
        break;
    case Round::numbers:
        currentRound = new NumbersRound(this);
        break;
    case Round::anagrams:
        currentRound = new AnagramsRound(this);
        break;
    default:
        break;
    }
    ui->round->addWidget(currentRound);
    connect(currentRound,SIGNAL(endRound(Round::rounds)),
            this,SLOT(changeRound(Round::rounds)));
}


