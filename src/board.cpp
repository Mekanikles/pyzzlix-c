#include "board.h"

#include "point.h"

#include <stdio.h>
#include <stdlib.h>

#include "resources.h"
#include "marker.h"
#include "block.h"

static double triangleArea(const Point& a, const Point& b, const Point& c)
{  
    return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

static double polygonArea(LinkedList<Point>* points)
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
                                      blocksFalling(false),
                                      glowColor(1.0, 0.0, 0.0, 1.0),
                                      glowDuration(0.0),
                                      gridSlotSize(16),
                                      width(width),
                                      height(height)
                                      
{   
    this->background = new Sprite();
    this->background->setImage(Resources::getInstance()->getImage("pixel", 1, 1));
    // this->background->scaleTo(Vector(160.0, 208.0));
    this->background->fadeTo(Color(0.0, 0.0, 0.0, 0.3));
    this->background->moveTo(Point(0.0, 0.0));
        
    this->blockContainer = new Sprite();
    this->blockContainer->moveTo(Point(0.0, 0.0));
    
    this->border = new Sprite();
    this->border->setImage(Resources::getInstance()->getImage("windowframes", 24, 0, 176, 232));
    this->border->moveTo(Point(-8.0, -16.0));
        
    this->glow = new Sprite();
    this->glow->setImage(Resources::getInstance()->getImage("windowglows", 24, 0, 176, 232));
    this->glow->moveTo(Point(0.0, 0.0));
    this->glow->fadeTo(Color(0.0, 0.0, 0.0, 0.0));
        
    this->marker = new Marker();
    this->setMarkerToCoord(this->width / 2, this->height / 2);
        
    this->addSprite(this->background);
    this->addSprite(this->marker);
    this->addSprite(this->blockContainer);
    this->addSprite(this->border);
    this->addSprite(this->glow);

    this->reset();

    fprintf(stderr, "Board (%i, %i) created.\n", this->width, this->height);
}

Board::~Board()
{
    //fprintf(stderr, "ran destructor!\n");
}

void Board::moveBlockToCoord(Block* block, int boardx, int boardy)
{
    block->boardx = boardx;
    block->boardy = boardy;
    block->moveTo(Point((boardx + 0.5f) * this->gridSlotSize,
                        (boardy + 0.5f) * this->gridSlotSize), 0.15);    
}

void Board::setBlockToCoord(Block* block, int boardx, int boardy)
{
    block->boardx = boardx;
    block->boardy = boardy;
    block->moveTo(Point((boardx + 0.5f) * this->gridSlotSize,
                        (boardy + 0.5f) * this->gridSlotSize));    
}

void Board::moveMarkerToCoord(int boardx, int boardy)
{
    this->marker->boardx = boardx;
    this->marker->boardy = boardy;
     
    this->marker->moveTo(Point(boardx * this->gridSlotSize,
                         boardy * this->gridSlotSize), 0.032);
}

void Board::setMarkerToCoord(int boardx, int boardy)
{   
    this->marker->boardx = boardx;
    this->marker->boardy = boardy;
     
    this->marker->moveTo(Point(boardx * this->gridSlotSize,
                         boardy * this->gridSlotSize));
}


void Board::moveMarker(int dx, int dy)
{
    if (this->marker->boardx + dx >= this->width || this->marker->boardx + dx <= 0)
        dx = 0;
    
    if (this->marker->boardy + dy >= this->height || this->marker->boardy + dy <= 0)
        dy = 0;
    
    if (dx != 0 || dy != 0)
    {
        this->moveMarkerToCoord(this->marker->boardx + dx,
                            this->marker->boardy + dy);
        
        //mixer.playSound(self.movesound)
    }
}
    

bool Board::rotateMarker(int direction)
{
    return rotateBlocks(this->marker->boardx, this->marker->boardy, direction, 1);
}

void Board::findCircles(LinkedList<Block*>* startBlocks)
{
    static struct Finder
    {
            int width, height;
            Grid* grid;
            Finder(int width, int height, Grid* grid) : width(width), height(height), grid(grid) {}
            
            Block* getNeighbor(Block* block, int x, int y)
            {
                if (block == NULL)
                    return NULL;
                x = block->boardx + x;
                y = block->boardy + y;
                if (x < 0 || x >= this->width || y < 0 || y >= this->height)
                    return NULL;
                return grid->get(x, y);
            }
            
            void searchPath(Block* block, Block* start, LinkedList<Block*>* path, LinkedList< LinkedList<Block*>* >* circles)
            {
                if (block->status & STATUS_MOVING || block->status & STATUS_ON_CIRCLE || block->status & STATUS_OFFSCREEN || block->status & STATUS_ON_PATH)
                    return;

                // Mark the picked block and pick it
                block->status |= STATUS_ON_PATH;
                path->addItem(block);
                
                // If we found the way back to the start, save the path
                if (path->getLength() >= 4 && block == start)
                {
                    circles->addItem(path->copy());
                    block->status &= !STATUS_ON_PATH;
                    return;
                }

                Block* lastBlock = path->getFirst();
                Block* nextBlock;

                nextBlock == this->getNeighbor(block, 0, 1);
                if (nextBlock != lastBlock && nextBlock != NULL && nextBlock->type == start->type)
                    finder(nextBlock, start, path, circles);
                
                nextBlock == this->getNeighbor(block, 1, 0);
                if (nextBlock != lastBlock && nextBlock != NULL)
                    finder(nextBlock, start, path, circles);

                nextBlock == this->getNeighbor(block, -1, 0);
                if (nextBlock != lastBlock && nextBlock != NULL)
                    finder(nextBlock, start, path, circles);

                nextBlock == this->getNeighbor(block, 0, -1);
                if (nextBlock != lastBlock && nextBlock != NULL)
                    finder(nextBlock, start, path, circles);

                // The current block is no longer considered picked
                block->status &= !STATUS_ON_PATH;
                path->
            }
    } finder(this->width, this->height, this->grid);


    LinkedList< LinkedList<Block*>* > foundCircles;
    
    
    // Go through all start blocks
    // Find all complete circle paths from each block
    LinkIterator<Block*> iter = startBlocks->getHeadIterator();
    while(!iter.isAtEnd())
    {
        LinkedList< LinkedList<Block*>* > circles;
        LinkedList<Block*> workingPath;
        
        finder.searchPath(iter.item(), iter.item(), workingPath, circles);

        workPath.clear();
        
        if (circles.length > 0)
        {
            // For each circle path, save the longest
            LinkIterator< LinkedList<Block*>* > iter = circles->getHeadIterator();
            LinkedList<Block*>* longestCircle = iter.item;
            iter.forward();
            while(!iter.isAtEnd())
            {
                if (iter.item->getLength() > longestCircle->getLength())
                {
                    longestCircle = iter.item;
                }
                
                iter.forward();
            }

            foundCircles->addItem(iter.item->copy());
        }
        
        circles.clear();
    }
    


    
    
    /*
        if rotation_circles or fall_circles:
            pygame.event.post(pygame.event.Event(EVENT_CIRCLE_FOUND, fall_blocks=fall_circles, rotation_blocks=rotation_circles))
            return True
            */
    return foundCircles;
}

bool Board::rotateBlocks(int x, int y, int direction, int radius)
{
    struct Coord
    {
            int x, y;
            Coord(int x, int y): x(x), y(y) {}
            Coord() : x(0), y(0) {}
    };
    
    struct CoordFactory
    {
            int width, height;
            CoordFactory(int width, int height):
                width(width), height(height) {}
            Coord coord(int x, int y) {
                return Coord((x + this->width) % this->width,
                             (y + this->height) % this->height); }
    } cf(this->width, this->height);

    // Cannot rotate radius < 1
    if (radius < 1)
        return false;

    // Create a number of orbits equal to the radius
    Coord** orbits = new Coord*[radius];
    // Calculate length of each orbit and create space
    for (int orbit = 1; orbit <= radius; orbit++)
    {
        orbits[orbit - 1] = new Coord[orbit * 4 + (orbit - 1) * 4];
        
    }
     
    //Fill each orbit with block position data, clockwise
    for (int orbit = 1; orbit <= radius; orbit++)
    {
        int offset = 0;
        // Top row, from top left block
        for (int j = 0; j < orbit * 2; j++)
        {
            orbits[orbit - 1][j + offset] = cf.coord(x - orbit + j, y - orbit); 
        }
        offset += orbit * 2;
        // Right row, from top right block
        // Do not count corner blocks
        for (int j = 0; j < (orbit - 1) * 2; j++)
        {
            orbits[orbit - 1][j + offset] = cf.coord(x + orbit - 1, y - orbit + 1 + j); 
        }
        offset += (orbit - 1) * 2;
        // Bottom row, from bottom right block
        for (int j = 0; j < orbit * 2; j++)
        {
            orbits[orbit - 1][j + offset] = cf.coord(x + orbit - 1 - j, y + orbit - 1); 
        }
        offset += orbit * 2;
        // Left row, from bottom left block
        // Do not count corner blocks
        for (int j = 0; j < (orbit - 1) * 2; j++)
        {
            orbits[orbit - 1][j + offset] = cf.coord(x - orbit, y + orbit - 2 - j); 
        }
    }


    // Go through the generated list of positions and check if anyone
    // is locked, in which case we will return false
    Block* block;
    for (int orbit = 1; orbit <= radius; orbit++)
    {
        for (int i = 0; i < orbit * 4 + (orbit - 1) * 4; i++)
        {
            int posx = orbits[orbit - 1][i].x;
            int posy = orbits[orbit - 1][i].y;
            block = this->grid.get(posx, posy + this->height);
            
            if ((block == NULL) ||
                (block->status & STATUS_MOVING) ||
                (block->status & STATUS_ON_CIRCLE) ||
                (block->status & STATUS_OFFSCREEN))
            {
                for (int i = 0; i < radius; i++)
                {
                    delete[] orbits[i];
                }
                delete[] orbits;
                
                return false;
            }
        }
    }

    if (direction > 0)
        direction = 1;
    else
        direction = -1;
    
    // Go through the generated list of points and switch them
    // along the circle in the direction
    Block * nextBlock;
    for (int orbit = 1; orbit <= radius; orbit++)
    {
        int orbitlength = orbit * 4 + (orbit - 1) * 4;
        int orbitpos = 0;
        int posx = orbits[orbit - 1][orbitpos].x;
        int posy = orbits[orbit - 1][orbitpos].y;
        block = this->grid.get(posx, posy + this->height);
        for (int i = 0; i < orbitlength; i++)
        {
            // Move orbitpos along path in direction
            // Make sure orbitpos is always positive, in range
            orbitpos = (orbitpos + direction + orbitlength) % orbitlength;
            posx = orbits[orbit - 1][orbitpos].x;
            posy = orbits[orbit - 1][orbitpos].y;
            nextBlock = this->grid.get(posx, posy + this->height);
            
            this->grid.set(posx, posy + this->height, block);
            this->moveBlockToCoord(block, posx, posy);
            block = nextBlock;
        }
    }

    for (int i = 0; i < radius; i++)
    {
        delete orbits[i];
    }
    delete[] orbits;
    
    return true;
}


int Board::getRandomBlockType()
{
    int x = 0;
    if (this->blockTypes > 0)
        x = rand() % this->blockTypes;
    
    return blockTypeArray[x];
}

void Board::clearBlockTypes()
{
    this->blockTypes = 0;

}

void Board::setBlockType(int type, bool enabled)
{
    for (int i = 0; i < this->blockTypes; i++)
    {
        if (this->blockTypeArray[i] == type)
        {
            if (enabled == true)
            {
                return;
            }
            else
            {
                this->blockTypeArray[i] = this->blockTypeArray[this->blockTypes - 1];
                this->blockTypes--;
            }
        }
    }

    if (enabled == true)
    {
        this->blockTypes++;
        this->blockTypeArray[this->blockTypes - 1] = type;
    }
    else
    {
        return;
    }
}



void Board::reset()
{
   
    this->grid.clear();
    this->blockContainer->subSprites->destroyAll();

    //this->lastRotated.release();

    this->clearBlockTypes();
    this->setBlockType(BLOCKTYPE_HEART, true);
    this->setBlockType(BLOCKTYPE_SQUARE, true);
    this->setBlockType(BLOCKTYPE_TRIANGLE, true);
    this->setBlockType(BLOCKTYPE_CIRCLE, true);
    this->setBlockType(BLOCKTYPE_DIAMOND, true);
    this->setBlockType(BLOCKTYPE_CROSS, true);
    this->setBlockType(BLOCKTYPE_PLUS, true);
}

void Board::clear(int x, int y)
{
    Block* block = this->grid.remove(x, y + this->height);
    delete block;
}

void Board::fillBuffer()
{
    for (int x = 0; x < this->width; x++)
    {
        for (int y = 0; y < this->height; y++)
        {
            if (!this->grid.get(x, y))
                this->grid.set(x, y, new Block(x, y - this->height,
                this->getRandomBlockType(), this->currentTime));
        }
    }

    return;
}

bool Board::full()
{
    for (int x = 0; x < this->width; x++)
    {
        for (int y = this->height; y < this->height * 2; y++)
        {
            if (!this->grid.get(x, y))
                return false;
        }
    }

    return true;
}

void Board::addBlock(Block* block)
{
    int x = block->boardx;
    int y = block->boardy;

    if (x < 0 || x >= this->width || y < 0 || y >= this->height)
    {
        return;
    }

    if (this->grid.get(x, y + this->height) == NULL)
    {
        this->grid.set(x, y + this->height, block);
    }
    else
    {
        return;
    }

    this->setBlockToCoord(block, x, y);
    this->blockContainer->addSprite(block);
}
