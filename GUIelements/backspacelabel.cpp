#include "backspacelabel.h"

BackspaceLabel::BackspaceLabel(QWidget *parent): QLabel(parent)
{
    this->setText("<");
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("QLabel {"
                        "background: rgb(215, 231, 247);"
                        "border-style: outset;"
                        "border-width: 2px;"
                        "border-radius: 10px;"
                        "border-color: rgb(255, 255, 255);"
                        "font-size: 16px;"
                        "color: rgb(0, 0, 128)"
                        "}");
}

void BackspaceLabel::mousePressEvent(QMouseEvent *event)
{
    emit backspace();
}


