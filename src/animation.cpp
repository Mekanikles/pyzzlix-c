#include "animation.h"

#include "resources.h"

Animation::Animation(const string& texturename, int width, int height,
    int srcx, int srcy, int srcw, int srch, Time frameLength, int mode, bool reverse)
{
    if (mode == ANIMATION_MODE_LOOP ||
        mode == ANIMATION_MODE_PINGPONG ||
        mode == ANIMATION_MODE_PINGPONGLOOP ||
        mode == ANIMATION_MODE_NORMAL)
    {
        this->mode = mode;
    }
    else
    {
        this->mode = ANIMATION_MODE_NORMAL;
    }
    
    this->reverse = reverse;
    
    this->images = Resources::getInstance()->getImageSheet(&this->frameCount,
        texturename, width, height,  srcx, srcy, srcw, srch);
    
    if (this->frameCount)
    {
        this->frameLengths = new Time[this->frameCount];
        for (int i = 0; i < this->frameCount; i++)
        {
            this->frameLengths[i] = frameLength;
        }
    }
    else
    {
        this->frameLengths = NULL;
    }

    this->reset(0.0);
}

Animation::~Animation()
{
    if (this->images != NULL)
        delete[] this->images;

    if (this->frameLengths != NULL)
        delete[] this->frameLengths;
}


void Animation::reset(Time currentTime)
{
    this->frameTimer = currentTime;
    
    if (this->reverse == true)
    {
        this->direction = -1;
        this->currentFrame = this->frameCount - 1;
    }
    else
    {
        this->direction = 1;
        this->currentFrame = 0;
    }
}

Image* Animation::getFrameImage(Time currentTime)
{
    if (this->frameCount <= 0)
        return NULL;
    
    while (this->direction != 0 && this->frameTimer + this->frameLengths[this->currentFrame] <= currentTime)
    {
        this->frameTimer += this->frameLengths[this->currentFrame];
        this->currentFrame += 1 * this->direction;
        if (this->currentFrame >= this->frameCount)
        {
            if (this->mode == ANIMATION_MODE_LOOP)
            {
                this->currentFrame = 0;
            }
            else if (this->mode == ANIMATION_MODE_PINGPONG)
            {
                if (!this->reverse)
                {
                    this->currentFrame = this->frameCount - 1;
                    this->direction = -1;
                }
                else
                {
                    this->direction = 0;
                    this->currentFrame = 0;
                    break;
                }
            }
            else if (this->mode == ANIMATION_MODE_PINGPONGLOOP)
            {
                this->currentFrame = this->frameCount - 1;
                this->direction = -1;
            }
            else
            {
                this->direction = 0;
                this->currentFrame = this->frameCount - 1;
                break;
            }
        }
        else if (this->currentFrame < 0)
        {
            if (this->mode == ANIMATION_MODE_LOOP)
            {
                this->currentFrame = this->frameCount - 1;                 
            }
            else if (this->mode == ANIMATION_MODE_PINGPONG)
            {
                if (!this->reverse)
                {
                    this->direction = 0;
                    this->currentFrame = 0;
                    break;
                }
                else
                {
                    this->currentFrame = 0;
                    this->direction = 1;
                }
            }
            else if (this->mode == ANIMATION_MODE_PINGPONGLOOP)
            {
                this->currentFrame = 0;
                this->direction = 1;
            }
            else
            {
                this->direction = 0;
                this->currentFrame = 0;
                break;
            }
        }
    }      
    return this->images[this->currentFrame];
}
  

