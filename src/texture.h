#ifndef _TEXTURE_H
#define _TEXTURE_H

struct Texture
{
    const char* filename;
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


    Texture(const char* filename):
        filename(filename)
    {
        this->updateData(-1, 1, 1);
    }

};

#endif
