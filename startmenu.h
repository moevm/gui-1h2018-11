#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = nullptr);

signals:

public slots:

    void gameStarted();
    void gameEnded();

};

#endif // STARTMENU_H
