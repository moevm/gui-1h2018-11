#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <singleplay/singleplay.h>
#include <startmenu.h>
#include <multyplay/multyplay.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void startNewSingleGame();    
    void startNewMultyGame();
    void startMenu();

signals:

    void gameStarted();

private:    
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
