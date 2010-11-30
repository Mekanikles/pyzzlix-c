#ifndef _RESOURCES_H
#define _RESOURCES_H


class Resources
{
public:
    void loadTexture(Texture* texture);
    Texture* getTexture(const char* name);
    Image* loadImage(const char* texturename, srcx = 0, srcy = 0, srcw = NULL, srch = NULL);

    void unloadAllTextures();

        
};


#endif
