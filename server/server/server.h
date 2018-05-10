#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>
#include <QDataStream>
#include "client.h"
#include "databasehandler.h"
#include "lattersround/chargenerator.h"
#include "numbersround/numbergenerator.h"

class Client;
class Dialog;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
    ~Server();
    bool doStartServer(QHostAddress addr, qint16 port);
    void doSendToAllUserJoin(QString name);
    void doSendToAllUserLeft(QString name);
    void doSendToAllMessage(QString message, QString fromUsername);
    void doSendToAllServerMessage(QString message);
    void doSendServerMessageToUsers(QString message, const QStringList &users);
    void doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername);
    void doSendMessageToUser(QString message, QString toUsername, quint8 messageType);
    QStringList getUsersOnline() const;
    bool isNameValid(QString name) const;
    bool isNameUsed(QString name) const;

    void initCharGenerator();
    CharGenerator &getCharGenerator();

    enum rounds {latters, numbers, anagrams} currentRound;

public slots:
    void onMessageFromGui(QString message, const QStringList &users);
    void onRemoveUser(Client *client);

    void takeResult(QString answer);

    void isGameReadyToStart();

    void setReady();

protected:
    void incomingConnection(qintptr handle);
    void setUpRound(int r);

private:

    QMap<Client *, QString *> clientsAnswers;
    QMap<Client *, bool> clientsReady;

    QList<Client *> clients;

    CharGenerator charGenerator;
    NumberGenerator *num_gen;

    DataBaseHandler *db;
};

#endif // SERVER_H
