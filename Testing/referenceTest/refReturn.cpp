// refReturn.cpp

#include "refReturn.h"

// just set a basic string in the Constructor
ReturnTest::ReturnTest()
  { strcpy(strc, "I am a ") ; }

// Return a local variable by reference -> warning C4172 from compiler
Test& ReturnTest::returnLocal()
  {
   Test t1 ;
   t1.addstr( "[inside ReturnTest::returnStatic] " ) ;
   return t1 ;
  }

// return a dynamically created object
Test ReturnTest::returnDynamic()
  {
   Test *t2 = new Test ;
   t2->addstr( "[inside ReturnTest::returnDynamic] " ) ;
   return *t2 ;
  }
