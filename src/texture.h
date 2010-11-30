#ifndef _TEXTURE_H
#define _TEXTURE_H

#include <string>


struct Texture
{
    string filename;
    int texID;
    int width;
    int height;
    float pw;
    float ph;


    void updateData(int texID, int width, int height)
    {
        this->texID = texID;
        this->width = width;
        this->height = height;
        this->pw = 1.0/(float)this->width;
        this->ph = 1.0/(float)this->height;      
    }


    Texture(string filename):
        filename(filename)
    {
        this->updateData(-1, 1, 1);
    }

};

#endif
