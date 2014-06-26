///////////////////////////////////////////////////////////////////////////////////////////
//	Developers:
//		Anil KAYAN	https://bitbucket.org/anilkayan
//		Onur OZUDURU	https://github.com/onurozuduru
//
//	This work is licensed under the Creative Commons Attribution 4.0 International License.
//	To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
///////////////////////////////////////////////////////////////////////////////////////////

//************************	Dictionary.h	************************
//	An ordered singly circular linked list which consists of strings

#include <stdexcept>
#include <string>
#include "List.h"


#ifndef DICTIONARY_H
#define DICTIONARY_H

class Dictionary : public List<string>
{

public:
    Dictionary& operator=( const Dictionary & );
    bool operator==( const Dictionary & ) const;
    bool operator!=( const Dictionary & ) const;
    void insertOrderly( const string & );

    //	it is not "const string &" because we swap the word with lower case
    int getNodeByValue( string & );
    void addToHead( const string & );
    void addToTail( const string & );
    Dictionary();
    Dictionary( const Dictionary & );
    ~Dictionary();
};


#endif
