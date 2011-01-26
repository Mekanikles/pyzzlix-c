#ifndef _INTERPOLATEDVALUE_H
#define _INTERPOLATEDVALUE_H

#include "time.h"
#include "linkedlist.h"




template <typename T>
class InterpolatedValue
{
    public:
        T oldVal;
        T newVal;
        
        LinkedList<T> waypoints;

        InterpolatedValue();
        InterpolatedValue(const T& val);
        T getVal();
        T calcVal(float factor);
        void setTo(T val);
        void forceTo(T val);
        void setOldVal(T val);
        void setNewVal(T val);
        void addWaypoint(T val, Time time);
        void clearWaypoints();
};

#include "interpolatedvalue.hpp"



#endif
