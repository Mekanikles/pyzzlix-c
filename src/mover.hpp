
template <typename T>
Mover<T>::Mover(MoveBehaviour* behaviour, InterpolatedValue<T>* variable, Time currentTime, T goalVal, Time duration)
    : behaviour(behaviour), variable(variable), startTime(currentTime), startVal(variable->getVal()), goalTime(currentTime + duration), goalVal(goalVal)
{
}

template <typename T>
void Mover<T>::updateValue(Time currentTime)
{
    float progress = this->behaviour->getProgress(this->startTime, this->goalTime, currentTime);
    this->variable->setTo(this->startVal + (this->goalVal - this->startVal) * progress);
}
