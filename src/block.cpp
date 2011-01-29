#include "block.h"

#include "animation.h"
#include "interpolation.h"

#include "stdio.h"

Interpolation_Linear blink_inter;
Interpolation_Linear pulse_inter;

Block::Block(int boardx, int boardy, int type, Time currentTime):
    Sprite(currentTime),
    type(type),
    gravityDelay(0.0f),
    status(STATUS_NONE),
    comboCounter(0),
    layer(type),
    boardx(boardx),
    boardy(boardy)
{
    int size = 16;
    
    this->center = Point(size * 0.5f, size * 0.5f);
    
    this->setPositionInterpolation(new Interpolation_Decelerated());
       
    this->animationFrameSet = new FrameSet("blocks",
         size, size, this->type * size, 0, size, 6 * size);
         
    this->normalFrameSet = new FrameSet("blocks",
         size, size, this->type * size, 0, size, size);        
    
    blink_inter.setMode(INTERPOLATION_MODE_LOOP);
    pulse_inter.setMode(INTERPOLATION_MODE_PINGPONG);
    
    this->doNormal();
}

Block::~Block()
{
    delete this->animationFrameSet;
    delete this->normalFrameSet;
}

void Block::doPulse()
{
    this->animate(this->animationFrameSet, 0.1, &pulse_inter);
}

void Block::doBlink()
{
    this->animate(this->animationFrameSet, 0.1, &blink_inter);
}

void Block::doNormal()
{
    this->animate(this->normalFrameSet);
}

void Block::animatePopup()
{
    this->fadeTo(Color(0.1, 0.1, 0.1, 1.0));
    this->fadeTo(Color(1.0, 1.0, 1.0, 1.0), 2.0);
    this->scaleTo(Vector(0.0, 0.0));
    this->scaleTo(Vector(1.0, 1.0), 0.15);

}
