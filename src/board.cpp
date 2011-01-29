#include "board.h"

#include "point.h"

#include <stdio.h>
#include <stdlib.h>

#include "resources.h"
#include "marker.h"
#include "block.h"

Board::Board(int width, int height) : Sprite(),
                                      grid(width, 2 * height, 0, height),
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
    Interpolation* behv = new Interpolation_Hybrid();
    behv->setMode(INTERPOLATION_MODE_PINGPONG);
    this->glow->setColorInterpolation(behv);
    this->glow->moveTo(Point(0.0, 0.0));
    this->glow->color = Color(0.0, 0.0, 0.0, 1.0);
    this->glow->fadeTo(Color(1.0, 0.7, 0.2, 1.0), 1.0);
        
    this->marker = new Marker();
    this->setMarkerInGrid(this->width / 2, this->height / 2);
        
    this->addSprite(this->background);
    this->addSprite(this->marker);
    this->addSprite(this->blockContainer);
    this->addSprite(this->border);
    this->border->addSprite(this->glow);

    this->reset();
    
    fprintf(stderr, "Board (%i, %i) created.\n", this->width, this->height);
}

Board::~Board()
{
    //fprintf(stderr, "ran destructor!\n");
}

static double triangleArea(const Block* a, const Block* b, const Block* c)
{  
    return (b->boardx - a->boardx) * (c->boardy - a->boardy) - (c->boardx - a->boardx) * (b->boardy - a->boardy);
}

static bool isClockwise(LinkedList<Block*> circle)
{
    double area = 0;

    LinkIterator<Block*> piter1 = circle.getIterator();
    LinkIterator<Block*> piter2 = circle.getIterator();
    LinkIterator<Block*> piter3 = circle.getIterator();

    // Start iterators on succeeding blocks
    piter2.step();
    piter3.step();
    piter3.step();
    
    while(piter3.isValid())
    {        
        area += triangleArea(piter1.item(), piter2.item(), piter3.item());

        piter2.step();
        piter3.step();
    }
    
    return (area > 0);
}

void Board::moveBlockInGrid(Block* block, int boardx, int boardy)
{
    block->boardx = boardx;
    block->boardy = boardy;
    
    this->grid.set(boardx, boardy, block);
    block->moveTo(Point((boardx + 0.5f) * this->gridSlotSize,
                        (boardy + 0.5f) * this->gridSlotSize), 0.15);    
}

void Board::setBlockInGrid(Block* block, int boardx, int boardy)
{
    block->boardx = boardx;
    block->boardy = boardy;
    
    this->grid.set(boardx, boardy, block); 
    block->moveTo(Point((boardx + 0.5f) * this->gridSlotSize,
                        (boardy + 0.5f) * this->gridSlotSize));    
}

void Board::moveMarkerInGrid(int boardx, int boardy)
{
    this->marker->boardx = boardx;
    this->marker->boardy = boardy;

    this->marker->moveTo(Point(boardx * this->gridSlotSize,
                         boardy * this->gridSlotSize), 0.05);
}

void Board::setMarkerInGrid(int boardx, int boardy)
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
        this->moveMarkerInGrid(this->marker->boardx + dx,
                            this->marker->boardy + dy);
        
        //mixer.playSound(self.movesound)
    }
}
    

bool Board::rotateMarker(int direction)
{
    return rotateBlocks(this->marker->boardx, this->marker->boardy, direction, 1);
}

