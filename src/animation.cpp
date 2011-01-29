#include "animation.h"

#include "resources.h"
#include "interpolation.h"

Animation::Animation(FrameSet* frameSet, Time startTime, Time duration, const Interpolation* inter) : 
                    frameSet(frameSet), startTime(startTime), stopTime(startTime + duration), inter(inter)
{
    this->frameTimer = 0.0;
    this->frameIndex = 0;
    
    if (this->inter == NULL)
        this->inter = &interpolation_default;
}

Animation::~Animation()
{
}


Image* Animation::getFrameImage(Time currentTime)
{
    if (this->frameSet->frameCount <= 0)
        return NULL;
    
    float progress = this->inter->getProgress(this->startTime, this->stopTime, currentTime);

    if (progress <= this->frameSet->getFrame(0)->length)
    {
        this->frameIndex = 0;
        this->frameTimer = 0.0;
        return this->frameSet->getFrame(0)->image;
    }
    else if (progress >= 1.0 - this->frameSet->getFrame(this->frameSet->getFrameCount() - 1)->length)
    {
        this->frameIndex = this->frameSet->getFrameCount() - 1;
        this->frameTimer = 1.0 - this->frameSet->getFrame(this->frameIndex)->length;
        return this->frameSet->getFrame(this->frameIndex)->image;
    }

    if (progress >= this->frameTimer)
    {
        // Search forward
        while (this->frameTimer + this->frameSet->getFrame(this->frameIndex)->length < progress)
        {
            this->frameTimer += this->frameSet->getFrame(this->frameIndex)->length;
            this->frameIndex++;
        }
    }
    else
    {
        // Search backward
        while (this->frameTimer > progress)
        {
            this->frameIndex--;
            this->frameTimer -= this->frameSet->getFrame(frameIndex)->length;
        }
    }
 
    return this->frameSet->getFrame(this->frameIndex)->image;
}
  

