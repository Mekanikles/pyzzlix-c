#ifndef _ANIMATION_H
#define _ANIMATION_H

#include "time.h"
#include "constants.h"

#include <string>
using namespace std;

const int ANIMATION_MODE_NORMAL = 0;
const int ANIMATION_MODE_LOOP = 1;
const int ANIMATION_MODE_PINGPONG = 2;
const int ANIMATION_MODE_PINGPONGLOOP = 3;

class Texture;
class Image;

class Animation
{
    public:
        Animation(const string& texturename, int width = 0, int height = 0,
            int srcx = 0, int srcy = 0, int srcw = 0, int srch = 0, Time frameLength = 0.1,
            int mode = ANIMATION_MODE_LOOP, bool reverse = false);
        
        ~Animation();
        
        void reset(Time currentTime);
        Image* getFrameImage(Time currentTime);
        
        Image** images;
        Time* frameLengths;
        int mode;
        bool reverse;
        Time frameTimer;
        int frameCount;
        int direction;
        int currentFrame;
        
};

#endif


