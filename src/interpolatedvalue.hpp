
template <typename T>
InterpolatedValue<T>::InterpolatedValue()
{
}

template <typename T>
InterpolatedValue<T>::InterpolatedValue(const T& val):
    oldVal(val), newVal(val)
{
}

template <typename T>
T InterpolatedValue<T>::getVal()
{
    return this->newVal;
}

template <typename T>
T InterpolatedValue<T>::calcVal(float factor)
{
    return this->newVal - (this->newVal - this->oldVal) * (1.0 - factor);
}

template <typename T>
void InterpolatedValue<T>::setTo(T val)
{
    this->oldVal = this->newVal;
    this->newVal = val;
}

template <typename T>
void InterpolatedValue<T>::forceTo(T val)
{
    this->oldVal = val;
    this->newVal = val;
}

template <typename T>
void InterpolatedValue<T>::setOldVal(T val)
{
    this->oldVal = val;
}

template <typename T>
void InterpolatedValue<T>::setNewVal(T val)
{
    this->newVal = val;
}

template <typename T>
void InterpolatedValue<T>::addWaypoint(T val, Time time)
{


}

template <typename T>
void InterpolatedValue<T>::clearWaypoints()
{


}
