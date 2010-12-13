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


class Sprite : public Linkable<Sprite>
{
    public:
        bool softblend;
        
        Time currentTime;
        Time lastTime;
        
        LinkedList<Sprite>* subSprites;
        Image* currentImage;
        Animation* currentAnimation;
        Point center;

        InterpolatedValue<Point> position;
        InterpolatedValue<Vector> scalevector;
        InterpolatedValue<Color> color;
        InterpolatedValue<float> rotation;
        
        
        Sprite();
        virtual ~Sprite();
        
        void setImage(Image* image);
        void setAnimation(Animation* animation);
        
        Point getPosition(Time currentTime = -1);
        void move(Point pos, Time duration = 0.0);
        void moveTo(Point pos, Time duration = 0.0);

        Vector getScale(Time currentTime = -1);
        void scale(Vector scale, Time duration = 0.0);
        void scaleTo(Vector scale, Time duration = 0.0);    

        float getRotation(Time currentTime = -1);
        void rotate(float angle, Time duration = 0.0);
        void rotateTo(float angle, Time duration = 0.0);

        Color getColor(Time currentTime = -1);
        void fade(Color pos, Time duration = 0.0);
        void fadeTo(Color pos, Time duration = 0.0);
        
        void update(Time currentTime);
};

#endif
