#include "authform.h"
#include "ui_authform.h"

AuthForm::AuthForm(MultyPlay *parent) :
    QWidget(parent),
    ui(new Ui::AuthForm)
{
    ui->setupUi(this);

    ui->port->setMinimum(1);
    ui->port->setMaximum(65535);
    ui->port->setValue(1224);

    /* Создаем строку для регулярного выражения */
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    /* Создаем регулярное выражение с применением строки, как
         * повторяющегося элемента
          */
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    /* Создаем Валидатор регулярного выражения с применением
         * созданного регулярного выражения
         */
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    /* Устанавливаем Валидатор на QLineEdit */
    ui->IP->setValidator(ipValidator);    

    ui->connect->setText("Подключиться");

    connect(ui->connect,SIGNAL(pressed()),
            this,SLOT(connectToServer()));

}

AuthForm::~AuthForm()
{
    delete ui;
}

void AuthForm::connectToServer()
{
    ui->connect->setEnabled(false);
    Connection* newConnection = new Connection(parent(),ui->nameText->text(),ui->IP->text(),ui->port->value());
    qobject_cast<MultyPlay*>(parent())->setConnection(newConnection);
    connect(newConnection,SIGNAL(connctionRefuse(QString)),
            qobject_cast<MultyPlay*>(parent()),SLOT(connctionRefuse(QString)));
}

