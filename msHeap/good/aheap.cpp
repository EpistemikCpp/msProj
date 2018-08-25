// FILE: aheap.cpp
// NAME: Mark Sattolo

#include "aheap.h"

/*************************
					  A_NODE METHODS
					  *******************************/

/* constructor: a_node's ind variable will record 
                each node's position in the array */
template<class T>
a_node<T>::a_node(const T& e,
									handle<T>::compare_fxn& f, 
									order& o, 
									int index): handle<T>(f, o, e)
  { ind = index ;  }

// assignment overload: must copy the ind variable
template<class T>
a_node<T>&  a_node<T>::operator=(const a_node<T>& a)
  {
	 ind = a.ind ;
	 return *this ;
  }


/*****************************
				    ARRAY_HEAP METHODS
				    **********************************/

// constructor: create the array and store its size
template<class T>
array_heap<T>::array_heap(compare_fxn f, order o, int c): heap<T>(f, o)
  {
	array = new a_node<T>*[c] ;
	max_size = c ;
  }

// copy constructor: create a new copy of the each array element
template<class T>
array_heap<T>::array_heap(const array_heap<T>& H): heap<T>(H)
  {
	array = new a_node<T>*[H.max_size] ;
	for ( int i = 0 ; i < H.size() ; i++ )
		 push(**H.array[i]) ;
	max_size = H.max_size ;
  }

// assignment overload: destroy the old array and copy the newly-assigned one
template<class T>
array_heap<T>& array_heap<T>::operator=(const array_heap<T>& H)
  {
	heap<T>::operator=(H) ;
	for ( int i = 0 ; i < size() ; i++ )
		 delete array[i] ;
	delete [] array ;
	array = new a_node<T>*[H.max_size] ;
	for ( int j = 0 ; j < H.size() ; j++ )
		 push(**H.array[j]) ;
	max_size = H.max_size ;
	return *this;
  }

/* destructor: have to delete the array elements 
               as they were dynamically allocated */
template<class T>
array_heap<T>::~array_heap()
  {
	for ( int i = 0 ; i < size() ; i++ )
		 delete array[i] ;
	delete [] array ;
  }

/* swap(): swap the positions of two a_nodes 
           - used in sift_up() and sift_down() */
template<class T>
void array_heap<T>::swap(handle<T>& h1, handle<T>& h2)
  {
	h1.swap(h2) ;
	a_node<T>& a1 = static_cast<a_node<T>&>(h1) ;
	a_node<T>& a2 = static_cast<a_node<T>&>(h2) ;

	a_node<T> temp = *array[a1.ind];
	*array[a1.ind] = *array[a2.ind];
	*array[a2.ind] = temp ;

	for (int i=0; i<size(); i++)
		(*array[i]).ind = i ;
  }

// left(): find the array index of the left child
template<class T>
int array_heap<T>::left(int a) const
  {
	if( empty() ) throw heap_exception();
	return (a+1)*2 - 1 ;
  }

// right(): find the array index of the right child
template<class T>
int array_heap<T>::right(int a) const
  {
	if( empty() ) throw heap_exception();
	return (a+1)*2 ;
  }

// parent(): find the array index of the parent node
template<class T>
int array_heap<T>::parent(int a) const
  {
	if( empty() ) throw heap_exception();
	return (a+1)/2 - 1 ;
  }

/* sift_up: move child node up the array 
            if it is higher priority than its parent */
template<class T>
void array_heap<T>::sift_up(handle<T>& h)
  {
	a_node<T>& a = static_cast<a_node<T>&>(h) ;
	int son = a.ind ;
	while( son != 0 )
	  {
		int dad = parent(son) ;
		if( (*array[son]).higher_priority(*array[dad]) )
		  {
			swap(*array[son], *array[dad]) ;
			son = dad ;
		  }
		else break ;
	  }
  }

/* sift_down(): continually move a node down if it is lower priority
					      than its highest priority child */
