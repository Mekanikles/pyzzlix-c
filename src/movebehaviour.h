#ifndef _MOVEBEHAVIOUR_H
#define _MOVEBEHAVIOUR_H

#include "time.h"

const int MOVEBEHAVIOUR_MODE_NORMAL = 0;
const int MOVEBEHAVIOUR_MODE_LOOP = 1;
const int MOVEBEHAVIOUR_MODE_PINGPONG = 2;


class MoveBehaviour
{
    public:
        int mode;
        float calcProgress(Time startTime, Time goalTime, Time currentTime);
        
        MoveBehaviour() : mode(MOVEBEHAVIOUR_MODE_NORMAL) {}
        void setMode(int mode);
        virtual float getProgress(Time startTime, Time goalTime, Time currentTime);
};

class MoveBehaviour_Accelerator : public MoveBehaviour
{
        float factor;

    public:
        
        MoveBehaviour_Accelerator(float factor);
        float getProgress(Time startTime, Time goalTime, Time currentTime);
};

class MoveBehaviour_Decelerator : public MoveBehaviour
{
        float factor;
        
    public:
        
        MoveBehaviour_Decelerator(float factor);
        float getProgress(Time startTime, Time goalTime, Time currentTime);
};


#endif
