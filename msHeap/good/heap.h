// FILE: heap.h
// NAME: Mark Sattolo

#ifndef _MHS_HEAP_H_
#define _MHS_HEAP_H_

	// a heap can be built by SMALLER_FIRST or LARGER_FIRST,
	// depending what "higher priority" means -- less or more
	enum order { SMALLER_FIRST, LARGER_FIRST };

/*******************************************************
 ABSTRACT CLASS HANDLE
	*
  * must be subclassed
  * it is the internal building block of a heap
  */
  template<class T>
	class handle
		{
		 public:
		// a function matching this prototype should be
		// used to establish the ordering property of the heap
		typedef bool (*compare_fxn)(const T&, const T&);

			private:
				// ALL PRIVATE, SO SUBCLASSES SHOULD
				// NOT CONCERN THEMSELVES WITH LOW LEVEL DETAILS

				// used to generate a unique id
				static long last_id;

				// a unique id, which helps to establish
				// temporal ordering if two nodes have the same priority
				long id;

				// a reference to the actual ordering function
				// (from the FORTRAN .lt. -> less than)
				compare_fxn& h_compare;

				// a reference to the heap's ordering
				order& h_order;

			protected:
				// PROTECTED SECTION
				// SUBCLASSES MOST PROBABLY NEED THEM BUT THE PUBLIC SHOULD NOT!

				// actual element
				T elem;

				// even the constructor is 'protected'
				// only heap and its subclasses should create handles!
				handle(compare_fxn&, order&, const T&);

			public:
				// INTERFACE

				// if h is a handle, *h is the element it stores
				virtual const T& operator*() const;

				// returns true that "this" is higher priority than the argument
				virtual bool higher_priority(const handle<T>&);

				// swap "this" with the argument
				// subclasses probably have to overload this method
				// to swap other instance variables declared there
				// if that is the case, they should call this
				// swap as well, to have the internal id's swapped
				virtual void swap(handle<T>&);

		}; // class handle

/*******************************************************/

/***  HEAP class
  **
  **  OPERATIONS:
  **       
  **    -  const T& top() const; 
  **          return a reference to the top element
  ** 
  **    -  void pop();
  **          remove the top element    
  **
  **    -  handle& push(const T&);
  **          insert a new element and return its handle
  **          this handle can be used to update its position
  **          within the heap, if its priority has changed at run-time
  **
  **    - void priority_change(handle&);
  **          update the elements position in the heap because
  **          its priority has changed asynchronously
  **
  **    -  bool empty() const;
  **          returns true if and only if heap is empty
  **
  **    -  int size() const;
  **          returns the number of elements stored in the heap
  **
  ***/
template<class T>
class heap
{
 public:
	 // used to establish the ordering property of the heap
	 typedef bool (*compare_fxn)(const T&, const T&);

	 /** exception class
		  *
		  * such an exception or one of its subclasses -- if any --
		  * should be thrown when unusual circumstances arise:
		  *   -- taking the top of an empty heap
		  *   -- popping an empty heap
		  *   -- an array implementation runs out of bounds
		  *   -- ... etc
		  */
	 class heap_exception { /*cerr << "Heap exception!" << endl ;*/ } ;

 protected:
		// PROTECTED SECTION
		// SUBCLASSES PROBABLY NEED ACCESS TO THE FOLLOWING INSTANCE VARIABLES

		// the function to establish ordering
		compare_fxn compare;

		// the number of elements currently stored in the heap
		int number_of_elements;

		// the ordering property of this heap
		order ordering;


		// THE FOLLOWING METHODS FORM A 'PROTECTED' INTERFACE
		// TO THE SUBCLASSES OF STANDARD HEAP OPERATIONS
		//
		// THE PUBLIC INTERFACE IS IMPLEMENTED USING THESE PRIMITIVE HEAP OPERATIONS


		// the 'sift up' operation, start at the argument
		virtual void sift_up(handle<T>&) = 0;

		// the 'sift down' operation, start at the argument
		virtual void sift_down(handle<T>&) = 0;

		// create a new handle at the 'right' position and return its handle
		virtual handle<T>& create_new(const T&) = 0;

		// return the handle of the first or 'highest priority' element
		virtual handle<T>& first() = 0;

		// mode the last element to become the first, needed for pop
		virtual void move_last_to_first() = 0;

		// delete the last element's handle
		virtual void delete_last() = 0;

		// returns a reference to the handle where the value is actually stored
		virtual handle<T>& index(const handle<T>&) const = 0;

 public:
		// HEAP INTERFACE

		// NOTE: THE COPY CONSTRUCTOR AND THE ASSIGNMENT OPERATOR
		// ARE NOT IMPLEMENTED BECAUSE THERE ARE NO POINTER OR
		// RESOURCE TYPE INSTANCE VARIABLES.  THIS MAY NOT BE THE CASE
		// FOR SUBCLASSES OF HEAP, WHO PROBABLY HAVE TO IMPLEMENT THEM

		// constructor, ordering function and the order
		heap(compare_fxn, order);

		// so the right version of the destructor gets called in the subclasses
		virtual ~heap();

		// return a reference to the top element
		virtual const T& top() const = 0;

		// remove the highest priority element
		virtual void pop();

		// insert a new element and return its handle
		virtual handle<T>& push(const T&);

		// change the position of the element with handle because its priority has changed
		virtual void priority_change(handle<T>&);

		// true iff heap is empty
		bool empty() const;

		// number of elements in the heap
		int size() const;
};

#endif
