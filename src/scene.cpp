#include <stdlib.h>

#include "scene.h"

#include "sprite.h"

Scene::Scene():
    realTime(0.0),
    currentTime(0.0),
    predictedNextTime(0.0),
    renderBlocker(false),
    updateBlocker(false)
{
    this->sprites = new FastLinkedList<Sprite>();
}
Scene::~Scene()
{
    delete this->sprites;
}

void Scene::updateTimer(Time deltaTime)
{
    this->realTime += deltaTime;
    if (this->realTime > this->predictedNextTime)
    {
        this->realTime = this->predictedNextTime;
    }
}

void Scene::updateLogic(Time frameLength)
{
    this->currentTime = this->realTime;
    this->predictedNextTime = this->currentTime + frameLength;
    
    Sprite* s = this->sprites->first;
    while (s != NULL)
    {
        s->update(this->currentTime);
        s = s->next;
    }
}

bool Scene::handleEvent(Event* event)
{
    return false;
}

bool Scene::isRenderBlocker()
{
    return this->renderBlocker;
}
bool Scene::isUpdateBlocker()
{
    return this->updateBlocker;
}
