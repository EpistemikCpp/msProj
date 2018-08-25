// refTest.cpp

#include "refTest.h"

// just set a basic string in the Constructor
Test::Test()
  { strcpy(str, "this is a ") ; }

void Test::setdata( int i )
  { data = i ; }

int Test::getdata()
  { return data ; }

char* Test::getstr()
  { return str ; }

void Test::addstr( char* newstr )
  { strcat(str, newstr) ; }

// display the variables
void Test::show( const char* name )
  {
   cout << name << " data == " << data << endl ;
   cout << name << " str is '" << str << "'" << endl ;
   cout << name << " address is " << this << endl ; 
   cout << name << " size is " << sizeof(*this) << endl ;
  }
