#include "showstack.h"

showstack::showstack(QWidget *parent) : QWidget(parent)
{
   // setFixedHeight(500);
   // setFixedWidth(500);

    num = 0;

    container = new QVBoxLayout();
    maxnumButton = new QPushButton("最大入栈数目");
    movenumButton = new QPushButton("盘子移动次数");

    color = new QColor(230,180,80);
    stackScene = new QGraphicsScene();
    stackScene->addRect(150,50,220,0);
    stackScene->addRect(150,80,20,320,QPen(*color),QBrush(*color));
    stackScene->addRect(350,80,20,320,QPen(*color),QBrush(*color));
    stackScene->addRect(150,400,220,20,QPen(*color),QBrush(*color));
    stackView = new QGraphicsView(stackScene);
    stackView->setStyleSheet("background: rgb(227,230,195)");

    container->addWidget(stackView);
    container->addWidget(maxnumButton);
    container->addWidget(movenumButton);
    this->setLayout(container);


}

void showstack::push(int n, int a, int b, int c)
{
    num++;
    //maxnum = maxnum>num?maxnum:num;
    QLabel *temp = new QLabel("n:  "+QString::number(n)+"  参数："+QString::number(a)+"  "+QString::number(b)+"  "+QString::number(c));
    //temp->setText(QString::number(num));
    QPalette palette;
    QColor *color = new QColor();
    color->setRgb(qrand()%255, qrand()%255, qrand()%255, 255);
    palette.setColor(QPalette::Window, *color);
    temp->setPalette(palette);
    temp->setGeometry(QRect(170,50,180,20));
    stackScene->addWidget(temp);
    QPropertyAnimation *animation = new QPropertyAnimation(temp, "geometry");
    animation->setDuration(speed);
    animation->setStartValue(QRect(170,50,180,20));
    animation->setEndValue(QRect(170,400-num*20,180,20));

    labelStack.push(temp);

    animation->start();
    QEventLoop eventloop;
    QTimer::singleShot(speed, &eventloop, SLOT(quit()));
    eventloop.exec();


}

void showstack::pop()
{
    QLabel *temp = labelStack.pop();
    QPropertyAnimation *animation = new QPropertyAnimation(temp, "geometry");
    animation->setDuration(speed);
    animation->setStartValue(QRect(170,400-num*20,180,20));
    animation->setEndValue(QRect(170,50,180,0));
    animation->start();
    QEventLoop eventloop;
    QTimer::singleShot(speed, &eventloop, SLOT(quit()));
    eventloop.exec();

    num--;
}

void showstack::setSpeed(int s)
{
    speed = s;
}

void showstack::showMaxnum(int num)
{
    maxnumButton->setText("入栈最大数目："+QString::number(num));
}

void showstack::showMoveNum(int num)
{
    movenumButton->setText("盘子移动数目: "+QString::number(num));
}


void showstack::applyClear()
{
    maxnumButton->setText("入栈最大数目");
    movenumButton->setText("盘子移动数目");
    stackScene->clear();
    stackScene->addRect(150,50,220,0);
    stackScene->addRect(150,80,20,320,QPen(*color),QBrush(*color));
    stackScene->addRect(350,80,20,320,QPen(*color),QBrush(*color));
    stackScene->addRect(150,400,220,20,QPen(*color),QBrush(*color));
}
