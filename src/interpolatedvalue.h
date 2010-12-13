#ifndef _INTERPOLATEDVALUE_H
#define _INTERPOLATEDVALUE_H

#include "time.h"

template <typename T>
class InterpolatedValue
{
    private:
        T val;
        Time time;
        T refval;
        Time reftime;

        void calcVal(Time currentTime);
    public:

        T getVal(Time currentTime);
        void setVal(T val, Time currentTime, Time duration = 0.0);
        void changeVal(T val, Time currentTime, Time duration = 0.0);
};

#include "interpolatedvalue.hpp"



#endif
