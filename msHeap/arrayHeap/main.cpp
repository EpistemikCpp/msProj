// FILE: main.cpp
// NAME: Mark Sattolo

#include <cstdlib>
#include <conio.h>

#include "..\test.h"
#include "arrayheap.h"

const int SEED = 17 ;
char* MYNAME = "arrayHeap" ;

/////////// FREE FUNCTIONS ////////////////////

/* implement a compare_fxn for 'less than'
   >> MUST BE STRICTLY LESS - NOT LESS OR EQUAL !!! */
bool lt( const test_class& c1, const test_class& c2 )
  { return *const_cast<test_class&>(c1) < *const_cast<test_class&>(c2) ; }

// get a random number
int myRand( int n )
  { return rand() % n ; }


////////////// MAIN /////////////////////////////////////////////////////////
void main( int argc, char* argv[] )
  {
   // create default values
   char* paramlist[] = { MYNAME, "13", "9", "102", "17", "30", "55", "43" } ;
   
   // check that there are values for nodes on the command line
   if( argc < 3 )
    {
	  // advise of usage and use default parameters if necessary
	  cerr << endl << "Usage: '" << MYNAME << " int1 int2 ... int_n'" << endl ;
	  argc = sizeof(paramlist)/sizeof(char*) ;
	  argv = paramlist ;
	  cout << endl << "Default values: " ;
     for( int i=1; i<(argc-1); i++ )
        cout << argv[i] << ", " ;
     cout << argv[argc-1] << endl ;
	  //exit(1) ;
	 }
   
	// create an array heap, of type 'test_class', called 'myHeap'
	array_heap<test_class>  myHeap( lt, SMALLER_FIRST );
   
	// process each command line value
	for( int i=1; i<argc; ++i )
	 {
     // create a test_class with var i and put it on the heap
	  handle<test_class>& hand1 = myHeap.push( test_class(atof(argv[i])) );
     
     // change every 2nd node value and see if the heap adjusts properly
	  if( i % 2 == 0 )
		 {
        // get a random value for k
		  int k = myRand( SEED );
		  /* use the overloaded * to get a reference to the element (test_class)
		     of hand1 and then remove the "const-ness" with a cast
		  	  - then use an overloaded * to get a reference to the actual integer
		  	  value held by the test_class and increment it by k */
		  *const_cast<test_class&>(*hand1) += k;
		  /* inform the heap that one of its nodes has changed and thus 
           the heap may need to adjust itself */
		  myHeap.priority_change( hand1 );
		 }
	 }//endfor
   
	cout << endl ;
	// print out the heap's structure and references
	myHeap.print(cout);
	cout << "-------------" << endl;
   
	// destroy the heap and print the values
	while( !myHeap.empty() )
	  {
		cout << myHeap.top() << ' ';
		myHeap.pop();
	  }

	cout << endl;
	getch() ; // pause program to see the results
  }
// main()