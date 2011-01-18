#include "sprite.h"

#include <stdio.h>
#include "animation.h"


Sprite::Sprite(Time currentTime):
    softblend(false),         
    currentTime(currentTime),
    lastTime(currentTime),
    subSprites(new FastLinkedList<Sprite>()),
    currentImage(NULL),
    currentAnimation(NULL), 
    center(Point(0.0, 0.0)),
    position(Point(0.0, 0.0)),
    scalevector(Vector(1.0, 1.0)),
    color(Color(1.0f, 1.0f, 1.0f, 1.0f)),
    rotation(0.0f)
{

}
Sprite::~Sprite()
{
    delete this->subSprites;
}


void Sprite::addSprite(Sprite* sprite)
{
    if (sprite == NULL)
        return;
    
    if (sprite->list != NULL)
    {
        fprintf(stderr, "Removing sprite from current list before adding!\n");
        sprite->list->releaseLink(sprite);
    }
    this->subSprites->addLink(sprite);
}

void Sprite::removeSprite(Sprite* sprite)
{
    if (sprite == NULL)
        return;

    if (sprite->list == this->subSprites)
    {
        this->subSprites->releaseLink(sprite);
    }
    else
    {
        fprintf(stderr, "Tried to remove sprite from wrong list!\n");
    }
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
    
    if (this->currentAnimation != NULL)
        this->currentImage = this->currentAnimation->getFrameImage(this->currentTime);

    
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
        
