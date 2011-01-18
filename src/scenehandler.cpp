#include "scenehandler.h"

#include "stdio.h"

#include "scene.h"

SceneHandler* SceneHandler::getInstance()
{
    static SceneHandler instance;
    return &instance;
}


SceneHandler::SceneHandler()
{
    this->sceneStack = new FastLinkedList<Scene>();
}
SceneHandler::~SceneHandler()
{
    // Since scenes are singletons
    // Make sure scenes are not auto-deleted
    Scene* n;
    Scene* s = this->sceneStack->first;
    while (s != NULL)
    {
        n = s->next;

        this->sceneStack->releaseLink(s);
        
        s = n;
    }
    delete this->sceneStack;
}

Scene* SceneHandler::getDeepestRenderedScene()
{
    Scene* deepest = NULL;
    Scene* s = this->sceneStack->first;
    while (s != NULL)
    {
        deepest = s;
        if (s->isRenderBlocker())
            return deepest;

        s = s->next;
    }
    return deepest;
}

void SceneHandler::pushScene(Scene* scene)
{
    if (scene->list != NULL)
    {
        fprintf(stderr, "Removed scene before push\n");
        scene->list->releaseLink(scene);
    }

    this->sceneStack->addLink(scene);
}

void SceneHandler::removeScene(Scene* scene)
{
    if (scene->list == this->sceneStack)
        this->sceneStack->releaseLink(scene);
    else
        fprintf(stderr, "Tried to remove scene from wrong list!\n");
}

void SceneHandler::update(Time deltaTime)
{
    bool blocked = false;

    Scene* s = this->sceneStack->first;
    while (s != NULL)
    {
        if (!blocked)
        {
            s->update(deltaTime);
            s->blockedThisTick = false;
        }
        else
        {
            s->blockedThisTick = true;
        }
        
        if (s->isUpdateBlocker())
            blocked = false;
        
        s = s->next;
    }
}

void SceneHandler::tickScenes()
{
    Scene* s = this->sceneStack->first;
    while (s != NULL)
    {   
        s->tick();
        
        if (s->isUpdateBlocker())
            break;
        
        s = s->next;
    }
}

void SceneHandler::handleEvent(Event* event)
{
    Scene* s = this->sceneStack->first;
    while (s != NULL)
    {
        if (s->handleEvent(event) || s->isUpdateBlocker())
            return;
        
        s = s->next;
    }

    delete event;
}
