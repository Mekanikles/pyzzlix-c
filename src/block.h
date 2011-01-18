#ifndef _BLOCK_H
#define _BLOCK_H

#include "time.h"
#include "time.h"

#include "vector.h"
#include "sprite.h"

class Animation;

const int BLOCKTYPE_HEART = 0;
const int BLOCKTYPE_SQUARE = 1;
const int BLOCKTYPE_TRIANGLE = 2;
const int BLOCKTYPE_CROSS = 3;
const int BLOCKTYPE_DIAMOND = 4;
const int BLOCKTYPE_CIRCLE = 5;
const int BLOCKTYPE_PLUS = 6;

const int MAX_BLOCKTYPES = 7;

const int STATUS_NONE = 0;
const int STATUS_MOVING = 1;
const int STATUS_IN_CIRCLE = 4;
const int STATUS_ACTIVE_CIRCLE = 8;
const int STATUS_ON_PATH = 16;
const int STATUS_OFFSCREEN = 32;

class Block : public Sprite
{
    public:        
        int type;
        Animation* blinkAnimation;
        Animation* pulseAnimation;
        Animation* normalAnimation;

        float gravityDelay;
        int status;
   
        int comboCounter;
        int layer;

        Block(int boardx, int boardy, int type, Time currentTime);
    
        void doPulse();      
        void doBlink();
        void doNormal();

        void moveToBoardCoord(int boardx, int boardy, Time currentTime);
        void setToBoardCoord(int boardx, int boardy);
        void animatePopup();
        
        int boardx;
        int boardy;

};
        
#endif
