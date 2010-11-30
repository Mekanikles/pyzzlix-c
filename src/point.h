#ifndef _POINT_H
#define _POINT_H

#include "vector.h"

struct Point : public Vector
{

    Point():
        Vector(0, 0)
    {
    }

    Point(double x, double y):
        Vector(x, y)
    {
    }

    Point operator+(const Vector& v)
    {
        return Point(this->x + v.x, this->y + v.y);       
    }
    Point operator-(const Vector& v)
    {
        return Point(this->x - v.x, this->y - v.y);       
    }
    Vector operator-(const Point& p)
    {
        return Vector(this->x - p.x, this->y - p.y);       
    }



};

#endif
