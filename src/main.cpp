#include "stdlib.h"
#include "stdio.h"


#include "GL/glfw.h"
#include "stdio.h"
#include "stdlib.h"

#include "time.h"
#include "renderer.h"
#include "scenehandler.h"

#include "scene_maingame.h"

#include "event.h"

#include "keymap.h"

Renderer* renderer = Renderer::getInstance();
SceneHandler* sceneHandler = SceneHandler::getInstance();
Scene_MainGame* scene_maingame = Scene_MainGame::getInstance();

bool done = false;

void GLFWCALL keyCallback(int key, int action)
{
    if (key == GLFW_KEY_F1)
    {
        if (action == GLFW_PRESS)
        {
            //renderer.toggleFullscreen();
        }
    }
    else if (key == GLFW_KEY_ESC)
    {
        done = true;
    }
    else
    {
        sceneHandler->queueEvent(new KeyEvent(key, (action == GLFW_PRESS)));
    }
}
 
bool init()
{
    glfwInit();
    
    renderer->init("Pyzzlix", 1280, 720, false);

    glfwDisable(GLFW_AUTO_POLL_EVENTS);
    glfwSetKeyCallback(&keyCallback);

    KeyMap* keymap = KeyMap::getInstance();

    keymap->setKey(GLFW_KEY_RIGHT, KEY_RIGHT);
    keymap->setKey(GLFW_KEY_LEFT, KEY_LEFT);
    keymap->setKey(GLFW_KEY_DOWN, KEY_DOWN);
    keymap->setKey(GLFW_KEY_UP, KEY_UP);
    keymap->setKey('X', KEY_ROTATE_RIGHT);
    keymap->setKey('Z', KEY_ROTATE_LEFT);
    
    sceneHandler->pushScene(scene_maingame);
    
    scene_maingame->startGame();
    
    return true;
}

void cleanup()
{
    renderer->cleanup();
    glfwTerminate();
}

int main(int argc, char** argv)
{
    fprintf(stderr, "Running pyzzlix!\n");

    init();

    Time time = glfwGetTime() * 1.0;
    
    Time nextupdatetime = time;
    Time lastupdatetime = time;
    Time lastrendertime = time;
    Time lastfpsupdate = time;
    int fpscounter = 0;
    
    double LOGICS_PER_SEC = 30.0;
    Time logicLength = 1.0 / LOGICS_PER_SEC;
    
    while (!done)
    {
        // Update all timers
        time = glfwGetTime() * 1.0;
        sceneHandler->updateTimers(time - lastupdatetime);
        lastupdatetime = time;

        glfwPollEvents();
        
        if (time >= nextupdatetime)
        {
            sceneHandler->handleQueuedEvents();
            sceneHandler->tickScenes(logicLength);
            nextupdatetime += logicLength;
            renderer->render(0);
            lastrendertime = time;
            fpscounter += 1;
        }
        else
        {
            renderer->render(time - lastrendertime);
            lastrendertime = time;
            fpscounter += 1;
        }
            
        if (time - lastfpsupdate >= 1.0)
        {
            fprintf(stderr, "FPS: %i\n", fpscounter);
            fpscounter = 0;
            lastfpsupdate = time;
        }
        
        fflush(stderr);    
        //glfwSleep(1.0/10.0);
    }
    
    
    cleanup();

    return 0;
}
