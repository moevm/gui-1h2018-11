#ifndef CONNECTION_H
#define CONNECTION_H

#include <QObject>
#include <QTcpSocket>
#include <QHostAddress>
#include <QDataStream>
#include <QString>
#include "server/server/client.h"

class Connection : public QObject
{
    Q_OBJECT
public:
    explicit Connection(QObject *parent = nullptr, QString name = "", QString IP = "127.0.0.1", int port = 1234);
    ~Connection();

    QString getError();
    void sendMessage(QString str);
    void getSetUpString();
    void getSystemAnswer(QString userAnswer);

signals:
    void connctionRefuse(QString str);
    void connectionSuccess();
    void gameStart(Server::rounds r, QString setUp);
    void finaScore(QString);
    void setUpAnswer(QString);

public slots:
    void setReady();

private slots:
    void onSokConnected();
    void onSokDisconnected();
    void onSokReadyRead();
    void onSokDisplayError(QAbstractSocket::SocketError socketError);


private:
    QTcpSocket *_sok;
    quint16 _blockSize;
    QString _name;
};

#endif // CONNECTION_H
