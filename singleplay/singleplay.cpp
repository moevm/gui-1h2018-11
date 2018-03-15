#include "singleplay.h"
#include "ui_singleplay.h"
#include "charlabel.h"
#include "backspacelabel.h"
#include <QtSql>
#include <map>

void singleplay::createConsonant()
{
    QString str = rand->getNextConsonant();
    if(str.contains("NONE") || chars.length() == 9 ){
        for(size_t i =0,size = chars.length();i<9-size;++i)
            createVowel();
        startLatterRound();
        return;
    }
    chars.append(str);
    charlabel* label = new charlabel(this,str);
    connect(label,SIGNAL(click(QString)),
            this,SLOT(addCharToPreAnswer(QString)));

    ui->charWidget->layout()->addWidget(label);
    vecLabel.append(label);
}

void singleplay::createVowel()
{
    QString str = rand->getNextVowel();
    if(str.contains("NONE") || chars.length() == 9){
        for(size_t i =0,size = chars.length();i<9-size;++i)
            createConsonant();
        startLatterRound();
        return;
    }

    chars.append(str);

    charlabel* label = new charlabel(this,str);
    connect(label,SIGNAL(click(QString)),
            this,SLOT(addCharToPreAnswer(QString)));
    ui->charWidget->layout()->addWidget(label);
    vecLabel.append(label);
}


void singleplay::addCharToPreAnswer(QString str)
{
    preAnswer.push_back(str);
    if(ui->LattersRound->isHidden()){
        ui->textAnswer_2->setText(preAnswer);
    }
    if(ui->NumbersRound->isHidden()){
        ui->textAnswer->setText(preAnswer);
    }

}

void singleplay::checkAnswerSlot()
{
    ui->finalScore->show();
    ui->answerWidget->hide();
    ui->charChoiser_2->hide();
    ui->charWidget->hide();
    ui->controlButtons->hide();
    //ui->skip->setText(QString::number(checkAnswer(preAnswer)));
    QString score;
    score.append("Ваш ответ: "+preAnswer+"\n");
    if(checkWord(preAnswer)){
        score.append("Значение слова: " + wordValue(preAnswer) +"\n");
    }else{
        score.append("К сожалению слово отсутствует в словаре\n");
    }

    score.append("Возможный вариант: "+systemAnswer+"\n"+"Значение слова: " + wordValue(systemAnswer) +"\n");
    ui->textScore->setText(score);
}

void singleplay::endGame()
{
    emit gameEnded();
}


singleplay::singleplay(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::singleplay)
{
    ui->setupUi(this);

    if(QSqlDatabase::contains(QSqlDatabase::defaultConnection)) {
        db_word = QSqlDatabase::database();
    } else {
        db_word = QSqlDatabase::addDatabase("QSQLITE");
        db_word.setDatabaseName(QCoreApplication::applicationDirPath()+"/sample1.db");
    }


    connect(ui->answer,SIGNAL(clicked(bool)),
            this,SLOT(checkAnswerSlot()));
    connect(ui->skip,SIGNAL(clicked(bool)),
            this,SLOT(nextRound()));
    connect(ui->nextRound,SIGNAL(clicked(bool)),
            this,SLOT(nextRound()));
    connect(ui->countBigNumbers,SIGNAL(valueChanged(int)),
            this,SLOT(changeBigNumbersCount(int)));
    connect(ui->countSmallNumbers,SIGNAL(valueChanged(int)),
            this,SLOT(changeSmallNumbersCount(int)));
    connect(ui->accept,SIGNAL(clicked(bool)),
            this,SLOT(startNumberRound()));

//    b = new backspaceLabel(this);
//    connect(b,SIGNAL(backspace()),
//            this,SLOT(backspacePress()));
//    connect(this,SIGNAL(gameStarted()),
//            b,SLOT(show()));

//    ui->charWidget->layout()->addWidget(b);

    //connect(ui->backspace,SIGNAL());
    rand = new randomchar();
    //num = new numberlogic(6,0);

    ui->controlButtons->hide();
    ui->answerWidget->hide();
    ui->finalScore->hide();

    ui->NumbersRound->hide();
}

singleplay::~singleplay()
{
    delete ui;
    delete num;
    delete rand;
    db_word.close();
}

