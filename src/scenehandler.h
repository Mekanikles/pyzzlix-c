#ifndef _SCENEHANDLER_H
#define _SCENEHANDLER_H

#include "linkedlist.h"
#include "time.h"

#include "event.h"

class Scene;

class SceneHandler
{
    public:
        
        FastLinkedList<Scene>* sceneStack;
        
        static SceneHandler* getInstance();
        
        SceneHandler();
        ~SceneHandler();
        
        Scene* getDeepestRenderedScene();
        
        void pushScene(Scene* scene);
        void removeScene(Scene* scene);
        void update(Time deltaTime);
        void tickScenes();
        
        void handleEvent(Event* event);  
};

#endif
