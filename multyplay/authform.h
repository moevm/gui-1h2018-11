#ifndef AUTHFORM_H
#define AUTHFORM_H

#include <QWidget>
#include <QTcpServer>
#include <QDebug>
#include <QDataStream>
#include "multyplay/multyplay.h"
class MultyPlay;
namespace Ui {
class AuthForm;
}

class AuthForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthForm(MultyPlay *parent = 0);
    ~AuthForm();

private slots:
    void connectToServer();
private:


    Ui::AuthForm *ui;
};

#endif // AUTHFORM_H
