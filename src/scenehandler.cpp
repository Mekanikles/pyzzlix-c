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
}
SceneHandler::~SceneHandler()
{
    // Since scenes are singletons
    // Make sure scenes are not auto-deleted
    Scene* n;
    Scene* s = this->sceneStack.first;
    while (s != NULL)
    {
        n = s->next;

        this->sceneStack.releaseLink(s);
        
        s = n;
    }
}

Scene* SceneHandler::getDeepestRenderedScene()
{
    Scene* deepest = NULL;
    Scene* s = this->sceneStack.first;
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

    this->sceneStack.addLink(scene);
}

void SceneHandler::removeScene(Scene* scene)
{
    if (scene->list == &this->sceneStack)
        this->sceneStack.releaseLink(scene);
    else
        fprintf(stderr, "Tried to remove scene from wrong list!\n");
}

void SceneHandler::updateTimers(Time deltaTime)
{
    bool blocked = false;

    Scene* s = this->sceneStack.first;
    while (s != NULL)
    {
        if (!blocked)
        {
            s->updateTimer(deltaTime);
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

void SceneHandler::tickScenes(Time frameLength)
{
    // Update all objects in scenes
    Scene* s = this->sceneStack.first;
    while (s != NULL)
    {
        s->updateLogic(frameLength);
        
        if (s->isUpdateBlocker())
            break;
        
        s = s->next;
    }
    
    // Do scene ticks
    s = this->sceneStack.first;
    while (s != NULL)
    {
        s->tick();
        
        if (s->isUpdateBlocker())
            break;
        
        s = s->next;
    }
}

void SceneHandler::queueEvent(Event* event)
{
    this->eventQueue.addLinkLast(event);
}

void SceneHandler::handleQueuedEvents()
{
    Event* e = this->eventQueue.first;
    Event* next = NULL;
    while (e != NULL)
    {
        next = e->next;
        this->eventQueue.releaseLink(e);
        this->handleEvent(e);
        e = next;
    }
}

void SceneHandler::handleEvent(Event* event)
{
    Scene* s = this->sceneStack.first;
    while (s != NULL)
    {
        if (s->handleEvent(event) || s->isUpdateBlocker())
            return;
        
        s = s->next;
    }

    delete event;
}

