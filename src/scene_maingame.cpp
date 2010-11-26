#include "scene_maingame.h"

#include "stdio.h"

Scene_MainGame Scene_MainGame::instance;
Scene_MainGame* Scene_MainGame::getInstance()
{
    return &Scene_MainGame::instance;
}


Scene_MainGame::Scene_MainGame():
    Scene()
{
    this->renderBlocker = false;
    this->updateBlocker = false;

}
Scene_MainGame::~Scene_MainGame()
{

}

void Scene_MainGame::tick()
{

    fprintf(stderr, "Maingame, tick: %d\n", this->currentTime);
}

