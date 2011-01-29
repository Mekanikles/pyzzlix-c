#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "time.h"
#include "constants.h"

#include <string>
using namespace std;

#include "frameset.h"

class Image;
class Interpolation;

class Animation
{
    public:
        FrameSet* frameSet;
        Time startTime;
        Time stopTime;
        const Interpolation* inter;
        Time frameTimer;
        int frameIndex;
        
        Animation(FrameSet* frameSet, Time startTime, Time duration, const Interpolation* inter = NULL);
        ~Animation();

        Image* getFrameImage(Time currentTime);        
};

#endif


