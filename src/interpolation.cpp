#include "interpolation.h"

#include "math.h"
#include "stdio.h"

const Interpolation_Linear interpolation_default;

float Interpolation::calcProgress(Time startTime, Time goalTime, Time currentTime) const
{
    Time length = (goalTime - startTime);
    
    switch(this->mode)
        {
        case INTERPOLATION_MODE_LOOP:
            currentTime = (currentTime - startTime);
            return (currentTime - ((int)(currentTime / length)) * length) / length;
            break;
        case INTERPOLATION_MODE_PINGPONG:
        {
            currentTime = (currentTime - startTime);
            int wraps = ((int)(currentTime / length));
            int even = wraps % 2;
            float result = (even) - (-1 + even * 2) * ((currentTime - (wraps * length)) / length);

            if (result < 0.0 || result > 1.0)
                fprintf(stderr, "Result: %f\n", result);
            return result;
            break;
        }
        default:
            if (currentTime <= startTime)
                return 0.0;
            if (currentTime >= goalTime)
                return 1.0;
            return (currentTime - startTime) / length;
            break;
    }

    return 1.0;
}

void Interpolation::setMode(int mode)
{
    switch(mode)
    {
        case INTERPOLATION_MODE_LOOP:
            this->mode = mode;
            break;
        case INTERPOLATION_MODE_PINGPONG:
            this->mode = mode;
            break;
        default:
            this->mode = INTERPOLATION_MODE_NORMAL;
            break;
    }
}

Interpolation_Linear::Interpolation_Linear() : Interpolation()
{
}

Interpolation_Accelerated::Interpolation_Accelerated() : Interpolation()
{
}

Interpolation_Decelerated::Interpolation_Decelerated() : Interpolation()
{
}

Interpolation_Hybrid::Interpolation_Hybrid() : Interpolation()
{
}

float Interpolation_Linear::getProgress(Time startTime, Time goalTime, Time currentTime) const
{
    return calcProgress(startTime, goalTime, currentTime);
};


float Interpolation_Accelerated::getProgress(Time startTime, Time goalTime, Time currentTime) const
{
    return pow(this->calcProgress(startTime, goalTime, currentTime), 2);
};

float Interpolation_Decelerated::getProgress(Time startTime, Time goalTime, Time currentTime) const
{
    return -1.0 * pow(1.0 - this->calcProgress(startTime, goalTime, currentTime), 2) + 1.0;
};


float Interpolation_Hybrid::getProgress(Time startTime, Time goalTime, Time currentTime) const
{
    float progress = this->calcProgress(startTime, goalTime, currentTime);

    if (progress <= 0.5f)
        return (pow(progress * 2, 2) * 0.5);
    else
        return (pow((1.0 - progress) * 2, 2) * -0.5) + 1.0;     
};
