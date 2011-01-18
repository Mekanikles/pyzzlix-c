
static bool checkBounds(int x, int y, int sizex, int sizey)
{
    if (x > sizex - 1 ||
        y > sizey - 1 ||
        x < 0 ||
        y < 0)
        return false;
    return true;
}

template <class T>
Grid<T>::Grid(int sizex, int sizey, int xoffset, int yoffset):
    sizex(sizex), sizey(sizey), xoffset(xoffset), yoffset(yoffset)
{
    this->array = new T*[sizex * sizey];

    this->clear();
}

template <class T>
Grid<T>::~Grid()
{ 
    delete[] this->array;
}

template <class T>
void Grid<T>::set(int x, int y, T* item)
{
   if (!checkBounds(x + this->xoffset, y + this->yoffset, this->sizex, this->sizey))
        return;
   
   this->array[(y + this->yoffset) * sizex + (x + this->xoffset)] = item;
}

template <class T>
T* Grid<T>::remove(int x, int y)
{
    if (!checkBounds(x + this->xoffset, y + this->yoffset, this->sizex, this->sizey))
        return NULL;
    
    T* retval = this->array[(y + this->yoffset) * sizex + (x + this->xoffset)];
    this->array[(y + this->yoffset) * sizex + (x + this->xoffset)] = NULL;
    return retval;
}

template <class T>
T* Grid<T>::get(int x, int y)
{
    if (!checkBounds(x + this->xoffset, y + this->yoffset, this->sizex, this->sizey))
        return NULL;
    
    return this->array[(y + this->yoffset) * sizex + (x + this->xoffset)];
}

template <class T>
void Grid<T>::clear()
{
    for (int i = 0; i < this->sizex * this->sizey; i++)
    {
        this->array[i] = NULL;
    }
}
