#ifndef _GRID_H
#define _GRID_H

template <class T>
class Grid
{
    public:
        
        T** array;
        int sizex;
        int sizey;
        
        Grid(int sizex, int sizey);
        virtual ~Grid();

        void set(int x, int y, T* item);
        T* remove(int x, int y);
        T* get(int x, int y);
        void clear();
};

#include "grid.hpp"

#endif
