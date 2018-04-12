#include "numbersroundmulty.h"
#include "ui_numbersroundmulty.h"

NumbersRoundMulty::NumbersRoundMulty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumbersRoundMulty)
{
    ui->setupUi(this);
}

NumbersRoundMulty::~NumbersRoundMulty()
{
    delete ui;
}
