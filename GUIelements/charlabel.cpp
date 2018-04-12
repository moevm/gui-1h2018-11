#include "charlabel.h"


Charlabel::Charlabel(QWidget *parent, QString str, bool actived) : QLabel(parent)
{
    this->setText(str);
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
    allowed = true;
    this->actived = actived;
}


void Charlabel::mousePressEvent(QMouseEvent *event)
{
    if(allowed && actived){
        setAllowed(false);
        emit click(this->text());
    }
}

void Charlabel::setActived(bool value)
{
    actived = value;
}

bool Charlabel::getAllowed() const
{
    return allowed;
}

void Charlabel::setAllowed(bool value)
{
    allowed = value;
    if(allowed || actived == false){
        this->setStyleSheet("QLabel {"
                            "background: rgb(215, 231, 247);"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "border-color: rgb(255, 255, 255);"
                            "font-size: 16px;"
                            "color: rgb(0, 0, 128)"
                            "}");
    }else{
        this->setStyleSheet("QLabel {"
                            "background: rgb(215, 231, 247);"
                            "border-style: outset;"
                            "border-width: 2px;"
                            "border-radius: 10px;"
                            "border-color: rgb(0, 0, 128);"
                            "font-size: 16px;"
                            "color: rgb(0, 0, 128)"
                            "}");
    }
}
