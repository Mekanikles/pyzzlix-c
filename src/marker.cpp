#include "marker.h"


#include "animation.h"

Marker::Marker()
{
    this->setAnimation(new Animation("marker.png", 32, 32));
    
    this->boardx = 0;
    this->boardy = 0;
        
    this->offset = Vector(0, 0);

    this->size = Vector(16, 16);
        
    this->setPos(Point(this->boardx * this->scale.x + this->offset.x,
                       this->boardy * this->scale.y + this->offset.y));
        
    //this->movesound = Resources().getSound("markermove");
    //self.turnsound = Resources().getSound("markerturn")  
    //self.failsound = Resources().getSound("markerfail")  
        
}

void Marker::setOffset(const Vector& offset)
{
    this->offset = offset;
}

               
void Marker::moveToBoardCoord(int boardx, int boardy, Time currentTime)
{
    this->boardx = this->boardx;
    this->boardy = this->boardy;
    
    this->moveTo(Point(this->boardx * this->scale.x + this->offset.x,
                       this->boardy * this->scale.y + this->offset.y), currentTime, 0.0)
}

void Marker::move(int dx, int dy, Time currentTime)
{
    //mixer.playSound(self.movesound)
    this->moveToBoardCoord(this->boardx + dx, this->boardy + dy, currentTime);

}

void Marker::turn()
{
    //mixer.playSound(self.turnsound)
}

void Marker::fail()
{
    //mixer.playSound(self.turnsound)
}
