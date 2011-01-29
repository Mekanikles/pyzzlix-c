#include "sprite.h"

#include <stdio.h>
#include "animation.h"

Sprite::Sprite(Time currentTime):
    softblend(false),         
    currentTime(currentTime),
    subSprites(new FastLinkedList<Sprite>()),
    currentImage(NULL),
    currentAnimation(NULL), 
    center(Point(0.0, 0.0)),
    position(Point(0.0, 0.0)),
    scale(Vector(1.0, 1.0)),
    color(Color(1.0f, 1.0f, 1.0f, 1.0f)),
    rotation(0.0f),
    ival_position(NULL),
    ival_scale(NULL), 
    ival_color(NULL),
    ival_rotation(NULL),
    position_inter(NULL),
    scale_inter(NULL), 
    color_inter(NULL),
    rotation_inter(NULL)
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

void Sprite::setPositionInterpolation(Interpolation* inter)
{
    if (this->position_inter != NULL) 
        delete this->position_inter; 
    this->position_inter = inter;
}
void Sprite::setScaleInterpolation(Interpolation* inter)
{
    if (this->scale_inter!= NULL) 
        delete this->scale_inter; 
    this->scale_inter = inter;
}       
void Sprite::setRotationInterpolation(Interpolation* inter)
{
    if (this->rotation_inter != NULL) 
        delete this->rotation_inter; 
    this->rotation_inter = inter;
}
void Sprite::setColorInterpolation(Interpolation* inter)
{
    if (this->color_inter != NULL) 
        delete this->color_inter; 
    this->color_inter = inter;
}

void Sprite::setImage(Image* image)
{
    this->currentImage = image;
}

void Sprite::animate(FrameSet* frameSet, Time duration, Interpolation* inter)
{
    if (this->currentAnimation != NULL)
    {
        delete this->currentAnimation;
        this->currentAnimation = NULL;
    }
    
    if (duration <= 0.0)
    {
        FrameSet::Frame* frame = frameSet->getFrame(0);
        if (frame != NULL)
            this->currentImage = frame->image;    
    }
    else
    {
        this->currentAnimation = new Animation(frameSet, this->currentTime, duration, inter);
        this->currentImage = this->currentAnimation->getFrameImage(this->currentTime);
    }
}

void Sprite::update(Time currentTime)
{
    //this->lastTime = this->currentTime;
    this->currentTime = currentTime;
    
    if (this->currentAnimation != NULL)
        this->currentImage = this->currentAnimation->getFrameImage(this->currentTime);

    // Update all movers
    /*
    if (this->position_mover != NULL)
        position_mover->updateValue(this->currentTime);
    
    if (this->scale_mover != NULL)
        scale_mover->updateValue(this->currentTime);

    if (this->color_mover != NULL)
        color_mover->updateValue(this->currentTime);

    if (this->rotation_mover != NULL)
        rotation_mover->updateValue(this->currentTime);
    */
        
    Sprite* s = this->subSprites->first;
    while (s != NULL)
    {
        s->update(currentTime);
        s = s->next;
    }
}

Point Sprite::getPosition(Time time)
{
    if (this->ival_position != NULL)
        return this->ival_position->getVal(time);
    return position;
}
void Sprite::moveTo(Point position, Time duration)
{
    if (this->ival_position != NULL)
    {
        this->position = ival_position->getVal(this->currentTime);
        delete this->ival_position;
        this->ival_position = NULL;
    }

    if (duration <= 0.0)
    {
        this->position = position;
        return;
    }

    if (position_inter == NULL)
    {
        position_inter = new Interpolation_Linear();
    }
    
    this->ival_position = new MovingValue<Point>(this->currentTime, this->position, position, duration, position_inter);
}

Vector Sprite::getScale(Time time)
{
    if (this->ival_scale != NULL)
        return this->ival_scale->getVal(time);
    return scale;
}
void Sprite::scaleTo(Vector scale, Time duration)
{
    if (this->ival_scale != NULL)
    {
        this->scale = ival_scale->getVal(this->currentTime);
        delete this->ival_scale;
        this->ival_scale = NULL;
    }

    if (duration <= 0.0)
    {
        this->scale = scale;
        return;
    }

    if (scale_inter == NULL)
    {
        scale_inter = new Interpolation_Linear();
    }
        
    this->ival_scale = new MovingValue<Vector>(this->currentTime, this->scale, scale, duration, scale_inter);
}
    
float Sprite::getRotation(Time time)
{
    if (this->ival_rotation != NULL)
        return this->ival_rotation->getVal(time);
    return rotation;

}
void Sprite::rotateTo(float rotation, Time duration)
{
    if (this->ival_rotation != NULL)
    {
        this->rotation = ival_rotation->getVal(this->currentTime);
        delete this->ival_rotation;
        this->ival_rotation = NULL;
    }

    if (duration <= 0.0)
    {
        this->rotation = rotation;
        return;
    }

    if (rotation_inter == NULL)
    {
        rotation_inter = new Interpolation_Linear();
    }
       
    this->ival_rotation = new MovingValue<float>(this->currentTime, this->rotation,  rotation, duration, rotation_inter);
}

Color Sprite::getColor(Time time)
{
    if (this->ival_color != NULL)
        return this->ival_color->getVal(time);
    return color;
}
void Sprite::fadeTo(Color color, Time duration)
{
    if (this->ival_color != NULL)
    {
        this->color = ival_color->getVal(this->currentTime);
        delete this->ival_color;
        this->ival_color = NULL;
    }

    if (duration <= 0.0)
    {
        this->color = color;
        return;
    }

    if (color_inter == NULL)
    {
        color_inter = new Interpolation_Linear();
    }
        
    this->ival_color = new MovingValue<Color>(this->currentTime, this->color, color, duration, color_inter);
}
        
