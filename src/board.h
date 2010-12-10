
#ifndef _BOARD_H
#define _BOARD_H

#include "sprite.h"

#include "grid.h"

#include "color.h"
#include "time.h"

class Scene;
class Sprite;
class Marker;
class Block;

class Board : public Sprite
{
        Grid<Block> grid;
        int width;
        int height;

        Sprite* background;
        Sprite* blockcontainer;
        Sprite* border;
        Sprite* glow;
        Marker* marker;

        bool blocksFalling;
        Color glowColor;
        Time glowDuration;
        bool gameOver;

        LinkedList<Sprite> lastRotated;
        
    public:
        Board(int width, int height);
        virtual ~Board();

        void reset();
        void clear(int x, int y);
        
};

#endif
