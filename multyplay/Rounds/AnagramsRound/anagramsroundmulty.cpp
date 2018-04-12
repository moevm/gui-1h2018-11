#include "anagramsroundmulty.h"
#include "ui_anagramsroundmulty.h"

AnagramsRoundMulty::AnagramsRoundMulty(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AnagramsRoundMulty)
{
    ui->setupUi(this);
}

AnagramsRoundMulty::~AnagramsRoundMulty()
{
    delete ui;
}
