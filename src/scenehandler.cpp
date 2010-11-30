#include "scenehandler.h"

#include "stdio.h"

#include "scene.h"

SceneHandler SceneHandler::instance;
SceneHandler* SceneHandler::getInstance()
{
    return &SceneHandler::instance;
}


SceneHandler::SceneHandler()
{
    this->sceneStack = new LinkedList<Scene>();
}
SceneHandler::~SceneHandler()
{
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
        ((LinkedList<Scene>*)(scene->list))->releaseItem(scene);
    }
        
    this->sceneStack->addItem(scene);
}


void SceneHandler::removeScene(Scene* scene)
{
    if (scene->list != NULL)
        ((LinkedList<Scene>*)(scene->list))->releaseItem(scene);

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
