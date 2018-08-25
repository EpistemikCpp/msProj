// charTest.cpp
// see if char's can be compared using '==' 

#include <iostream>
using namespace std;

const int PLACE = 14 ;
const int OFFSET = 9 ;
char* myChars = "one ring to rule them all" ;
char* moreChars = "to rule them all" ;
char* testChars ;

///// MAIN /////
void main()
 {
  // compare a char[] to a literal character
  if( myChars[PLACE] == 'l' )
    cout << "char[] and literal character CAN be compared with '==' !" << endl ;
  else
      cout << "char[] and literal character CANNOT be compared with '==' !" << endl ;
  cout << "myChars[" << PLACE << "] == '" << myChars[PLACE] << "'\n" << endl ;

  // compare a char[] to another char[]
  if( myChars[PLACE] == moreChars[PLACE] )
    cout << "char[]'s CAN be compared with '==' !" << endl ;
  else
      cout << "char[]'s CANNOT be compared with '==' !" << endl ;
  cout << "moreChars[" << PLACE << "] == '" << moreChars[PLACE] << "'\n" << endl ;

  // compare a char* to a literal string
  if( myChars == "one ring to rule them all" )
    cout << "char* and literal string CAN be compared with '==' !" << endl ;
  else
      cout << "char* and literal string CANNOT be compared with '==' !" << endl ;
  cout << "myChars == '" << myChars << "'\n" << endl ;

  // compare two strings (char*)
  testChars = &myChars[OFFSET] ;
  cout << "testChars == '" << testChars << "'" << endl ;
  if( testChars == moreChars )
    cout << "Strings (char*'s) CAN be compared with '==' !" << endl ;
  else
      cout << "Strings (char*'s) CANNOT be compared with '==' !" << endl ;
  cout << "moreChars == '" << moreChars << "'\n" << endl ;

 }
//main()