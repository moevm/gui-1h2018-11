#include "lattersroundmulty.h"
#include "ui_lattersroundmulty.h"

LattersRoundMulty::LattersRoundMulty(MultyPlay *parent) :
    Round(parent),
    ui(new Ui::LattersRoundMulty)
{
    ui->setupUi(this);

    parent->getConnection()->getSetUpString();

    initSignalsAndSlots();

    setState(Round::roundState::play);
}

void LattersRoundMulty::initSignalsAndSlots()
{
    connect(ui->answer, SIGNAL(clicked(bool)),
            this, SLOT(sendAnswer()));
    connect(ui->skip, SIGNAL(clicked(bool)),
            this, SLOT(sendAnswer()));
    connect(ui->nextRound, SIGNAL(clicked(bool)),
            this, SLOT(nextRound()));
}

void LattersRoundMulty::setState(Round::roundState st)
{
    switch (st)
    {
    case Round::roundState::preparation:
        break;
    case Round::roundState::play:
        ui->charChoiser_2->hide();

        ui->answerWidget->show();
        ui->controlButtons->show();
        break;
    case Round::roundState::end:
        ui->finalScore->show();

        ui->answerWidget->hide();
        ui->charChoiser_2->hide();
        ui->charWidget->hide();
        ui->controlButtons->hide();
        break;
    default:
        break;
    }
}

void LattersRoundMulty::addCharLabel(QString str)
{
    Charlabel* label = new Charlabel(this, str);

    connect(label, SIGNAL(click(QString)),
            this, SLOT(addCharToPreAnswer(QString)));

    ui->charWidget->layout()->addWidget(label);
}

void LattersRoundMulty::fillCharWidget(QString chars)
{
    for(auto c : chars){
        addCharLabel(QString(c));
    }
    startLattersRound();
}

void LattersRoundMulty::startLattersRound()
{
    for (Charlabel *a : ui->charWidget->findChildren<Charlabel*>()) {
        a->setActived(true);
    }

    addBackspaceLabel();    

    setState(roundState::play);
}

void LattersRoundMulty::addBackspaceLabel(){
    BackspaceLabel *bl = new BackspaceLabel(this);

    ui->charWidget->layout()->addWidget(bl);
    connect(bl,SIGNAL(backspace()),this,SLOT(backspacePress()));
}


void LattersRoundMulty::addCharToPreAnswer(QString str)
{
    ui->textAnswer->setText(ui->textAnswer->text().append(str));
}


void LattersRoundMulty::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Backspace) {
        backspacePress();
    }
}

void LattersRoundMulty::backspacePress()
{
    if(ui->textAnswer->text().isEmpty())
        return;
    QString s = QString(ui->textAnswer->
                        text()[ui->textAnswer->text().length() - 1]);
    for (Charlabel* a : ui->charWidget->findChildren<Charlabel*>()) {
        if (a->text() == s && !a->getAllowed()) {
            a->setAllowed(true);
            break;
        }
    }

    ui->textAnswer->setText(
                ui->textAnswer->
                text().left(ui->textAnswer->text().size() - 1));
}

void LattersRoundMulty::getFinalScore(QString answer,QString answerDiscription,QString userAnswerDiscription)
{
    QString score = "Ваш ответ: " + ui->textAnswer->text() + "\n";
    if (!userAnswerDiscription.isEmpty()) {
        score.append("Значение слова: " + userAnswerDiscription + "\n");
    }
    else {
        score.append("К сожалению слово отсутствует в словаре\n");
    }

    score.append("Возможный вариант: " + answer + "\n" +
                 "Значение слова: " + answerDiscription + "\n");

    ui->textScore->setText(score);

    setState(Round::roundState::end);
}

void LattersRoundMulty::sendAnswer()
{
    qobject_cast<MultyPlay*>(parent())->getConnection()->getSystemAnswer(ui->textAnswer->text());
}

void LattersRoundMulty::nextRound()
{
    emit endRound(Round::latters);
}

LattersRoundMulty::~LattersRoundMulty()
{
    delete ui;
}
