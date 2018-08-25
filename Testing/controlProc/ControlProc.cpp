// ControlProc.cpp

#include "ControlProc.h"

void ControlProc::setTestProc( int i )
  { myTestProc.setData( i ) ; }

int ControlProc::getTestProc()
  { return myTestProc.data ; }

float ControlProc::getNum()
  { return num ; }

void ControlProc::addNum( float f )
  {
   num += f ;
//   this = (class ControlProc *const)&myTestProc ;
  }

void ControlProc::test( int i )
  {
   // access the TestProc directly and call one of its methods
   myTestProc.initStr() ;
   cout << " str is '" << myTestProc.str << "'" << endl ;
   // access the TestProc directly and access one of its variables
   strcat( myTestProc.str, " with hello there!" ) ;
   cout << " str is '" << myTestProc.getStr() << "'" << endl << endl ;
   cout << " data == " << myTestProc.data << endl ;
   // access TestProc data directly
   myTestProc.data = i ;
   cout << " data == " << myTestProc.getData() << endl ;
   cout << endl << "End of ControlProc::test() " << endl ;
  }

// initialize the static variable
int TestProc::testStat = 0 ;

///////// MAIN /////////////////////////////////////////////////////
void main()
  {
   // create a ControlProc object
   ControlProc cp1 ;
   // check the static variable of TestProc
   printf( "TestProc.testStat == %d \n\n", TestProc::testStat ) ;
   // access TestProc through a ControlProc method
   cp1.setTestProc( 13 ) ;
   // check the static variable of TestProc
   printf( "TestProc.testStat == %d \n\n", TestProc::testStat ) ;
   // access TestProc data through the cp1 object
   printf( "TestProc.data == %d \n\n", cp1.myTestProc.data ) ;
   // try the cp1 test method to access various members of TestProc
   cp1.test( 47 ) ;

   printf( "End of main() \n" ) ;
  }
//main()
