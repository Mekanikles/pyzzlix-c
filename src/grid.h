#ifndef _GRID_H
#define _GRID_H

template <class T>
class Grid
{
    public:
        
        T** array;
        int sizex;
        int sizey;
        int xoffset;
        int yoffset;
        
        Grid(int sizex, int sizey, int xoffset = 0, int yoffset = 0);
        virtual ~Grid();

        void set(int x, int y, T* item);
        T* remove(int x, int y);
        T* get(int x, int y);
        void clear();
};

#include "grid.hpp"

#endif
