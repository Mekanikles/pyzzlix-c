#ifndef _IMAGE_H
#define _IMAGE_H

#include "texture.h"
#include "stdlib.h"

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

        if (texture != NULL)
        {
            this->tx1 = (float)(this->srcx * this->texture->pw);
            this->ty1 = (float)(this->srcy * this->texture->ph);
            this->tx2 = (float)((this->srcx + this->width) * this->texture->pw);
            this->ty2 = (float)((this->srcy + this->height) * this->texture->ph);
        }
    }
};

#endif
