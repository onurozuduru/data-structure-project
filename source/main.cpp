///////////////////////////////////////////////////////////////////////////////////////////
//	Developers:
//		Anil KAYAN	https://bitbucket.org/anilkayan
//		Onur OZUDURU	https://github.com/onurozuduru
//
//	This work is licensed under the Creative Commons Attribution 4.0 International License.
//	To view a copy of this license, visit http://creativecommons.org/licenses/by/4.0/.
///////////////////////////////////////////////////////////////////////////////////////////

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


