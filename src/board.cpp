#include "board.h"

#include "point.h"

#include <stdio.h>

static double _triangleArea(Point* a, Point* b, Point* c)
{  
    return (b->x - a->x) * (c->y - a->y) - (c->x - a->x) * (b->y - a->y);
}

static double _polygonArea(LinkedList<LinkNode<Point> >* points)
{
    LinkNode<Point>* first = points->first;
    LinkNode<Point>* prev = first->next;
    LinkNode<Point>* next = prev->next;
    double area = 0;

    while(next != 0)
    {        
        area += _triangleArea(first->item, prev->item, next->item);

        prev = next;
        next = next->next;
    }
    
    return area;
}

Board::Board() : Sprite()
{
}

/*virtual*/ Board::~Board()
{
    fprintf(stderr, "ran destructor!\n");
}
