#include "stdlib.h"

template <class T>        
void LabelMap<T>::set(const string& label, T* item)
{
    if (this->exists(label))
    {
        this->remove(label);
    }
    
    LabelItem<T>* i = new LabelItem<T>(label, item);
    
    this->list.addItem(i);
}

template <class T>
void LabelMap<T>::remove(const string& label)
{
    LabelItem<T>* p = this->list.first;
    while(p != NULL)
    {
        if (p->s == label)
        {
            this->list.deleteItem(p);
            return;
        }

        p = p->next;
    }
}

template <class T>
T* LabelMap<T>::get(const string& label)
{
    LabelItem<T>* p = this->list.first;
    while(p != NULL)
    {
        if (p->s == label)
        {
            return p->item;
        }

        p = p->next;
    }

    return NULL;
}

template <class T>
bool LabelMap<T>::exists(const string& label)
{
    return (this->get(label) != NULL);

}
