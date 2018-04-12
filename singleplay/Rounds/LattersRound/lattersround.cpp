#include "lattersround.h"
#include "ui_lattersround.h"


LattersRound::LattersRound(SinglePlay *parent):
    Round(parent),
    ui(new Ui::LattersRound)
{
    ui->setupUi(this);

    db = parent->getDataBaseHandler();

    initCharGenerator();

    initSignalsAndSlots();

    setState(Round::roundState::preparation);
}

void LattersRound::initCharGenerator()
{
    for (auto word : charGenerator.getPossibleCombination()) {
        if (db->searchSystemAnswer(word).isEmpty()) {
            charGenerator.reGenerateChars();
            initCharGenerator();
            return;
        }
    }
}

void LattersRound::initSignalsAndSlots()
{
    connect(ui->answer, SIGNAL(clicked(bool)),
            this, SLOT(getFinalScore()));
    connect(ui->skip, SIGNAL(clicked(bool)),
            this, SLOT(nextRound()));
    connect(ui->nextRound, SIGNAL(clicked(bool)),
            this, SLOT(nextRound()));

    connect(ui->vowel, SIGNAL(clicked(bool)),
            this, SLOT(createVowel()));
    connect(ui->consonant, SIGNAL(clicked(bool)),
            this, SLOT(createConsonant()));
}

void LattersRound::setState(Round::roundState st)
{
    switch (st)
    {
    case Round::roundState::preparation:
        ui->controlButtons->hide();
        ui->finalScore->hide();
        ui->answerWidget->hide();
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

void LattersRound::createConsonant()
{    
    addCharLabel( charGenerator.generateNextChar(CharGenerator::Consonant));

    if (charGenerator.isGenerated()) {
        fillCharWidget(CharGenerator::charType::Vovel);
        startLattersRound();
    }
}

void LattersRound::createVowel()
{    
    addCharLabel(charGenerator.generateNextChar(CharGenerator::Vovel));

    if (charGenerator.isGenerated()) {
        fillCharWidget(CharGenerator::charType::Consonant);
        startLattersRound();
    }
}

void LattersRound::addCharLabel(QString str)
{
    Charlabel* label = new Charlabel(this, str);

    connect(label, SIGNAL(click(QString)),
            this, SLOT(addCharToPreAnswer(QString)));

    ui->charWidget->layout()->addWidget(label);
}

void LattersRound::fillCharWidget(CharGenerator::charType ct)
{
    for (unsigned int i = 0,
         count = CharGenerator::LATTERS_COUNT - charGenerator.getCurrentCharsCount();
         i < count; ++i) {
        addCharLabel(charGenerator.generateNextChar(ct));
    }
}

void LattersRound::startLattersRound()
{
    for (Charlabel *a : ui->charWidget->findChildren<Charlabel*>()) {
        a->setActived(true);
    }

    addBackspaceLabel();

    systemAnswer = getSystemAnswer();

    setState(roundState::play);
}

void LattersRound::addBackspaceLabel(){
    BackspaceLabel *bl = new BackspaceLabel(this);

    ui->charWidget->layout()->addWidget(bl);
    connect(bl,SIGNAL(backspace()),this,SLOT(backspacePress()));
}

QString LattersRound::getSystemAnswer()
{
    QString str;
    for (Charlabel *a : ui->charWidget->findChildren<Charlabel*>()) {
        str.append(a->text());
    }
    return db->searchSystemAnswer(str);
}

void LattersRound::addCharToPreAnswer(QString str)
{
    ui->textAnswer->setText(ui->textAnswer->text().append(str));
}


void LattersRound::keyPressEvent(QKeyEvent * event)
{
    if (event->key() == Qt::Key_Backspace) {
        backspacePress();
    }
}

void LattersRound::backspacePress()
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

void LattersRound::getFinalScore()
{
    QString score, userAnswer = ui->textAnswer->text();
    score.append("Ваш ответ: " + userAnswer + "\n");
    if (db->isWordContained(userAnswer)) {
        score.append("Значение слова: " + db->getWordValue(userAnswer) + "\n");
    }
    else {
        score.append("К сожалению слово отсутствует в словаре\n");
    }

    score.append("Возможный вариант: " + systemAnswer + "\n" +
                 "Значение слова: " + db->getWordValue(systemAnswer) + "\n");

    ui->textScore->setText(score);

    setState(Round::roundState::end);
}

void LattersRound::nextRound()
{
    emit endRound(Round::latters);
}

LattersRound::~LattersRound()
{
    delete ui;
}
