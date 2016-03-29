#ifndef HANOIPANEL_H
#define HANOIPANEL_H

#include <QGraphicsItemAnimation>
#include <QWidget>
#include <QComboBox>
#include <QSlider>
#include <QGraphicsView>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QTimer>
#include <QPalette>
#include <QStack>
#include <QTimeLine>
#include <QThread>
#include <QPropertyAnimation>
#include <QDebug>
#include <QTimeLine>
#include <QEventLoop>
#include <QPauseAnimation>
#include <QElapsedTimer>
#include <QCoreApplication>
#include <QTextEdit>
#include <QTextBrowser>
#include <QFont>

#include "disk.h"
#include "diskstack.h"
#include "showstack.h"

struct group
{
    int n;
    diskstack *x,*y,*z;
    group(int v=0,diskstack *i=NULL,diskstack *j=NULL, diskstack *k=NULL)
    {
       n = v;
       x = i,y = j,z = k;
    }
};

class hanoiPanel : public QWidget
{
    Q_OBJECT
public:
    explicit hanoiPanel(QWidget *parent = 0);

    //menu
    QComboBox *numComboBox;
    QSlider *speedSlider;
    QHBoxLayout *menuContainer,*hanoiContainer,*hcontainer1,*hcontainer2;
    QVBoxLayout *container,*vcontainer;
    QPushButton *start1,*start2,*stop,*reset;
    QLabel *numLabel,*speedLabel;
    QLabel *fromtoLabel,*codeLabel,*paraLabel;
    QStringList *values;


    //hanoi tower Graphics view
    QGraphicsScene *hanoiScene;
    QGraphicsView *hanoiView;

    showstack *stackwin;

    QTextEdit *showfromto,*showpara;
    QTextBrowser *showcode;
    //number
    int num;
    int speed;
    bool state;
    bool resetState;
    bool pauseState;

    int curNum,maxNum;//迭代算法的实时入栈数目和最大入栈数目
    int moveNum;

    diskstack StackA,StackB,StackC;
    QTimer *timer;
   // QStack<QLabel> labelStackA,labelStackB,labelStackC;



    void algorithm(int n, diskstack *A, diskstack *B,diskstack *C);
    void algorithm2(int n, diskstack *A, diskstack *B,diskstack *C);
    void diskmove(diskstack*, diskstack*);

    void getdraw();

    //void highLightCode(QString *);

signals:
    void sendPush(int, int, int, int);
    void sendPop();
    void sendSpeed(int);
    void sendMaxNum(int);
    void sendMoveNum(int);
    void sendClear();

public slots:
    void applystart();
    void applystart2();
    void applystop();
    void applyreset();
    void applyspeedchange();
    void applynewstackwin();
};

#endif // HANOIPANEL_H
