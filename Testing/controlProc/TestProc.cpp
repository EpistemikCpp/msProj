// TestProc.cpp

#include <cstring>
#include "TestProc.h"

void TestProc::setData( int i )
  {
   data = i ;
   TestProc::testStat = i ;
//   this = &myTestProc ;
  }

int TestProc::getData()
  { return data ; }


void TestProc::initStr( )
  { strcpy( str, "this is a basic string" ) ; }

char* TestProc::getStr()
  { return str ; }

void TestProc::addStr( char* newstr )
  { strcat( str, newstr ) ; }
