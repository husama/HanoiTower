#ifndef SHOWSTACK_H
#define SHOWSTACK_H

#include <QWidget>
#include <QGraphicsView>
#include <QStack>
#include <QLayout>
#include <QPushButton>
#include <QPalette>
#include <QPropertyAnimation>
#include <QRect>
#include <QColor>
#include <QLabel>
#include <QEventLoop>
#include <QTimer>


//#include "hanoipanel.h"


class showstack : public QWidget
{
    Q_OBJECT
public:
    explicit showstack(QWidget *parent = 0);

    QGraphicsScene *stackScene;
    QGraphicsView *stackView;
    QVBoxLayout *container;

    QStack<QLabel *> labelStack;

    QPushButton *maxnumButton;
    QPushButton *movenumButton;

    QColor *color;


    int num;//已经入栈的数目
    int speed;//动画速度
   // int maxnum;
    //int moveNum;//盘子移动次数

signals:

public slots:
    void push(int,int,int,int);
    void pop();
    void setSpeed(int);
    void showMaxnum(int);
    void showMoveNum(int);
    void applyClear();

};

#endif // SHOWSTACK_H
