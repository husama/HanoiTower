#ifndef DISKSTACK_H
#define DISKSTACK_H




#include <QDebug>
#include <QRect>
#include <QStack>
#include <QLabel>

#include "disk.h"

class diskstack
{
    public:
        disk *initial;
        QStack <disk> s_stack;
        int s_height; // Height of the stack = number of disks
        int id;//柱子编号
        QStack<QLabel*> labels;

        void update_position();
        void init(int, int);

};

#endif // DISKSTACK_H
