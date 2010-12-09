#include "board.h"

#include "point.h"

#include <stdio.h>

static double triangleArea(Point* a, Point* b, Point* c)
{  
    return (b->x - a->x) * (c->y - a->y) - (c->x - a->x) * (b->y - a->y);
}

static double polygonArea(LinkedList<LinkNode<Point> >* points)
{
    LinkNode<Point>* first = points->first;
    LinkNode<Point>* prev = first->next;
    LinkNode<Point>* next = prev->next;
    double area = 0;

    while(next != 0)
    {        
        area += triangleArea(first->item, prev->item, next->item);

        prev = next;
        next = next->next;
    }
    
    return area;
}

Board::Board(int width, int height) : Sprite(),
                                      grid(width, 2 * height),
                                      width(width),
                                      height(height),
                                      blocksFalling(false),
                                      glowColor(0.0, 0.0, 0.0, 0.0),
                                      glowDuration(0.0)
{
    this->reset();
    
    this->background = new Sprite();
    this->background->setImage(loadImage("pixel", 1, 1));
    this->background->setScale(Point(160.0, 208.0));
    this->background->setColor(Color(0.0, 0.0, 0.0, 0.3));
    this->background->setPos(Point(8.0, 16.0));
        
    this->blockcontainer = new Sprite();
    this->blockcontainer->setPos(Point(8.0, 16.0));
    
    this->border = new Sprite();
    this->border.setImage(loadImage("windowframes.png", 24, 0, 176, 232));
    this->border.setPos(Point(0.0,0.0));
        
    this->glow = new Sprite();
    this->glow.setImage(loadImage("windowglows.png", 24, 0, 176, 232));
    this->glow.setPos(Point(0.0, 0.0));
    this->glow.setCol(Color(0.0, 0.0, 0.0, 0.0));
        
    this->marker = new Marker();
    this->marker->offset_x = this->blocks->pos.x;
    this->marker->offset_y = this->blocks->pos.y;
    this->marker->moveToBoardCoord(2, 14, this->currentTime);
        
    this->subSprites.addItem(this->background);
    this->subSprites.addItem(this->blockcontainer);
    this->subSprites.addItem(this->marker);
    this->subSprites.addItem(this->border);
    this->subSprites.addItem(this->glow);
}

/*virtual*/ Board::~Board()
{
    //fprintf(stderr, "ran destructor!\n");
}

void Board::reset()
{
    this->grid.clear();
    this->blockcontainer->subSprites.destroy();

    this->lastRotated.release();
}

void Board::clear(int x, int y)
{
    Block* block = this->grid.remove(x, y);
    delete block;
}
