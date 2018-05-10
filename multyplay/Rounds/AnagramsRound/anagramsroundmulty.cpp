#include "anagramsroundmulty.h"
#include "ui_anagramsroundmulty.h"


AnagramsRoundMulty::AnagramsRoundMulty(MultyPlay *parent, QString setUP) :
    Round(parent),
    ui(new Ui::AnagramsRoundMulty)
{
    ui->setupUi(this);

    QVector<QString> *anagramWords  = new QVector<QString>();

    anagramWords->append(setUP.split(" ")[1]);
    anagramWords->append(setUP.split(" ")[2]);

    anagram = setUP.split(" ")[3];

    setUpWords(anagramWords);

    BackspaceLabel *bl = new BackspaceLabel(this);

    bl->setMinimumWidth(30);

    ui->preAnswerLayout->layout()->addWidget(bl);
    connect(bl, SIGNAL(backspace()), this, SLOT(backspacePress()));

    connect(ui->answer, SIGNAL(clicked(bool)),
            this, SLOT(sendAnswer()));

    connect(ui->next, SIGNAL(clicked(bool)),
            this, SLOT(nextRound()));

    setState(Round::play);
}

AnagramsRoundMulty::~AnagramsRoundMulty()
{
    delete ui;
}



void AnagramsRoundMulty::setState(Round::roundState st)
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

void AnagramsRoundMulty::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace) {
        backspacePress();
    }
}

void AnagramsRoundMulty::addCharToPreAnswer(QString str)
{
    ui->preAnswer->setText(ui->preAnswer->text().append(str));
}

void AnagramsRoundMulty::sendAnswer()
{
    ui->answer->setEnabled(false);
    qobject_cast<MultyPlay *>(parent())->getConnection()->sendMessage(ui->preAnswer->text());
}

void AnagramsRoundMulty::getFinalScore(QString score)
{
    QString answer = "Ваш ответ: " + ui->finalScore->text() + "\n" + score;
//    if (!userAnswerDiscription.isEmpty()) {
//        score.append("Значение слова: " + userAnswerDiscription + "\n");
//    } else {
//        score.append("К сожалению слово отсутствует в словаре\n");
//    }

//    score.append("Возможный вариант: " + answer + "\n" +
//                 "Значение слова: " + answerDiscription + "\n");

    ui->finalScore->setText(answer);

    setState(Round::roundState::end);
}

void AnagramsRoundMulty::nextRound()
{
    ui->next->setEnabled(false);
    emit endRound(Round::anagrams);
}

void AnagramsRoundMulty::backspacePress()
{
    if (ui->preAnswer->text().isEmpty())
        return;
    QString s = QString(ui->preAnswer->
                        text()[ui->preAnswer->text().length() - 1]);
    for (Charlabel *a : ui->word1->findChildren<Charlabel *>()) {
        if (a->text() == s && !a->getAllowed()) {
            a->setAllowed(true);
            ui->preAnswer->setText(
                ui->preAnswer->
                text().left(ui->preAnswer->text().size() - 1));
            return;
        }
    }
    for (Charlabel *a : ui->word2->findChildren<Charlabel *>()) {
        if (a->text() == s && !a->getAllowed()) {
            a->setAllowed(true);
            ui->preAnswer->setText(
                ui->preAnswer->
                text().left(ui->preAnswer->text().size() - 1));
            return;
        }
    }

}

void AnagramsRoundMulty::setUpWords(QVector<QString> *anagram)
{
    for (int i = 0, size = anagram->at(0).length(); i < size; ++i) {
        Charlabel *cl = new Charlabel(this, QString(anagram->at(0)[i]).toUpper(), true);

        connect(cl, SIGNAL(click(QString)),
                this, SLOT(addCharToPreAnswer(QString)));

        ui->word1->layout()->addWidget(cl);

    }
    for (int i = 0, size = anagram->at(1).length(); i < size; ++i) {
        Charlabel *cl = new Charlabel(this, QString(anagram->at(1)[i]).toUpper(), true);

        connect(cl, SIGNAL(click(QString)),
                this, SLOT(addCharToPreAnswer(QString)));

        ui->word2->layout()->addWidget(cl);

    }
}
