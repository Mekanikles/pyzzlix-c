#include "movebehaviour.h"

#include "math.h"

float MoveBehaviour::calcProgress(Time startTime, Time goalTime, Time currentTime)
{
    Time length = (goalTime - startTime);
    
    switch(this->mode)
        {
        case MOVEBEHAVIOUR_MODE_LOOP:
            currentTime = (currentTime - startTime);
            return currentTime - ((int)(currentTime / length)) * length;
            break;
        case MOVEBEHAVIOUR_MODE_PINGPONG:
            currentTime = (currentTime - startTime);

            // Wrong, just placeholder
            return currentTime - ((int)(currentTime / length)) * length;
            this->mode = mode;
            break;
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

void MoveBehaviour::setMode(int mode)
{
    switch(mode)
    {
        case MOVEBEHAVIOUR_MODE_LOOP:
            this->mode = mode;
            break;
        case MOVEBEHAVIOUR_MODE_PINGPONG:
            this->mode = mode;
            break;
        default:
            this->mode = MOVEBEHAVIOUR_MODE_NORMAL;
            break;
    }
}

float MoveBehaviour::getProgress(Time startTime, Time goalTime, Time currentTime)
{
    return calcProgress(startTime, goalTime, currentTime);
};

MoveBehaviour_Accelerator::MoveBehaviour_Accelerator(float factor) : MoveBehaviour(), factor(factor)
{
    if (this->factor < 1.0)
        this->factor = 1.0;
}

MoveBehaviour_Decelerator::MoveBehaviour_Decelerator(float factor) : MoveBehaviour(), factor(factor)
{
    if (this->factor < 1.0)
        this->factor = 1.0;
}

float MoveBehaviour_Accelerator::getProgress(Time startTime, Time goalTime, Time currentTime)
{
    return pow(this->calcProgress(startTime, goalTime, currentTime), this->factor);
};

float MoveBehaviour_Decelerator::getProgress(Time startTime, Time goalTime, Time currentTime)
{
    return pow(this->calcProgress(startTime, goalTime, currentTime), 1.0/this->factor);
};
