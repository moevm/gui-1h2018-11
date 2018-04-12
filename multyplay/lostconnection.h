#ifndef LOSTCONNECTION_H
#define LOSTCONNECTION_H

#include <QWidget>

namespace Ui {
class LostConnection;
}

class LostConnection : public QWidget
{
    Q_OBJECT

public:
    explicit LostConnection(QWidget *parent = 0,QString str = "Connection refuse");
    ~LostConnection();
signals:
    void tryCreateConnection();
private slots:
    void tryConnectionAgain();
private:
    Ui::LostConnection *ui;
};

#endif // LOSTCONNECTION_H
