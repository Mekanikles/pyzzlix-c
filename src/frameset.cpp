#include "frameset.h"
#include "resources.h"


FrameSet::FrameSet(const string& texturename, int width, int height,
                   int srcx, int srcy, int srcw, int srch)
{
    
    Image** images = Resources::getInstance()->getImageSheet(&this->frameCount,
                    texturename, width, height, srcx, srcy, srcw, srch);
    
    if (this->frameCount)
    {
        this->frames = new Frame[this->frameCount];
        for (int i = 0; i < this->frameCount; i++)
        {
            this->frames[i] = Frame(images[i], 1.0);
        }
    }
    else
    {
        this->frames = NULL;
        this->frameCount = 0;
    }
    
    this->normalizeFrames();
}
    
FrameSet::~FrameSet()
{
    if (this->frames != NULL && this->frameCount > 0)
    {
        for(int i = 0; i < this->frameCount; i++)
        {   
            delete this->frames[i].image;
        }
        delete[] this->frames;
    }
}

void FrameSet::normalizeFrames()
{   
    if (this->frames == NULL || this->frameCount <= 0)
        return;

    Time totalLength = 0.0;
    for (int i = 0; i < this->frameCount; i++)
    {
        totalLength += this->frames[i].length;
    }
    
    for (int i = 0; i < this->frameCount; i++)
    {
        this->frames[i].length = this->frames[i].length / totalLength;
    }   
}

int FrameSet::getFrameCount()
{
    return this->frameCount;
}
    
FrameSet::Frame* FrameSet::getFrame(int index)
{   
    if (index >= 0 && index < this->frameCount)
        return &this->frames[index];
    else    
        return NULL;
}
