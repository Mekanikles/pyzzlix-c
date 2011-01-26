#ifndef _SPRITE_H
#define _SPRITE_H

#include "linkedlist.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "time.h"

#include "mover.h"

#include "interpolatedvalue.h"

struct Image;
class Animation;
class MoveBehaviour;

class Sprite : public Linkable<Sprite>
{
    public:
        bool softblend;
        
        Time currentTime;
        
        FastLinkedList<Sprite>* subSprites;
        Image* currentImage;
        Animation* currentAnimation;
        Point center;

        InterpolatedValue<Point> position;
        InterpolatedValue<Vector> scaleVector;
        InterpolatedValue<Color> color;
        InterpolatedValue<float> rotation;

        MoveBehaviour* position_behaviour;
        MoveBehaviour* scale_behaviour;
        MoveBehaviour* color_behaviour;
        MoveBehaviour* rotation_behaviour;

        Mover<Point>* position_mover;
        Mover<Vector>* scale_mover;
        Mover<Color>* color_mover;
        Mover<float>* rotation_mover;
        
        Sprite(Time currentTime = 0);
        virtual ~Sprite();
        
        void addSprite(Sprite* sprite);
        void removeSprite(Sprite* sprite);
        
        void setImage(Image* image);
        void setAnimation(Animation* animation);
        
        Point getPosition();
        void moveTo(Point position, Time duration = 0.0);

        Vector getScale();
        void scaleTo(Vector scale, Time duration = 0.0);    

        float getRotation();
        void rotateTo(float rotation, Time duration = 0.0);

        Color getColor();
        void fadeTo(Color color, Time duration = 0.0);
        
        void update(Time currentTime);
};

#endif
