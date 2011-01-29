
template <typename T>
InterpolatedValue<T>::InterpolatedValue(const Interpolation* inter) :
    inter(inter)
{
    if (inter == NULL)
        inter = &interpolation_default;
}

template <typename T>
MovingValue<T>::MovingValue(Time startTime, T startVal, T goalVal, Time duration, const Interpolation* inter) : InterpolatedValue<T>(inter), startTime(startTime), startVal(startVal), goalVal(goalVal), goalTime(startTime + duration)
{

}


template <typename T>
T MovingValue<T>::getVal(Time time)
{
    float progress = this->inter->getProgress(this->startTime, this->goalTime, time);
    return startVal + (goalVal - startVal) * progress;
}

template <typename T>
WaypointedValue<T>::WaypointedValue(Interpolation* inter) : InterpolatedValue<T>(inter)
{
    
}

template <typename T>
T WaypointedValue<T>::getVal(Time time)
{

}

template <typename T>
void WaypointedValue<T>::addWaypoint(T val, Time time)
{

}

template <typename T>
void WaypointedValue<T>::clearWaypoints()
{

}

template <typename T>
SplinedValue<T>::SplinedValue(Interpolation* inter) : WaypointedValue<T>(inter)
{

}

template <typename T>
T SplinedValue<T>::getVal(Time time)
{

}









