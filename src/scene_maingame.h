#ifndef _SCENE_MAINGAME_H
#define _SCENE_MAINGAME_H

#include "scene.h"
#include "board.h" // has: Board

#include "event.h"

class Scene_MainGame : public Scene
{
    public:
        
        static Scene_MainGame* getInstance();
        
        Scene_MainGame();
        virtual ~Scene_MainGame();


        void resetGame();

        void startGame();
        void pauseGame();
        void show();
        void moveInWindows();
        void moveOutWindows();
        void hide();
        
        void tick();
        void removeBlocks(LinkedList<Block*> blocks);
        bool handleEvent(Event* event);

        void fillZigZag();
        
        static Scene_MainGame* instance;

        Board* board;
        int state;
        int fillPosX;
        int fillPosY;
        int fillDir;
        int fillCounter;

        bool windowsInPlace;

private:
        
        //Board* board;
};


#endif
