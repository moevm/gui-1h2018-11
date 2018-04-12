#include "lostconnection.h"
#include "ui_lostconnection.h"

LostConnection::LostConnection(QWidget *parent,QString str) :
    QWidget(parent),
    ui(new Ui::LostConnection)
{
    ui->setupUi(this);

    ui->label->setText(str);

    connect(ui->tryAgain,SIGNAL(pressed()),this,SLOT(tryConnectionAgain()));
}

LostConnection::~LostConnection()
{
    delete ui;
}

void LostConnection::tryConnectionAgain()
{
    emit tryCreateConnection();
}
