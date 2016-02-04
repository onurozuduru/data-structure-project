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

//************************	main.cpp	************************

#include "WordCounter.h"

void menu( WordCounter &wc )
{
    char choice;

    while ( 1 ) {
        cout<<"(1) List the most popular words in the text.\n"
            <<"(2) Get the total number of words.\n"
            <<"(3) Get the counter of the given word.\n"
            <<"(4) Print words.\n"
            <<"(q) Quit\n";

        cin>>choice;

        if ( choice == 'q' || choice == 'Q' )
            { break; }
        else if ( choice == '1' ) {
            int popNum;
            cout<<"Please enter number of words which will be listed: ";
            cin>>popNum;

            try {
                wc.listPopular( popNum );
                cout<<endl;
            }
            catch ( invalid_argument &error ) {
                cout<<error.what()<<endl<<endl;
            }
        }
        else if ( choice == '2' )
            { cout<<"There are "<<wc.getSize()<<" number of words in your dictionary.\n"<<endl; }
        else if ( choice == '3' ) {
            string word;
            cout<<"Please enter a word: ";
            cin>>word;
            cout<<"Counter of the word \""<<word<<"\" is "<<wc.getCounter( word )<<endl<<endl;
        }
        else if ( choice == '4' )
            { wc.print(); }
        else
            { cout<<"Invalid value!\n"<<endl; }
    }//End Of Loop

}

int main( int argc, char *argv[] )
{

    if ( argc == 1 ) {
        cout<<"Enter the file name\n";
        return 0;
    }

    try {
        WordCounter wc( argv[1] );
        menu( wc );
    }
    catch ( invalid_argument &error ) {
        cout<<error.what()<<endl;
    }

    return 0;
}


