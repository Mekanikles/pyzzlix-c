#include "scene_maingame.h"

#include "stdio.h"

#include "texture.h"
#include "sprite.h"
#include "image.h"

Sprite* s1;
Sprite* s2;


Scene_MainGame* Scene_MainGame::getInstance()
{
    static Scene_MainGame instance;
    return &instance;
}


Scene_MainGame::Scene_MainGame():
    Scene()
{
    this->renderBlocker = false;
    this->updateBlocker = false;
    
    Texture* t = new Texture("blocks");
    
    Image* i = new Image(t, 0, 0, 32, 32);
    s1 = new Sprite();
    s2 = new Sprite();
    s1->setImage(i);
    s2->setImage(i);
    s1->setPos(Point(32, 32));
    s2->setPos(Point(64, 64));
    
    this->sprites->addItem(s1);
    this->sprites->addItem(s2);

    this->board = new Board();
    this->sprites->addItem(this->board);
}

Scene_MainGame::~Scene_MainGame()
{
}

void Scene_MainGame::tick()
{
    Point pos = s1->calcPos(this->currentTime);
    Point pos2 = s2->calcPos(this->currentTime);
    Vector vec = Point(160, 120) - s1->calcPos(this->currentTime);
    fprintf(stderr, "s1 pos: (%f, %f)\n", pos.x, pos.y);
    fprintf(stderr, "s2 pos: (%f, %f)\n", pos2.x, pos2.y);

    
    s1->move(vec, 1.0);
    //s2->move(Point(160, 120) - s1->calcPos(this->currentTime) * 2.5, 1.0);
    
}

