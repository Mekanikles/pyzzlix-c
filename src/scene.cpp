#include <stdlib.h>

#include "scene.h"

#include "sprite.h"

Scene::Scene()
{
    this->sprites = new LinkedList<Sprite>();
}
Scene::~Scene()
{
    this->sprites->destroy();
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

bool Scene::isRenderBlocker()
{
    return this->renderBlocker;
}
bool Scene::isUpdateBlocker()
{
    return this->updateBlocker;
}
