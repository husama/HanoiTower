#include "hanoipanel.h"

hanoiPanel::hanoiPanel(QWidget *parent) : QWidget(parent)
{
    //Init
    num = 3;
    state = true;
    resetState = false;
    pauseState = false;
    timer = new QTimer();
    container = new QVBoxLayout(this);
    menuContainer = new QHBoxLayout();
    hanoiContainer = new QHBoxLayout();
    hcontainer1 = new QHBoxLayout();
    hcontainer2 = new QHBoxLayout();
    vcontainer = new QVBoxLayout();

    container->addLayout(menuContainer);
    container->addLayout(hanoiContainer);
    this->setLayout(container);

    values = new QStringList();
    for (int i = 1; i <=10;i++)
    {
        values->append(QString::number(i));
    }
    numComboBox = new QComboBox();
    numComboBox->addItems(*values);

    start1 = new QPushButton("开始：递归");
    start2 = new QPushButton("开始：迭代");
    stop = new QPushButton("暂停");
    reset = new QPushButton("重置");
    numLabel = new QLabel("盘子数目:");
    speedLabel = new QLabel("         Speed:");
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setValue(50);
    hanoiScene = new QGraphicsScene();

    fromtoLabel = new QLabel("盘子移动");
    codeLabel = new QLabel("代码:");
    paraLabel = new QLabel("递归参数:");

    showfromto = new QTextEdit();
    showcode = new QTextBrowser();
    showpara = new QTextEdit();



    showfromto->setStyleSheet("QTextEdit { background: rgb(227,230,195)}");
    showpara->setStyleSheet("QTextEdit { background: rgb(227,230,195)}");
    showcode->setStyleSheet("QTextEdit { background: rgb(227,230,195)}");




    QFont *font = new QFont("Times",18,QFont::Bold);
    showfromto->setFont(*font);
    showcode->setFont(QFont("Times",12,QFont::Bold));

    showfromto->setReadOnly(true);
    showpara->setReadOnly(true);
    showcode->setReadOnly(true);


    //showfromto->setTextBackgroundColor(QColor(230,180,80));


    hanoiScene->addRect(0,300,650,15,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));
    hanoiScene->addRect(100,50,10,250,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));
    hanoiScene->addRect(320,50,10,250,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));
    hanoiScene->addRect(540,50,10,250,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));

    menuContainer->addWidget(numLabel);
    menuContainer->addWidget(numComboBox);
    menuContainer->addWidget(start1);
    menuContainer->addWidget(start2);
    menuContainer->addWidget(stop);
    menuContainer->addWidget(reset);

    menuContainer->addWidget(speedLabel);
    menuContainer->addWidget(speedSlider);


    hanoiView = new QGraphicsView(hanoiScene);
    hanoiView->setStyleSheet("background: rgb(227,230,195)");
    stackwin = new showstack();

    vcontainer->addWidget(hanoiView);
    hcontainer1->addLayout(hcontainer2);
    container->addLayout(hcontainer1);

    hcontainer2->addWidget(fromtoLabel);
    hcontainer2->addWidget(showfromto);
    hcontainer2->addWidget(paraLabel);
    hcontainer2->addWidget(showpara);
    hcontainer1->addWidget(codeLabel);
    hcontainer1->addWidget(showcode);


    hanoiContainer->addLayout(vcontainer);
    hanoiContainer->addWidget(stackwin);


   /* QLabel *test = new QLabel();
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::blue);
    test->setPalette(palette);
    test->setGeometry(QRect(190,10,50,20));
    hanoiScene->addWidget(test);*/

    connect(start1,&QPushButton::clicked,this,&applystart);
    connect(start2,&QPushButton::clicked,this,&applystart2);
    connect(reset,&QPushButton::clicked,this,&applyreset);
    connect(speedSlider,&QSlider::actionTriggered,this,&applyspeedchange);
    connect(stop,&QPushButton::clicked,this,&applystop);


    connect(this,&hanoiPanel::sendPush,stackwin,&showstack::push);
    connect(this,&hanoiPanel::sendPop,stackwin,&showstack::pop);
    connect(this,&hanoiPanel::sendSpeed,stackwin,&showstack::setSpeed);
    connect(this,&hanoiPanel::sendMaxNum,stackwin,&showstack::showMaxnum);
    connect(this,&hanoiPanel::sendMoveNum,stackwin,&showstack::showMoveNum);
    connect(this,&hanoiPanel::sendClear,stackwin,&showstack::applyClear);

}

void hanoiPanel::applystart()
{

    num = numComboBox->currentText().toInt();
    speed = speedSlider->value()*50;
    //timer->start(speed_value*50);
    if(state)
    {state = false;

        //start1->setText("Stop");
        StackA.init(num,1);
        StackB.init(0,2);
        StackC.init(0,3);
        getdraw();
        algorithm(num,&StackA,&StackB,&StackC);
        resetState = true;
    }
    else
    {
            //start1->setText("Start");
    }
    //algorithm(number_disks, &StackA, &StackC, &StackB);

}

