#include "board.h"

#include <stdio.h>

Board::Board() : Sprite()
{
}

/*virtual*/ Board::~Board()
{
    fprintf(stderr, "ran destructor!\n");
}
