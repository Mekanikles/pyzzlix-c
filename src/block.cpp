#include "block.h"


        int type;
        Animation* blinkAnimation;
        Animation* pulseAnimation;
        Animation* normalAnimation;

        int boardx;
        int boardy;

        float gravityDelay;
        int status;
        
        Vector size;
        Vector center;
        Vector offset;

        int comboCounter;
        int layer;
    public:

Block::Block(int boardx, int boardy, int type, Vector& offset):
    type(type),
    boardx(boardx),
    boardy(boardy),
    gravityDelay(0.0f),
    status(STATUS_NONE),
    comboCounter(0),
    layer(type)
{
    this->blinkAnimation = new Animation(Resources::getTexture("blocks"),
         16, 16, this->type * 16, 0, 16, 6 * 16, 0.0, 0.016, "pingpongloop");
    
    this-pulseAnimation = new Animation(Resources::getTexture("blocks"),
         16, 16, this->type * 16, 0, 16, 6 * 16, 0.0, 0.016, "pingpongloop");
    
    this->normalAnimation = new Animation(Resources::getTexture("blocks"),
         16, 16, this->type * 16, 0, 16, 16, 0.0, 0.016, "normal");
    
    this->setAnimation(this->normalAnimation);
    this->size = Vector(16, 16);
    this->center = this->size * 0.5f;
    this->offset = offset;        
}
    
        void doPulse();      
        void doBlink();
        void doNormal();

        void moveToBoardCoord(int boardx, int boardy, Time currentTime);
        void setToBoardCoord(boardx, boardy);
        void animatePopup(self, currentTime);
