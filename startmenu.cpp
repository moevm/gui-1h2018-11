#include "startmenu.h"


StartMenu::StartMenu(MainWindow *parent) : QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);

	QPushButton *startSinglePlay = new QPushButton("Одиночная игра");
	QPushButton *startMultyPlay = new QPushButton("Многопользовательская игра");

	connect(startSinglePlay, SIGNAL(pressed()),
        parent,SLOT(startNewSingleGame()));

	layout->addWidget(startSinglePlay);
	layout->addWidget(startMultyPlay);

	this->setLayout(layout);
}
