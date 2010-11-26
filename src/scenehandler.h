#ifndef _SCENEHANDLER_H
#define _SCENEHANDLER_H

#include "linkedlist.h"
#include "time.h"

class Scene;

class SceneHandler
{
public:

    LinkedList<Scene>* sceneStack;


    static SceneHandler instance;
    static SceneHandler* getInstance();

    SceneHandler();
    ~SceneHandler();

    Scene* getDeepestRenderedScene();
    
    void pushScene(Scene* scene);
    void removeScene(Scene* scene);
    void update(Time deltaTime);
    void tickScenes();

};

#endif
