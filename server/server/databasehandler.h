#pragma once

#include <QString>
#include <QSqlDatabase>
#include <QVector>
class DataBaseHandler
{
public:
    DataBaseHandler();
    ~DataBaseHandler();

    QString searchSystemAnswer(QString str);
    QString getWordValue(QString str);

    QVector<QString>* getAnagram();

    bool isWordContained(QString);
    bool isWordContainsString(QString,QString);

private:

    QString parsingRow(QString str);

    QSqlDatabase db_word;
};

