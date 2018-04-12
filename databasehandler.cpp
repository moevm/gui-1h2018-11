#include "databasehandler.h"
#include <QCoreApplication>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QVariant>
#include <QString>
#include <random>
#include <QFile>
#include <QStandardPaths>
#include <QDebug>
#include <ctime>

DataBaseHandler::DataBaseHandler()
{
    //    QFile dfile("./words.db");
    //    if (dfile.exists())
    //    {
    //        quint64 t = dfile.size();
    //        QFile::setPermissions("./words.db",QFile::WriteOwner |     QFile::ReadOwner);
    //     }


    if (QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        db_word = QSqlDatabase::database();
    }
    else {
        db_word = QSqlDatabase::addDatabase("QSQLITE");
#if defined(Q_OS_ANDROID)
        QFile file("assets:/db/words.db") ;
        QString patientDbPath;
        if (file.exists()) {
            patientDbPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
            if (patientDbPath.isEmpty())
            {
                qDebug() << "Could not obtain writable location.";
            }
            patientDbPath.append("/words.db");
            file.copy(patientDbPath) ;
            QFile::setPermissions(patientDbPath ,QFile::WriteOwner | QFile::ReadOwner) ;
        } else qDebug() << "the file does not exist" ;
        db_word.setDatabaseName(patientDbPath);
        qDebug() << "ANDROID";
#elif defined(Q_OS_LINUX)
        qDebug() << "LINUX";
#elif defined(Q_OS_WIN)
        db_word.setDatabaseName(QCoreApplication::applicationDirPath() + "/words.db");
        qDebug() << "WIN";
#endif
    }

    db_word.open();
}


DataBaseHandler::~DataBaseHandler()
{
    db_word.close();
}

QString DataBaseHandler::searchSystemAnswer(QString str)
{
    str = str.toLower();
    QSqlQuery qr;

    if (qr.exec("select word from ozhigov where length(word)>3 and length(word)<9 order by length(word) desc")) {
        while (qr.next()) {
            QString row = qr.value(0).toString();
            if (isWordContainsString(row, str)) {
                return row.toUpper();
            }
        }
    }

    QString str1 =  qr.lastError().text();

    return QString();
}

QString DataBaseHandler::getWordValue(QString str)
{
    QSqlQuery qr;
    if (qr.exec("select word,description from ozhigov where word = '" + str.toLower() + "'")) {
        if (qr.next()) {
            return parsingRow(qr.value(1).toString());
        }
    }

}

QVector<QString>* DataBaseHandler::getAnagram()
{
    srand(time(0));
    int anagram = rand()%2423+1;

    QVector<QVector<QString>*>* variants =new QVector<QVector<QString>*>();
    QSqlQuery qr;
    if (qr.exec("SELECT root,word1,value1,word2,value2 FROM leefAnagrams,rootAnagrams WHERE id_root ="+QString::number(anagram)+"  and id = "+QString::number(anagram))) {
        if (qr.next()) {
            QVector<QString>* row = new QVector<QString>();
            row->push_back(qr.value(0).toString());
            row->push_back(qr.value(1).toString());
            row->push_back(qr.value(2).toString());
            row->push_back(qr.value(3).toString());
            row->push_back(qr.value(4).toString());

            variants->push_back(row);
        }
    }

    return *(variants->begin()+rand()%variants->length());
}

bool DataBaseHandler::isWordContained(QString str)
{
    QSqlQuery qr;
    if (qr.exec("select word from ozhigov where word = '" + str.toLower() + "'")) {
        return qr.next();
    }
}

bool DataBaseHandler::isWordContainsString(QString word, QString str)
{
    QMap<QChar, bool> m;
    for (auto s : str) {
        m.insert(s, true);
    }
    for (auto a : word) {
        if (m.contains(a) && m.value(a)) {
            m[a] = false;
        }
        else {
            return false;
        }
    }
    return true;
}

QString DataBaseHandler::parsingRow(QString row)
{
    QString str = row.left(row.indexOf(QChar(50)));
    while (str.indexOf(QChar(92)) != -1) {
        str[str.indexOf(QChar(92))] = '\n';
    }
    str.remove(QChar(92));
    str.remove(QChar(110));
    return str;
}
