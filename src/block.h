#ifndef _BLOCK_H
#define _BLOCK_H

#include "time.h"
#include "time.h"

#include "vector.h"
#include "sprite.h"

class Animation;

class Block : public Sprite
{
        int type;
        Animation* blinkAnimation;
        Animation* pulseAnimation;
        Animation* normalAnimation;

        int boardx;
        int boardy;

        float gravityDelay;
        int status;
        
        Vector size;
        Vector center;
        Vector offset;

        int comboCounter;
        int layer;
    public:

        Block(int boardx, int boardy, int type, Vector& offset);
    
        void doPulse();      
        void doBlink();
        void doNormal();

        void moveToBoardCoord(int boardx, int boardy, Time currentTime);
        void setToBoardCoord(int boardx, int boardy);
        void animatePopup(Time currentTime);
};
        
#endif
