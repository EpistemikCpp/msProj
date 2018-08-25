/*!***************************************************
    Mark Sattolo (mhsatto@po.cse)
   -----------------------------------------------
     File: @(#)node.hpp
     Version: 1.9
     Last Update: 03/03/14 08:41:01
   
***************************************************!*/

#ifndef MHS_ALG_NODE_H
#define MHS_ALG_NODE_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std ;

class Knapnode
{
 protected:
  
     string	_name   ;
     int	   _level  ; // in the state space tree
     int	   _profit ;
     int	   _weight ;
     float	_pwr    ; // profit to weight ratio
     float	_bound  ; // i.e. potential max profit of each node

 public:
  
     Knapnode( string s, int l=0 );
	
     Knapnode( string s, int p, int w, int l=0, float b=0.0 );

     string  name() const { return _name ; };
     void    name( string s ) { _name.assign( s ); };
     void    addname( string s ) { _name.append( s ); };

     int     level() const { return _level ; };
     void    level( int l ) { _level = l ; };

     int     profit() const { return _profit ; };
     void    profit( int p ) { _profit = p ; };

     int     weight() const { return _weight ; };
     void    weight( int w ) { _weight = w ; };

     float   pwr() const { return _pwr ; };
     void    pwr( float r ) { _pwr = r ; };

     float   bound() const { return _bound ; };
     void    bound( float b ) { _bound = b ; };

     Knapnode operator=( Knapnode k );

     void display( ostream &strm ) const ;
     
     // FUNCTIONS TO ENABLE less<Knapnode>
     friend bool operator< ( const Knapnode&, const Knapnode& );
     friend bool operator== ( const Knapnode&, const Knapnode& );

};//! class Knapnode


///// PRIORITY QUEUE FUNCTIONS ////////////////////////////////////////////////////////////

//! typedefs for priority_queue
// - see "The C++ Standard Template Library", by Plauger et al., p.455
typedef allocator<Knapnode> knapPqAl ;
typedef less<Knapnode> knapPqPred ;
typedef vector<Knapnode, knapPqAl> knapPqImpl ;
typedef priority_queue<Knapnode, knapPqImpl, knapPqPred> knapPqCont ;
//knapPqCont::container_type *p_cont = (knapPqImpl*)0 ;
knapPqCont::value_type *p_val = (Knapnode*)0 ;
knapPqCont::size_type *p_size = (size_t*)0 ;

//! function objects for ordering the priority_queues
bool operator< ( const Knapnode& k1, const Knapnode& k2 );
bool operator== ( const Knapnode& k1, const Knapnode k2 );

//$ CAN'T GET THIS ONE TO WORK !
struct order_bound
{
  bool operator()( Knapnode a, Knapnode b ) const
  {
    return( a.bound() < b.bound() );
  }
}
 bound_compare ;

//! displayPq()
void displayPq( knapPqCont pq, ostream &strm );


///// VECTOR FUNCTIONS ///////////////////////////////////////////////////////////////////

//! typedef for vector
typedef vector<Knapnode> knapVec ;

//! function object for ordering the vector
struct order_pwr
{
  bool operator()( Knapnode a, Knapnode b ) const
  {
    return( a.pwr() > b.pwr() ); // descending order
  }
}
 pwr_compare ;


//! displayVector()
void displayVector( knapVec v, ostream &strm );


#endif // MHS_ALG_NODE_H