void hanoiPanel::applystart2()
{
    speed = speedSlider->value()*50;
    emit sendSpeed(speed);
    num = numComboBox->currentText().toInt();
    //speed = speedSlider->value();
    //timer->start(speed_value*50);
    if(state)
    {state = false;

        //start1->setText("Stop");
        StackA.init(num,1);
        StackB.init(0,2);
        StackC.init(0,3);
        getdraw();
        algorithm2(num,&StackA,&StackB,&StackC);
        resetState = true;
    }


}

void hanoiPanel::algorithm(int n, diskstack *A, diskstack *B,diskstack *C)
{


    showpara->append("n: "+QString::number(n)+" 起始柱子:"+QString::number(A->id)+" 辅助柱子:"+QString::number(B->id)+" 目标柱子:"+QString::number(C->id));

    if ( n == 1)
    {
        diskmove(A,C);
        showcode->append("void hanoiPanel::algorithm(int n, diskstack *A, diskstack *B,diskstack *C)\n{\n    if ( n == 1)\n    {");
        showcode->append("<font color = \"red\">&nbsp; &nbsp; &nbsp; &nbsp; diskmove(A,C);</font>");
        qDebug()<<A->id<<"->"<<C->id<<"ok";
        QEventLoop eventloop;
        QTimer::singleShot(speed, &eventloop, SLOT(quit()));
        eventloop.exec();

    }
    else
    {
        algorithm(n-1,A,C,B);
        diskmove(A,C);
        showcode->append("        QEventLoop eventloop;\n        QTimer::singleShot(speed, &eventloop, SLOT(quit()));\n        eventloop.exec();\n    }\n    else\n    {\n        algorithm(n-1,A,C,B);");
        showcode->append("<font color = \"red\">&nbsp;&nbsp;&nbsp;&nbsp;diskmove(A,C);</font>");
        showcode->append("        QEventLoop eventloop;\n        QTimer::singleShot(speed, &eventloop, SLOT(quit()));\n        eventloop.exec();\n        algorithm(n-1,B,A,C);\n   }");

        qDebug()<<A->id<<"->"<<C->id<<"ok";
        QEventLoop eventloop;
        QTimer::singleShot(speed, &eventloop, SLOT(quit()));
        eventloop.exec();
        algorithm(n-1,B,A,C);

    }
}

void hanoiPanel::algorithm2(int n ,diskstack *A, diskstack *B, diskstack *C)
{
        curNum = 0;
        maxNum = 0;
        moveNum = 0;
        QStack<group> s;
        group t = group(n,A,B,C);
        s.push(t);
        curNum++;
        maxNum++;
        emit sendPush(n,A->id,B->id,C->id);
        showcode->append("void hanoiPanel::algorithm2(int n ,diskstack *A, diskstack *B, diskstack *C)\n"
                         "{\n"
                         "        QStack<group> s;\n"
                         "        group t = group(n,A,B,C);\n");

        showcode->append( "<font color = \"red\">&nbsp;&nbsp;&nbsp; &nbsp;s.push(t);</font>");
        showcode->append("        emit sendPush();\n");
        while (!s.empty())
        {
            int v;
            diskstack *i,*j,*k;
            t =s.top();
            s.pop();
            curNum--;
            emit sendPop();

            v = t.n; i = t.x; j = t.y; k = t.z;

            showcode->append(
                             "        while (!s.empty())\n"
                             "        {\n"
                             "            int v;\n"
                             "            diskstack *i,*j,*k;\n"
                             "            t =s.top();\n");
            showcode->append("<font color = \"red\">&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; s.pop();</font>");

            showcode->append("            emit sendPop();\n"
                             "            v = t.n; i = t.x; j = t.y; k = t.z;\n");
            if ( v == 1 )
            {
                diskmove(i,k);
                showcode->append(
                                 "            if ( v == 1 )\n"
                                 "            {");

                showcode->append("<font color = \"red\">&nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp; diskmove(i，k);</font>");

                showcode->append("              QEventLoop eventloop;\n"
                                 "              QTimer::singleShot(speed, &eventloop, SLOT(quit()));\n"
                                 "                eventloop.exec();              \n"
                                 "            }\n"
                               );
                num++;
                QEventLoop eventloop;
                QTimer::singleShot(speed, &eventloop, SLOT(quit()));
                eventloop.exec();
                moveNum++;

            }
            else
            {
                showcode->append(  "            else\n"
                                   "            {\n"
                                   "                t.n = v-1; t.x = j; t.y = i; t.z = k;\n");

               showcode->append( "<font color = \"red\">&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp; &nbsp;s.push(t);</font>");
               showcode->append( "                emit sendPush();\n"
                                   "                t.n = 1; t.x = i; t.y = j; t.z = k;\n");
               showcode->append( "<font color = \"red\">&nbsp;&nbsp;&nbsp;&nbsp; &nbsp; &nbsp; &nbsp;s.push(t);</font>");
               showcode->append( "                emit sendPush();\n"
                                   "                t.n = v-1; t.x = i; t.y = k; t.z = j;\n");
               showcode->append( "<font color = \"red\">&nbsp;&nbsp; &nbsp;&nbsp;&nbsp; &nbsp; &nbsp;s.push(t);</font>");
               showcode->append( "                emit sendPush();\n"
                                   "            }\n"
                                   "        }\n"
                                   "        emit sendMaxNum(maxNum);\n"
                                   "        emit sendMoveNum(moveNum);\n"
                                   "      }\n"
                                   "}");

                t.n = v-1; t.x = j; t.y = i; t.z = k;
                s.push(t);
                curNum++;
                maxNum = curNum>maxNum?curNum:maxNum;
                emit sendPush(t.n,t.x->id,t.y->id,t.z->id);
                t.n = 1; t.x = i; t.y = j; t.z = k;
                s.push(t);
                curNum++;
                maxNum = curNum>maxNum?curNum:maxNum;
                emit sendPush(t.n,t.x->id,t.y->id,t.z->id);
                t.n = v-1; t.x = i; t.y = k; t.z = j;
                s.push(t);
                curNum++;
                maxNum = curNum>maxNum?curNum:maxNum;
                emit sendPush(t.n,t.x->id,t.y->id,t.z->id);
            }
        }
        emit sendMaxNum(maxNum);
        emit sendMoveNum(moveNum);
}

