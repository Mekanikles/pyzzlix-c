#include "stdlib.h"
#include "stdio.h"

#include "linkedlist.h"

template <class T>
FastLinkedList<T>::~FastLinkedList()
{
    this->destroyAll();
}

template <class T>
int FastLinkedList<T>::getLength()
{
    return length;
}

template <class T>
void FastLinkedList<T>::addLinkLast(T* p)
{
    bool isempty = (first == 0);
    if (!isempty) {
        last->next = p;
        p->prev = last;
        p->next = 0;
    }
    else
        first=p;
    last = p;

    length++;
    
    p->list = this;
}

template <class T>
void FastLinkedList<T>::addLink(T* p)
{   
    bool isempty = (first == 0);
    if (!isempty) {
        first->prev = p;
        p->next = first;
        p->prev = 0;
    }
    else
        last=p;
    first = p;

    length++;
    
    p->list = this;
}

template <class T>
void FastLinkedList<T>::deleteLink(T* p)
{   
    bool isfirst = (p->prev == 0);
    bool islast = (p->next == 0);

    if (islast) {
        if (isfirst) {
            first = 0;
            last = 0;
        } else {
            last = p->prev;
            p->prev->next = 0;
        }
    } else {
        if (isfirst) {
            first = p->next;
            first->prev = 0;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
    }

    length--;
    
    delete p;
}

template <class T>
T* FastLinkedList<T>::releaseLink(T* p)
{
    bool isfirst = (p->prev == 0);
    bool islast = (p->next == 0);
    if (islast) {
        if (isfirst) {
            first = 0;
            last =0;
        } else {
            last = p->prev;
            p->prev->next = 0;
			
        }
    } else {
        if (isfirst) {
            first = p->next;
            first->prev = 0;
        } else {
            p->prev->next = p->next;
            p->next->prev = p->prev;
        }
    }

    p->prev = 0;
    p->next = 0;

    p->list = NULL;

    length--;
    
    return p;
}

template <class T>
void FastLinkedList<T>::destroyAll()
{
    while (first != 0)
    {
        deleteLink(first);
    }
}

template <class T>
void FastLinkedList<T>::swap(T* p, T* q)
{
    T* temp = p->next; 
    p->next =q->next;
    q->next->prev = p;
    q->next = temp;
    temp->prev =q;

    temp = p->prev; 
    p->prev =q->prev;
    q->prev->next = p;
    q->prev = temp;
    temp->next =q;
}

template <class T>
void FastLinkedList<T>::insertNext(T* p, T* n)
{
    length++;
    
    if (n==0) 
    {
        addLinkLast(p);
        return;
    }
    
    bool islast = (last == n);
    if (!islast) {
        p->prev = n;
        p->next = n->next;
        n->next->prev = p;
        n->next = p;
    }
    else
        addLinkLast(p);

    p->list = this;
}
template <class T>
void FastLinkedList<T>::insertPrev(T* p, T* n)
{
    length++;
    
    if (n==0) 
    {
        addLink(p);
        return;
    }

    bool isfirst = (first == n);
    if (!isfirst) {
        p->next = n;
        p->prev = n->prev;
        n->prev->next = p;
        n->prev = p;
    }
    else
        addLink(p);

    p->list = this;
}

template <class T>
bool LinkIterator<T>::isAtEnd()
{
    return (this->node->next == NULL);
}

template <class T>
bool LinkIterator<T>::isAtBeginning()
{
    return (this->node->prev == NULL);
}

template <class T>
void LinkedIterator<T>::deleteMoveNext()
{
    
    
    if (this->first != NULL)
        this->deleteLink(this->first);
}

template <class T>
void LinkedIterator<T>::deleteMovePrevious()
{
    if (this->first != NULL)
        this->deleteLink(this->first);
}

template <class T>
void LinkIterator<T>::next()
{
    assert (this->node != NULL);
    this->node = this->node->next;
}

template <class T>
void LinkIterator<T>::previous()
{
    assert (this->node != NULL);
    this->node = this->node->next;
}

template <class T>
T LinkIterator<T>::item()
{
    assert (this->node != NULL);
    return this->node->item;
}

template <class T>
T LinkedList<T>::clear()
{
    this->destroyAll();
}

template <class T>
T LinkedList<T>::getFirstItem()
{
    assert(this->first != NULL);
    return this->first->item;
}

template <class T>
T LinkedList<T>::getLastItem()
{
    assert(this->last != NULL);
    return this->last->item;
}

template <class T>
void LinkedList<T>::removeFirst()
{
    if (this->first != NULL)
        this->deleteLink(this->first);
}

template <class T>
void LinkedList<T>::removeLast()
{
    if (this->last != NULL)
        this->deleteLink(this->last);
}

template <class T>
void LinkedList<T>::addItem(T p)
{
    this->addLink(new LinkNode<T>(p));
}

template <class T>
void LinkedList<T>::addItemLast(T p)
{
    this->addLinkLast(new LinkNode<T>(p));
}

template <class T>
LinkIterator<T> LinkedList<T>::getHeadIterator()
{
    return LinkIterator<T>(this->first);
}

template <class T>
LinkIterator<T> LinkedList<T>::getEndIterator()
{
    return LinkIterator<T>(this->last);
}
    

