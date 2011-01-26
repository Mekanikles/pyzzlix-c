#include "sprite.h"

#include <stdio.h>
#include "animation.h"
#include "movebehaviour.h"
#include "mover.h"

Sprite::Sprite(Time currentTime):
    softblend(false),         
    currentTime(currentTime),
    subSprites(new FastLinkedList<Sprite>()),
    currentImage(NULL),
    currentAnimation(NULL), 
    center(Point(0.0, 0.0)),
    position(Point(0.0, 0.0)),
    scaleVector(Vector(1.0, 1.0)),
    color(Color(1.0f, 1.0f, 1.0f, 1.0f)),
    rotation(0.0f)
{

    position_behaviour = new MoveBehaviour_Decelerator(2);
    scale_behaviour = new MoveBehaviour();
    color_behaviour = new MoveBehaviour();
    rotation_behaviour = new MoveBehaviour();

    position_mover = NULL;
    scale_mover = NULL;
    color_mover = NULL;
    rotation_mover = NULL;
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

    // Update all movers
    if (this->position_mover != NULL)
        position_mover->updateValue(this->currentTime);
    
    if (this->scale_mover != NULL)
        scale_mover->updateValue(this->currentTime);

    if (this->color_mover != NULL)
        color_mover->updateValue(this->currentTime);

    if (this->rotation_mover != NULL)
        rotation_mover->updateValue(this->currentTime);
    
    Sprite* s = this->subSprites->first;
    while (s != NULL)
    {
        s->update(currentTime);
        s = s->next;
    }
}

Point Sprite::getPosition()
{
    return this->position.getVal();
}
void Sprite::moveTo(Point position, Time duration)
{
    if (this->position_mover != NULL)
    {
        this->position_mover->updateValue(this->currentTime);
        delete this->position_mover;
    }

    if (duration <= 0.0)
    {
        this->position.forceTo(position);
        return;
    }
    
    this->position_mover = new Mover<Point>(this->position_behaviour,
                                            &this->position, this->currentTime,
                                            position, duration);
}

Vector Sprite::getScale()
{
    return this->scaleVector.getVal();
}
void Sprite::scaleTo(Vector scaleVector, Time duration)
{
    if (this->scale_mover != NULL)
    {
        this->scale_mover->updateValue(this->currentTime);
        delete this->scale_mover;
    }

    if (duration <= 0.0)
    {
        this->scaleVector.forceTo(scaleVector);
        return;
    }
    
    this->scale_mover = new Mover<Vector>(this->scale_behaviour,
                                            &this->scaleVector, this->currentTime,
                                            scaleVector, duration);
}

float Sprite::getRotation()
{
    return this->rotation.getVal();
}
void Sprite::rotateTo(float rotation, Time duration)
{
    if (this->rotation_mover != NULL)
    {
        this->rotation_mover->updateValue(this->currentTime);
        delete this->rotation_mover;
    }

    if (duration <= 0.0)
    {
        this->rotation.forceTo(rotation);
        return;
    }
    
    this->rotation_mover = new Mover<float>(this->rotation_behaviour,
                                            &this->rotation, this->currentTime,
                                            rotation, duration);
}

Color Sprite::getColor()
{
    return this->color.getVal();
}
void Sprite::fadeTo(Color color, Time duration)
{
    if (this->color_mover != NULL)
    {
        this->color_mover->updateValue(this->currentTime);
        delete this->color_mover;
    }

    if (duration <= 0.0)
    {
        this->color.forceTo(color);
        return;
    }
    
    this->color_mover = new Mover<Color>(this->color_behaviour,
                                            &this->color, this->currentTime,
                                            color, duration);
}
        
