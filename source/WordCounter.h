///////////////////////////////////////////////////////////////////////////////////////////
//	Developers:
//		Anil KAYAN	https://bitbucket.org/anilkayan
//		Onur OZUDURU	https://github.com/onurozuduru
//
//	This work is licensed under the Creative Commons Attribution 4.0 International License.
//	To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
///////////////////////////////////////////////////////////////////////////////////////////

//************************	WordCounter.h	************************

#include <fstream>
#include "Dictionary.h"

#ifndef WORDCOUNTER_H
#define WORDCOUNTER_H

class WordCounter
{
private:
    Dictionary dic;
    string fileName;

    string fixWord( string & );
    void fillDictionary();
public:
    WordCounter( const string & );
    ~WordCounter();

    //	it is not "const string &" because we swap the word with lower case
    int getCounter( string & );
    int getSize();
    void print();
    void listPopular( const int & );
};

#endif
