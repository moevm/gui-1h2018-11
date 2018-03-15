#include "startmenu.h"

StartMenu::StartMenu(QWidget *parent) : QWidget(parent)
{

}

void StartMenu::gameStarted()
{
    this->hide();
}

void StartMenu::gameEnded()
{
    this->show();
}
