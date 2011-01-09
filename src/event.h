#ifndef _EVENT_H
#define _EVENT_H

const int EVENT_NONE = 0;
const int EVENT_KEY = 1;

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


#endif
