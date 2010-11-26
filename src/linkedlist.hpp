#include "stdlib.h"
#include "stdio.h"


template <class T>
void LinkedList<T>::addItemLast(T* p)
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
    
    p->list = this;
}

template <class T>
void LinkedList<T>::addItem(T* p)
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
    
    p->list = this;
}

template <class T>
void LinkedList<T>::deleteItem(T* p)
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

	delete p;
}

template <class T>
T* LinkedList<T>::releaseItem(T* p)
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
    
	return p;
}

template <class T>
void LinkedList<T>::destroy()
{
	while (first != 0)
	{
		deleteItem(first);
	}
}

template <class T>
void LinkedList<T>::release()
{
	while (first != 0)
	{
		releaseItem(first);
	}
}

template <class T>
void LinkedList<T>::swap(T* p, T* q)
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
void LinkedList<T>::insertNext(T* p, T* n)
{
	if (n==0) 
	{
		addItemLast(p);
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
		addItemLast(p);
	
}
template <class T>
void LinkedList<T>::insertPrev(T* p, T* n)
{
	if (n==0) 
	{
		addItem(p);
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
		addItem(p);
	
}
