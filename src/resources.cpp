#include "resources.h"

#include "GL/glfw.h"

#include <string>
#include "labelmap.h"

#include "lodepng/lodepng.h"
#include "texture.h"
#include "image.h"

using namespace std;

static LabelMap<Texture> textures;

static string getFullTexturePath(const string& name)
{
    return string("data/textures/") + name + string(".png");
}


static ImageFile* loadImageFile(const string& filename)
{   
    unsigned char* buffer = NULL;
    unsigned int buffersize;

    FILE* file = fopen(filename.c_str(),"rb");
    if (!file)
    {
        fprintf(stderr, "Couldn't locate image file '%s'.\n", filename.c_str());
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    unsigned int filelen = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = new unsigned char[filelen];
    
    if (fread(buffer, 1, filelen, file) != filelen)
    {
        fprintf(stderr, "Load image (%s) failed: did not read correct amount of bytes.\n", filename.c_str());
        fclose(file);
        delete[] buffer;
        return NULL;
    }

    fclose(file);
    buffersize = filelen;

    ImageFile* imgfile = new ImageFile(); 
    
    LodePNG_Decoder decoder;
    LodePNG_Decoder_init(&decoder);
    LodePNG_decode(&decoder, &imgfile->data, &imgfile->size, buffer, buffersize);

    if(decoder.error)
    {
        fprintf(stderr, "PNG decoding failed for file %s, error: %d\n", filename.c_str(), decoder.error);
        delete imgfile;
        return NULL;
    }

    imgfile->width = decoder.infoPng.width;
    imgfile->height = decoder.infoPng.height;
    imgfile->channels = LodePNG_InfoColor_getChannels(&decoder.infoPng.color);
    
    LodePNG_Decoder_cleanup(&decoder);

    delete[] buffer;
    
    return imgfile;    
}

Resources* Resources::getInstance()
{
    static Resources instance;
    return &instance;
}

bool Resources::loadTexture(Texture* texture)
{
    if (texture == NULL)
        return false;

    ImageFile* img;
    if (texture->img != NULL)
        img = texture->img;
    else
        img = loadImageFile(getFullTexturePath(texture->name));
    
    if (img == NULL)
    {
        fprintf(stderr, "Could not load texture %s.\n", texture->name.c_str());
        return false;
    }
        
    unsigned int texID;
    glGenTextures(1, &texID);
    
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    texture->updateData(texID, img);
    
    return true;
}

Texture* Resources::getTexture(const string& name)
{
    bool exists = textures.exists(name);
    if (exists)
    {
        return textures.get(name);
    }
    else
    {
        Texture* t = new Texture(name);
        if (!this->loadTexture(t))
        {
            delete t;
            return false;
        }
        textures.set(name, t);
        return t;
    }
}

Image* Resources::getImage(const string& texturename, int srcx, int srcy,
    int srcw, int srch)
{
    Texture* t = this->getTexture(texturename);
    if (t == NULL)
    {
        fprintf(stderr, "Could not load texture %s.\n", texturename.c_str());
    }

    if (srcw == 0 || srch == 0)
    {
        srcw = t->width;
        srch = t->height;
    }

    
    return new Image(t, srcx, srcy, srcw, srch);
}


Image** Resources::getImageSheet(int* frameCount, const string& texturename, int width,
    int height, int srcx, int srcy, int srcw, int srch)
{
    Image** images = NULL;
    Texture* texture = this->getTexture(texturename);
    if (texture == NULL)
    {
        *frameCount = 0;
        return NULL;
    }

    if (srcw == 0)
        srcw = texture->width;
        
    if (srch == 0)
        srch = texture->height;

    if (width == 0)
        width = srcw;

    if (height == 0)
        height = srch;

    int imagexcount = srcw / width;
    int imageycount = srch / height;

    *frameCount = imageycount * imagexcount;
    if (imageycount * imagexcount <= 0)
    {
        fprintf(stderr, "Could not load image(s) from: %s\n", texturename.c_str());
        return NULL;
    }
    
    images = new Image*[imageycount * imagexcount];
    
    for (int iy = 0; iy < imageycount; iy++)
    {
        for (int ix = 0; ix < imagexcount; ix++)
        {
            images[iy * imagexcount + ix] = new Image(texture,
                srcx + ix * width,
                srcy + iy * height, width, height);
        }
    }
           
    return images;
}

void Resources::unloadAllTextures()
{
    LabelItem<Texture>* i = textures.list->first;
    while (i != NULL)
    {
        if (i->item != NULL && i->item->texID != -1)
        {
            unsigned int texID = i->item->texID;
            glDeleteTextures(1, &texID);
            i->item->texID = -1;
        }

        i = i->next;
    }
}

void Resources::loadAllTextures()
{
    LabelItem<Texture>* i = textures.list->first;
    while (i != NULL)
    {
        if (i->item != NULL && i->item->texID == -1)
        {
            if (!this->loadTexture(i->item))
            {
                fprintf(stderr, "Could not load Texture %s!\n", i->item->name.c_str());
            }
        }

        i = i->next;
    }
}
