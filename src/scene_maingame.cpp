#include "scene_maingame.h"

#include "stdio.h"

#include "resources.h"

#include "texture.h"
#include "sprite.h"
#include "image.h"

#include "constants.h"

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


    Sprite* s1;
    Sprite* s2;


    
    Texture* t = Resources::getInstance()->getTexture("blocks");

    //Board* board = new Board(BOARD_WIDTH, BOARD_HEIGHT);
    //board->setImage(i);
    //this->sprites->addItem(board);
    
    Image* i = new Image(t, 0, 0, 64, 64);
    s1 = new Sprite();
    s2 = new Sprite();
    //s1->setImage(i);
    s2->setImage(i);
    //s1->moveTo(Point(32, 32));
    s2->moveTo(Point(64, 64));
    
    //this->sprites->addItem(s1);
    this->sprites->addItem(s2);

    
    //s1->moveTo(Point(1200, 700), 5.0);
    s2->moveTo(Point(1200, 700), 5.0);

    fprintf(stderr, "Lololololool\n");
    
}

Scene_MainGame::~Scene_MainGame()
{
}

void Scene_MainGame::tick()
{
    //fprintf(stderr, "Maingame.currenttime: %f\n", this->currentTime);
    //fprintf(stderr, "Maingame.rendertime: %f\n", this->renderTime);   
}

