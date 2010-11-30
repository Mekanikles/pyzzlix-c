#include "resources.h"

#include <string>
#include <hash_map>

#include "lodepng/lodepng.h"

using namespace std;

struct imageFile
{
    unsigned char* buffer;
    unsigned int buffersize;

    unsigned char* data;
        
    unsigned int width;
    unsigned int size;
    unsigned int height;
    unsigned int channels;    
};


static hash_map<string, Texture*> textures;

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
    int filelen = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = new (unsigned char)[filelen];
    
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
    LodePNG_decode(&decoder, &imgfile.data, &imgfile.size, buffer, buffersize);

    if(decoder.error)
    {
        ERROR("PNG decoding failed for file %s, error: %d\n", filename, decoder.error);
        delete imgfile;
        return NULL;
    }

    imgfile.width = decoder.infoPng.width;
    imgfile.height = decoder.infoPng.height;
    imgfile.channels = LodePNG_InfoColor_getChannels(&decoder.infoPng.color);

    LodePNG_Decoder_cleanup(&decoder);
   
    return imgfile;    
}


bool resources::loadTexture(Texture* texture)
{
    imageFile* img;
    
    img = loadImageFile(texture.fullname);
    if (img == NULL)
    {
        fprintf(stderr, "Could not load texture from file %s.", texture.fullname);
        return false;
    }
        
    int texID = glGenTextures(1);
    
    glBindTexture(GL_TEXTURE_2D, &texID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->width, img->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img->data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    texture.updateData(texID, img->width, img->height);

    delete[] img->data;
    delete[] img->buffer;
    delete img;
    
    return true;
}

Texture* resources::getTexture(const char* name)
{
    string path = string(name);
    path = string("\\data\\") + name;

    bool exists = textures.exist(name);
    if (exists)
    {
        return textures[path];
    }
    else
    {
        Texture* t = new Texture(path);
        if (!this->loadTexture(t))
        {
            delete t;
            return false;
        }
        textures[path] = t;
        return t;
    }
}

Image* resources::loadImage(const char* texturename, srcx = 0, srcy = 0, srcw = NULL, srch = NULL)
{
    Texture t = getTexture[texturename];
    if (t == NULL)
    {
        fprintf(stderr, "Could not load texture %s.", texturename);
    }
    
    return new Image(texture, srcx, srcy, srcw, srch);
}


void resources::unloadAllTextures()
{
    
    hash_map<string, Texture*>::iterator endIter = hashMap.end();
    for (hash_map<string, Texture*>::iterator iter = hashMap.begin(); iter != endIter; ++iter)
    {
        iter->first // TODO, fix;
    }
}

    for t in textures:
    glDeleteTextures(textures[t].texID);

    
}
