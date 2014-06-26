///////////////////////////////////////////////////////////////////////////////////////////
//	Developers:
//		Anil KAYAN	https://bitbucket.org/anilkayan
//		Onur OZUDURU	https://github.com/onurozuduru
//
//	This work is licensed under the Creative Commons Attribution 4.0 International License.
//	To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
///////////////////////////////////////////////////////////////////////////////////////////

//************************	WordCounter.cpp	************************

#include "WordCounter.h"

//////////////////////////	PRIVATE	////////////////////////

string WordCounter::fixWord( string &word )
{
    for ( int i=0; i < word.length(); i++ ) {
        //	Set all characters to lower case
        word[i] = tolower( word[i] );

        bool isLetter = ( word[i] >= 'a' && word[i] <= 'z' );

        //	Note: "it" refers to i^th character of the word
        //	If it's at the beginning OR at the end and not a letter --> Delete character
        if ( ( i == 0 || i == word.length()-1 ) && !isLetter ) {
            word.erase( i,1 );
            i--;
        }

        //	If it's somewhere in the middle, it's not a letter --> Go inside if-else block
        else if ( !isLetter ) {
            
			//	If it's - OR ' --> check the next character
			if( word[i] == '-' || word[i] == '\'' ) {

				//	If the next character is not a letter --> Substring the new word --> Assign rest of the word as word
				//	Note: we know that i is not the last index
				if ( word[i+1]<'a' || word[i+1]>'z' ) {
					string str = word.substr( 0,i );
					dic.insertOrderly( str ); //			sent substring to insertOrderly
					word = word.substr( i );
					i = -1;
				}
				else {
					word.erase( i,1 );
					i--;
				}
			}
			//	If it's not - OR ' --> delete the character
			else {
				string str = word.substr( 0,i );
                dic.insertOrderly( str ); //			sent substring to insertOrderly
                word = word.substr( i );
                i = -1;
			}
			//	If the next character is a letter --> Continue to check the other characters
        }
    }//End Of For Loop

    //	End of the loop there are TWO cases can be seen as returned value:
    //	- First case --> a word which consists of lower case characters
    //	- Second case --> empty string ("")
    return word;
}//End Of Function

void WordCounter::fillDictionary()
{
	const char *f = fileName.c_str();//	convert string to char for ifstream
    ifstream file( f, ios::in );

    if ( !file.is_open() )
        { throw invalid_argument( "File is not exist!" ); }

    string word;

    while ( !file.eof() ) {
        file >> word;
        string x = fixWord( word );

        if ( x != "" )
            { dic.insertOrderly( word ); }
    }

    file.close();
}

//////////////////////////	PUBLIC	////////////////////////

//========================	LIFECYCLE	=====================

WordCounter::WordCounter( const string &fileName )
{
    this->fileName = fileName;
    fillDictionary();
}

WordCounter::~WordCounter()
{
}

//========================	FUNCTIONS	=====================

void WordCounter::listPopular( const int &num )
{
    if ( num > dic.getSize() ) {
        throw invalid_argument( "Given number is more than all the words on the text!" );
        return;
    }

    int s = dic.getSize();
    Node<string> *popularList = new Node<string>[s];
    Node<string> *temp = dic.getHead();

    for ( int i = 0; i < s; i++ ) {
        popularList[i].data = temp->data;
        popularList[i].counter = temp->counter;
        temp = temp->next;
    }

//	SHELL SORT
    int flag = 1;
    int d = s;

	// boolean flag (true when not equal to 0)
    while ( flag || ( d > 1 ) ) {
        // reset flag to 0 to check for future swaps
		flag = 0;
        d = ( d+1 ) / 2;

        for ( int i = 0; i < ( s - d ); i++ ) {
            if ( popularList[i + d].counter > popularList[i].counter ) {
				// swap positions i+d and i
                Node<string> tmp = popularList[i + d];
                popularList[i + d] = popularList[i];
                popularList[i] = tmp;
                // tells swap has occurred
				flag = 1;
            }
        }
    }

//	END OF SORTING
    for ( int i = 0; i < num; i++ ) {
        cout<<popularList[i].data<<"\t\t= "<<popularList[i].counter<<"\t";

        for ( int j = 0; j < popularList[i].counter/10; j++ )
            { cout<<"|"; }

        cout<<endl;
    }

    delete [] popularList;
}//End Of Function

int WordCounter::getCounter( string &word )
{
    return dic.getNodeByValue( word );
}

void WordCounter::print()
{
    dic.printList();
}

int WordCounter::getSize()
{
    return dic.getSize();
}
