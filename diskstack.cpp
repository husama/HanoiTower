#include "diskstack.h"


void diskstack::init(int height, int n)
{
    initial=new disk;
    s_stack.clear();
    int x,y,w,h;

    id = n;
    s_height = height;

    for (int i=s_height; i>=1; i--)
    {
        initial->color.setRgb(qrand()%255, qrand()%255, qrand()%255, 255);
        qDebug () << initial->color;
        //initial->d_disk = new QRect(0,0,i*2+1,3);
        initial->d_size = i;
        s_stack.push(*initial);
    }
    disk *data = s_stack.data();
    for(int i=s_stack.size()-1; i>=0; i--){
        x = (id-1)*220 + 100 - s_stack.at(i).d_size*10;
        y = 300-(i+1)*14;
        w = s_stack.at(i).d_size*20+10;
        h = 10;
        data[i].d_disk = new QRect(x,y,w,h);
    }
}

void diskstack::update_position()
{
    int x,y,w,h;
    disk *data = s_stack.data();
    for(int i=s_stack.size()-1; i>=0; i--)
    {
        x = (id-1)*220 + 100 - s_stack.at(i).d_size*10;
        y = 300-(i+1)*14;
        w = s_stack.at(i).d_size*20+10;
        h = 10;
        data[i].d_disk = new QRect(x,y,w,h);
    }
}



