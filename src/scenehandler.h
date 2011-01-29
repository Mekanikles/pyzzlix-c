#ifndef _SCENEHANDLER_H
#define _SCENEHANDLER_H

#include "linkedlist.h"
#include "time.h"

#include "event.h"

class Scene;

class SceneHandler
{
    public:
        
        FastLinkedList<Scene> sceneStack;
        FastLinkedList<Event> eventQueue;

        static SceneHandler* getInstance();
        
        SceneHandler();
        ~SceneHandler();
        
        Scene* getDeepestRenderedScene();
        
        void pushScene(Scene* scene);
        void removeScene(Scene* scene);
        void updateTimers(Time deltaTime);
        void tickScenes(Time frameLength);
        
        void queueEvent(Event* event);
        void handleEvent(Event* event);
        void handleQueuedEvents();
};

#endif
