// TestProc.h

#ifndef __TESTPROC_H__
#define __TESTPROC_H__

#include <iostream> // need this to use a namespace delcaration
using namespace std;

class TestProc
{
 public:
    void setData( int i ) ;
    int getData() ;

    void initStr() ;
    char* getStr() ;
    void addStr( char* newstr ) ;

    static int testStat ;

 private:
    int data ;
    char str[99] ;

 friend class ControlProc ; // ControlProc can access private members
 friend void main() ;
};
//class TestProc

#endif