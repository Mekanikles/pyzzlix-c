#include "block.h"

#include "animation.h"

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
    
    this->blinkAnimation = new Animation("blocks",
         size, size, this->type * size, 0, size, 6 * size, 0.015, ANIMATION_MODE_LOOP);
    
    this->pulseAnimation = new Animation("blocks",
         size, size, this->type * size, 0, size, 6 * size, 0.015, ANIMATION_MODE_PINGPONGLOOP);
    
    this->normalAnimation = new Animation("blocks",
         size, size, this->type * size, 0, size, size, 0, ANIMATION_MODE_NORMAL);

    
    this->setAnimation(this->normalAnimation);
    this->center = Point(size * 0.5f, size * 0.5f);

}

void Block::doPulse()
{
    this->setAnimation(this->pulseAnimation);
}

void Block::doBlink()
{
    this->setAnimation(this->blinkAnimation);
}

void Block::doNormal()
{
    this->setAnimation(this->normalAnimation);
}

void Block::animatePopup()
{
    this->fadeTo(Color(0.1, 0.1, 0.1, 1.0));
    this->fadeTo(Color(1.0, 1.0, 1.0, 1.0), 2.0);
    this->scaleTo(Vector(0.0, 0.0));
    this->scaleTo(Vector(1.0, 1.0), 0.15);

}
