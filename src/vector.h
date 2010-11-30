#ifndef _VECTOR_H
#define _VECTOR_H

#include "linkedlist.h"

class Point;

struct Vector
{
    double x;
    double y;


    Vector(double x, double y):
        x(x), y(y)
    {
    }

    Vector operator*(const double d)
    {
        return Vector(this->x * d, this->y * d);       
    }

};

#endif