void singleplay::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Backspace ){
        backspacePress();
    }
}

void singleplay::startNumberRound()
{

    num = new numberlogic(ui->countSmallNumbers->value(),ui->countBigNumbers->value());
    for(int i =0,size = num->getSet()->length();i<size; ++i)
    {
        charlabel* label = new charlabel(this,QString::number(num->getSet()->at(i)));
        connect(label,SIGNAL(click(QString)),
                this,SLOT(addCharToPreAnswer(QString)));

        ui->numberWidget->layout()->addWidget(label);
        vecLabel.append(label);
    }
    ui->controlButtons_2->hide();
}

void singleplay::startLatterRound()
{
    emit gameStarted();
    ui->charChoiser_2->hide();
    ui->answerWidget->show();
    ui->controlButtons->show();
    QString str;
    for(charlabel* a : vecLabel ){
        a->setActived(true);
        str.append(a->text());
    }
    str = str.toLower();
    systemAnswer = searchSystemAnswer(str);
}

void singleplay::nextRound()
{
    ui->controlButtons->hide();
    ui->answerWidget->hide();
    ui->finalScore->hide();
    ui->charChoiser_2->show();
    ui->charWidget->show();
    delete rand;
    rand = new randomchar();

    chars.clear();
    preAnswer.clear();
    systemAnswer.clear();
    for(charlabel* v : vecLabel){
        delete v;
    }

    vecLabel.clear();
    //b->hide();

    //    if(ui->LattersRound->isHidden())
    //    {
    //        ui->LattersRound->show();

    //        ui->NumbersRound->hide();

    //        rand = new randomchar();
    //        ui->controlButtons->hide();
    //        ui->answerWidget->hide();
    //        ui->finalScore->hide();
    //    }
    //    if(ui->NumbersRound->isHidden())
    //    {
    //        ui->NumbersRound->show();

    //        ui->LattersRound->hide();

    //        delete rand;
    //        rand = NULL;
    //        vecLabel.clear();
    //    }
}

void singleplay::changeBigNumbersCount(int n)
{
    ui->countSmallNumbers->setValue(6-n);
}

void singleplay::changeSmallNumbersCount(int n)
{
    ui->countBigNumbers->setValue(6-n);
}

void singleplay::backspacePress()
{
    if(!ui->LattersRound->isHidden() &&
            preAnswer.length()>0){
        QString s = QString(preAnswer[preAnswer.length()-1]);
        for(charlabel* a : vecLabel){
            if(a->text() == s && !a->getAllowed()){
                a->setAllowed(true);
                break;
            }
        }
        preAnswer.chop(1);
        ui->textAnswer->setText(preAnswer);
    }
}



QString singleplay::searchSystemAnswer(QString str)
{
    if(db_word.open())
    {
        QSqlQuery qr;
        if(qr.exec("select word from ozhigov where length(word)>3 and length(word)<9 order by length(word) desc")){
            while(qr.next()){
                QString row = qr.value(0).toString();
                bool ans = true;
                QMap<QChar,bool> m;
                for(auto s : str){
                    m.insert(s,true);
                }
                for(auto a : row){
                    if(m.contains(a) && m.value(a)){
                        m[a] = false;
                    }else{
                        ans = false;
                        break;
                    }
                }
                for(auto s : str){
                    m[s]= true;
                }
                if(ans)
                    return row.toUpper();
            }
        }

    }
}

QString singleplay::wordValue(QString str)
{
    if(db_word.open())
    {
        QSqlQuery qr;
        if(qr.exec("select word,description from ozhigov where word = '" + str.toLower() + "'")){
            if(qr.next()){
                QString s = qr.value(1).toString().left(qr.value(1).toString().indexOf(QChar(50)));
                while(s.indexOf(QChar(92))!=-1){
                    s[s.indexOf(QChar(92))]='\n';
                }
                s.remove(QChar(92));
                s.remove(QChar(110));
                return s;
            }
        }
    }
}

bool singleplay::checkWord(QString str)
{
    if(db_word.open())
    {
        QSqlQuery qr;
        if(qr.exec("select word from ozhigov where word = '" + str.toLower() + "'")){
            if(qr.next()){
                return true;
            }
            else {
                return false;
            }
        }
    }
}


