
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
Grid<T>::Grid(int sizex, int sizey)
{
    this->array = new T*[sizex * sizey];

    this->sizex = sizex;
    this->sizey = sizey;

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
   if (!checkBounds(x, y, this->sizex, this->sizey))
        return;
   
   this->array[y * sizex + x] = item;
}

template <class T>
T* Grid<T>::remove(int x, int y)
{
    if (!checkBounds(x, y, this->sizex, this->sizey))
        return NULL;
    
    T* retval = this->array[y * sizex + x];
    this->array[y * sizex + x] = NULL;
    return retval;
}

template <class T>
T* Grid<T>::get(int x, int y)
{
    if (!checkBounds(x, y, this->sizex, this->sizey))
        return NULL;
    
    return this->array[y * sizex + x];
}

template <class T>
void Grid<T>::clear()
{
    for (int i = 0; i < this->sizex * this->sizey; i++)
    {
        this->array[i] = NULL;
    }
}
