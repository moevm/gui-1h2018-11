#include "server.h"


Server::Server(QObject *parent) : QTcpServer(parent)
{
    db = new DataBaseHandler();
}

Server::~Server()
{
    for (auto client : clientsAnswers.keys()) {
        delete clientsAnswers[client];
    }
}

bool Server::doStartServer(QHostAddress addr, qint16 port)
{
    if (!listen(addr, port)) {
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
    out << (quint16)0 << Client::comUserIsReady << fromUsername << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    QDataStream outToSender(&blockToSender, QIODevice::WriteOnly);
    outToSender << (quint16)0 << Client::comUserIsReady << users.join(",") << message;
    outToSender.device()->seek(0);
    outToSender << (quint16)(blockToSender.size() - sizeof(quint16));
    for (int j = 0; j < clients.length(); ++j)
        if (users.contains(clients.at(j)->getName()))
            clients.at(j)->socket->write(block);
        else if (clients.at(j)->getName() == fromUsername)
            clients.at(j)->socket->write(blockToSender);
}

void Server::doSendMessageToUser(QString message, QString toUsername, quint8 messageType)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out << (quint16)0 << messageType << message;
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    for (int j = 0; j < clients.length(); ++j) {
        if (clients.at(j)->getName() == toUsername) {
            clients.at(j)->socket->write(block);
        }
    }
}

QStringList Server::getUsersOnline() const
{
    QStringList l;
    foreach (Client *c, clients)
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
    if (charGenerator.getCurrentCharsCount() != 0) {
        charGenerator.reGenerateChars();
    }

    for (auto word : charGenerator.getPossibleCombination()) {
        if (db->searchSystemAnswer(word).isEmpty()) {
            charGenerator.reGenerateChars();
            initCharGenerator();
            return;
        }
    }
}

CharGenerator &Server::getCharGenerator()
{
    return charGenerator;
}

void Server::incomingConnection(qintptr handle)
{
    Client *client = new Client(handle, this, this);
    connect(client, SIGNAL(removeUser(Client *)), this, SLOT(onRemoveUser(Client *)));
    connect(client, SIGNAL(readyToStart()),
            this, SLOT(isGameReadyToStart()));
    connect(client, SIGNAL(takeAnswer(QString)),
            this, SLOT(takeResult(QString)));
    connect(client, SIGNAL(userIsReady()),
            this, SLOT(setReady()));
    clients.append(client);
    clientsAnswers.insert(client, nullptr);
    clientsReady.insert(client, true);
}

void Server::setUpRound(int r)
{
    QString message;

    switch (r) {
    case latters: {

        currentRound = latters;

        message.append("Latters ");

        initCharGenerator();

        const int vowelsCount = CharGenerator::MIN_VOWEL_COUNT
                                + rand() % (CharGenerator::MAX_VOWEL_COUNT - CharGenerator::MIN_VOWEL_COUNT);


        for (int i = 0; i < vowelsCount ; ++i) {
            message.append(charGenerator.generateNextChar(CharGenerator::Vovel)[0]);
        }
        for (int i = 0; i < CharGenerator::LATTERS_COUNT - vowelsCount; ++i) {
            message.append(charGenerator.generateNextChar(CharGenerator::Consonant)[0]);
        }

        message += " " + db->searchSystemAnswer(message);

        break;
    }
    case numbers: {
        currentRound = numbers;

        const int lowNumbersCount = rand() % 4 + 2;

        delete num_gen;

        num_gen = new NumberGenerator(lowNumbersCount, 6 - lowNumbersCount);

        message.append("Numbers ");

        for (QString s : num_gen->getNumbers()) {
            message.append(s + ";");
        }
        message.chop(1);

        message.append(" ");

        message.append(num_gen->getRequiredNumber());

        break;
    }
    case anagrams: {
        currentRound = anagrams;

        message.append("Anagrams ");


        QVector<QString> *anagram =  db->getAnagram();

        message.append(anagram->at(1) + " ");
        message.append(anagram->at(3) + " ");
        message.append(anagram->at(0));

        break;
    }
    default:
        break;
    }

    doSendToAllServerMessage(message);
    qDebug() << message;
}

void Server::onRemoveUser(Client *client)
{
    clients.removeAt(clients.indexOf(client));
    clientsAnswers.remove(client);
    clientsReady.remove(client);
}

void Server::takeResult(QString answer)
{
    QList<QString> pair = answer.split(" ");

    for (auto client : clientsAnswers.keys()) {
        if (client->getName() == pair.first()) {
            clientsAnswers[client] = new QString(pair.last());
        }
    }

    QString result = "Result ";

    for (auto client : clientsAnswers.keys()) {
        if (clientsAnswers[client] == nullptr) {
            return;
        }
        result += client->getName() + " " +  *clientsAnswers[client] + " ";
    }
    doSendToAllServerMessage(result.trimmed());

    for (auto client : clientsAnswers.keys()) {
        delete clientsAnswers[client];
        clientsAnswers[client] = nullptr;
        clientsReady[client] = false;
    }

    qDebug() << result;

}

void Server::isGameReadyToStart()
{
    int autchedCount = 0;
    for (auto client : clients) {
        if (client->isAutched) {
            autchedCount++;
        }
    }
    if (autchedCount == 2) {
        setUpRound(latters);
    }
}

void Server::setReady()
{
    clientsReady[(Client *)QObject::sender()] = true;

    for (auto clientIsReady : clientsReady.values()) {
        if (!clientIsReady) {
            return;
        }
    }

    switch (currentRound) {
    case latters:
        setUpRound(numbers);
        qDebug() << "SetUP numbers";
        break;
    case numbers:
        setUpRound(anagrams);
        qDebug() << "SetUP anagrams";
        break;
    case anagrams:
        setUpRound(latters);
        qDebug() << "SetUP latters";
        break;
    default:
        break;
    }

}

void Server::onMessageFromGui(QString message, const QStringList &users)
{
    if (users.isEmpty())
        doSendToAllServerMessage(message);
    else
        doSendServerMessageToUsers(message, users);
}
