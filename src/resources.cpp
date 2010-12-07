#include "resources.h"

#include <string>
#include "labelmap.h"

#include "lodepng/lodepng.h"
#include "texture.h"

using namespace std;

static LabelMap<Texture> textures;

static imageFile* loadImageFile(const char* filename)
{   
    unsigned char* buffer = NULL;
    unsigned int buffersize;

    FILE* file = fopen(filename,"rb");
    if (!file)
    {
        fprintf(stderr, "Couldn't locate image file '%s'.", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    unsigned int filelen = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = new unsigned char[filelen];
    
    if (fread(buffer, 1, filelen, file) != filelen)
    {
        fprintf(stderr, "Load image (%s) failed: did not read correct amount of bytes.", filename);
        fclose(file);
        delete[] buffer;
        return NULL;
    }

    fclose(file);
    buffersize = filelen;

    imageFile* imgfile = new imageFile(); 
    
    LodePNG_Decoder decoder;
    LodePNG_Decoder_init(&decoder);
    LodePNG_decode(&decoder, &imgfile->data, &imgfile->size, buffer, buffersize);

    if(decoder.error)
    {
        fprintf(stderr, "PNG decoding failed for file %s, error: %d\n", filename, decoder.error);
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
    
    imageFile* img;
    
    img = loadImageFile(texture.filename);
    if (img == NULL)
    {
        fprintf(stderr, "Could not load texture from file %s.", texture->fullname);
        return false;
    }
        
    int texID = glGenTextures(1);
    
    glBindTexture(GL_TEXTURE_2D, &texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    texture->updateData(texID, img);
    
    return true;
}

bool Resources::reloadTexture(Texture* texture)
{
    if (texture == NULL)
        return;
    
    if (texture->img != NULL)
        texture->img = loadImageFile(texture.fullname);
    
    if (texture->img == NULL)
    {
        fprintf(stderr, "Could not load texture from file %s.", texture->fullname);
        return false;
    }
        
    int texID = glGenTextures(1);
    
    glBindTexture(GL_TEXTURE_2D, &texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->img->width, texture->img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->img->data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
    return true;
}

Texture* Resources::getTexture(const char* name)
{
    string path = string(name);
    path = string("\\data\\") + name;

    bool exists = textures.exists(name);
    if (exists)
    {
        return textures.get(name);
    }
    else
    {
        Texture* t = new Texture(path);
        if (!this->loadTexture(t))
        {
            delete t;
            return false;
        }
        textures.set(name, t);
        return t;
    }
}

Image* Resources::loadImage(const char* texturename, srcx = 0, srcy = 0, srcw = NULL, srch = NULL)
{
    Texture t = getTexture[texturename];
    if (t == NULL)
    {
        fprintf(stderr, "Could not load texture %s.", texturename);
    }
    
    return new Image(texture, srcx, srcy, srcw, srch);
}


void Resources::unloadAllTextures()
{
    LabelItem<Texture>* i = textures.list.first;
    while (i != NULL)
    {
        if (i->item != NULL && i->item->texID != -1)
        {
            glDeleteTextures(i->item->texID);
            i->item->texID = -1;
        }

        i = i->next;
    }
}

void Resources::loadAllTextures()
{
    LabelItem<Texture>* i = textures.list.first;
    while (i != NULL)
    {
        if (i->item != NULL && i->item->texID == -1)
        {
            if (!this->loadTexture(i->item))
            {
                fprintf(stderr, "Could not load Texture %s!\n", i->item->filename);
            }
        }

        i = i->next;
    }
}
