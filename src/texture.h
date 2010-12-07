#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>

using namespace std;

struct imageFile
{
    unsigned char* data;
        
    unsigned int width;
    unsigned int size;
    unsigned int height;
    unsigned int channels;    
};

struct Texture
{
    string filename;
    imageFile* img;      
    int texID;
    int width;
    int height;
    float pw;
    float ph;


    void updateData(int texID, imageFile* img)
    {
        this->img = img;
        this->texID = texID;
        this->width = width;
        this->height = height;
        this->pw = 1.0/(float)this->width;
        this->ph = 1.0/(float)this->height;      
    }

    Texture(string filename):
        filename(filename)
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
