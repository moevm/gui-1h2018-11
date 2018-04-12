#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "singleplay/singleplay.h"
#include "QSqlError"
#include <QFile>


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

    this->setStyleSheet("QWidget{background-color:rgb(135, 206, 235);}"
                        "QPushButton:enabled { "
                        "color: rgb(255, 255, 255); "
                        "border-style: outset; "
                        "border-width: 2px; "
                        "border-radius: 10px; "
                        "border-color: rgb(0, 0, 255);"
                        "padding: 6px; "
                        "background-color: rgb(65, 105, 225); "
                        "font-size: 20px; "
                        "font-family: Times New Roman;} ");
//    this->setStyleSheet("QWidget{background-color:rgb(135, 206, 235);}");
    startMenu();
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::startNewSingleGame()
{
    this->setCentralWidget(new SinglePlay(this));
}

void MainWindow::startNewMultyGame()
{
    this->setCentralWidget(new MultyPlay(this));
}

void MainWindow::startMenu()
{
    this->setCentralWidget(new StartMenu(this));
}
