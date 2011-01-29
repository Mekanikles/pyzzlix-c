#include "renderer.h"

//#include "GL/gl.h"
#include "GL/glfw.h"

#include "stdio.h"

#include "resources.h"
#include "scenehandler.h"
#include "point.h"
#include "sprite.h"
#include "image.h"
#include "scene.h"

Renderer* Renderer::getInstance()
{
    static Renderer instance;
    return &instance;
}

Renderer::Renderer()
{
    this->fullscreen = false;
    this->title = "A game";
    this->deltaTime = 0.0;
    this->width = 0;
    this->height = 0;
    this->currentTexID = -1;
    
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
    Resources::getInstance()->unloadAllTextures();
    glfwCloseWindow();
}
bool Renderer::setDisplay()
{
    Resources::getInstance()->unloadAllTextures();
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
    glOrtho(0, 320, 240, 0, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClear(GL_COLOR_BUFFER_BIT);
    
    Resources::getInstance()->loadAllTextures();
    
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

void Renderer::drawSprite(Sprite* sprite, Time time)
{
    if (sprite->currentImage == NULL && sprite->subSprites == NULL)
        return;

    glPushMatrix();

    //Point p = sprite->position.getVal();
    
    Point p = sprite->getPosition(time);
    
    glTranslatef(p.x, p.y, 0.0f);
    glRotatef(sprite->getRotation(time), 0.0f, 0.0f, 1.0f);
    Vector s = sprite->getScale(time);
    glScalef(s.x, s.y, 1.0f);
    Color c = sprite->getColor(time);
    glColor4f(c.r, c.g, c.b, c.a);


    if(sprite->currentImage != NULL)
    {
        Image* img = sprite->currentImage;
        if (img->texture != NULL && this->currentTexID != img->texture->texID)
        {
            glBindTexture(GL_TEXTURE_2D, img->texture->texID);
            this->currentTexID = img->texture->texID;
        }

        float px = -sprite->center.x;
        float py = -sprite->center.y;

        glBegin(GL_QUADS);
        {
            glTexCoord2f(img->tx1, img->ty1);
            glVertex2f(px, py);
            glTexCoord2f(img->tx1, img->ty2);
            glVertex2f(px, img->height + py);
            glTexCoord2f(img->tx2, img->ty2);
            glVertex2f(img->width + px, img->height + py);
            glTexCoord2f(img->tx2, img->ty1);
            glVertex2f(img->width + px, py);
        }
        glEnd();
    }
    
    if (sprite->subSprites != NULL)
    {
        Sprite* s = sprite->subSprites->first;
        while(s != NULL)
        {
            this->drawSprite(s, time);
            s = s->next;
        }
        
    }
    
    glPopMatrix();    
}

void Renderer::renderScene(Scene* scene)
{
    Sprite* s = scene->sprites->first;
    while(s != NULL)
    {
        this->drawSprite(s, scene->realTime);
        
        //fprintf(stderr, "Render: (%f : %f)\n", scene->realTime, scene->currentTime);
        if (scene->realTime > scene->currentTime)
        {
            //fprintf(stderr, "    RENDERTIME > CURRENTIME! (%f > %f)\n", scene->realTime, scene->currentTime);
        }
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