template<class T>
void array_heap<T>::sift_down(handle<T>& h)
  {
	a_node<T>& a = static_cast<a_node<T>&>(h);
//	a_node<T>& a = dynamic_cast<a_node<T>&>(h);
//	a_node<T>& a = (a_node<T>&)h ;
	int upper = a.ind ;
	while (true)
	  {
		if (left(upper) > last())
		  // no children
		  break ;
		int hpchild ;
		if (right(upper) > last())
		  // if no right then highest priority is left child
		  hpchild = left(upper) ;
		else
			// find highest priority child
			hpchild = (*array[left(upper)]).higher_priority(*array[right(upper)])
						 ? left(upper) : right(upper) ;

		// swap node and child if child is higher priority
		if ( (*array[hpchild]).higher_priority(*array[upper]) )
		  {
			swap(*array[hpchild], *array[upper]) ;
			upper = hpchild ;
		  }
		else break;
	  } // while
  }

// create_new(): used in heap::push()
template<class T>
handle<T>&  array_heap<T>::create_new(const T& e)
  {
	if (size() >= max_size)
	  throw heap_exception() ;
	array[size()] = new a_node<T>(e, compare, ordering, size()) ;
	return *array[size()] ;
  }

// first(): reference the first element
template<class T>
handle<T>&  array_heap<T>::first()
  {
	if (empty())
	  throw heap_exception() ;
	return *array[0] ;
  }

// last(): index of the current last element
template<class T>
int array_heap<T>::last() const
  {
	if (empty() || size() > max_size)
	  throw heap_exception() ;
	return (size()-1) ;
  }

// move_last_to_first(): used in heap::pop()
template<class T>
void array_heap<T>::move_last_to_first()
  { swap( *array[0], *array[last()] ) ; }

// delete_last(): ONLY used in heap::pop()
template<class T>
void array_heap<T>::delete_last()
  {
	if( empty() ) throw heap_exception() ;
	delete array[last()] ;
  }

// index(): used in heap::priority_change()
template<class T>
handle<T>&  array_heap<T>::index(const handle<T>& h) const
  {
//	handle<T>& nc_h = const_cast<handle<T>&>(h) ;
//	a_node<T>& a = static_cast<a_node<T>&>(nc_h);
//	const a_node<T>& a = dynamic_cast<const a_node<T>&>(h);
	const a_node<T>& a = static_cast<const a_node<T>&>(h);
//	const a_node<T>& a = (const a_node<T>&)h ;
//	const a_node<T>& a = DYNAMIC_DOWNCAST(const a_node<T>&, h) ;
	return *array[a.ind] ;
  }

// top(): get the value at the top of the array
template<class T>
const T& array_heap<T>::top() const
  {
	if( empty() ) throw heap_exception();
	return **array[0];
  }

// print(): recursively print a node and all its sub-nodes
template<class T>
void array_heap<T>::print(ostream& os, const a_node<T>* n, int k) const
  {
	for (int i=0; i < k; ++i)
		 os << "   " ;

	os << **n << "   ( this=" << (void*)n << ", l=" << array[left((*n).ind)]
		<< ", r=" << array[right((*n).ind)] << ", p=" << array[parent((*n).ind)] << ")" <<  endl ;

	if ( left((*n).ind) <= last() )
	  print(os, array[left((*n).ind)], k+1) ;
	else
	  {
		for (int i=0; i < k+1; ++i)
			 os << "   " ;
		os << "."  << endl ;
	  }

	if (right((*n).ind) <= last())
	  print(os, array[right((*n).ind)], k+1) ;
	else
	  {
		for (int i=0; i < k+1; ++i)
			 os << "   " ;
		os << "." << endl ;
	  }
  }

// print(): print the first and last node addresses then print the array
template<class T>
void array_heap<T>::print(ostream& os) const
  {
	 os << "First = " << array[0] << "   Last = " << array[last()] << endl ;
	 print(os, array[0]) ;
  }
