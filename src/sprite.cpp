#include "sprite.h"
    
Sprite::Sprite()
{
    this->subSprites = new LinkedList<Sprite>();
}
Sprite::~Sprite()
{
    this->subSprites->destroy();
    delete this->subSprites;
}


void Sprite::setImage(Image* image)
{
    this->currentImage = image;
}
Point Sprite::calcPos(Time currentTime)
{
    if (this->pos_reftime <= currentTime)
    {
        return this->pos_ref;
    }
    else
    {
        double factorT = (this->pos_reftime - currentTime) / (this->pos_reftime - this->pos_lasttime);
        return this->pos_ref - (this->pos_ref - this->pos) * factorT;
    }

}
void Sprite::updatePos()
{
    this->pos = this->calcPos(this->currentTime);
    this->pos_lasttime = this->currentTime;

}
void Sprite::update(Time currentTime)
{
    this->lastTime = this->currentTime;
    this->currentTime = currentTime;
    
    this->updatePos();
}

void Sprite::setPos(Point pos)
{
    this->pos_ref = pos;
    this->pos = pos;
    this->pos_reftime = this->currentTime;
}

void Sprite::moveTo(Point pos, Time duration)
{
    this->updatePos(); // <- hm, necessary?
    this->pos_ref = pos;
    this->pos_reftime = this->currentTime + duration;
}
