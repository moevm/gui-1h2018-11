#include "connection.h"

Connection::Connection(QObject *parent, QString name, QString IP, int port) : QObject(parent)
{
    _name = name;
    _sok = new QTcpSocket(this);
    connect(_sok, SIGNAL(readyRead()), this, SLOT(onSokReadyRead()));
    connect(_sok, SIGNAL(connected()), this, SLOT(onSokConnected()));
    connect(_sok, SIGNAL(disconnected()), this, SLOT(onSokDisconnected()));
    connect(_sok, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSokDisplayError(QAbstractSocket::SocketError)));
    _sok->connectToHost(IP, port);
}

Connection::~Connection()
{

}


void Connection::onSokDisplayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        emit connctionRefuse("The host has close");
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found";
        emit connctionRefuse("The host was not found");
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer.";
        emit connctionRefuse("The connection was refused by the peer.");
        break;
    default:
        qDebug() << "The following error occurred: " << _sok->errorString();
        emit connctionRefuse("The following error occurred: " + _sok->errorString());
    }
}

void Connection::onSokReadyRead()
{
    QDataStream in(_sok);
    //если считываем новый блок первые 2 байта это его размер
    if (_blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (_sok->bytesAvailable() < (int)sizeof(quint16))
            return;
        //считываем размер (2 байта)
        in >> _blockSize;
        qDebug() << "_blockSize now " << _blockSize;
    }
    //ждем пока блок прийдет полностью
    if (_sok->bytesAvailable() < _blockSize)
        return;
    else
        //можно принимать новый блок
        _blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;

    switch (command) {
    case Client::comUsersOnline: {
        qDebug() << "Received user list " << _name;
        QString users;
        in >> users;
        emit connectionSuccess();
        if (users == "") {
            return;
        }
        QStringList l =  users.split(",");
        for (auto u : l) {
            qDebug() << u;
        }

    }
    break;
    case Client::comPublicServerMessage: {
        QString message;
        in >> message;

        QStringList words = message.split(" ");

        if (words.first() == "Latters") {
            emit gameStart(Server::latters, message);
        } else if (words.first()  == "Numbers") {
            emit gameStart(Server::numbers, message);
        } else if (words.first() == "Anagrams") {
            emit gameStart(Server::anagrams, message);
        } else if (words.first() == "Result") {
            emit finaScore(message);
        }

        qDebug() << "[PublicServerMessage]: " << message;
    }
    break;
    case Client::comMessageToAll: {
        QString user;
        in >> user;
        QString message;
        in >> message;
        qDebug() << "[" + user + "]: " << message;
    }
    break;
    case Client::comUserIsReady: {
        QString user;
        in >> user;
        QString message;
        in >> message;
        qDebug() << "[" + user + "](private): " << message;
    }
    break;
    case Client::comPrivateServerMessage: {
        QString message;
        in >> message;
        qDebug() << "[PrivateServerMessage]: " << message;
    }
    break;
    case Client::comUserJoin: {
        QString name;
        in >> name;
        qDebug() << name << " joined";
    }
    break;
    case Client::comUserLeft: {
        emit connctionRefuse("Another player disconected");
        qDebug() << "User left";
    }
    break;
    case Client::comErrNameInvalid: {
        qDebug() << "This name is invalid.";
        emit connctionRefuse("This name is invalid.");
        _sok->disconnectFromHost();
    }
    break;
    case Client::comErrNameUsed: {
        qDebug() << "This name is already used.";
        emit connctionRefuse("This name is already used.");
        _sok->disconnectFromHost();
    }
    break;
    case Client::comGetAnswer: {
        QString message;
        in >> message;
        emit setUpAnswer(message);
        qDebug() << "Set up answer " << message;
    }
    break;
    }
}

void Connection::onSokConnected()
{
    _blockSize = 0;
    //AddToLog("Connected to"+_sok->peerAddress().toString()+":"+QString::number(_sok->peerPort()),Qt::green);

    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << (quint8)1;
    out << _name;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Connection::onSokDisconnected()
{

}


void Connection::sendMessage(QString str)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;

    out << (quint8)Client::comGetMessage;

    out << (_name + " " + str);
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Connection::getSetUpString()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;

    out << (quint8)Client::comGetSetUpString;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Connection::getSystemAnswer(QString userAnswer)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;

    out << (quint8)Client::comGetAnswer;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}

void Connection::setReady()
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;

    out << (quint8)Client::comUserIsReady;

    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    _sok->write(block);
}
