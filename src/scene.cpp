#include <stdlib.h>

#include "scene.h"

#include "sprite.h"

Scene::Scene():
    renderBlocker(false),
    updateBlocker(false)
{
    this->sprites = new FastLinkedList<Sprite>();
}
Scene::~Scene()
{
    delete this->sprites;
}

void Scene::update(Time deltaTime)
{
    this->currentTime += deltaTime;
    this->renderTime = this->currentTime;
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
