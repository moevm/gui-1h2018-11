#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QThreadPool>
#include <QRegExp>
#include "server.h"
#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QThreadPool>
#include <QRegExp>
#include "server.h"
class Server;

class Client : public QObject
{
    friend class Server;
    Q_OBJECT

public:
    static const QString constNameUnknown;
    static const quint8 comAutchReq = 1;
    static const quint8 comUsersOnline = 2;
    static const quint8 comUserJoin = 3;
    static const quint8 comUserLeft = 4;
    static const quint8 comMessageToAll = 5;
    static const quint8 comUserIsReady = 6;
    static const quint8 comPublicServerMessage = 7;
    static const quint8 comPrivateServerMessage = 8;
    static const quint8 comAutchSuccess = 9;
    static const quint8 comErrNameInvalid = 201;
    static const quint8 comErrNameUsed = 202;
    static const quint8 comGetMessage = 10;
    static const quint8 comGetSetUpString = 35;
    static const quint8 comGetAnswer = 36;

    explicit Client(int desc, Server *serv, QObject *parent = 0);
    ~Client();
    void setName(QString name) {name = name;}
    QString getName() const {return name;}
    bool getAutched() const {return isAutched;}
    void doSendCommand(quint8 comm) const;
    void doSendConnectionSuccesed() const;

signals:
    void addUserToGui(QString name);
    void removeUser(Client *client);
    void readyToStart();
    void takeAnswer(QString answer);
    void userIsReady();

private slots:
    void onConnect();
    void onDisconnect();
    void onReadyRead();
    void onError(QAbstractSocket::SocketError socketError) const;

private:
    QTcpSocket *socket;
    Server *server;
    quint16 blockSize;
    QString name;
    bool isAutched;

};

#endif // CLIENT_H
