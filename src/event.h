#ifndef _EVENT_H
#define _EVENT_H

#include "linkedlist.h"

class Block;

const int EVENT_NONE = 0;
const int EVENT_KEY = 1;
const int EVENT_CIRCLE = 2;

struct Event
{
        int type;

        Event(int type):
            type(type)
        {}
};


struct KeyEvent : public Event
{
        int id;
        bool pressed;
        
        KeyEvent(int id, bool pressed) :
            Event(EVENT_KEY), id(id), pressed(pressed)
        {}
        
};

struct CircleEvent : public Event
{
        LinkedList<Block*> blocks;
        bool falling;

        CircleEvent(LinkedList<Block*> blocks, bool falling) :
            Event(EVENT_CIRCLE), blocks(blocks), falling(falling)
        {}
};


#endif
