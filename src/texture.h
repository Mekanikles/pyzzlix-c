#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>

using namespace std;

struct ImageFile
{
    unsigned char* data;
        
    unsigned int width;
    unsigned int size;
    unsigned int height;
    unsigned int channels;    
};

struct Texture
{
    string name;
    ImageFile* img;      
    int texID;
    int width;
    int height;
    double pw;
    double ph;


    void updateData(int texID, ImageFile* img)
    {
        this->img = img;
        this->texID = texID;

        if (img != NULL)
        {
            this->pw = 1.0/(double)this->img->width;
            this->ph = 1.0/(double)this->img->height;
            this->width = this->img->width;
            this->height = this->img->height;
        }
        else
        {
            this->pw = 1.0;
            this->ph = 1.0;
            this->width = 0;
            this->height = 0;
        }
    }

    Texture(string name):
        name(name),
        img(NULL),      
        texID(-1),
        width(0),
        height(0),
        pw(0.0),
        ph(0.0)
    {
        this->updateData(-1, NULL);
    }

    virtual ~Texture()
    {
        if (this->img != NULL)
        {
            if (this->img->data != NULL)
                delete[] this->img->data;
            delete this->img;
        }
    }

};

#endif