// TODO! Fix the corner problem!
void Board::handleCircle(LinkedList<Block*> circle, LinkedList<Block*>* blocks)
{  
    LinkIterator<Block*> iiter = circle.getIterator();
    ReverseLinkIterator<Block*> riter = circle.getReverseIterator();
    
    LinkIterator<Block*>* iter = &iiter;
        
    // If the blocks are ordered counterclockwise, iterate backwards instead
    if (!isClockwise(circle))
        iter = &riter;
    
    Block* lastBlock = circle.getLast();
    Block* block = NULL;

    // Mark whole circle as active circle
    while (iter->isValid())
    {
        iter->item()->status |= STATUS_ACTIVE_CIRCLE;
        iter->step();
    }
    
    // Go through all blocks in circle, clockwise
    iter->reset();
    while (iter->isValid())
    {
        block = iter->item();

        blocks->addItem(block);
        
        // Check the direction from the old block
        // If the direction is left, the block
        // must be on the bottom of the circle
        // Add all blocks from that block upwards to block list
        // Mark those block as circle blocks
        if (block->boardx < lastBlock->boardx)
        {
            Block* b = this->grid.get(block->boardx, block->boardy - 1);
            while(!(b == NULL || (b->status & STATUS_ACTIVE_CIRCLE)))
            {
                if (!(b->status & STATUS_IN_CIRCLE))
                {
                    blocks->addItem(b);
                    b->status |= STATUS_IN_CIRCLE;
                }
                b = this->grid.get(b->boardx, b->boardy - 1);
            }
        }
            
        lastBlock = block;
        iter->step();
    }

    // Unmark whole circle
    iter->reset();
    while (iter->isValid())
    {
        iter->item()->status &= ~STATUS_ACTIVE_CIRCLE;
        iter->step();
    }
}

void Board::findCircles(Block* startBlock)
{
    static struct Finder
    {
            int width, height;
            Grid<Block>* grid;
            Finder(int width, int height, Grid<Block>* grid) : width(width), height(height), grid(grid) {}
            
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
            
            void searchPath(Block* block, Block* start, LinkedList<Block*>* path, LinkedList< LinkedList<Block*> >* circles)
            {
                // If we found the way back to the start, save the path
                if (block == start && path->getLength() >= 4)
                {
                    circles->addItem(*path);
                    return;
                }

                // Make sure this block is valid for selecting
                if (block->status & STATUS_ON_PATH ||
                    block->status & STATUS_MOVING ||
                    block->status & STATUS_IN_CIRCLE ||
                    block->status & STATUS_OFFSCREEN)
                    return;

                // Select the block and mark it
                path->addItem(block);
                block->status |= STATUS_ON_PATH;

                Block* lastBlock = path->getFirst();
                Block* nextBlock;


                nextBlock = this->getNeighbor(block, 0, 1);
                if (nextBlock != lastBlock && nextBlock != NULL && nextBlock->type == start->type)
                    this->searchPath(nextBlock, start, path, circles);
                
                nextBlock = this->getNeighbor(block, 1, 0);
                if (nextBlock != lastBlock && nextBlock != NULL && nextBlock->type == start->type)
                   this->searchPath(nextBlock, start, path, circles);

                nextBlock = this->getNeighbor(block, -1, 0);
                if (nextBlock != lastBlock && nextBlock != NULL && nextBlock->type == start->type)
                    this->searchPath(nextBlock, start, path, circles);

                nextBlock = this->getNeighbor(block, 0, -1);
                if (nextBlock != lastBlock && nextBlock != NULL && nextBlock->type == start->type)
                    this->searchPath(nextBlock, start, path, circles);

                // The current block is no longer considered picked
                block->status &= ~STATUS_ON_PATH;
                path->removeFirst();
            }
    } finder(this->width, this->height, &this->grid);
    
    
    LinkedList< LinkedList<Block*> > circles;
    LinkedList<Block*> workPath;

    // Find a path originating from startblock
    finder.searchPath(startBlock, startBlock, &workPath, &circles);
    
    workPath.clear();
    
    if (circles.getLength() > 0)
    {
        // For each circle path, save the longest
        LinkIterator< LinkedList<Block*> > circiter = circles.getIterator();
        LinkedList<Block*> longestCircle = circiter.item();
        circiter.step();
        while(circiter.isValid())
        {
            // Delete all circles but the longest
            if (circiter.item().getLength() > longestCircle.getLength())
                longestCircle = circiter.item();
            
            circiter.step();
        }
        
        // Mark all blocks in circle and add to found circles
        LinkIterator<Block*> blockiter = longestCircle.getIterator();
        while(blockiter.isValid())
        {
            blockiter.item()->status |= STATUS_IN_CIRCLE;
            blockiter.step();
        }
        this->foundCircles.addItem(longestCircle);
    }
    
    circles.clear();
}

