#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


template <class T>
class FastLinkedList {

    public:
        
	T* last;	
	T* first;
        int length;
	
	FastLinkedList():last(0), first(0)
	{}


	virtual ~FastLinkedList();

        int getLength();
	void addLink(T* p);
	void addLinkLast(T* p);
	void deleteLink(T* p);
	T* releaseLink(T* p);
	void swap(T* p, T* q);
	void destroyAll();
	void insertNext(T* p, T* n);
	void insertPrev(T* p, T* n);

};

template <class T>
class Linkable {
    public:
        T* prev;
	T* next;
        FastLinkedList<T>* list;
        
	Linkable():prev(0), next(0), list(0)
	{}
        
        virtual ~Linkable() {}
};



template <typename T>
class LinkNode : public Linkable< LinkNode<T> > {
    public:

	T item;

	LinkNode(T item) : Linkable< LinkNode<T> >(), item(item)
	{}
};


template <typename T>
class LinkIterator {
    public:
	
	LinkNode<T> node;

	LinkIterator(LinkNode<T> node) : node(node)
	{}

        bool isAtEnd();
        bool isAtBeginning();
        void forward();
        void back();
        T item();
        
};


template <typename T>
class LinkedList : public FastLinkedList< LinkNode<T> > {
    public:
        LinkedList() : FastLinkedList< LinkNode<T> >()
        {
        }

        virtual ~LinkedList()
	{}

        void clear();
        T getFirstItem();
        T getLastItem();
        void removeFirst();
        void removeLast();
	void addItem(T p);
	void addItemLast(T p);
        LinkIterator<T> getHeadIterator();
        LinkIterator<T> getEndIterator();
};


#include "linkedlist.hpp"

#endif
