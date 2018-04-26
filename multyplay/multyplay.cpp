#include "multyplay.h"
#include "ui_multyplay.h"
#include <QLabel>

MultyPlay::MultyPlay(MainWindow *parent) :
    QWidget(parent),
    currentConnection(nullptr),
    centralWidget(nullptr),
    ui(new Ui::MultyPlay)
{
    ui->setupUi(this);

    showAuthForm();

    connect(ui->exit_2, SIGNAL(clicked(bool)),
            parent, SLOT(startMenu()));
}

MultyPlay::~MultyPlay()
{
    delete ui;
    delete currentConnection;
}

void MultyPlay::setConnection(Connection *newConnection)
{
    if (currentConnection != nullptr) {
        delete currentConnection;
    }
    currentConnection = newConnection;

    connect(currentConnection, SIGNAL(connctionRefuse(QString)),
            this, SLOT(connctionRefuse(QString)));
    connect(currentConnection, SIGNAL(connectionSuccess()),
            this, SLOT(connectionSuccess()));
    connect(currentConnection, SIGNAL(gameStart(Server::rounds, QString)),
            this, SLOT(changeRound(Server::rounds, QString)));
}

Connection *MultyPlay::getConnection()
{
    return currentConnection;
}

void MultyPlay::changeRound(Server::rounds r, QString setUp)
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    switch (r) {
    case Server::latters:
        centralWidget = new LattersRoundMulty(this, setUp);
        connect(currentConnection, SIGNAL(finaScore(QString)),
                qobject_cast<LattersRoundMulty *>(centralWidget), SLOT(getFinalScore(QString)));
        connect(qobject_cast<LattersRoundMulty *>(centralWidget), SIGNAL(endRound(Round::rounds)),
                currentConnection, SLOT(setReady()));
        break;
    case Server::numbers:
        centralWidget = new NumbersRoundMulty(this);
        break;
    case Server::anagrams:
        centralWidget = new AnagramsRoundMulty(this);
        break;
    default:
        break;
    }
    ui->centralLayout->addWidget(centralWidget);
}

void MultyPlay::connctionRefuse(QString str)
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new LostConnection(this, str);
    connect(qobject_cast<LostConnection *>(centralWidget), SIGNAL(tryCreateConnection()),
            this, SLOT(showAuthForm()));
    ui->centralLayout->addWidget(centralWidget);
}

void MultyPlay::connectionSuccess()
{
    if (centralWidget != nullptr) {
        delete centralWidget;
    }
    centralWidget = new QLabel("Ожидается игроков", this);
    ui->centralLayout->addWidget(centralWidget);
}

void MultyPlay::showAuthForm()
{
    if (centralWidget != nullptr) {

        delete centralWidget;
    }
    centralWidget = new AuthForm();
    ui->centralLayout->addWidget(centralWidget);
}
