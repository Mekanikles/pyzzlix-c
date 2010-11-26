#include "renderer.h"

#include "GL/gl.h"
#include "GL/glfw.h"

#include "scenehandler.h"
#include "point.h"
#include "sprite.h"
#include "image.h"
#include "scene.h"

Renderer Renderer::instance;
Renderer* Renderer::getInstance()
{
    return &Renderer::instance;
}

Renderer::Renderer()
{
    this->fullscreen = false;
    this->title = "A game";
    this->deltaTime = 0.0;
    this->width = 0;
    this->height = 0;
    
}
    

bool Renderer::init(const char* title, int width, int height, bool fullscreen = false)
{
    this->width = width;
    this->height = height;
    this->title = title;
    this->fullscreen = fullscreen;
    this->setDisplay();

    return true;
}

void Renderer::cleanup()
{
    glfwCloseWindow();
}
bool Renderer::setDisplay()
{
    glfwCloseWindow();
    glfwOpenWindow(this->width, this->height, 0, 0, 0, 0, 0, 0, this->fullscreen? GLFW_FULLSCREEN : GLFW_WINDOW);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDisable(GL_DEPTH_TEST);     
    glShadeModel(GL_FLAT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    //glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glViewport(0, 0, this->width, this->height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, this->width, this->height, 0, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    return true;
}
void Renderer::setFullscreen(bool value)
{
    this->fullscreen = value;
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers();
    this->setDisplay();
}

void Renderer::toggleFullScreen()
{
    this->setFullscreen(!this->fullscreen);
}

void Renderer::drawSprite(Sprite* sprite, Time currentTime)
{
    Point p = sprite->calcPos(currentTime);
                 
    double px = p.x - sprite->center.x;
    double py = p.y - sprite->center.y;
    Image* img = sprite->currentImage;
    
    glBegin(GL_QUADS);
    {
        //glTexCoord2f(i.tCoords[0], i.tCoords[1])
        glVertex2f(px, py);
        //glTexCoord2f(i.tCoords[2], i.tCoords[3])
        glVertex2f(px, img->height + py);
        //glTexCoord2f(i.tCoords[4], i.tCoords[5])
        glVertex2f(img->width + px, img->height + py);
        //glTexCoord2f(i.tCoords[6], i.tCoords[7])
        glVertex2f(img->width  + px, py);
    }
    glEnd();
}

void Renderer::renderScene(Scene* scene)
{
    if (!scene->blockedThisTick)
        scene->renderTime += this->deltaTime;

    Sprite* s = scene->sprites->first;
    while(s != NULL)
    {
        this->drawSprite(s, scene->renderTime);  
        s = s->next;
    }
}

void Renderer::render(Time deltaTime)
{
    this->deltaTime = deltaTime;
    
    // Clear the screen
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
      
    Scene* s = SceneHandler::getInstance()->getDeepestRenderedScene();
    while (s != NULL)
    {   
        this->renderScene(s);
            
        s = s->prev;
    }
        
    glfwSwapBuffers();
        
}
