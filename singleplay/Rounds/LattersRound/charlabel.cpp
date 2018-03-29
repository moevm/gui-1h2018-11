#include "charlabel.h"


charlabel::charlabel(QWidget *parent, QString str, bool actived) : QLabel(parent)
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


void charlabel::mousePressEvent(QMouseEvent *event)
{
    if(allowed && actived){
        setAllowed(false);
        emit click(this->text());
    }
}

void charlabel::setActived(bool value)
{
    actived = value;
}

bool charlabel::getAllowed() const
{
    return allowed;
}

void charlabel::setAllowed(bool value)
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
