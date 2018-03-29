#include "numbersround.h"
#include "ui_numbersround.h"
#include "singleplay/Rounds/LattersRound/charlabel.h"
#include "singleplay/Rounds/LattersRound/backspacelabel.h"

NumbersRound::NumbersRound(SinglePlay *parent) :
    Round(parent),
    ui(new Ui::NumbersRound)
{
    ui->setupUi(this);

    initBigAndLowCounters();

    connect(ui->acceptButton,SIGNAL(clicked(bool)),
            this,SLOT(startNumbersRound()));
    connect(ui->answerButton,SIGNAL(clicked(bool)),
            this,SLOT(showFinalScore()));
    connect(ui->nextRound,SIGNAL(clicked(bool)),
            this,SLOT(nextRound()));


    setState(Round::preparation);
}

void NumbersRound::initBigAndLowCounters()
{
    ui->lowNumbersCount->setValue(6);
    ui->bigNumbersCount->setValue(0);

    ui->bigNumbersCount->setMinimum(0);
    ui->bigNumbersCount->setMaximum(4);

    ui->lowNumbersCount->setMinimum(2);
    ui->lowNumbersCount->setMaximum(6);

    connect(ui->lowNumbersCount,SIGNAL(valueChanged(int)),
            this,SLOT(controlValuesOfNumbers()));
    connect(ui->bigNumbersCount,SIGNAL(valueChanged(int)),
            this,SLOT(controlValuesOfNumbers()));
}

void NumbersRound::controlValuesOfNumbers()
{
    if(sender()->objectName() == "bigNumbersCount"){
        ui->lowNumbersCount->setValue(NUMBERS_COUNT-ui->bigNumbersCount->value());
    }
    else
    {
        ui->bigNumbersCount->setValue(NUMBERS_COUNT-ui->lowNumbersCount->value());
    }
}

void NumbersRound::backspacePress()
{
    if(ui->preAnswerExpresion->text().isEmpty())
        return;

    QString s = QString(ui->preAnswerExpresion->
                        text()[ui->preAnswerExpresion->text().length() - 1]);

    if(s[0].isNumber())
    {
        for(int i = 2;i<=ui->preAnswerExpresion->text().length() &&
            ui->preAnswerExpresion->
            text()[ui->preAnswerExpresion->text().length() - i].isNumber();
            ++i)
        {
            s.push_front(ui->preAnswerExpresion->
                         text()[ui->preAnswerExpresion->text().length() - i]);
        }
        for (charlabel* a : ui->numbersWidget->findChildren<charlabel*>()) {
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

void NumbersRound::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Backspace) {
        backspacePress();
    }
}

void NumbersRound::setState(Round::roundState st)
{
    switch (st) {
    case Round::preparation:
        ui->finalScoreWiget->hide();
        ui->requiredNumber->hide();
        ui->arithmeticWidget->hide();
        ui->numbersWidget->hide();
        ui->preAnswerWiget->hide();
        ui->countNumbersWidget->show();
        break;
    case Round::play:
        ui->requiredNumber->show();
        ui->arithmeticWidget->show();
        ui->numbersWidget->show();
        ui->preAnswerWiget->show();
        ui->countNumbersWidget->hide();
        ui->finalScoreWiget->hide();
        break;
    case Round::end:
        ui->requiredNumber->hide();
        ui->arithmeticWidget->hide();
        ui->numbersWidget->hide();
        ui->preAnswerWiget->hide();
        ui->countNumbersWidget->hide();
        ui->finalScoreWiget->show();
        break;
    default:
        break;
    }
}

void NumbersRound::startNumbersRound(){

    num_gen = new NumberGenerator(ui->lowNumbersCount->text().toInt(),
                                  ui->bigNumbersCount->text().toInt());

    addNumbers();

    addArithmeticOperators();

    ui->requiredNumber->setText(num_gen->getRequiredNumber());

    setState(Round::play);
}
void NumbersRound::addNumbers()
{
    for(QString s : num_gen->getNumbers()){
        charlabel *cl = new charlabel(this,s,true);

        ui->numbersWidget->layout()->addWidget(cl);

        connect(cl,SIGNAL(click(QString)),this,SLOT(addNumber(QString)));
    }
}

void NumbersRound::addNumber(QString q)
{
    if(!(ui->preAnswerExpresion->text().end()-1)->isNumber())
        ui->preAnswerExpresion->setText(ui->preAnswerExpresion->text()+q);
    else
    {
        qobject_cast<charlabel*>(sender())->setAllowed(true);
    }
}

void NumbersRound::addArithmeticOperators(){
    charlabel *plus = new charlabel(this,"+",true);
    charlabel *minus = new charlabel(this,"-",true);
    charlabel *multiply = new charlabel(this,"*",true);
    charlabel *divide = new charlabel(this,"/",true);
    backspaceLabel *bl = new backspaceLabel(this);

    ui->arithmeticLayout->addWidget(plus);
    ui->arithmeticLayout->addWidget(minus);
    ui->arithmeticLayout->addWidget(multiply);
    ui->arithmeticLayout->addWidget(divide);
    ui->arithmeticLayout->addWidget(bl);

    connect(plus,SIGNAL(click(QString)),this,SLOT(addArithmeticOperator(QString)));
    connect(minus,SIGNAL(click(QString)),this,SLOT(addArithmeticOperator(QString)));
    connect(multiply,SIGNAL(click(QString)),this,SLOT(addArithmeticOperator(QString)));
    connect(divide,SIGNAL(click(QString)),this,SLOT(addArithmeticOperator(QString)));
    connect(bl,SIGNAL(backspace()),this,SLOT(backspacePress()));
}

void NumbersRound::addArithmeticOperator(QString q){
    if((ui->preAnswerExpresion->text().end()-1)->isNumber())
        ui->preAnswerExpresion->setText(ui->preAnswerExpresion->text()+q);
    qobject_cast<charlabel*>(sender())->setAllowed(true);
}

void NumbersRound::showFinalScore(){

    QString userAnswer = ui->preAnswerExpresion->text();

    if(!(userAnswer.end()-1)->isNumber())
        userAnswer.chop(1);
    QString userAnswerValue = num_gen->getUserAnswer(userAnswer);
    if(userAnswerValue == "Дроби в ходе вычисления" || userAnswerValue == "Вы не дали ответ"){
        ui->finalScoreLabel->setText(userAnswerValue+ "\nВозможное решение: "+
                                     num_gen->getExpression() + " = "+num_gen->getRequiredNumber());
    }
    else
    {
        ui->finalScoreLabel->setText("Ваш ответ: "+userAnswer+" = "+userAnswerValue+
                                     "\nВозможное решение: "+
                                     num_gen->getExpression() + " = "+num_gen->getRequiredNumber());
    }


    setState(Round::end);
}

void NumbersRound::nextRound()
{
    emit endRound(Round::numbers);
}

NumbersRound::~NumbersRound()
{
    delete ui;
    delete num_gen;
}