void hanoiPanel::getdraw()
{
    for (int i =0; i < num; i++)
    {
        QLabel *temp = new QLabel();
        QPalette palette;
        palette.setColor(QPalette::Window, StackA.s_stack.at(i).color);
        temp->setPalette(palette);
        temp->setGeometry(*StackA.s_stack.at(i).d_disk);
        hanoiScene->addWidget(temp);
        StackA.labels.push(temp);
    }
}

void hanoiPanel::diskmove(diskstack *A, diskstack *B)
{
    QLabel *temp = A->labels.pop();
    //QRect mid1(210,60,A->s_stack.top().d_disk->height(),A->s_stack.top().d_disk->width());
    if (temp == NULL)
    {
                qDebug()<<"ERROR:LABELS ARE NULL!";
        return;
    }
    QPropertyAnimation *animation = new QPropertyAnimation(temp, "geometry");
    animation->setDuration(speed);
    animation->setStartValue(*A->s_stack.top().d_disk);
    animation->setKeyValueAt(0,*A->s_stack.top().d_disk);

    QRect tempRect(A->s_stack.top().d_disk->x(),30,A->s_stack.top().d_disk->width(),A->s_stack.top().d_disk->height());
    animation->setKeyValueAt(0.3,tempRect);

    A->s_height--;
    B->s_height++;
    B->s_stack.push(A->s_stack.pop());
    B->labels.push(temp);
    A->update_position();
    B->update_position();
   // temp->move(B->s_stack.top().d_disk->topLeft());
    tempRect.setRect(B->s_stack.top().d_disk->x(),30,B->s_stack.top().d_disk->width(),B->s_stack.top().d_disk->height());
    animation->setKeyValueAt(0.7,tempRect);

    animation->setKeyValueAt(1,*B->s_stack.top().d_disk);
    animation->setEndValue(*B->s_stack.top().d_disk);
    animation->start();
    qDebug()<<A->id<<"->"<<B->id;
    showfromto->append(QString::number(A->id)+"->"+QString::number(B->id));
}

void hanoiPanel::applyreset()
{
    if (resetState)
    {
        hanoiScene->clear();

        hanoiScene->addRect(0,300,650,15,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));
        hanoiScene->addRect(100,50,10,250,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));
        hanoiScene->addRect(320,50,10,250,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));
        hanoiScene->addRect(540,50,10,250,QPen(QColor(230,180,80)),QBrush(QColor(230,180,80)));

        resetState = false;
        showcode->clear();
        emit sendClear();
        showfromto->clear();
        showpara->clear();
        showcode->clear();
        state = true;
    }

}


void hanoiPanel::applyspeedchange()
{
    speed = speedSlider->value()*50;
    emit sendSpeed(speed);
}

void hanoiPanel::applystop()
{
    pauseState = !pauseState;
    if (pauseState)
    {
        stop->setText("继续");
    }
    else
    {
        stop->setText("暂停");
    }
    QElapsedTimer t;
    t.start();
    while(t.elapsed()<10000000&&pauseState == true)
    QCoreApplication::processEvents();

}

void hanoiPanel::applynewstackwin()
{
    stackwin = new showstack();
    connect(this,&hanoiPanel::sendPush,stackwin,&showstack::push);
    connect(this,&hanoiPanel::sendPop,stackwin,&showstack::pop);
    connect(this,&hanoiPanel::sendSpeed,stackwin,&showstack::setSpeed);
    stackwin->show();
}

//void hanoiPanel::highLightCode(QString *target)
//{

//}
