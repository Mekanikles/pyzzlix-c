#ifndef _RESOURCES_H
#define _RESOURCES_H

#include <string>

using namespace std;

class Texture;
class Image;

class Resources
{
public:

    static Resources* getInstance();
        
    bool loadTexture(Texture* texture);
    Texture* getTexture(const string& name);
    Image* loadImage(const string& texturename, int srcx = 0, int srcy = 0, int srcw = NULL, int srch = NULL);

    void unloadAllTextures();
    void loadAllTextures();
        
};


#endif
