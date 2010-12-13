#ifndef _VECTOR_H
#define _VECTOR_H

class Point;

struct Vector
{
        double x;
        double y;

        Vector():
            x(0.0), y(0.0)
        {
        }
        
        Vector(double x, double y):
            x(x), y(y)
        {
        }
        
        Vector operator*(const double d)
        {
            return Vector(this->x * d, this->y * d);       
        }
        Vector operator+(const Vector& v)
        {
            return Vector(this->x + v.x, this->y + v.y);       
        }
        Vector operator-(const Vector& v)
        {
            return Vector(this->x - v.x, this->y - v.y);       
    }
        
        
};

#endif
