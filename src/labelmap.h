#ifndef _MAP_H
#define _MAP_H

#include "linkedlist.h"

template<class T>
struct LabelItem : public Linkable< LabelItem<T> >
{
        string s;
        T* item;
        
        LabelItem(const string& s, T* item)
            :s(s), item(item)
        {        
        }
};


template <class T>
class LabelMap
{
    public:
        FastLinkedList< LabelItem<T> >* list;
        
        
        LabelMap():
            list(new FastLinkedList< LabelItem<T> >())
        {
        }
        
        ~LabelMap()
        {
            delete this->list;
        }
        
        void set(const string& label, T* item);
        void remove(const string& label);
        T* get(const string& label);
        bool exists(const string& label);
        
};

#include "labelmap.hpp"

#endif
