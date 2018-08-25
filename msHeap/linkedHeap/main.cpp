//FILE: main.cpp
//NAME: Mark Sattolo

#include <stdlib.h>
#include <iostream.h>

#include "..\test.h"
#include "..\heap.h"
#include "linkedheap.h"

bool lt(const test_class& c1, const test_class& c2)
  {  return *const_cast<test_class&>(c1) < *const_cast<test_class&>(c2) ;  }

int rrr(int n)
  {
	#if defined(__GNUG__)
		return random() % n;
	#else
		return random(n);
	#endif
  }

int main(int argc, char* argv[])
  {
//	me(cout) ;

	linked_heap<test_class> H(lt, linked_heap<test_class>::SMALLER_FIRST);

	for(int i=1; i< argc; ++i)
	  {
		heap<test_class>::handle& h1 = H.push(test_class(atof(argv[i])));
		if (i % 2 == 0)
		 {
		  int k = rrr(10);
		  *const_cast<test_class&>(*h1) += k;
		  H.priority_change(h1);
		 }
	  }

	cout << endl ;
	H.print(cout);
	cout << "-----" << endl;

	while(!H.empty())
	  {
		cout << H.top() << ' ';
		H.pop();
	  }

	cout << endl;
	return 0;
  }

