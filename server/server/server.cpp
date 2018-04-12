#include "server.h"


Server::Server(QObject *parent) :QTcpServer(parent)
{
    db = new DataBaseHandler();
}

bool Server::doStartServer(QHostAddress addr, qint16 port)
{
    if (!listen(addr, port))
    {
        qDebug() << "Server not started at" << addr << ":" << port;
        return false;
    }
    qDebug() << "Server started at" << addr << ":" << port;
    return true;
}

void Server::doSendToAllUserJoin(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);    
    out << (quint16)0 << Client::comUserJoin << name;    
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));    
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getName() != name && clients.at(i)->getAutched())
            clients.at(i)->socket->write(block);
}

void Server::doSendToAllUserLeft(QString name)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << Client::comUserLeft << name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getName() != name && clients.at(i)->getAutched())
            clients.at(i)->socket->write(block);
}

void Server::doSendToAllMessage(QString message, QString fromUsername)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << Client::comMessageToAll << fromUsername << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getAutched())
            clients.at(i)->socket->write(block);
}

void Server::doSendToAllServerMessage(QString message)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << Client::comPublicServerMessage << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getAutched())
            clients.at(i)->socket->write(block);
}

void Server::doSendServerMessageToUsers(QString message, const QStringList &users)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << Client::comPrivateServerMessage << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    for (int j = 0; j < clients.length(); ++j)
        if (users.contains(clients.at(j)->getName()))
            clients.at(j)->socket->write(block);
}

void Server::doSendMessageToUsers(QString message, const QStringList &users, QString fromUsername)
{
    QByteArray block, blockToSender;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << Client::comMessageToUsers << fromUsername << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QDataStream outToSender(&blockToSender, QIODevice::WriteOnly);
    outToSender << (quint16)0 << Client::comMessageToUsers << users.join(",") << message;
    outToSender.device()->seek(0);
    outToSender << (quint16)(blockToSender.size() - sizeof(quint16));
    for (int j = 0; j < clients.length(); ++j)
        if (users.contains(clients.at(j)->getName()))
            clients.at(j)->socket->write(block);
        else if (clients.at(j)->getName() == fromUsername)
            clients.at(j)->socket->write(blockToSender);
}

void Server::doSendMessageToUser(QString message, QString toUsername,quint8 messageType)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << messageType << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    for (int j = 0; j < clients.length(); ++j){
        if (clients.at(j)->getName() == toUsername)
        {
            clients.at(j)->socket->write(block);
        }
    }
}

QStringList Server::getUsersOnline() const
{
    QStringList l;
    foreach (Client * c, clients)
        if (c->getAutched())
            l << c->getName();
    return l;
}

bool Server::isNameValid(QString name) const
{
    if (name.length() > 20 || name.length() < 5)
        return false;
    QRegExp r("[A-Za-z0-9_]+");
    return r.exactMatch(name);
}

bool Server::isNameUsed(QString name) const
{
    for (int i = 0; i < clients.length(); ++i)
        if (clients.at(i)->getName() == name)
            return true;
    return false;
}

void Server::initCharGenerator()
{
    for (auto word : charGenerator.getPossibleCombination()) {
        if (db->searchSystemAnswer(word).isEmpty()) {
            charGenerator.reGenerateChars();
            initCharGenerator();            
            return;
        }
    }
}

CharGenerator Server::getCharGenerator()
{
    return charGenerator;
}

void Server::incomingConnection(qintptr handle)
{
    Client *client = new Client(handle, this, this);
    connect(client, SIGNAL(removeUser(Client*)), this, SLOT(onRemoveUser(Client*)));
    clients.append(client);
}

void Server::onRemoveUser(Client *client)
{
    clients.removeAt(clients.indexOf(client));
}

void Server::onMessageFromGui(QString message, const QStringList &users)
{
    if (users.isEmpty())
        doSendToAllServerMessage(message);
    else
        doSendServerMessageToUsers(message, users);
}
