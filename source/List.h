/*********************************************************************************
*	Developers:
*		Anil KAYAN	https://bitbucket.org/anilkayan
*		Onur OZUDURU	https://github.com/onurozuduru
*
*License: The MIT License (MIT)
*
*   Copyright (c) 2015 Onur Ozuduru - Anil Kayan
*   Permission is hereby granted, free of charge, to any person obtaining a copy
*   of this software and associated documentation files (the "Software"), to deal
*   in the Software without restriction, including without limitation the rights
*   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*   copies of the Software, and to permit persons to whom the Software is
*   furnished to do so, subject to the following conditions:
*  
*   The above copyright notice and this permission notice shall be included in all
*   copies or substantial portions of the Software.
*  
*   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*   SOFTWARE.
*********************************************************************************/

//************************	List.h	************************
//		A singly circular linked list

#include <iostream>
using namespace std;

#ifndef LIST_H
#define LIST_H

//	Node struct
template<class T>
struct Node
{
//======================== DATA MEMBERS ====================

    T		data;
    int		counter;
    Node	*next;

//======================== LIFECYCLE =======================

    //	Default constructor
    Node()
    {
        next = NULL;
        counter = 0;
    }

    //	Destructor
    ~Node()
    {
    }

    //	Constructor
    Node( const T &data, Node *next = NULL )
    {
        this->data = data;
        this->next = next;
        this->counter = 1;
    }
};// End of Node struct

//	List class
template<class T>
class List
{
protected:
    Node<T>	*head,	*tail;
    int size;//		size of the list
public:
    List();
    ~List();

    void addToHead( const T & );
    void addToTail( const T & );
    void removeFromHead();
    void removeFromTail();
    bool isEmpty() const;
    void printList();

    Node<T>* getHead() const;
    Node<T>* getTail() const;
    int		 getSize() const;
};

//////////////////////////	PUBLIC	////////////////////////

//======================== LIFECYCLE =======================

template<class T>
List<T>::List()
{
    this->head = this->tail = NULL;
    size = 0;
}
template<class T>
List<T>::~List()
{
    while	( !isEmpty() )
        { removeFromHead(); }
}

//======================== FUNCTIONS ======================

template<class T>
void List<T>::addToHead( const T &data )
{
    if ( head != NULL ) {
        Node<T>	*newNode	= new Node<T>( data, head );
        tail->next	= head	= newNode;
        size++;
    }
    else {
        head = tail	= new Node<T>( data );
        size++;
    }
}
template<class T>
void List<T>::addToTail( const T &data )
{
    if ( tail != NULL ) {
        Node<T> *newNode = new Node<T>( data, head );
        tail->next = newNode;
        tail = tail->next;
        size++;
    }
    else	{
        tail = head	= new Node<T>( data );
        size++;
    }
}
template<class T>
void List<T>::removeFromHead()
{
    if ( head == NULL )
        { return; }

    //	if there is only one element
    if ( tail->next == NULL || tail->next == tail ) {
        Node<T>	*temp = tail;
        head = tail	= NULL;
        delete	temp;
        size--;
        return;
    }

    tail->next = head->next;
    Node<T>	*temp = head;
    head = head->next;
    delete	temp;
    size--;
}
template<class T>
void List<T>::removeFromTail()
{
    //	If List is Empty --> do nothing
    if ( tail == NULL )
        { return; }

    //	If there is only one element
    if ( tail->next == NULL || tail->next == tail ) {
        Node<T>	*temp = tail;
        head = tail = NULL;
        delete	temp;
        size--;
        return;
    }

    Node<T>	*temp = head;

    while ( temp->next != tail )
        { temp = temp->next; }

    tail = temp;
    temp = temp->next;
    tail->next = head;
    delete	temp;
    size--;
}
template<class T>
bool List<T>::isEmpty() const
{

    //	If List is Empty --> do nothing
    if ( tail == NULL )
        { return true; }

    return false;
}
template<class T>
void List<T>::printList()
{
    if ( isEmpty() ) {
        cout<<"List is Empty\n";
        return;
    }

    Node<T>	*temp = head;

    while ( temp != tail ) {
        cout<<temp->data<<endl;
        temp = temp->next;
    }

    cout<<temp->data<<endl;
}

template<class T>
Node<T>* List<T>::getHead()	const
{
    return head;
}
template<class T>
Node<T>* List<T>::getTail()	const
{
    return tail;
}
template<class T>
int List<T>::getSize()	const
{
    return size;
}

#endif
