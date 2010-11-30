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
        
    Board* board = new Board();
    board->setImage(i);
    this->sprites->addItem(board);
    
    s1->moveTo(Point(1200, 700), 5.0);
    s2->moveTo(Point(1200, 700), 5.0);

}

Scene_MainGame::~Scene_MainGame()
{
}

void Scene_MainGame::tick()
{

    //fprintf(stderr, "Maingame.currenttime: %f\n", this->currentTime);
    //fprintf(stderr, "Maingame.rendertime: %f\n", this->renderTime);
    
}

