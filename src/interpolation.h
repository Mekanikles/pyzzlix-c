#ifndef _INTERPOLATION_H
#define _INTERPOLATION_H

#include "time.h"

const int INTERPOLATION_MODE_NORMAL = 0;
const int INTERPOLATION_MODE_LOOP = 1;
const int INTERPOLATION_MODE_PINGPONG = 2;

class Interpolation
{
    public:
        int mode;
        float calcProgress(Time startTime, Time goalTime, Time currentTime) const;
        
        Interpolation() : mode(INTERPOLATION_MODE_NORMAL) {}
        void setMode(int mode);
        virtual float getProgress(Time startTime, Time goalTime, Time currentTime) const = 0;
};

class Interpolation_Linear : public Interpolation
{
    public:       
        Interpolation_Linear();
        float getProgress(Time startTime, Time goalTime, Time currentTime) const;
};

class Interpolation_Accelerated : public Interpolation
{
    public:
        
        Interpolation_Accelerated();
        float getProgress(Time startTime, Time goalTime, Time currentTime) const;
};

class Interpolation_Decelerated : public Interpolation
{       
    public:
        
        Interpolation_Decelerated();
        float getProgress(Time startTime, Time goalTime, Time currentTime) const;
};

class Interpolation_Hybrid : public Interpolation
{       
    public:
        
        Interpolation_Hybrid();
        float getProgress(Time startTime, Time goalTime, Time currentTime) const;
};

extern const Interpolation_Linear interpolation_default;

#endif
