#include "backspacelabel.h"

backspaceLabel::backspaceLabel(QWidget *parent): QLabel(parent)
{
    this->setText("<");
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("QLabel {"
                        "border-style: solid;"
                        "border-width: 1px;"
                        "border-color: black; "
                        "}");
    this->hide();
}

void backspaceLabel::mousePressEvent(QMouseEvent *event)
{
    emit backspace();
}


