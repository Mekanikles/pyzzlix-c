#include "scene_maingame.h"

#include "stdio.h"

#include "texture.h"
#include "sprite.h"
#include "image.h"

Scene_MainGame Scene_MainGame::instance;
Scene_MainGame* Scene_MainGame::getInstance()
{
    return &Scene_MainGame::instance;
}


Scene_MainGame::Scene_MainGame():
    Scene()
{
    fprintf(stderr, "AGADGDGADGA\n");
    this->renderBlocker = false;
    this->updateBlocker = false;
    
    Texture* t = new Texture("Whatever.png");
    Image* i = new Image(t, 0, 0, 32, 32);
    Sprite* s = new Sprite();
    s->setImage(i);
    //this->sprites->addItem(s);

}
Scene_MainGame::~Scene_MainGame()
{

}

void Scene_MainGame::tick()
{

    fprintf(stderr, "Maingame, tick: %d\n", this->currentTime);
}

