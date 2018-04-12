#include <QCoreApplication>
#include "server.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server s;
//    QHostAddress addr;
//    addr.setAddress("127.0.0.1");
    s.doStartServer(QHostAddress::LocalHost,1224);
    return a.exec();
}
