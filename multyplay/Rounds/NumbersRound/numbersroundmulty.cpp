#include "numbersroundmulty.h"
#include "ui_numbersroundmulty.h"

NumbersRoundMulty::NumbersRoundMulty(MultyPlay *parent, QString setUP) :
    Round(parent),
    ui(new Ui::NumbersRoundMulty)
{
    ui->setupUi(this);


    QStringList settings = setUP.split(" ");

    addNumbers(settings[1]);

    addArithmeticOperators();

    ui->requiredNumber->setText(settings[2]);

    setState(Round::play);

    connect(ui->answerButton, SIGNAL(clicked(bool)), this, SLOT(sendAnswer()));
    connect(ui->nextRound, SIGNAL(clicked(bool)), this, SLOT(nextRound()));

}

NumbersRoundMulty::~NumbersRoundMulty()
{
    delete ui;
}

void NumbersRoundMulty::setState(Round::roundState st)
{
    switch (st) {
    case Round::preparation:
        ui->finalScoreWiget->hide();
        ui->requiredNumber->hide();
        ui->arithmeticWidget->hide();
        ui->numbersWidget->hide();
        ui->preAnswerWiget->hide();
        break;
    case Round::play:
        ui->requiredNumber->show();
        ui->arithmeticWidget->show();
        ui->numbersWidget->show();
        ui->preAnswerWiget->show();
        ui->finalScoreWiget->hide();
        break;
    case Round::end:
        ui->requiredNumber->hide();
        ui->arithmeticWidget->hide();
        ui->numbersWidget->hide();
        ui->preAnswerWiget->hide();
        ui->finalScoreWiget->show();
        break;
    default:
        break;
    }
}

void NumbersRoundMulty::backspacePress()
{
    if (ui->preAnswerExpresion->text().isEmpty())
        return;

    QString s = QString(ui->preAnswerExpresion->
                        text()[ui->preAnswerExpresion->text().length() - 1]);

    if (s[0].isNumber()) {
        for (int i = 2; i <= ui->preAnswerExpresion->text().length() &&
                ui->preAnswerExpresion->
                text()[ui->preAnswerExpresion->text().length() - i].isNumber();
                ++i) {
            s.push_front(ui->preAnswerExpresion->
                         text()[ui->preAnswerExpresion->text().length() - i]);
        }
        for (Charlabel *a : ui->numbersWidget->findChildren<Charlabel *>()) {
            if (a->text() == s && !a->getAllowed()) {
                a->setAllowed(true);
                break;
            }
        }
    }

    ui->preAnswerExpresion->setText(
        ui->preAnswerExpresion->
        text().left(ui->preAnswerExpresion->text().size() - s.length()));
}

void NumbersRoundMulty::sendAnswer()
{
    ui->answerButton->setEnabled(false);
    qobject_cast<MultyPlay *>(parent())->getConnection()->sendMessage(ui->preAnswerExpresion->text());
}

void NumbersRoundMulty::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace) {
        backspacePress();
    }
}

void NumbersRoundMulty::getFinalScore(QString score)
{
    QString answer = "Ваш ответ: " + ui->finalScoreLabel->text() + "\n" + score;
//    if (!userAnswerDiscription.isEmpty()) {
//        score.append("Значение слова: " + userAnswerDiscription + "\n");
//    } else {
//        score.append("К сожалению слово отсутствует в словаре\n");
//    }

//    score.append("Возможный вариант: " + answer + "\n" +
//                 "Значение слова: " + answerDiscription + "\n");

    ui->finalScoreLabel->setText(answer);

    setState(Round::roundState::end);
}

void NumbersRoundMulty::nextRound()
{
    ui->nextRound->setEnabled(false);
    emit endRound(Round::numbers);
}

void NumbersRoundMulty::addNumber(QString q)
{
    if (!(ui->preAnswerExpresion->text().end() - 1)->isNumber())
        ui->preAnswerExpresion->setText(ui->preAnswerExpresion->text() + q);
    else {
        qobject_cast<Charlabel *>(sender())->setAllowed(true);
    }
}

void NumbersRoundMulty::addArithmeticOperator(QString q)
{
    if ((ui->preAnswerExpresion->text().end() - 1)->isNumber())
        ui->preAnswerExpresion->setText(ui->preAnswerExpresion->text() + q);
    qobject_cast<Charlabel *>(sender())->setAllowed(true);
}

void NumbersRoundMulty::addArithmeticOperators()
{
    Charlabel *plus = new Charlabel(this, "+", true);
    Charlabel *minus = new Charlabel(this, "-", true);
    Charlabel *multiply = new Charlabel(this, "*", true);
    Charlabel *divide = new Charlabel(this, "/", true);
    BackspaceLabel *bl = new BackspaceLabel(this);

    ui->arithmeticLayout->addWidget(plus);
    ui->arithmeticLayout->addWidget(minus);
    ui->arithmeticLayout->addWidget(multiply);
    ui->arithmeticLayout->addWidget(divide);
    ui->arithmeticLayout->addWidget(bl);

    connect(plus, SIGNAL(click(QString)), this, SLOT(addArithmeticOperator(QString)));
    connect(minus, SIGNAL(click(QString)), this, SLOT(addArithmeticOperator(QString)));
    connect(multiply, SIGNAL(click(QString)), this, SLOT(addArithmeticOperator(QString)));
    connect(divide, SIGNAL(click(QString)), this, SLOT(addArithmeticOperator(QString)));
    connect(bl, SIGNAL(backspace()), this, SLOT(backspacePress()));
}

void NumbersRoundMulty::addNumbers(QString setUP)
{
    QStringList setUpNumbers = setUP.split(";");
    for (QString s : setUpNumbers) {
        Charlabel *cl = new Charlabel(this, s, true);

        ui->numbersWidget->layout()->addWidget(cl);

        connect(cl, SIGNAL(click(QString)), this, SLOT(addNumber(QString)));
    }
}
