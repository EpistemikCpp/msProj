// refTest.h

#ifndef __REFTEST_H__
#define __REFTEST_H__

#include <iostream>
#include <cstring>
using namespace std;

class Test
{
 //default private:
   int data ;
   char str[99] ;

 public:
    Test() ;
    void setdata( int ) ;
    int getdata() ;
    char* getstr() ;
    void addstr( char* ) ;
    void show( const char* ) ;
};
//class Test

#endif