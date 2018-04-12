#include "client.h"

const QString Client::constNameUnknown = QString(".Unknown");

Client::Client(int desc, Server *serv, QObject *parent) :QObject(parent)
{
    //храниим указатель на объект-сервер
    server = serv;
    //клиент не прошел авторизацию
    isAutched = false;
    name = constNameUnknown;
    //размер принимаемого блока 0
    blockSize = 0;
    //создаем сокет
    socket = new QTcpSocket(this);
    //устанавливаем дескриптор из incomingConnection()
    socket->setSocketDescriptor(desc);
    //подключаем сигналы
    connect(socket, SIGNAL(connected()), this, SLOT(onConnect()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onError(QAbstractSocket::SocketError)));

    qDebug() << "Client connected" << desc;
}

Client::~Client()
{

}

void Client::onConnect()
{
    //never calls, socket already connected to the tcpserver
    //we just binding to this socket here: _sok->setSocketDescriptor(desc);
}

void Client::onDisconnect()
{
    qDebug() << "Client disconnected";
    //если авторизован
    if (isAutched)
    {
        //убирием из интерфейса
        emit removeUserFromGui(name);
        //сообщаем всем, что клиент вышел
        server->doSendToAllUserLeft(name);
        //убираем из списка
        emit removeUser(this);
    }
    deleteLater();
}

void Client::onError(QAbstractSocket::SocketError socketError) const
{
    //w нужна для обсвобождения памяти от QMessageBox (посредством *parent = &w)
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug() <<  "The connection was refused by the peer.";
        break;
    default:
        qDebug() << "The following error occurred: " << socket->errorString();
    }
    //тут вызовутся деструктор w и соответственно QMessageBox (по правилам с++)
}


void Client::onReadyRead()
{
    QDataStream in(socket);
    //если считываем новый блок первые 2 байта это его размер
    if (blockSize == 0) {
        //если пришло меньше 2 байт ждем пока будет 2 байта
        if (socket->bytesAvailable() < (int)sizeof(quint16))
            return;
        //считываем размер (2 байта)
        in >> blockSize;
        qDebug() << "_blockSize now " << blockSize;
    }
    //ждем пока блок прийдет полностью
    if (socket->bytesAvailable() < blockSize)
        return;
    else
        //можно принимать новый блок
        blockSize = 0;
    //3 байт - команда серверу
    quint8 command;
    in >> command;
    qDebug() << "Received command " << command;
    //для неавторизованный пользователей принимается только команда "запрос на авторизацию"
    if (!isAutched && command != comAutchReq)
        return;

    switch(command)
    {
    //запрос на авторизацию
    case comAutchReq:
    {
        //считываем имя
        QString name;
        in >> name;
        //проверяем его
        if (!server->isNameValid(name))
        {
            //отправляем ошибку
            doSendCommand(comErrNameInvalid);
            return;
        }
        //проверяем не используется ли имя
        if (server->isNameUsed(name))
        {
            //отправляем ошибку
            doSendCommand(comErrNameUsed);
            return;
        }
        //авторизация пройдена
        this->name = name;
        isAutched = true;
        //отправляем новому клиенту список активных пользователей
        doSendUsersOnline();        
        //сообщаем всем про нового ползователя
        server->doSendToAllUserJoin(name);
    }
        break;
        //от текущего пользователя пришло сообщение для всех
    case comMessageToAll:
    {
        QString message;
        in >> message;
        //отправляем его всем
        server->doSendToAllMessage(message, name);
        //обновляем лог событий
        emit messageToGui(message, name, QStringList());
    }
        break;
        //от текущего пользователя пришло сообщение для некоторых пользователей
    case comMessageToUsers:
    {
        QString users_in;
        in >> users_in;
        QString message;
        in >> message;
        //разбиваем строку на имена
        QStringList users = users_in.split(",");
        //отправляем нужным
        server->doSendMessageToUsers(message, users, name);
        //обновляем интерфейс
        emit messageToGui(message, name, users);
    }
        break;
    case comGetMessage:
    {
        QString message;
        in >> message;
        qDebug() << message;
    }
        break;
    case comGetSetUpString:
    {
//        QString message;
//        _serv->initCharGenerator();

//        int vowelsCount = CharGenerator::MIN_VOWEL_COUNT
//                + rand() % (CharGenerator::MAX_VOWEL_COUNT-CharGenerator::MIN_VOWEL_COUNT);



//        for(int i = 0; i < vowelsCount ;++i)
//        {
//            message.append(_serv->getCharGenerator().generateNextChar(CharGenerator::Vovel)[0]);
//        }
//        for(int i = 0; i < CharGenerator::LATTERS_COUNT - vowelsCount; ++i)
//        {
//            message.append(_serv->getCharGenerator().generateNextChar(CharGenerator::Consonant)[0]);
//        }


//        _serv->doSendToAllServerMessage(message);
//        qDebug() << message;
    }
        break;

    }

    //for (long long i = 0; i < 4000000000; ++i){}
}



void Client::doSendCommand(quint8 comm) const
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << comm;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    socket->write(block);
    qDebug() << "Send to" << name << "command:" << comm;
}

void Client::doSendUsersOnline() const
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0;
    out << comUsersOnline;
    QStringList l = server->getUsersOnline();
    QString s;
    for (int i = 0; i < l.length(); ++i)
        if (l.at(i) != name)
            s += l.at(i)+(QString)",";
    s.remove(s.length()-1, 1);
    out << s;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));
    socket->write(block);
    qDebug() << "Send user list to" << name << ":" << s;
}





