
#ifndef _BOARD_H
#define _BOARD_H

#include "scenehandler.h"

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
        
        LinkedList< LinkedList<Block*> > foundCircles;
    
        int blockTypeArray[MAX_BLOCKTYPES];
        int blockTypes;

        float gridSlotSize;

        int width;
        int height;
        
        Board(int width, int height);
        virtual ~Board();

        void moveBlockInGrid(Block* block, int boardx, int boardy);
        void setBlockInGrid(Block* block, int boardx, int boardy);
        void moveMarkerInGrid(int boardx, int boardy);
        void setMarkerInGrid(int boardx, int boardy);


        void moveMarker(int dx, int dy);
        bool rotateMarker(int direction);
        void handleCircle(LinkedList<Block*> circle, LinkedList<Block*>* blocks);
        void findCircles(Block* startBlocks);
        bool rotateBlocks(int x, int y, int direction, int radius);
        
        int getRandomBlockType();
        void clearBlockTypes();
        void setBlockType(int type, bool enabled = true);

        
        void reset();
        void clear(int x, int y);
        void fillBuffer();
        bool full();
        void addBlock(Block* block);

        void updateBoard();
};

#endif
