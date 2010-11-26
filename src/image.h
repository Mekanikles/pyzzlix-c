#ifndef _IMAGE_H
#define _IMAGE_H

#include "texture.h"

struct Image
{
    Texture* texture;
    int srcx;
    int srcy;
    int width;
    int height;
    float tx1, ty1, tx2, ty2;

    Image(Texture* texture, int srcx, int srcy, int width, int height)
    {
        this->texture = texture;
        this->srcx = srcx;
        this->srcy = srcy;
        this->width = width;
        this->height = height;
        this->tx1 = this->srcx * this->texture->pw;
        this->ty1 = this->srcy * this->texture->ph;
        this->tx2 = (this->srcx + this->width) * this->texture->pw;
        this->ty1 = (this->srcy + this->height) * this->texture->ph;
    }
};

#endif
