#ifndef _SCENE_MAINGAME_H
#define _SCENE_MAINGAME_H

#include "scene.h"
#include "board.h" // has: Board

class Scene_MainGame : public Scene
{
public:

    static Scene_MainGame* instance;
    static Scene_MainGame* getInstance();


    Scene_MainGame();
    virtual ~Scene_MainGame();
    
    void tick(); 

private:
        
        //Board* board;
};


#endif
