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

//************************	Dictionary.cpp	************************

#include "Dictionary.h"

//////////////////////////	PUBLIC	////////////////////////

//========================	LIFECYCLE	=====================

Dictionary::Dictionary() : List()
{

}
Dictionary::Dictionary( const Dictionary &copy )//	Copy Constructer
{
    *this = copy;
}
Dictionary::~Dictionary()
{
    //	Since Dictionary is a derived class from List, we don't need to write destructor.
		//	List class' destructor is working.
}

//========================	FUNCTIONS	=====================

void	Dictionary::insertOrderly( const string &word )
{

    //	If list is empty --> add word to head
    if ( head == NULL ) {
        addToHead( word );
        return;
    }

    Node<string> *temp = head;

        //	If there is only one element --> enter the while loop
    while ( temp != tail	|| tail->next==NULL || tail->next == tail ) {

        //		If word is already on the list --> increase the counter
        if ( word == temp->data )	{
                temp->counter++;
                return;
        }

        //		If word is less than the first element on the list --> add word to head
        if ( word < temp->data ) {
                addToHead( word );
                return;
        }

        //		If there is only one element on the list AND word is greater than it --> add word to head
        if ( tail->next == NULL || tail->next == tail && word > temp->data )	{
                addToTail( word );
                return;
        }

        //		If word must be added in the middle
        if ( word < temp->next->data ) {
                Node<string> *newNode = new Node<string>( word, temp->next );
                temp->next = newNode;
                size++;
                return;
        }

        temp	= temp->next;//	assign temp to temp next
    }//	End Of While Loop

        //	If word is equal to tail --> increase counter of the tail
        if ( word == tail->data ) {
            tail->counter++;
            return;
        }

		//	If the function is not terminated because of the previous conditions --> add word to tail
        addToTail( word );

}

int Dictionary::getNodeByValue( string &word )
{
    if ( isEmpty() )
        { return 0; }

    for ( int i = 0; i < word.length(); i++ )
        { word[i] = tolower( word[i] ); }

    Node<string> *temp = head;

	//	If temp is not equal to tail OR If there is only one element on the list --> enter the while loop
    while ( temp != tail || tail->next == NULL ) {

        //		If there is only one element on the list AND it is not equal to word --> return zero
        if ( temp == NULL )
            { return 0; }

        if ( word == temp->data )
            { return temp->counter; }

		//	If word is less temp, that means word is not on the list. So return zero
        if ( word < temp->data )
            { return 0; }

        temp = temp->next;
    }

    if ( word == tail->data )
        { return tail->counter; }

    return 0;
}

void Dictionary::addToHead( const string &data )
{

    //		If list is empty which means head == NULL don't try to reach head's data
		//	If data is less than head's data --> call List class' addToHead function
    if ( isEmpty() || data < head->data )
        { List::addToHead( data ); }
    else if ( data == head->data )
        { head->counter++; }
    else
        { throw invalid_argument( "Given Word cannot be added to head! Since the alphabetic order cannot be broken!" ); }
}

void Dictionary::addToTail( const string &data )
{

    //	If list is empty which means tail == NULL don't try to reach tail's data
		//	If data is less than tail's data --> call List class' addToTail function
    if ( isEmpty() || data > tail->data )
        { List::addToTail( data ); }
    else if ( data == tail->data )
        { tail->counter++; }
    else
        { throw invalid_argument( "Given Word cannot be added to tail! Since the alphabetic order cannot be broken!" ); }
}

//======================== OPERATORS =======================

Dictionary &Dictionary::operator=( const Dictionary &right )
{

    //	If both objects are empty --> do nothing
    if ( this->isEmpty() && right.isEmpty() )
        { return *this; }

    //	If right is empty --> delete all nodes of the left list
    if ( right.isEmpty() ) {
        while ( !this->isEmpty() )
            { this->removeFromHead(); }

        return *this;
    }

    //	If left is empty
    if ( this->isEmpty() ) {
        Node<string> *leftTemp	= this->getHead();
        Node<string> *rightTemp	= right.getHead();

        //	add nodes to end of the left object
        while ( this->getSize() != right.getSize() ) {
            this->addToTail( rightTemp->data );
            leftTemp  = this->getTail();
            leftTemp->counter = rightTemp->counter;
            leftTemp  = leftTemp->next;
            rightTemp = rightTemp->next;
        }

        return *this;
    }

    //	If sizes of both objects are equal --> assign right's datas and counters to left
    if ( this->getSize() == right.getSize() ) {
        Node<string> *leftTemp	= this->getHead();
        Node<string> *rightTemp	= right.getHead();

        while ( leftTemp != this->getTail() ) {
            leftTemp->data = rightTemp->data;
            leftTemp->counter = rightTemp->counter;

            leftTemp  = leftTemp->next;
            rightTemp = rightTemp->next;
        }

        this->tail->data = right.tail->data;
        this->tail->counter = right.tail->counter;

        return *this;
    }

    //	If size of left less than right
    if ( this->getSize() < right.getSize() ) {

        Node<string> *leftTemp = this->getHead();
        Node<string> *rightTemp = right.getHead();

        for ( int i = 0; i < this->getSize(); i++ ) {
            leftTemp->data = rightTemp->data;
            leftTemp->counter = rightTemp->counter;

            leftTemp = leftTemp->next;
            rightTemp = rightTemp->next;
        }

        //	add nodes to end of left
        while ( this->getSize() != right.getSize() ) {
            this->addToTail( rightTemp->data );
			leftTemp = this->getTail();
			leftTemp->counter = rightTemp->counter;
            leftTemp = leftTemp->next;
            rightTemp = rightTemp->next; 
        }

        return *this;
    }

    //	If size of left is greater than right
    if ( this->getSize() > right.getSize() ) {

        Node<string> *leftTemp = this->getHead();
        Node<string> *rightTemp = right.getHead();

        for ( int i = 0; i < right.getSize(); i++ ) {
            leftTemp->data = rightTemp->data;
            leftTemp->counter = rightTemp->counter;

            leftTemp = leftTemp->next;
            rightTemp = rightTemp->next;
        }

        //	delete left object's extra nodes
        for ( int i = 0; i < ( this->getSize() - right.getSize() + 1 ); i++ )
            { this->removeFromTail(); }

        return *this;
    }
}

bool Dictionary::operator==( const Dictionary &right ) const
{
    if ( this->getSize() != right.getSize() )
        { return false; }

    Node<string> *leftTemp = this->getHead();
    Node<string> *rightTemp = right.getHead();

    for ( int i = 0; i < this->getSize(); i++ ) {
        if ( leftTemp->data != rightTemp->data || leftTemp->counter != rightTemp->counter )
            { return false; }

        leftTemp = leftTemp->next;
        rightTemp = rightTemp->next;
    }

    return true;
}

bool Dictionary::operator!=( const Dictionary &right ) const
{
    return !( *this == right );
}
