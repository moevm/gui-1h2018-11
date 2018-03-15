#include "charlabel.h"


charlabel::charlabel(QWidget *parent,QString str) : QLabel(parent)
{
    this->setText(str);
    this->setAlignment(Qt::AlignCenter);
    this->setStyleSheet("QLabel {"
                        "border-style: solid;"
                        "border-width: 1px;"
                        "border-color: black; "
                        "}");
    allowed = true;
    actived = false;
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
                            "border-style: solid;"
                            "border-width: 1px;"
                            "border-color: black; "
                            "}");
    }else{
        this->setStyleSheet("QLabel {"
                            "border-style: solid;"
                            "border-width: 1px;"
                            "border-color: red; "
                            "color: red"
                            "}");
    }
}
