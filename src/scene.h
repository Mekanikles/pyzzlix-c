#ifndef _SCENE_H
#define _SCENE_H

#include "linkedlist.h"
#include "time.h"

class Sprite;


class Scene : public Linkable<Scene>
{
public:


    Time currentTime;
    Time renderTime;
    bool renderBlocker;
    bool updateBlocker;

    bool blockedThisTick;


    LinkedList<Sprite>* sprites;

    
    Scene();
    virtual ~Scene();
    
    void update(Time deltaTime);
    virtual void tick() = 0;
    bool isRenderBlocker();
    bool isUpdateBlocker(); 
    


};

#endif
