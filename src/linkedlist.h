#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


template <class T>
class FastLinkedList {
    public:
        
        T* last;	
	T* first;
        int length;
        
	FastLinkedList();
        FastLinkedList(const FastLinkedList<T>& c);
        FastLinkedList<T>& operator=(const FastLinkedList<T>& c);
        
	virtual ~FastLinkedList();

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
        LinkNode<T>* node;
        FastLinkedList< LinkNode<T> >* list;
        
	LinkIterator(LinkNode<T>* node, FastLinkedList< LinkNode<T> >* list) : node(node), list(list)
	{}

        bool isValid();
        virtual void step();
        virtual void reset();
        void deleteAndStep();
        T item();
};

template <typename T>
class ReverseLinkIterator : public LinkIterator<T> {
    public:
        ReverseLinkIterator(LinkNode<T>* node, FastLinkedList< LinkNode<T> >* list) : LinkIterator<T>(node, list)
	{}

        void step();
        void reset();
};

template <typename T>
class WrappingLinkIterator : public LinkIterator<T> {
    public:
        WrappingLinkIterator(LinkNode<T>* node, FastLinkedList< LinkNode<T> >* list) : LinkIterator<T>(node, list)
	{}

        void step();
        void reset();
};

template <typename T>
class ReverseWrappingLinkIterator : public LinkIterator<T> {
    public:
        ReverseWrappingLinkIterator(LinkNode<T>* node, FastLinkedList< LinkNode<T> >* list) : LinkIterator<T>(node, list)
	{}

        void step();
        void reset();
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
        int getLength();
        bool hasItem(T* item);
        T getFirst();
        T getLast();
        void removeFirst();
        void removeLast();
	void addItem(T p);
	void addItemLast(T p);
        LinkIterator<T> getIterator();
        ReverseLinkIterator<T> getReverseIterator();
        WrappingLinkIterator<T> getWrappingIterator();
        ReverseWrappingLinkIterator<T> getReverseWrappingIterator();
};

#include "linkedlist.hpp"

#endif
