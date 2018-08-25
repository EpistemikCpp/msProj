// ControlProc.h

#ifndef __CONTROLPROC_H__
#define __CONTROLPROC_H__

#include "TestProc.h"

class ControlProc
{
 public:
   // methods to access the contained object
   void test( int ) ;
   void setTestProc( int ) ;
   int getTestProc() ;

   // access the float primitive
   float getNum() ;
   void addNum( float ) ;

 private:
   float num ;
   // contains a TestProc object
   TestProc myTestProc ;

 friend void main() ;

};
//class ControlProc

#endif