// FILE: main.cpp
// NAME: Mark Sattolo

#include <stdlib.h>
#include <iostream.h>

#include "test.h"
#include "heap.h"
#include "aheap.h"

/////////// FREE FUNCTIONS ////////////////////

// implement a compare_fxn for 'less than'
// *** MUST BE STRICTLY LESS - NOT LESS OR EQUAL !!! ***
bool lt(const test_class& c1, const test_class& c2)
  { return *const_cast<test_class&>(c1) < *const_cast<test_class&>(c2) ; }

// get a random number
int rrr(int n)
  { return rand() % n ; }

////////////// MAIN ///////////////////////////
int main(int argc, char* argv[])
  {
	 // create default values
	 char* paramlist[] = {"MVCpp_Heap", "3", "9", "12", "17", "30", "55", "43"} ;
	// check that there are values for nodes on the command line
	if (argc < 3)
	 {
	  // advise of usage and create default parameters if needed
	  cerr << "Usage: 'heap int1 int2 int3 intx ...' " << endl ;
	  cout << "MVCpp_Heap: 3, 9, 12, 17, 30, 55, 43" << endl ;
		argc = 8 ;
		argv = paramlist ;
	  //exit(1) ;
	 }

	// create an array heap, of type 'test_class', called 'AAA'
	array_heap<test_class> AAA(lt, SMALLER_FIRST);

	// push the command line values onto the heap
	for (int i=1; i<argc; ++i)
	  {
		handle<test_class>& h1 = AAA.push( test_class(atof(argv[i])) );
	  /* randomly change some node values and see if the heap adjusts properly */
		if (i % 2 == 0)
		  {
			int k = rrr(10);
			/* use the overloaded * to get a reference to the element (test_class)
				of h1 and remove the "const-ness" with a cast
				- then use an overloaded * to get a reference to the actual integer
				  value held by the test_class and increment it by k */
			*const_cast<test_class&>(*h1) += k;
			/* inform the heap that one of the nodes has changed and the heap
				may need to adjust itself */
			AAA.priority_change(h1);
		  }
	  }

	cout << endl ;
	// print out the heap's structure and references
	AAA.print(cout);
	cout << "-------------" << endl;

	// destroy the heap and print the values
	while(!AAA.empty())
	  {
		cout << AAA.top() << ' ';
		AAA.pop();
	  }

	cout << endl;
	return 0;
  }
//main()