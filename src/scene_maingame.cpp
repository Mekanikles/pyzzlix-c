#include "scene_maingame.h"

#include "stdio.h"

#include "resources.h"

#include "texture.h"
#include "sprite.h"
#include "image.h"

#include "constants.h"

#include "event.h"

#include "keymap.h"

Scene_MainGame* Scene_MainGame::getInstance()
{
    static Scene_MainGame instance;
    return &instance;
}


Scene_MainGame::Scene_MainGame():
    Scene(),
    state(STATE_IDLE),
    fillPosX(0),
    fillPosY(0),
    fillDir(1),
    fillCounter(0),
    windowsInPlace(false)
{    
    this->board = new Board(BOARD_WIDTH, BOARD_HEIGHT);
    this->board->moveTo(Point(24.0, -300.0));
    this->sprites->addLink(board);

 
    this->resetGame();
}
     
Scene_MainGame::~Scene_MainGame()
{
}


void Scene_MainGame::resetGame()
{

    /*this->setLevel(1)
        this->blocksToLevel = this->getBlocksToLevel()
        this->activeBlock = this->getActiveBlock()
        this->background.setTheme(this->activeBlock)
 4       this->blockCount = 0
        this->score = 0
        this->board.reset()
        this->hourglass.reset(HOURGLASS_DEFAULT)*/
    this->fillPosX = 0;
    this->fillPosY = this->board->height - 1;
    this->fillDir = 1;
    this->fillCounter = this->board->width * this->board->height;
/*
        this->sprites.remove_sprites_of_layer(LAYER_BLOCKS)
        this->blocks.empty()
        this->comboCounter = 0
        this->comboResetCounter = 0
        
        this->board.stopPulseBorder()
        this->hourglass.stopPulseBorder()
        this->scoreboard.stopPulseBorder()
        this->levelboard.stopPulseBorder()
        this->scoreboard.setHighscore(Scene_Highscore().getHighscore())

        this->state = this->statelist["idle"]
        this->playMusicForLevel()*/
}
   
                       
void Scene_MainGame::startGame()
{
    this->state = STATE_RUNNING;

    if (!this->windowsInPlace)
        this->moveInWindows();    
}

void Scene_MainGame::pauseGame()
{
    this->state = STATE_IDLE;
}

void Scene_MainGame::show()
{
    fprintf(stderr, "Showing main game\n");
    //for mus in this->music:
    //Mixer().playMusic(mus, volume=0.0, loops=-1)


    this->resetGame();

        
        /*      if Options().get("show_tutorials"):
            this->showSplash()
        else:
            this->startGame()
        */
}
        
void Scene_MainGame::moveInWindows()
{
    fprintf(stderr, "Moving in windows.\n");    
    this->windowsInPlace = true;
    this->board->moveTo(Point(24.0, 16.0), 0.3);
    //this->scoreboard.moveTo((208.0, 8.0), this->currentTime, 0.5)
    //this->levelboard.moveTo((208.0, 80.0), this->currentTime, 0.5)
    //this->hourglass.moveTo((208, 136), this->currentTime, 0.5)
}

void Scene_MainGame::moveOutWindows()
{
    fprintf(stderr, "Moving out windows.\n");
    this->windowsInPlace = false;
    this->board->moveTo(Point(24.0, -300.0), 0.7);
//    this->scoreboard.setPos((408.0, 8.0))
    //       this->levelboard.setPos((408.0, 80.0))
    //     this->hourglass.setPos((408, 136))
}


void Scene_MainGame::hide()
{
    fprintf(stderr, "Hiding main game\n");
    this->pauseGame();
    this->moveOutWindows();
//    for mus in this->music:
//            Mixer().stopMusic(mus)
}   


void Scene_MainGame::fillZigZag()
{
    for (int i = 0; i < 4; i++)
    {
        if (this->fillCounter > 0)
        {
            this->fillCounter--;
            Block* block = new Block(this->fillPosX, this->fillPosY,
                this->board->getRandomBlockType(), this->currentTime);
            
            block->animatePopup();
            this->board->addBlock(block);

            this->fillPosX += this->fillDir;
            
            if (this->fillPosX >= this->board->width)
            {
                this->fillDir = -1;
                this->fillPosX --;
                this->fillPosY --;
            }

            if (this->fillPosX < 0)
            {
                this->fillDir = 1;
                this->fillPosX ++;
                this->fillPosY --;
            }
        }
    }
}
    
void Scene_MainGame::tick()
{
    //fprintf(stderr, "maingame tick\n");
    if (this->state == STATE_RUNNING)
    {
        if (this->fillCounter > 0)
        {
            this->fillZigZag();
        }
        else
        {
            this->board->fillBuffer();
        }

        
        /* this->scoreboard.updateScoreboard(this->score)
            
            this->board.updateBoard()
            
            if this->comboCounter > 0:
        if this->board.inactive():                    
                    this->comboResetCounter += 1
                else:
                    this->comboResetCounter = 0

                if this->comboResetCounter > 3:
                    this->comboCounter = 0
                                
            if this->doLevelUp:
                if this->board.inactive():
                    this->doLevelUpCounter += 1
                else:
                    this->doLevelUpCounter = 0

                if this->doLevelUpCounter > 3:
                    this->newLevel()
        */
    }

}

bool Scene_MainGame::handleEvent(Event* event)
{
    switch (event->type)
    {
        case EVENT_KEY:
        {
            KeyEvent* keyevent = (KeyEvent*)event;
            unsigned int key = KeyMap::getInstance()->getKey(keyevent->id);
            
            if (this->state == STATE_RUNNING && keyevent->pressed)
            {
                switch (key)
                {
                    case KEY_RIGHT:
                    {
                        this->board->moveMarker(1, 0);
                        break;
                    }
                    case KEY_LEFT:
                    {
                        this->board->moveMarker(-1, 0);
                        break;
                    }    
                    case KEY_UP:
                    {
                        this->board->moveMarker(0, -1);
                        break;
                    }    
                    case KEY_DOWN:
                    {
                        this->board->moveMarker(0, 1);
                        break;
                    }        
                    case KEY_ROTATE_RIGHT:
                    {
                        this->board->rotateMarker(1);
                        break;
                    }
                    case KEY_ROTATE_LEFT:
                    {
                        this->board->rotateMarker(-1);
                        break;
                    }
                    default:
                    {}
                }

                return true;
            }
            
            break;
        }
        default:
        {
            return false;
        }
    }
    return false;
}
