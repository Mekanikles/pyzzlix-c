#ifndef _FRAMESET_H
#define _FRAMESET_H

#include "image.h"
#include "time.h"


class FrameSet
{
public:
    struct Frame
    {
        Frame() : image(NULL), length(0.0) {}
        Frame(Image* image, Time length): image(image), length(length) {}
        Image* image;
        Time length;
    };

    Frame* frames;
    int frameCount;
    
    FrameSet(const string& texturename, int width = 0, int height = 0,
            int srcx = 0, int srcy = 0, int srcw = 0, int srch = 0);
    ~FrameSet();
    
    void normalizeFrames();
    int getFrameCount();
    Frame* getFrame(int index); 
};

#endif