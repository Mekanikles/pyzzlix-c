#include "block.h"

#include "animation.h"

Block::Block(int boardx, int boardy, int type, Vector& offset):
    type(type),
    boardx(boardx),
    boardy(boardy),
    gravityDelay(0.0f),
    status(STATUS_NONE),
    comboCounter(0),
    layer(type)
{
    this->blinkAnimation = new Animation("blocks",
         16, 16, this->type * 16, 0, 16, 6 * 16, 0.016, ANIMATION_MODE_PINGPONGLOOP);
    
    this->pulseAnimation = new Animation("blocks",
         16, 16, this->type * 16, 0, 16, 6 * 16, 0.016, ANIMATION_MODE_PINGPONGLOOP);
    
    this->normalAnimation = new Animation("blocks",
         16, 16, this->type * 16, 0, 16, 16, 0.016, ANIMATION_MODE_NORMAL);
    
    this->setAnimation(this->normalAnimation);
    this->size = Vector(16, 16);
    this->center = this->size * 0.5f;
    this->offset = offset;        
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

void Block::moveToBoardCoord(int boardx, int boardy, Time currentTime)
{
    this->boardx = boardx;
    this->boardy = boardy;
    this->moveTo(Point(this->boardx * this->size.x + this->offset.x,
                       this->boardy * this->size.y + this->offset.y), 0.15);    
}

void Block::setToBoardCoord(int boardx, int boardy)
{
    this->boardx = boardx;
    this->boardy = boardy;
    this->setPos(Point(this->boardx * this->size.x + this->offset.x,
                       this->boardy * this->size.y + this->offset.y));
}

void Block::animatePopup(Time currentTime)
{
    //this->setCol(Color(0.1, 0.1, 0.1, 1.0));
    //this->fadeTo(Color(1.0, 1.0, 1.0, 1.0), currentTime, 1.0);
    //this->setScale(Vector(0.0, 0.0));
    //this->scaleTo(Vector(1.0, 1.0), currentTime, 0.15);
    //this->setRot(180.0);
    //this->rotateTo(0, currentTime, 0.3);
}