bool Board::rotateBlocks(int x, int y, int direction, int radius)
{
    // Cannot rotate radius < 1
    if (radius < 1)
        return false;

    // Create a number of orbits equal to the radius
    LinkedList<Block*> orbits[radius];
     
    //Fill each orbit with block position data, clockwise
    for (int orbit = 0; orbit < radius; orbit++)
    {
        // Top row, from top left block
        for (int j = 0; j < (orbit + 1) * 2; j++)
        {
            orbits[orbit].addItem(this->grid.get(x - orbit - 1 + j, y - orbit - 1));
        }

        // Right row, from top right block
        // Do not count corner blocks
        for (int j = 0; j < orbit * 2; j++)
        {
            orbits[orbit].addItem(this->grid.get(x + orbit, y - orbit + j)); 
        }

        // Bottom row, from bottom right block
        for (int j = 0; j < (orbit + 1) * 2; j++)
        {
            orbits[orbit].addItem(this->grid.get(x + orbit - j, y + orbit));
        }

        // Left row, from bottom left block
        // Do not count corner blocks
        for (int j = 0; j < orbit * 2; j++)
        {
            orbits[orbit].addItem(this->grid.get(x - orbit - 1, y + orbit - 1 - j)); 
        }
    }

    // Go through the generated list of blocks and check if anyone
    // is locked, in which case we will return false
    Block* block;
    for (int orbit = 0; orbit < radius; orbit++)
    {
        LinkIterator<Block*> iter = orbits[orbit].getIterator();
        
        while (iter.isValid())
        {
            block = iter.item();
            
            if ((block == NULL) ||
                (block->status & STATUS_MOVING) ||
                (block->status & STATUS_IN_CIRCLE) ||
                (block->status & STATUS_OFFSCREEN))
            {                
                return false;
            }

            iter.step();
        }
    }
    
    // Go through the generated list of blocks and switch them
    // along the circle in the given direction
    Block * nextBlock;
    for (int orbit = 0; orbit < radius; orbit++)
    {
        int orbitlength = orbits[orbit].getLength();
        
        LinkIterator<Block*> witer = orbits[orbit].getIterator();
        ReverseLinkIterator<Block*> rwiter = orbits[orbit].getReverseIterator();
            
        LinkIterator<Block*>* iter;
        if (direction > 0)
            iter = &rwiter;
        else
            iter = &witer;
        
        block = iter->item();
        int firstposx = block->boardx;
        int firstposy = block->boardy;

        for (int i = 0; i < orbitlength - 1; i++)
        {
            // Move along path in direction
            iter->step();
        
            nextBlock = iter->item();
            int posx = nextBlock->boardx;
            int posy = nextBlock->boardy;
            
            this->moveBlockInGrid(block, posx, posy);
            block = nextBlock;
        }

        this->moveBlockInGrid(block, firstposx, firstposy);
        
    }

    // Detect new circles for all blocks that were moved
    for (int orbit = 0; orbit < radius; orbit++)
    {
        LinkIterator<Block*> iter = orbits[orbit].getIterator();           
        while (iter.isValid())
        {
            this->findCircles(iter.item());
            iter.step();
        }
    }
    
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
    Block* block = this->grid.remove(x, y);
    delete block;
}

void Board::fillBuffer()
{
    for (int x = 0; x < this->width; x++)
    {
        for (int y = -this->height; y < 0; y++)
        {
            if (!this->grid.get(x, y))
            {
                this->grid.set(x, y, new Block(x, y,
                               this->getRandomBlockType(), this->currentTime));
            }
        }
    }

    return;
}

bool Board::full()
{
    for (int x = 0; x < this->width; x++)
    {
        for (int y = -this->height; y < this->height; y++)
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

    if (this->grid.get(x, y) == NULL)
    {
        this->grid.set(x, y, block);
    }
    else
    {
        return;
    }

    this->setBlockInGrid(block, x, y);
    this->blockContainer->addSprite(block);
}

void Board::updateBoard()
{
    if (this->foundCircles.getLength() > 0)
    {
        fprintf(stderr, "Found %i circle(s)!\n", this->foundCircles.getLength());

        LinkedList<Block*> blocks;
        
        LinkIterator< LinkedList<Block*> > iter = this->foundCircles.getIterator();
        while (iter.isValid())
        {
            this->handleCircle(iter.item(), &blocks);
            iter.step();
        }

        SceneHandler* sceneHandler = SceneHandler::getInstance();
        sceneHandler->handleEvent(new CircleEvent(blocks, false));
        
        this->foundCircles.clear();
    }

        
}
