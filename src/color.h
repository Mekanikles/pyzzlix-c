#ifndef _COLOR_H
#define _COLOR_H

struct Color
{
        double r;
        double g;
        double b;
        double a;
        
        Color(double r, double g, double b, double a):
            r(r), g(g), b(b), a(a)
        {
        }
        
        Color operator*(const double d)
        {
            return Color(this->r * d, this->g * d, this->b * d, this->a * d);       
        }
        
};

#endif
