#include "stdlib.h"
#include "stdio.h"


#include "GL/glfw.h"
#include "stdio.h"
#include "stdlib.h"

#include "time.h"
#include "renderer.h"
#include "scenehandler.h"

#include "scene_maingame.h"

Renderer* renderer = Renderer::getInstance();
SceneHandler* sceneHandler = SceneHandler::getInstance();
Scene* scene_maingame = Scene_MainGame::getInstance();

bool init()
{

    glfwInit();
    
    renderer->init("Pyzzlix", 320, 240, false);
    sceneHandler->pushScene(scene_maingame);
    
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

    Time time = glfwGetTime();
    
    Time nextupdatetime = time;
    Time lastrendertime = time;
    Time lastfpsupdate = time;
    int fpscounter = 0;
    
    double LOGICS_PER_SEC = 5.0;
    Time logicLength = 1.0 / LOGICS_PER_SEC;
    
    while (true)
    {
        
        if (glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
        {
            break;
        }
    
        time = glfwGetTime();
        
        if (time - lastfpsupdate >= 1.0)
        {
            fprintf(stderr, "FPS: %i\n", fpscounter);
            fpscounter = 0;
            lastfpsupdate = time;
        }

               
        if (time >= nextupdatetime)
        {
            while (time >= nextupdatetime)
            {
                nextupdatetime += logicLength;
                sceneHandler->update(logicLength);
                sceneHandler->tickScenes();
                renderer->render(time - lastrendertime);
                lastrendertime = time;
                fpscounter += 1;
            }
        }
        else
        {
            //renderer->render(time - lastrendertime);
            //lastrendertime = time;
            //fpscounter += 1;
        }
            
        glfwSleep(1.0/60.0);
    }
    
    
    cleanup();

    return 0;
}
