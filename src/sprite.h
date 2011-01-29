#ifndef _SPRITE_H
#define _SPRITE_H

#include "linkedlist.h"
#include "point.h"
#include "vector.h"
#include "color.h"
#include "time.h"

#include "interpolatedvalue.h"

struct Image;
class Animation;
class Interpolation;

class Sprite : public Linkable<Sprite>
{
    public:
        bool softblend;
        
        Time currentTime;
        
        FastLinkedList<Sprite>* subSprites;
        Image* currentImage;
        Animation* currentAnimation;
        Point center;

        Point position;
        Vector scale;
        Color color;
        float rotation;
        
        InterpolatedValue<Point>* ival_position;
        InterpolatedValue<Vector>* ival_scale;
        InterpolatedValue<Color>* ival_color;
        InterpolatedValue<float>* ival_rotation;

        Interpolation* position_inter;
        Interpolation* scale_inter;
        Interpolation* color_inter;
        Interpolation* rotation_inter;
        
        Sprite(Time currentTime = 0);
        virtual ~Sprite();
        
        void addSprite(Sprite* sprite);
        void removeSprite(Sprite* sprite);
        
        void setImage(Image* image);
        void setAnimation(Animation* animation);
        
        Point getPosition(Time time = 0.0);
        void moveTo(Point position, Time duration = 0.0);

        Vector getScale(Time time = 0.0);
        void scaleTo(Vector scale, Time duration = 0.0);    

        float getRotation(Time time = 0.0);
        void rotateTo(float rotation, Time duration = 0.0);

        Color getColor(Time time = 0.0);
        void fadeTo(Color color, Time duration = 0.0);
        
        void update(Time currentTime);
};

#endif
