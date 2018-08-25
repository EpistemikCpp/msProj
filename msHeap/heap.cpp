// FILE: heap.cpp
// NAME: Mark Sattolo

#include "heap.h"

/*****************************
				    HANDLE METHODS
				    *************************************************/

// used to generate the unique ids: initialize the static variable
template<class T>
long handle<T>::last_id = 0 ;

// handle's constructor
template<class T>
handle<T>::handle( heap<T>::compare_fxn& f, order& o, 
						 const T& e ): h_compare(f), h_order(o), elem(e)
  { id = ++last_id ; }

// returns true if 'this' is higher priority than h
template<class T>
bool handle<T>::higher_priority(const handle<T>& h)
  {
	if( h_order == SMALLER_FIRST )
	  {
		if( h_compare(h.elem, elem) ) return false;
		if( h_compare(elem, h.elem) ) return true;
		return id < h.id ;
	  }
	else if( h_order == LARGER_FIRST )
	  {
		if( h_compare(elem, h.elem) ) return false;
		if( h_compare(h.elem, elem) ) return true;
		return id > h.id ;
	  }
	else
       throw heap<T>::heap_exception();
  } // handle::higher_priority()

// swap 'this' and handle
// IMPORTANT: id is a private instance variable, hence subclasses of handle
// that overload this method should explicitly invoke this method like:
//    handle::swap(h)
// and do not forget that elem is swapped here!
template<class T>
void handle<T>::swap(handle<T>& h)
  {
	long temp_i = id;
	id = h.id;
	h.id = temp_i;

	T temp_e = elem;
	elem = h.elem;
	h.elem = temp_e;
  } // handle::swap()

// returns the element associated with this handle
template<class T>
const T&  handle<T>::operator*() const
  { return elem ; }
// handle::operator*


/*******************************
				        HEAP METHODS
				        *************************************************/

// heap constructor
template<class T>
heap<T>::heap(heap<T>::compare_fxn f, order o)
  {
	compare = f ;
	ordering = o ;
	number_of_elements = 0 ;
  }

// virtual destructor because of polymorphism
template<class T>
heap<T>::~heap()
  {  }

// push() most probably does not have to be overloaded in the subclass
// IMPORTANT: increments the number of elements so create_new() shouldn't !!
template<class T>
handle<T>&  heap<T>::push(const T& ex)
  {
	handle<T>& h = create_new(ex);
	++number_of_elements;
	sift_up(h);
	return h;
  } // push()

// notify the heap that the element with handle h 
// may have had its priority changed!
template<class T>
void heap<T>::priority_change(handle<T>& h)
  {
	sift_up( index(h) );   // does nothing if priority is lower
	sift_down( index(h) ); // does nothing if priority is higher
  } // priority_change

// pop() most probably does not have to be overloaded in the subclass
// IMPORTANT: decrements the number of elements so delete_last() shouldn't !!
template<class T>
void heap<T>::pop()
  {
	if( empty() )
	  throw heap_exception();
	move_last_to_first();
	delete_last();
	--number_of_elements;
	if( !empty() )
	  sift_down(first());
  } // pop()

// return if heap is empty
template<class T>
bool heap<T>::empty() const
  { return number_of_elements == 0 ; }

// return the number of elements
template<class T>
int heap<T>::size() const
  { return number_of_elements ; }
