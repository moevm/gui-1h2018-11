#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singleplay/singleplay.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    s = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startNewSingleGame()
{
    s = new singleplay(this);
    ui->MainLayout->addWidget(s);
    connect(s,SIGNAL(gameEnded()),ui->startmenu,SLOT(gameEnded()));
    connect(s,SIGNAL(gameEnded()),this,SLOT(endLastGame()));
    emit gameStarted();
}

void MainWindow::endLastGame()
{
    delete s;
}
