// refReturn.h

#ifndef __REFRETURN_H__
#define __REFRETURN_H__

#include <iostream>
#include <cstring>
#include "refTest.h"

using namespace std;

class ReturnTest
{
 //default private:
   int dat ;
   char strc[99] ;

 public:
    ReturnTest() ;
    Test& returnLocal() ;
    Test returnDynamic() ;
};
//class returnTest

#endif
