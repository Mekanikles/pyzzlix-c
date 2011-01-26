#ifndef _MOVER_H
#define _MOVER_H

#include "time.h"
#include "movebehaviour.h"

#include "interpolatedvalue.h"

template <typename T>
class Mover
{
    public:
        MoveBehaviour* behaviour;
        InterpolatedValue<T>* variable;

        Time startTime;
        T startVal;
        Time goalTime;
        T goalVal;

        Mover(MoveBehaviour* behaviour, InterpolatedValue<T>* variable, Time currentTime, T goalVal, Time duration);

        void updateValue(Time currentTime);
};

#include "mover.hpp"

#endif
