#include "marker.h"


#include "animation.h"
#include "interpolation.h"

Marker::Marker()
{
    this->setAnimation(new Animation("marker", 32, 32));
    
    this->boardx = 0;
    this->boardy = 0;
        
    //this->movesound = Resources().getSound("markermove");
    //self.turnsound = Resources().getSound("markerturn")  
    //self.failsound = Resources().getSound("markerfail")  

    this->center = Point(16.0f, 16.0f);
    
    this->setPositionInterpolation(new Interpolation_Decelerated());
}
