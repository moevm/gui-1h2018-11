#include "anagramsround.h"
#include "ui_anagramround.h"
#include <QVector>
#include <QString>

AnagramsRound::AnagramsRound(SinglePlay *parent) :
    Round(parent),
    ui(new Ui::AnagramRound)
{
    ui->setupUi(this);

    db = parent->getDataBaseHandler();

    QVector<QString>* anagram = db->getAnagram();

    this->anagram = anagram->at(0);

    setUpWords(anagram);

    backspaceLabel *bl = new backspaceLabel(this);

    bl->setMinimumWidth(30);

    ui->preAnswerLayout->layout()->addWidget(bl);
    connect(bl,SIGNAL(backspace()),this,SLOT(backspacePress()));

    connect(ui->answer,SIGNAL(clicked(bool)),
            this,SLOT(showFinalScore()));

    connect(ui->next,SIGNAL(clicked(bool)),
            this,SLOT(nextRound()));

    setState(Round::play);
}

void AnagramsRound::nextRound()
{
    emit endRound(Round::anagrams);
}

void AnagramsRound::setUpWords(QVector<QString>* anagram){
    for(int i= 0,size = anagram->at(1).length();i<size;++i){
        charlabel* cl = new charlabel(this,QString(anagram->at(1)[i]).toUpper(),true);

        connect(cl, SIGNAL(click(QString)),
                this, SLOT(addCharToPreAnswer(QString)));

        ui->word1->layout()->addWidget(cl);

    }
    for(int i= 0,size = anagram->at(3).length();i<size;++i){
        charlabel* cl = new charlabel(this,QString(anagram->at(3)[i]).toUpper(),true);

        connect(cl, SIGNAL(click(QString)),
                this, SLOT(addCharToPreAnswer(QString)));

        ui->word2->layout()->addWidget(cl);

    }
}

void AnagramsRound::addCharToPreAnswer(QString str)
{
    ui->preAnswer->setText(ui->preAnswer->text().append(str));
}

void AnagramsRound::showFinalScore()
{
    ui->finalScore->setText("Ваш ответ: "+ui->preAnswer->text()+
                            "\nЗагаданная анаграмма: "+this->anagram);
    setState(Round::end);
}


void AnagramsRound::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Backspace) {
        backspacePress();
    }
}

void AnagramsRound::backspacePress()
{
    if(ui->preAnswer->text().isEmpty())
        return;
    QString s = QString(ui->preAnswer->
                        text()[ui->preAnswer->text().length() - 1]);
    for (charlabel* a : ui->word1->findChildren<charlabel*>()) {
        if (a->text() == s && !a->getAllowed()) {
            a->setAllowed(true);
            ui->preAnswer->setText(
                        ui->preAnswer->
                        text().left(ui->preAnswer->text().size() - 1));
            return;
        }
    }
    for (charlabel* a : ui->word2->findChildren<charlabel*>()) {
        if (a->text() == s && !a->getAllowed()) {
            a->setAllowed(true);
            ui->preAnswer->setText(
                        ui->preAnswer->
                        text().left(ui->preAnswer->text().size() - 1));
            return;
        }
    }


}


AnagramsRound::~AnagramsRound()
{
    delete ui;
}

void AnagramsRound::setState(Round::roundState st)
{
    switch (st) {
    case Round::preparation:
        break;
    case Round::play:
        ui->wordsWidget->show();
        ui->preAnswerWidget->show();
        ui->finalScoreWidget->hide();

        break;
    case Round::end:
        ui->wordsWidget->hide();
        ui->preAnswerWidget->hide();
        ui->finalScoreWidget->show();
        break;
    default:
        break;
    }
}
