
#ifndef _BOARD_H
#define _BOARD_H

#include "sprite.h"

#include "grid.h"

#include "color.h"
#include "time.h"

#include "block.h"

class Scene;
class Sprite;
class Marker;


class Board : public Sprite
{
    public:
        Grid<Block> grid;

        Sprite* background;
        Sprite* blockContainer;
        Sprite* border;
        Sprite* glow;
        Marker* marker;

        bool blocksFalling;
        Color glowColor;
        Time glowDuration;
        bool gameOver;

        LinkedList<Sprite*> lastRotated;

        int blockTypeArray[MAX_BLOCKTYPES];
        int blockTypes;

        float gridSlotSize;

        int width;
        int height;
        
        Board(int width, int height);
        virtual ~Board();

        void moveBlockToCoord(Block* block, int boardx, int boardy);
        void setBlockToCoord(Block* block, int boardx, int boardy);
        void moveMarkerToCoord(int boardx, int boardy);
        void setMarkerToCoord(int boardx, int boardy);


        void moveMarker(int dx, int dy);
        bool rotateMarker(int direction);

        bool rotateBlocks(int x, int y, int direction, int radius);
        
        int getRandomBlockType();
        void clearBlockTypes();
        void setBlockType(int type, bool enabled = true);

        
        void reset();
        void clear(int x, int y);
        void fillBuffer();
        bool full();
        void addBlock(Block* block);        
};

#endif
