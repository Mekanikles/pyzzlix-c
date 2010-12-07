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
    LinkedList< LabelItem<T> > list;

        
    LabelMap()
    {}

    ~LabelMap()
    {
        this->list.destroy();
    }
        
    void set(const string& label, T* item);
    void remove(const string& label);
    T* get(const string& label);
    bool exists(const string& label);

};

#include "labelmap.hpp"

#endif
