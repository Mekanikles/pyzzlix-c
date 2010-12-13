#ifndef _COLOR_H
#define _COLOR_H

struct Color
{
        double r;
        double g;
        double b;
        double a;

        Color():
            r(0), g(0), b(0), a(0)
        {
         
        }
        
        Color(double r, double g, double b, double a):
            r(r), g(g), b(b), a(a)
        {
        }
        
        Color operator*(const double d)
        {
            return Color(this->r * d, this->g * d, this->b * d, this->a * d);       
        }

        Color operator+(const Color& c)
        {
            return Color(this->r + c.r, this->g + c.g, this->b + c.b, this->a + c.a);       
        }
        Color operator-(const Color& c)
        {
            return Color(this->r - c.r, this->g - c.g, this->b - c.b, this->a - c.a);       
        }
        

        
};

#endif
