#ifndef _SPRITE_H
#define _SPRITE_H

#include "linkedlist.h"
#include "point.h"
#include "time.h"

struct Image;

class Sprite : public Linkable<Sprite>
{
public:


    bool softblend;
    
    Time currentTime;
    Time lastTime;
    
    LinkedList<Sprite>* subSprites;
    Image* currentImage;
    Point center;
    Point pos;
    Time pos_lasttime;
    Point pos_ref;
    Time pos_reftime;
       
    Sprite();
    ~Sprite();

    void setImage(Image* image);
    Point calcPos(Time currentTime);
    void updatePos();
    void update(Time currentTime);

    void setPos(Point pos);
    void moveTo(Point pos, Time duration);

};

#endif
