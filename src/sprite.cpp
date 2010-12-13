#include "sprite.h"

#include <stdio.h>
#include "animation.h"


Sprite::Sprite()
{
    this->subSprites = new LinkedList<Sprite>();
    this->currentAnimation = NULL;
    this->currentImage = NULL;
    this->currentTime = 0;
        
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

void Sprite::setAnimation(Animation* animation)
{
    animation->reset(this->currentTime);
    this->currentAnimation = animation;
    this->currentImage = animation->getFrameImage(this->currentTime);
}

void Sprite::update(Time currentTime)
{
    //this->lastTime = this->currentTime;
    this->currentTime = currentTime;

    Sprite* s = this->subSprites->first;
    while (s != NULL)
    {
        s->update(currentTime);
        s = s->next;
    }
}

Point Sprite::getPosition(Time currentTime)
{
    if (currentTime == -1)
        return this->position.getVal(this->currentTime);
    else
        return this->position.getVal(currentTime);
}
void Sprite::move(Point pos, Time duration)
{
    return this->position.changeVal(pos, this->currentTime, duration);
}
void Sprite::moveTo(Point pos, Time duration)
{
    return this->position.setVal(pos, this->currentTime, duration);    
}

Vector Sprite::getScale(Time currentTime)
{
    if (currentTime == -1)
        return this->scalevector.getVal(this->currentTime);
    else
        return this->scalevector.getVal(currentTime);
}

void Sprite::scale(Vector scalevector, Time duration)
{
    return this->scalevector.changeVal(scalevector, this->currentTime, duration);
}

void Sprite::scaleTo(Vector scalevector, Time duration)
{
    return this->scalevector.setVal(scalevector, this->currentTime, duration);
}

float Sprite::getRotation(Time currentTime)
{
    if (currentTime == -1)
        return this->rotation.getVal(this->currentTime);
    else
        return this->rotation.getVal(currentTime);
}

void Sprite::rotate(float rotation, Time duration)
{
    return this->rotation.changeVal(rotation, this->currentTime, duration);
}

void Sprite::rotateTo(float rotation, Time duration)
{
    return this->rotation.setVal(rotation, this->currentTime, duration);
}

Color Sprite::getColor(Time currentTime)
{
    if (currentTime == -1)
        return this->color.getVal(this->currentTime);
    else
        return this->color.getVal(currentTime);
}

void Sprite::fade(Color color, Time duration)
{
    return this->color.changeVal(color, this->currentTime, duration);
}

void Sprite::fadeTo(Color color, Time duration)
{
    return this->color.setVal(color, this->currentTime, duration);
}
        
