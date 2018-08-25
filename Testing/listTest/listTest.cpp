// listTest.cpp
// A simple generic linked list
// see C/C++ Programmer's Reference 2nd Edition, p.97

#include <iostream>
using namespace std;

template<class data_type>
class List
{
 //default private:
    data_type myData ;
    List *next ;

 public:
    List( data_type d ) ;

   /* should be called addTo() !! 
      - adds this list to the end of the parameter list */
   void add( List *node )
     {
      node->next = this ;
      next = 0 ;
     }

   List* getnext()
     { return next ; }

   data_type getdata()
     { return myData ; }
};
// class List
  
// definition of Constructor
template<class data_t>
List<data_t>::List( data_type d )
  {
   myData = d ;
   next = 0 ;
  }

///// MAIN /////
void main()
 {
   List<char> start('Z') ;
   List<char> *p, *last ;
   int i ;

   // build a list
   last = &start ;
   // start with 'Z'
   for( i=0; i<26; i++ )
     {
      p = new List<char>('a' + i) ;
      // add each new char to end of previous list
      p->add( last ) ;
      last = p ;
     }

   // follow the list
   p = &start ;
   while( p )
     {
      cout << p->getdata() ;
      p = p->getnext() ;
     }
   cout << endl << endl ;

   // make a float list
   List<float> fstart( (float)1.01 ) ;
   List<float> *fp, *flast ;

   // build a list
   flast = &fstart ;
   // start with '0.01'
   for( int j=1; j<27; j++ )
     {
      fp = new List<float>( 1.01 + (float)j ) ;
      //add each new float to end of previous list
      fp->add( flast ) ;
      flast = fp ;
     }

   //follow the list
   fp = &fstart ;
   while( fp )
     {
      cout << fp->getdata() << " " ;
      if( ( (int)(fp->getdata())%5 ) == 0 )
        cout << endl ;
      fp = fp->getnext() ;
     }
   cout << endl << endl ;

 }
//main()