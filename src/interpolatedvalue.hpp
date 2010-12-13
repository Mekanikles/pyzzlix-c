
template <typename T>
InterpolatedValue<T>::InterpolatedValue():
    time(0.0), reftime(0.0)
{
}

template <typename T>
void InterpolatedValue<T>::calcVal(Time currentTime)
{
    if (currentTime <= this->time)
        return;
    
    if (currentTime >= this->reftime)
    {
        this->val = this->refval;
        this->time = currentTime;
    }
    else
    {
        double factorT = (this->reftime - currentTime) / (this->reftime - this->time);
        this->val = this->refval - (this->refval - this->val) * factorT;
        this->time = currentTime;
    }
}

template <typename T>
T InterpolatedValue<T>::getVal(Time currentTime)
{
    this->calcVal(currentTime);
    return this->val;
}

template <typename T>
void InterpolatedValue<T>::setVal(T val, Time currentTime, Time duration)
{
    if (duration == 0.0)
    {
        this->refval = val;
        this->val = val;
        this->reftime = currentTime;
    }
    else
    {
        this->calcVal(currentTime);
        this->refval = val;
        this->reftime = currentTime + duration;
    }
}

template <typename T>
void InterpolatedValue<T>::changeVal(T val, Time currentTime, Time duration)
{
    this->calcVal(currentTime);
    this->refval = this->val + val;
    this->reftime = currentTime + duration;
}
