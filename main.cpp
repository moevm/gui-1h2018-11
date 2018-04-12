#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
//    QFile dfile("assets:/db/words.db");
//    if (dfile.exists())
//    {
//        dfile.copy("./words.db");
//        quint64 t = dfile.size();
//        QFile::setPermissions("./words.db",QFile::WriteOwner |     QFile::ReadOwner);
//     }

	QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
