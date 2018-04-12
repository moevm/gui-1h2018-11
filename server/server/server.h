#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QDebug>
#include <QDataStream>
#include "client.h"
#include "databasehandler.h"
#include "lattersround/chargenerator.h"

class Client;
class Dialog;

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);
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
    CharGenerator getCharGenerator();


public slots:
    void onMessageFromGui(QString message, const QStringList &users);
    void onRemoveUser(Client *client);

protected:
    void incomingConnection(qintptr handle);

private:
    QList<Client *> clients;

    CharGenerator charGenerator;

    DataBaseHandler *db;
};

#endif // SERVER_H
