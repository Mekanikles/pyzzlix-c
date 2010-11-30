#ifndef _RENDERER_H
#define _RENDERER_H

#include "time.h"

class Sprite;
class Scene;
class Texture;

class Renderer
{
        
public:
        
    bool fullscreen;
    const char* title;
    Time deltaTime;
    int width;
    int height;
    
    
    static Renderer instance;
    static Renderer* getInstance();


    Renderer();  
    
   
    bool init(const char* title, int width, int height, bool fullscreen);
    
    void cleanup();
    bool setDisplay();
    void setFullscreen(bool value = false);
    void toggleFullScreen();
    
    void drawSprite(Sprite* sprite, Time currentTime);
    void renderScene(Scene* scene);
    void render(Time deltaTime);
        
    void loadTexture(Texture* texture);
};

#endif
