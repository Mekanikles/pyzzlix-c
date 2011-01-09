
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
    Image* getImage(const string& texturename, int srcx = 0, int srcy = 0,
        int srcw = 0, int srch = 0);
    Image** getImageSheet(int* frameCount, const string& texturename,
        int width, int height, int srcx = 0, int srcy = 0, int srcw = 0, int srch = 0);

    void unloadAllTextures();
    void loadAllTextures();
        
};


#endif
