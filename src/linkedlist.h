#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


template <class T>
class LinkNode {
public:
	
	LinkNode* prev;
	LinkNode* next;

	T* object;

	LinkNode():prev(0), next(0)
	{}
};

template <class T>
class LinkedList {

public:

	T* last;	
	T* first;
	
	LinkedList():last(0), first(0)
	{}

	void addItem(T* p);
	void addItemLast(T* p);
	void deleteItem(T* p);
	T* releaseItem(T* p);
	void swap(T* p, T* q);
	void destroy();
	void release();
	void insertNext(T* p, T* n);
	void insertPrev(T* p, T* n);

	~LinkedList()
	{}
};

template <class T>
class Linkable {
public:
	T* prev;
	T* next;
        LinkedList<T>* list;

	Linkable():prev(0), next(0)
	{}
};


#include "linkedlist.hpp"

#endif
