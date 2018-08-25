//refMain.cpp

#include "refReturn.h"

///// MAIN /////
void main()
  {
   int i = 1 ;
   ReturnTest ret ;

   /* test a reference to another object
      - see if 'class_test' and 'ref1_test' are really aliases  */
   Test class_test ;
//   test& ref1_test ; // won't compile: "references must be initialized"
   Test& ref1_test = class_test ;
   class_test.setdata( i++ ) ;
   class_test.addstr( "class" ) ;
   class_test.show( "class_test" ) ;
   cout << endl ;
   cout << "ref1 data == " << ref1_test.getdata() << endl ;
   ref1_test.addstr( "ref1" ) ;
   ref1_test.show( "ref1_test" ) ;
   cout << endl ;

   /* test returning a local variable to a reference object
      - see the assignments below */
   //Test& stat_test = ret.returnLocal() ; // PRODUCES A POINTER ERROR
   Test stat_test = ret.returnLocal() ;    // OK

   /* variant way to get a reference to a dynamic object
      - see "OOP in C++", Lafore, p.422 */
   Test& ref2_test = *(new Test);
   ref2_test.setdata( i++ ) ;
   ref2_test.addstr( "ref2" ) ;
   ref2_test.show( "ref2_test" ) ;
   cout << endl ;

   // return a dynamically created object from a method
   Test dyn_test( ret.returnDynamic() ) ;
   dyn_test.setdata( i++ ) ;
   dyn_test.addstr( "dyn" ) ;
   dyn_test.show( "dyn_test" ) ;
   cout << endl ;

   // create a reference to a Constructed object
   Test& ref3_test = Test() ;
   ref3_test.setdata( i++ ) ;
   ref3_test.addstr( "ref3" ) ;
   ref3_test.show( "ref3_test" ) ;
   cout << endl ;

   // create a dynamic object using a pointer and memory allocation with 'new'
   Test* pointer_test ;
   pointer_test = new Test() ;
   pointer_test->setdata( i++ ) ;
   pointer_test->addstr( "pointer" ) ;
   pointer_test->show( "pointer_test" ) ;
   cout << endl ;

   /* by this point in the program, a reference to a local variable will 
      almost certainly be overwritten and thus invalid  */
   stat_test.setdata( i++ ) ;
   stat_test.addstr( "stat" ) ;
   stat_test.show( "stat_test" ) ;
   cout << endl ;
  }
//main()