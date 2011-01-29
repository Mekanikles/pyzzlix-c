#ifndef _INTERPOLATEDVALUE_H
#define _INTERPOLATEDVALUE_H

#include "time.h"
#include "linkedlist.h"

#include "interpolation.h"

template <typename T>
class InterpolatedValue
{
    public:
        Interpolation* inter;

        InterpolatedValue(Interpolation* inter);
        virtual T getVal(Time time) = 0;
};

template <typename T>
class MovingValue : public InterpolatedValue<T>
{
    public:
        Time startTime;
        T startVal;
        T goalVal;
        Time goalTime;
        MovingValue(Time startTime, T startVal, T goalVal, Time duration = 0.0, Interpolation* inter = NULL);
        T getVal(Time time);
};


template <typename T>
class WaypointedValue : public InterpolatedValue<T>
{
    protected:
        template<typename S>
        struct TimedValue : Linkable< TimedValue<S> >
        {
                Time time;
                S val;
        };
        
    public:
        
        FastLinkedList< TimedValue<T> > waypoints;

        WaypointedValue(Interpolation* inter);
        T getVal(Time time);
        void addWaypoint(T val, Time time);
        void clearWaypoints();
};

template <typename T>
class SplinedValue : public WaypointedValue<T>
{
    public:
        SplinedValue(Interpolation* inter);
        T getVal(Time time);
};

#include "interpolatedvalue.hpp"



#endif
