
#ifndef _SCENE_H
#define _SCENE_H

#include "linkedlist.h"
#include "time.h"

#include "event.h"

class Sprite;

class Scene : public Linkable<Scene>
{
    public:
        
        Time realTime;
        
        Time currentTime;
        Time oldTime;
        bool renderBlocker;
        bool updateBlocker;
        
        
        bool blockedThisTick;
        
        FastLinkedList<Sprite>* sprites;
        
        
        Scene();
        virtual ~Scene();

        void updateTimer(Time deltaTime);
        void updateLogic(Time frameLength);
        virtual void tick() = 0;
        virtual bool handleEvent(Event* event);    
        bool isRenderBlocker();
        bool isUpdateBlocker(); 
        
};

#endif
