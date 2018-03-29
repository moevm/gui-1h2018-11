#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QLayout>
#include <QPushButton>
#include <mainwindow.h>

class MainWindow;

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(MainWindow *parent = nullptr);
};

#endif // STARTMENU_H
