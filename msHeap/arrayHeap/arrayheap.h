// FILE: arrayheap.h
// NAME: Mark Sattolo

#ifndef __MHS_ARRAY_HEAP_H__
#define __MHS_ARRAY_HEAP_H__

#include "..\heap.h"
// FOR SOME REASON WILL NOT COMPILE WITH #include <iostream> !!
#include <iostream.h>
//using namespace std;  // CANNOT USE NAMESPACE WITHOUT #include <iostream>

/*****************************
					  A_NODE DECLARATION
					  *******************************/

// Subclass of handle -- it inherits the 'elem' variable
template<class T>
class a_node: public handle<T>
{
 public:
 // a variable to keep track of the array index of each a_node
 mutable int ind ;

 // constructor
 a_node<T>(const T&, handle<T>::compare_fxn&, order&, int);

 // assignment overload
 a_node<T>&  operator=(const a_node<T>& a);
};
// class a_node
	 

/*********************************
				    ARRAY_HEAP DECLARATION
				    ************************************/

// heap implemented as an array
template<class T>
class array_heap: public heap<T>
{
 private:
	 // print a node and all its sub-nodes
	 void print(ostream&, const a_node<T>*, int = 0) const ;

 protected:
	 // the variables of array_heap
	 int max_size ;
	 a_node<T>** array ;

	 // some useful methods
	 void swap(handle<T>&, handle<T>&) ;
	 int left(int) const ;
	 int right(int) const ;
	 int parent(int) const ;
	 int last() const ;

	 // pure virtual methods of parent class 'heap' are declared
	 void sift_up(handle<T>&) ;
	 void sift_down(handle<T>&) ;
	 handle<T>& create_new(const T&) ;
	 handle<T>& first() ;
	 void move_last_to_first() ;
	 void delete_last() ;
	 handle<T>& index(const handle<T>&) const ;

 public:
	 // constructor with default array size of 30
	 array_heap(compare_fxn, order, int=30) ;

	 // copy constructor
	 array_heap(const array_heap<T>&) ;

	 // assignment overload
	 array_heap<T>& operator=(const array_heap<T>&) ;

	 // destructor
	 ~array_heap() ;

	 // print
	 void print(ostream&) const ;

	 // pure virtual method of parent class 'heap' declared
	 const T& top() const ;

};
//class array_heap

#endif