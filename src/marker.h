#ifndef _MARKER_H
#define _MARKER_H

#include "sprite.h"
#include "time.h"


class Marker : public Sprite
{
    public:
        Marker();

        void setOffset(const Vector& offset);
               
        void move(int dx, int dy, Time currentTime);
        void turn();
        void fail();
        
        
        int boardx;
        int boardy;
        
        Vector offset;
        Vector size;
        //Sound* moveSound;
        //Sound* turnSound;
        //Sound* failSound;
        
};

#endif
